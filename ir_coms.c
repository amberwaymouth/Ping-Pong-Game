/** @file   ir_coms.c
    @author A. Waymouth, E. Sanders (Team 526)
    @date   16 October 2022
    @brief  This module implements the ir communication for the pong game.
*/

#include "system.h"
#include "ir_uart.h"
#include "ball.h"
#include "ir_coms.h"
void send_won(void)
{
    ir_uart_putc(WIN); 
}

uint8_t receive_win (void)
{
    uint8_t c; 
    if (ir_uart_read_ready_p()) {
        c = ir_uart_getc();
        return c;
    }
    return 0; 
}

dir_t receive_direction (uint8_t send_code) 
{
    dir_t dir;
    switch (send_code) 
    {
        case SOUTH:
            dir = DIR_S;
            break;
        case SOUTH_WEST:
            dir = DIR_SW;
            break;
        case SOUTH_EAST:
            dir = DIR_SE;
            break; 
        default:
            dir = NOT_MOVING;
            break;
    }
    return dir; 
}

uint8_t get_direction (dir_t direction)
{
    uint8_t to_send = 0;
    switch (direction) {

        case DIR_N:
            to_send = SOUTH;
            break;
        
        case DIR_NW:
            to_send = SOUTH_WEST;
            break;

        case DIR_NE:
            to_send = SOUTH_EAST;
            break; 
        default:
            break;
    }
    return to_send; 
}

void ball_send(ball_t ball)
{
    ir_uart_putc(ball.pos.y);
    ir_uart_putc(get_direction(ball.dir));
}

transmit_t ball_receive (void)
{
    transmit_t transmission = {0, 0};
    if (ir_uart_read_ready_p()) {
        transmission.ypos = ir_uart_getc();
        transmission.direction = ir_uart_getc(); 
    }
    return transmission; 
}
