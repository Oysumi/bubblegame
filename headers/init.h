#ifndef __INIT_H__
#define __INIT_H__
#include "const.h"
#include "struct.h"

void screenInit ( init_t * window ) ;

void frameImageInit ( init_t * window ) ;

void text_init ( text_t * text ) ;

void launcherImageInit ( init_t * window ) ;

void bubImageInit ( game_t * game ) ;

void bubImageExplosionInit ( game_t * game ) ;

void gameInit ( game_t * game, ceiling_t * ceil ) ;

void ceilingInit ( ceiling_t * ceil ) ;

void ceilingstateInit ( ceiling_t * ceil ) ; 

void loadingSprite ( game_t * game, init_t * window ) ;

void freeScreen ( init_t * window ) ;

void setTransparency ( game_t * game, init_t * window, ceiling_t * ceil )  ;

void updateScreen ( bubble_t * bub, SDL_Rect * launcher , init_t * window, game_t * game, timecheck_t * timer, ceiling_t * ceil ) ;

void update_timer ( timecontrol_t * timer ) ;

void init_timer ( timecontrol_t * timer ) ;

void get_timer ( timecontrol_t * timer ) ;

unsigned int rand_color ( void ) ;

void bubcomponent_init ( game_t * game ) ;

void bubfile_init ( game_t * game ) ;

void freecomponent_array ( game_t * game ) ;

bool we_have_a_winner ( game_t * game ) ;

int sky_is_falling ( timecheck_t * timer, ceiling_t * ceil, game_t * game, bubble_t * bub ) ;

int game_over ( bubble_t * bub, ceiling_t * ceil, game_t * game, timecheck_t * timer ) ;

int you_win ( bubble_t * bub, ceiling_t * ceil, game_t * game, timecheck_t * timer ) ;

bool limite_fps_expl ( timecontrol_t * time ) ;

bool limite_fps_fall ( timecontrol_t * time ) ;

void init_time_variable ( timecheck_t * timer ) ;

bool check_pause ( input_t * in, timecheck_t * timer ) ;

void print_pause ( text_t * text, input_t * in, bubble_t * bub, init_t * window, timecheck_t * timer ) ;

void HandleEvent ( input_t * inkey, bubble_t * bub ) ;

bool escape ( input_t * inkey ) ;

#endif
