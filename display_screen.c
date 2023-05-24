/** @file   ball.h
    @author A. Waymouth, E. Sanders (Team 526)
    @date   16 October 2022
    @brief  This module implements all the text used within the game of pong
*/

#include "system.h"
#include "../fonts/font3x5_1.h"
#include "tinygl.h"

#define PACER_RATE 500
#define MESSAGE_RATE 20

void tinygl_setup(void)
{
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
}

void tinygl_initial_text(void)
{
    tinygl_text("PUSH TO START");
}

void tinygl_endgame_text(void)
{
    tinygl_text("END GAME");
}

void tinygl_player_win(void)
{
    tinygl_text("YOU WIN!");
}

void tinygl_player_lose(void)
{
    tinygl_text("YOU LOSE!");
}
