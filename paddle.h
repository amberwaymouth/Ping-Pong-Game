/** @file   paddle.h
    @author A. Waymouth, E. Sanders (Team 526)
    @date   13 October 2022
    @brief  This module implements a paddle for the ping-pong game.
*/

#ifndef PADDLE_H
#define PADDLE_H 

#include "system.h"
#include "tinygl.h"
#include "navswitch.h"

/** Defining paddle constants */ 
#define PADDLE_START_COLUMN 2
#define PADDLE_START_ROW 4
#define PADDLE_END_COLUMN 4
#define PADDLE_END_ROW 4
#define PADDLE_WIDTH 3 
#define UP 0
#define DOWN 4
#define PADDLE_SHOW 1
#define PADDLE_HIDE 0
#define RIGHT_COLUMN 6
#define LEFT_COLUMN 0

/** Struct for a paddle which contains the start and the end points for the paddle line*/
typedef struct {
    tinygl_point_t start;
    tinygl_point_t end;
} paddle_t;

paddle_t paddle;

/**
 * @brief Displays the current position of the paddle
 * 
 */
void display_paddle(void);

/**
 * @brief Initialise the paddle to its starting position, which is in the middle of the board in the bottom column
 * 
 */
void paddle_init(void);

/**
 * @brief Turns the currently displayed paddle off
 * 
 */
void paddle_off(void);

/**
 * @brief Allows the paddle to be moved by the player by updating the paddle position when the navswitch is pushed north, south, east and west
 * 
 */
void paddle_update(void);

#endif
