/** @file   ball.h
    @author A. Waymouth, E. Sanders (Team 526)
    @date   16 October 2022
    @brief  This module is the header file for display_screen.h
*/

#ifndef DISPLAY_SCREEN_H
#define DISPLAY_SCREEN_H

#include "system.h"
#include "../fonts/font3x5_1.h"
#include "tinygl.h"

//initializes the tinygl giving it message speed and Hz
void tinygl_setup(void);

//the initial text for the game
void tinygl_initial_text(void);

//The text when the game ends
void tinygl_endgame_text(void);

//The text after the end game screen if a player wins
void tinygl_player_win(void);

//The text after the end game screen if player a player loses
void tinygl_player_lose(void);

#endif // DISPLAY_SCREEN_H
