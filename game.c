/**
 * @file game.c
 * @author Ellen Sanders & Amber Waymouth
 * @brief A simple game of pong (read the README to learn how to play & compile)
 * @version 4
 * @date 2022-10-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "system.h"
#include "paddle.h"
#include "navswitch.h"
#include "ledmat.h"
#include "display.h"
#include "pio.h"
#include "tinygl.h"
#include "pacer.h"
#include "ball.h"
#include "ir_uart.h"
#include <stdint.h>
#include "ir_coms.h"
#include "display_screen.h"



/**
 * @brief Define polling rate in Hz.  
 * 
 */
#define LOOP_RATE 500
#define MESSAGE_RATE 10
#define TRUE 1
#define FALSE 0
#define START_ROW 0
#define START_COLUMN 2
#define UNDECIDED 0
#define LOSS 1
#define WIN 2 
#define LEFT_COLUMN 0
#define BOTTOM_ROW 4
#define RIGHT_COLUMN 6

static uint8_t xpos = START_ROW; 
static uint8_t ypos = START_COLUMN; 
static dir_t dir = DIR_S; 

typedef enum {
    INITIAL_STARTUP,
    PLAYING,
    WAITING,
    GAME_OVER,
} state_t;

static state_t state = INITIAL_STARTUP;

static int8_t result = UNDECIDED;

void game_init(void) 
{
    paddle_init();
    navswitch_init();
}

/**
 * @brief displays when a player has won the game resets when navswitched pushed.
 * 
 */
void show_won(void) {
    tinygl_draw_line(paddle.start, paddle.end, PADDLE_HIDE);
    tinygl_update();  
    tinygl_player_win();
    tinygl_update(); 
    while (!navswitch_push_event_p(NAVSWITCH_PUSH)) {
        navswitch_update(); 
        pacer_wait();
        tinygl_update(); 
    }
}

/**
 * @brief displays when a player has lost the game resets when navswitched pushed.
 * 
 */
void show_lose(void)
{
    tinygl_draw_line(paddle.start, paddle.end, PADDLE_HIDE);
    tinygl_update();  
    tinygl_player_lose();
    tinygl_update(); 
    while (!navswitch_push_event_p(NAVSWITCH_PUSH)) {
        navswitch_update(); 
        pacer_wait();
        tinygl_update(); 
    }
}

/**
 * @brief Checks if the ball has reached the edges of the LED matrix, and if so reverses its direction. 
 * 
 * @param ball current ball object 
 * @return ball_t 
 */
ball_t check_sides(ball_t ball) {
    if (ball.pos.y < LEFT_COLUMN || ball.pos.y > RIGHT_COLUMN) {
        ball = ball_reverse(ball);
    }
    return ball; 
}

/**
 * @brief Checks if the ball has hit the paddle, and changes the direciton depending on where on the paddle it has hit. 
 * 
 * @param ball current ball object 
 * @return ball_t 
 */
ball_t paddle_tasks(ball_t ball)
{
    if (ball.pos.y >= paddle.start.y && ball.pos.y <= paddle.end.y && ball.pos.x == ROW_BEFORE_PADDLE) {
        if (ball.pos.y == paddle.start.y) {
                    ball = ball_switch(DIR_NW, ball);  
                } else if (ball.pos.y == paddle.end.y) {
                    ball = ball_switch(DIR_NE, ball);
                } else if (ball.pos.y == (paddle.end.y + paddle.start.y) / 2) {
                    ball = ball_switch(DIR_N, ball); 
                } 
    }
    return ball; 
}

/**
 * @brief runs all the states for the game
 * 
 * @param player_num if player one then they start with PLAYING after INITIAL_STARTUP else goes to WAITING
 */
void game_state(int8_t* player_num)
{
    navswitch_update();
    switch(state)
    {
    //Selects what player is player 1 and player 2 so that they can go to the correct states
    case INITIAL_STARTUP:
        while (state == INITIAL_STARTUP) {
            pacer_wait();
            navswitch_update ();
            tinygl_update();
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                ir_uart_putc ('1');
                *player_num = 1;
                tinygl_clear();
                state = PLAYING;  
            } else if (ir_uart_read_ready_p ()) {
                int8_t player_name = ir_uart_getc();
                if (player_name == '1') {
                    *player_num = 2;
                    tinygl_clear();
                    state = WAITING;
                }
            }
    }
    break;

    /**
     * @brief This case will be entered when a player has the ball on their screeen so that they can move the paddle. Also when this player loses it will send this player to the losing screen, but send a signal to the other player that they won.
     * 
     */
    case PLAYING: 
        tinygl_clear();
        paddle_init();
        ball_t ball = ball_init(xpos, ypos, dir); //initialises ball position (set to south to test)
        uint16_t ball_tick = 0;
        while(state == PLAYING) {
            paddle_update(); 
            navswitch_update ();
            tinygl_draw_point (ball.pos, 1);
            tinygl_update();
            ball_tick++;
            if (ball_tick > 1000)
                {   
                paddle_update(); 
                ball = paddle_tasks(ball); 
                ball_tick = 0;
                ball = ball_move(ball);
                //sends the ball once the position of the ball is at the edge of the screen
                if (check_position(ball)) {
                    send_position(ball);
                    state = WAITING; 
                }

                //when the bostion of the ball goes past the paddle then it will send to the other player that they have won, changes state to GAME_OVER
                if (ball.pos.x > BOTTOM_ROW) {
                    send_won(); 
                    result = LOSS; 
                    state = GAME_OVER; 
                } 

                //receves the win state; changes state to GAME_OVER
                if (receive_win()) {
                    tinygl_update(); 
                    result = WIN;
                    state = GAME_OVER; 
                }
                ball = check_sides(ball);
            } 
                tinygl_update();
        }
        break;

    //this case is for when the ball isnt on the screen, keeps the paddle on the screen once receives ir_transmition then the state changes to PLAYING
    case WAITING:
        tinygl_clear(); 
        paddle_init();
        while (state == WAITING) {
            navswitch_update();
            paddle_update();
            tinygl_update();
            if (ir_uart_read_ready_p()) {
                ypos = ir_uart_getc();
                dir = receive_direction(ir_uart_getc()); 
                xpos = LEFT_COLUMN;
                tinygl_clear();
                paddle_off();
                state = PLAYING; 
            }
        }
        break;

    //this state is the end screen and when the button is pushed the game will restart so state changes to INITIAL_STARTUP
    case GAME_OVER:
        display_clear();
        tinygl_clear(); 
        navswitch_update(); 
        while (!navswitch_push_event_p(NAVSWITCH_PUSH)) {
        if (result == LOSS) {
            show_lose(); 
            display_clear();
        } else if (result == WIN) {
            show_won(); 
            display_clear(); 
            }
        } 
        result = 0;
        tinygl_initial_text();
        xpos = START_ROW;
        ypos = START_COLUMN;
        dir = DIR_S; 
        tinygl_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            state = INITIAL_STARTUP;
        }
        break;
    }
}

/**
 * @brief controls the starting for the game; initialises all setups and will run the states for the game
 * 
 * @return int 
 */
int main (void)
{
    navswitch_init(); 
    system_init();
    ir_uart_init();
    tinygl_setup();
    tinygl_initial_text();
    navswitch_init ();
    pacer_init (LOOP_RATE);
    int8_t player_num = 0;
    while (TRUE) {
        //starts the state
        game_state(&player_num);
    }
    return 0;
}
