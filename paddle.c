/** @file   paddle.c
    @author A. Waymouth, E. Sanders (Team 526)
    @date   13 October 2022
    @brief  Source code for the paddle module 
*/

#include "system.h"
#include "ledmat.h"
#include "paddle.h"
#include "display.h"
#include "pio.h"
#include "tinygl.h"

void display_paddle (void) 
{
    tinygl_draw_line(paddle.end, paddle.start, PADDLE_SHOW); 
}

void paddle_init(void) 
{
    tinygl_point_t start = tinygl_point(PADDLE_START_ROW, PADDLE_START_COLUMN);
    tinygl_point_t end = tinygl_point(PADDLE_END_ROW, PADDLE_END_COLUMN); 
    paddle.start = start;
    paddle.end = end; 
    display_paddle(); 
}

void paddle_off(void) 
{
    tinygl_draw_line(paddle.end, paddle.start, PADDLE_HIDE);
}

void paddle_update(void) 
{
    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && paddle.end.y < RIGHT_COLUMN) {
        paddle_off();
        paddle.start.y += 1; 
        paddle.end.y += 1;
        display_paddle();
    }
    if (navswitch_push_event_p(NAVSWITCH_NORTH) && paddle.start.y > LEFT_COLUMN) {
        paddle_off();
        paddle.start.y --;
        paddle.end.y --;
        display_paddle(); 
    }
}
