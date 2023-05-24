/** @file   ball.c
    @author A. Waymouth, E. Sanders (Team 526)
    @date   16 October 2022
    @brief  Source code for the ball module 
*/

#include "system.h"
#include "ledmat.h"
#include "paddle.h"
#include "display.h"
#include "pio.h"
#include "tinygl.h"
#include "pacer.h"
#include "ball.h"
#include "paddle.h"
#include "ir_coms.h"

ball_t ball_init(uint8_t x, uint8_t y, dir_t direction)
{
    ball_t ball;
    ball.dir = direction;
    ball.pos.y = y;
    ball.pos.x = x; 
    return ball; 
}

ball_t ball_move (ball_t ball)
{
    tinygl_draw_point(ball.pos, HIDE_BALL);
    switch (ball.dir)
    {
        case NOT_MOVING:
            break;
        case DIR_N:
            ball.pos.x = ball.pos.x - 1;
            break;

        case DIR_S:
            ball.pos.x = ball.pos.x + 1;
            break;
        
        case DIR_NW:
            ball.pos.y = ball.pos.y - 1;
            ball.pos.x = ball.pos.x - 1; 
            break;
        
        case DIR_NE:
            ball.pos.y = ball.pos.y + 1;
            ball.pos.x = ball.pos.x - 1; 
            break;
        
        case DIR_SE:
            ball.pos.y = ball.pos.y - 1;
            ball.pos.x = ball.pos.x + 1;
            break; 
        
        case DIR_SW:
            ball.pos.y = ball.pos.y + 1;
            ball.pos.x = ball.pos.x + 1; 
            break;
    }
    tinygl_draw_point (ball.pos, SHOW_BALL);
    return ball;
}

bool check_paddle(ball_t ball) 
{
    if (ball.pos.y >= paddle.start.y && ball.pos.y <= paddle.end.y && ball.pos.x == ROW_BEFORE_PADDLE) {
        return 1; 
    }
    return 0; 
}

uint8_t check_position(ball_t ball)
{
    if (ball.pos.x == TOP_ROW && (ball.dir == DIR_N || ball.dir == DIR_NW || ball.dir == DIR_NE)) {
        return 1; 
    }
    return 0; 
}

ball_t ball_reverse(ball_t ball) 
{
    switch (ball.dir)
    {
        case NOT_MOVING:
            break;
        case DIR_N:
            ball.dir = DIR_S;
            break;

        case DIR_S:
            ball.dir = DIR_N;
            break;

        case DIR_NW:
            ball.dir = DIR_NE; 
            break;
        
        case DIR_NE:
            ball.dir = DIR_NW;
            break;
        
        case DIR_SE:
            ball.dir = DIR_SW; 
            break; 
        
        case DIR_SW:
            ball.dir = DIR_SE; 
            break;
    }
    return ball; 
}

ball_t ball_switch(dir_t direction, ball_t ball) 
{
    ball.dir = direction;
    return ball;
}

void kill_ball(ball_t ball)
{
    tinygl_draw_point(ball.pos, HIDE_BALL); 
}

void send_position(ball_t ball)
{
    ball_send(ball); 
    tinygl_draw_point(ball.pos, HIDE_BALL); 
}
