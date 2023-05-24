/** @file   ball.h
    @author A. Waymouth, E. Sanders (Team 526)
    @date   16 October 2022
    @brief  This module implements a ball for the ping-pong game.
*/

#ifndef BALL_H
#define BALL_H

#include "tinygl.h"
#include "system.h"


#define LEFT_COLUMN 0
#define RIGHT_COLUMN 6
#define TOP_ROW 0
#define BOTTOM_ROW 4
#define BALL_SPEED 2
#define SHOW_BALL 1
#define HIDE_BALL 0
#define ROW_BEFORE_PADDLE 3

//enum for all the directions that the ball can travel
enum dir {
    NOT_MOVING,
    DIR_N, 
    DIR_NW, 
    DIR_NE, 
    DIR_S, 
    DIR_SE, 
    DIR_SW};

typedef enum dir dir_t;

struct ball 
{
    /* Current position of ball.  */
    tinygl_point_t pos;
    /* Current direction.  */
    enum dir dir;
};

typedef struct ball ball_t;


/**
 * @brief Initialise the ball
 * 
 * @param x are the collumns of the matrix 
 * @param y are the rows of the matrix 
 * @param direction is the direction that the ball starts in
 * @return ball_t 
 */
ball_t ball_init(uint8_t x, uint8_t y, dir_t direction);

/**
 * @brief Moves the ball in the given direction
 * 
 * @param ball takes the ball that is currently moving around the screen
 * @return ball_t 
 */
ball_t ball_move (ball_t ball);

/**
 * @brief Check the position of the paddle in relation to the ball
 * 
 * @param ball takes te current ball moving towards the paddle
 * @return true 
 * @return false 
 */
bool check_paddle(ball_t ball);

/**
 * @brief reverses the ball to the opposite direction
 * 
 * @param ball takes the ball that hit the paddle
 * @return ball_t 
 */
ball_t ball_reverse(ball_t ball);

/**
 * @brief Switch the direction of the ball to a given direction
 * 
 * @param direction the direction the ball is currently moving
 * @param ball the ball currently moving
 * @return ball_t 
 */
ball_t ball_switch(dir_t direction, ball_t ball);

/**
 * @brief Removes the ball from the display
 * 
 * @param ball the ball that we want to remove
 */
void kill_ball(ball_t ball); 

/**
 * @brief Checks the position of the ball to decide whether to send it to the other board or not
 * 
 * @param ball current all on display
 * @return uint8_t 
 */
uint8_t check_position(ball_t ball);

/**
 * @brief Sends the position of the ball
 * 
 * @param ball the new ball that has just been transmitted
 */
void send_position(ball_t ball);




#endif
