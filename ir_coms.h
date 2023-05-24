/** @file   ir_coms.h
    @author A. Waymouth, E. Sanders (Team 526)
    @date   16 October 2022
    @brief  This is the header file for the ir communication for the pong game.
*/

#ifndef IR_COMS_H
#define IR_COMS_H

#include "system.h"
#include "ir_uart.h"
#include "ball.h"

/** Defining direction codes to be sent */
#define SOUTH 2
#define SOUTH_WEST 3
#define SOUTH_EAST 4
#define WIN 1
#define LOSE 0 

/**
 * @brief Structure containing the position and direction of the ball to be sent
 * 
 */
typedef struct {
    uint8_t ypos;
    uint8_t direction; 
} transmit_t; 

/**
 * @brief Send a win code so that the other board knows the game is over
 * 
 */
void send_won(void);

/**
 * @brief Receive a win code so that this board knows that te game is over
 * 
 * @return uint8_t 
 */
uint8_t receive_win(void); 

/**
 * @brief Receive the direction of the ball
 * 
 * @param send_code takes the direction sent by ir transmition and gives the ball a direction
 * @return dir_t 
 */
dir_t receive_direction (uint8_t send_code);

/**
 * @brief Get the direction of the ball
 * 
 * @param direction takes the current direction to revert it
 */
uint8_t get_direction (dir_t direction);

/**
 * @brief Sends the location and direction of the ball to the other player via ir transmition
 * 
 * @param ball the current ball to get position and direction from
 */
void ball_send(ball_t ball);

/**
 * @brief Receive the location and direction from the other board via ir transmition
 * 
 * @return transmit_t 
 */
transmit_t ball_receive (void); 

#endif