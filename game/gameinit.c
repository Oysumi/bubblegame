#ifndef __GAMEINIT_C__
#define __GAMEINIT_C__

#include "../headers/init.h"
#include "../headers/struct.h"
#include "../headers/bubble.h"
#include "../headers/const.h"
#include "bubinit.c"

void screenInit ( init_t * window )
{

	SDL_Init ( SDL_INIT_VIDEO ) ;

	/* Set the title bar */
	SDL_WM_SetCaption ( "Puzzle Bobble Game", "Puzzle Bobble Game" ) ;

	/* Create windows */
	window->screen = SDL_SetVideoMode ( SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0 ) ;

}

void text_init ( text_t * text )
{
	/* Loading of the font */
	text->font = TTF_OpenFont ("../font/04B_30__.TTF", 35) ;

	/* Defining the color of the text (orange / golden) */
	SDL_Color font_color = {237, 127, 16} ;

	/* Loading of the first level */
	text->level = 1 ;

	/* Writting the texts in the SDL_Surface */
	text->score = TTF_RenderText_Blended ( text->font, "SCORE", font_color ) ;
	text->game_over = TTF_RenderText_Blended ( text->font, "GAME OVER", font_color ) ;
	text->you_won = TTF_RenderText_Blended ( text->font, "YOU WON !", font_color ) ;
	text->pause = TTF_RenderText_Blended ( text->font, "[ PAUSE ]", font_color ) ;
	text->round = TTF_RenderText_Blended ( text->font, "ROUND 1", font_color ) ;

	/* Defining the position of the texts */
	text->score_pos = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;
	text->score_pos->x = SCORE_POS ;
	text->score_pos->y = BUB_SIZE ;

	text->game_over_pos = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;
	text->game_over_pos->x = GAME_OVER_POS ;
	text->game_over_pos->y = SCREEN_HEIGHT / 2 - BUB_SIZE ;

	text->you_won_pos = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;
	text->you_won_pos->x = YOU_WON_POS ;
	text->you_won_pos->y = SCREEN_HEIGHT / 2 - BUB_SIZE ;

	text->pause_pos = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;
	text->pause_pos->x = PAUSE_POS ;
	text->pause_pos->y = SCREEN_HEIGHT / 2 - BUB_SIZE ;

	text->round_pos = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;
	text->round_pos->x = ROUND_POS ;
	text->round_pos->y = SCREEN_HEIGHT / 2 - BUB_SIZE ;
}

void frameImageInit ( init_t * window )
{
	SDL_Surface * temp ;

	/* Loading the frame */
	temp = SDL_LoadBMP ( "../img/gamebackground/frame_1p.bmp" ) ;
	window->frame = SDL_DisplayFormat ( temp ) ;

	SDL_FreeSurface ( temp ) ;
}

void launcherImageInit ( init_t * window )
{
	SDL_Surface * temp ;

	/* Loading the images for the launcher */
	temp = SDL_LoadBMP ( "../img/launcher/frame_launcher.bmp") ;
	window->launcher = SDL_DisplayFormat ( temp ) ;

	SDL_FreeSurface ( temp ) ;
}

void bubImageInit ( game_t * game )
{

	SDL_Surface * temp ;

	/* Loading the images for the bubble */
	temp = SDL_LoadBMP ( "../img/bubs/bub_black.bmp" ) ;
	game->bub_colors[0] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/bubs/bub_blue.bmp" ) ;
	game->bub_colors[1] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/bubs/bub_green.bmp" ) ;
	game->bub_colors[2] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/bubs/bub_orange.bmp" ) ;
	game->bub_colors[3] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/bubs/bub_purple.bmp" ) ;
	game->bub_colors[4] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/bubs/bub_red.bmp" ) ;
	game->bub_colors[5] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/bubs/bub_white.bmp" ) ;
	game->bub_colors[6] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/bubs/bub_yellow.bmp" ) ;
	game->bub_colors[7] = SDL_DisplayFormat ( temp ) ;
	
	SDL_FreeSurface ( temp ) ;
	
	game->currentOrientation = 22 ;
}

void bubImageExplosionInit ( game_t * game )
{

	SDL_Surface * temp ;

	/* Loading the images for the explosions */
	temp = SDL_LoadBMP ( "../img/explode/bubex_black.bmp" ) ;
	game->bub_explosion[0] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/explode/bubex_blue.bmp" ) ;
	game->bub_explosion[1] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/explode/bubex_green.bmp" ) ;
	game->bub_explosion[2] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/explode/bubex_orange.bmp" ) ;
	game->bub_explosion[3] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/explode/bubex_purple.bmp" ) ;
	game->bub_explosion[4] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/explode/bubex_red.bmp" ) ;
	game->bub_explosion[5] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/explode/bubex_white.bmp" ) ;
	game->bub_explosion[6] = SDL_DisplayFormat ( temp ) ;

	temp = SDL_LoadBMP ( "../img/explode/bubex_yellow.bmp" ) ;
	game->bub_explosion[7] = SDL_DisplayFormat ( temp ) ;
	
	SDL_FreeSurface ( temp ) ;

}

void gameInit ( game_t * game, ceiling_t * ceil )
{

	/* Initialize bub array which informs about the positions and the colors of bubbles displayed on the game board */
	game->bub_array = ( int * * ) malloc ( BUB_NY * sizeof ( int * ) ) ;

	/* We have to make sure that there are no bubbles on the screen at first */
	bubarray_init ( game ) ;

	/* We fill the cells of the array with the different possible coordinates of the bubbles */
	game->bub_center = ( int * * * ) malloc ( BUB_NY * sizeof ( int * * ) ) ;
	bubarray_initcenters ( game, ceil ) ;

	/* We first fill the cells of this array with zeros */
	game->bub_connected_component = ( int * * ) malloc ( BUB_NY * sizeof ( int * ) ) ;
	bubcomponent_init ( game ) ;

	/* We have to init the file */
	game->bub_fifo = ( int * * ) malloc ( BUB_NY * BUB_NX * sizeof ( int * ) ) ;
	bubfile_init ( game ) ;
	
	/* Initialize bub array which informs about the state of the bubble. If we have a one on a cell, then it means that a bubble has to fall */
	game->bub_falling = ( explode_t * ) malloc ( BUB_NY * BUB_NX * sizeof ( explode_t ) ) ;
	bubfalling_init ( game ) ;
	game->counter = 0 ;

}

void bubfalling_init ( game_t * game )
{
	unsigned int i ;
	game->fall_head = 0 ;  
	game->nb_bubexplosions = 0 ;
	game->nb_bubout = 0 ;

	for ( i = 0 ; i < BUB_NX * BUB_NY ; i++ )
	{
		game->bub_falling[i].image = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;
		game->bub_falling[i].position = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;
	}
}

void bubfalling_free_rect ( game_t * game )
{
	unsigned int i ;

	for ( i = 0 ; i < BUB_NX * BUB_NY ; i++ )
	{
		free( game->bub_falling[i].image ) ;
		free( game->bub_falling[i].position ) ;
	}
}

void ceilingInit ( ceiling_t * ceil )
{

	SDL_Surface * temp ;

	ceil->ceiling = ( ceiling_control_t * ) malloc ( sizeof ( ceiling_control_t ) ) ;
	ceil->first_chain = ( ceiling_control_t * ) malloc ( sizeof ( ceiling_control_t ) ) ;
	ceil->second_chain = ( ceiling_control_t * ) malloc ( sizeof ( ceiling_control_t ) ) ;

	/* Loading the image of the ceiling */
	temp = SDL_LoadBMP ( "../img/top/frame_top.bmp" ) ;
	ceil->ceiling->image_ceiling = SDL_DisplayFormat ( temp ) ;

	/* Loading the image of the chain */
	temp = SDL_LoadBMP ( "../img/top/frame_chain.bmp") ;
	ceil->first_chain->image_chain = SDL_DisplayFormat ( temp ) ;
	ceil->second_chain->image_chain = SDL_DisplayFormat ( temp ) ;

	SDL_FreeSurface ( temp ) ;

	ceil->ceiling->ceil_pos = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;
	ceil->first_chain->chain_pos = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;
	ceil->first_chain->chain_sprite = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;
	ceil->second_chain->chain_pos = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;
	ceil->second_chain->chain_sprite = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;

	ceil->ceiling->ceil_pos->x = BOARD_LEFT ;
	ceil->ceiling->ceil_pos->y = BOARD_TOP ;

	ceil->first_chain->chain_sprite->x = 0 ;
	ceil->first_chain->chain_sprite->y = 0 ;
	ceil->first_chain->chain_sprite->w = CHAIN_WIDTH ;

	ceil->second_chain->chain_sprite->x = 0 ;
	ceil->second_chain->chain_sprite->y = 0 ;
	ceil->second_chain->chain_sprite->w = CHAIN_WIDTH ;

	ceil->first_chain->chain_pos->y = BOARD_TOP ;
	ceil->first_chain->chain_pos->x = BOARD_LEFT + 1.5 * BUB_SIZE ;

	ceil->second_chain->chain_pos->y = BOARD_TOP ;
	ceil->second_chain->chain_pos->x = BOARD_RIGHT - 2 * BUB_SIZE ;

	ceilingstateInit ( ceil ) ;

}

void ceilingstateInit ( ceiling_t * ceil )
{
	ceil->state = 0 ;
}

void freeScreen ( init_t * window )
{
	free ( window ) ;
}

void setTransparency ( game_t * game, init_t * window, ceiling_t * ceil ) 
{
	int colorkey ;
	unsigned int i ;

	colorkey = SDL_MapRGB ( window->screen->format, 255, 0, 255 ) ;

	/* Set frame transparency */
	SDL_SetColorKey ( window->frame, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey ) ;

	/* Set launcher transparency */
	SDL_SetColorKey ( window->launcher, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey ) ;

	/* Set bubbles transparency */
	for ( i = 0 ; i < NUM_COLORS ; i++ )
	{
		SDL_SetColorKey ( game->bub_colors[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey ) ;
		SDL_SetColorKey ( game->bub_explosion[i], SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey ) ;

	}

	SDL_SetColorKey ( ceil->ceiling->image_ceiling, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey ) ;
	SDL_SetColorKey ( ceil->first_chain->image_chain, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey ) ;
	SDL_SetColorKey ( ceil->second_chain->image_chain, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey ) ;
}

void updateScreen ( bubble_t * bub, SDL_Rect * launcher , init_t * window, game_t * game, timecheck_t * timer, ceiling_t * ceil )
{
	unsigned int i, j ;
	unsigned int j_max ;
	int color ; /* Will be the color of the cache (black) */
	SDL_Rect * temp ;
	
	temp = ( SDL_Rect * ) malloc ( sizeof ( SDL_Rect ) ) ;

	/* First, we draw a black cache */
	SDL_Rect cache ;
	cache.x = 0 ;
	cache.y = 0 ;
	cache.w = SCREEN_WIDTH ;
	cache.h = SCREEN_HEIGHT ;

	color = SDL_MapRGB ( window->screen->format, 0, 0, 0 ) ;

	SDL_FillRect ( window->screen, &cache, color ) ;

	/* Then, we draw the game board */
	SDL_Rect framePos ;
	framePos.x = 0 ;
	framePos.y = 0 ;

	SDL_BlitSurface ( window->frame, NULL, window->screen, &framePos ) ;

	/* We can draw the top falling */

	ceil->ceiling->ceil_pos->y = TOP_START + ceil->state * 35 ;
	ceil->first_chain->chain_sprite->h = TOP_START + ceil->state * 35 - 25 ;
	ceil->second_chain->chain_sprite->h = TOP_START + ceil->state * 35 - 25 ;

	if ( ceil->state > 0 )
	{
		SDL_BlitSurface ( ceil->first_chain->image_chain, ceil->first_chain->chain_sprite, window->screen, ceil->first_chain->chain_pos ) ;
		SDL_BlitSurface ( ceil->second_chain->image_chain, ceil->second_chain->chain_sprite, window->screen, ceil->second_chain->chain_pos ) ;
		SDL_BlitSurface ( ceil->ceiling->image_ceiling, NULL, window->screen, ceil->ceiling->ceil_pos ) ;
	}


	/* Then, we draw the launcher */
	SDL_Rect launcherImg ;
	launcherImg.w = LAUNCHER_WIDTH ;
	launcherImg.h = LAUNCHER_HEIGHT ;
	launcherImg.x = 0 ;
	launcherImg.y = LAUNCHER_HEIGHT * game->currentOrientation ;

	SDL_BlitSurface ( window->launcher, &launcherImg, window->screen, launcher ) ;
	
	/* Finally, we draw the bubs */
	SDL_Rect bubRect ;
	
	bubRect.x = 0 ;
	bubRect.y = 0 ;
	bubRect.w = BUB_SIZE ;
	bubRect.h = BUB_SIZE ;
	
	for ( i = 0 ; i < BUB_NY ; i++ )
	{
	  j_max = ( i % 2 == 0 ) ? BUB_NX : BUB_NX - 1 ;
	  
	  for ( j = 0 ; j < j_max ; j++ )
	  {
	    /* We only draw the bubbles set to 1 in the array */
	    if ( game->bub_array[i][j] > 0 )
	    {
	      /* Get the position of bubbles */
	      temp = calculPosBub ( i, j, temp, ceil ) ;
	      
	      /* Display them */
	      SDL_BlitSurface ( game->bub_colors[game->bub_array[i][j] - 1], &bubRect, window->screen, temp ) ;
	    }
	  }
	}

	get_timer ( timer->explosion ) ;
	get_timer ( timer->fall ) ;

	for ( i = 0 ; i < game->fall_head ; i++ )
	{ 
		if ( game->nb_bubout == game->nb_bubexplosions - 1 )
		{
			bub_disappears ( game ) ;
			break ;
		}
		if ( game->bub_falling[i].isExplosing )
		{
			bub_explosion ( game, i, timer ) ;
		}
		else
		{ 
			bub_falling ( game, i, timer ) ;
		}
		if ( !bub_isOut ( game, i ) )
		{
			SDL_BlitSurface ( game->bub_explosion[game->bub_falling[i].bub_color - 1], game->bub_falling[i].image, window->screen, game->bub_falling[i].position ) ;
		} 
	}

	if ( limite_fps_expl ( timer->explosion ) )
	{
		update_timer ( timer->explosion ) ;
	}

	if ( limite_fps_fall ( timer->fall ) )
	{
		update_timer ( timer->fall ) ;
	}

	game->nb_bubout = 0 ;
	bubRect.y = bub->rotation * BUB_SIZE ;

	
	/* Display the current bubble which is moving */
	SDL_BlitSurface ( bub->sprite, &bubRect, window->screen, &(bub->pos) ) ; /* &(bub->position) ? */
	SDL_BlitSurface ( ceil->ceiling->image_ceiling, NULL, window->screen, ceil->ceiling->ceil_pos ) ;

	free ( temp ) ;

	/* We update the time */
	get_timer ( timer->ceiling ) ;
	
}

void update_timer ( timecontrol_t * timer )
{
	timer->previousTime = timer->currentTime ;
}

void init_timer ( timecontrol_t * timer )
{
	timer->previousTime = 0 ;
}

void get_timer ( timecontrol_t * timer )
{
	timer->currentTime = SDL_GetTicks() ;
}

void initBubblesOnBoard ( game_t * game, bubble_t * bubble )
{
    /* 1 = black ; 2 = blue ; 3 = green ; 4 = orange ; 5 = purple ; 6 = red ; 7 = white ; 8 = yellow */
	unsigned int i, j, j_max ;
	
	unsigned int level[BUB_NY][BUB_NX] = { {2,2,8,6,6,8,2,2} ,
                                           {7,2,8,6,8,2,7} ,
                                           {3,3,2,8,8,2,4,4} ,
                                           {1,7,2,8,2,3,3} ,
                                           {5,1,7,2,2,4,7,1} ,
                                           {4,5,8,2,6,4,1} ,
                                           {3,5,3,6,8,5,3,1} ,
                                           {0,0,0,0,0,0,0} ,
                                           {0,0,0,0,0,0,0,0} ,
                                           {0,0,0,0,0,0,0} ,
                                           {0,0,0,0,0,0,0,0} ,
                                           {0,0,0,0,0,0,0} } ;

	for ( i = 0 ; i < BUB_NY ; i++ )
	{
		j_max = ( i % 2 == 0 ) ? BUB_NX : BUB_NX - 1 ;

		for ( j = 0 ; j < j_max ; j++ )
		{
			game->bub_array[i][j] = level[i][j] ; //rand_color() ;
		}
	}

	bubble->rotation = 0 ;

}

void bubcomponent_init ( game_t * game )
{
	unsigned int i, j, j_max ;

	for ( i = 0 ; i < BUB_NY ; i++ )
	{

		game->bub_connected_component[i] = ( int * ) malloc ( BUB_NX * sizeof ( int ) ) ;

		j_max = ( i % 2 == 0 ) ? BUB_NX : BUB_NX - 1 ;

		for ( j = 0 ; j < j_max ; j++ )
		{
			game->bub_connected_component[i][j] = 0 ;
		}
	}


}


void bubfile_init ( game_t * game )
{
	unsigned int i ;

	for ( i = 0 ; i < BUB_NY * BUB_NX ; i++ )
	{
		game->bub_fifo[i] = ( int * ) malloc ( 2 * sizeof ( int ) ) ;
	}

	game->head = 0 ;
	game->tail = 0 ;
}

void freecomponent_array ( game_t * game )
{
	unsigned int i ;

	for ( i = 0 ; i < BUB_NY ; i++ )
	{

		free( game->bub_connected_component[i] ) ;
	}

}

bool we_have_a_winner ( game_t * game )
{
	unsigned int i, j, j_max ;

	for ( i = 0 ; i < BUB_NY ; i ++ )
	{
		j_max = ( i % 2 == 0 ) ? BUB_NX : BUB_NX - 1 ;

		for ( j = 0 ; j < j_max ; j++ )
		{
			if ( game->bub_array[i][j] > 0 )
			{
				return false ;
			}
		}
	}
	return true ;
}

int sky_is_falling ( timecheck_t * timer, ceiling_t * ceil, game_t * game, bubble_t * bub ) 
{
	if ( timer->ceiling->currentTime - timer->ceiling->previousTime > 10000 )
	{
		ceil->state += 1 ;
		update_timer ( timer->ceiling ) ;
		bubarray_centersrecalcul ( game, ceil, bub, timer ) ;
	} 

	return 1 ;
}

int game_over ( bubble_t * bub, ceiling_t * ceil, game_t * game, timecheck_t * timer )
{
	printf("GAME OVER.\n") ; 
	ceilingstateInit ( ceil ) ;   
	bubarray_free ( game ) ; 
	gameInit ( game, ceil ) ;    
	initBubblesOnBoard ( game, bub ) ; 
	bubPosInit ( bub, game ) ; 
	bubcomponent_init ( game ) ; 
	update_timer ( timer->ceiling ) ;
    update_timer ( timer->explosion ) ;
	update_timer ( timer->fall ) ;
    get_timer ( timer->ceiling ) ;
	get_timer ( timer->explosion ) ;
	get_timer ( timer->fall ) ;

	return EXIT_SUCCESS ;
}

int you_win ( bubble_t * bub, ceiling_t * ceil, game_t * game, timecheck_t * timer )
{
	printf("CONGRATULATIONS ! YOU WIN !\n") ;
    ceilingstateInit ( ceil ) ;   
	bubarray_free ( game ) ; 
	gameInit ( game, ceil ) ;    
	initBubblesOnBoard ( game, bub ) ; 
	bubPosInit ( bub, game ) ; 
	bubcomponent_init ( game ) ; 
	update_timer ( timer->ceiling ) ;
    update_timer ( timer->explosion ) ;
	update_timer ( timer->fall ) ;
    get_timer ( timer->ceiling ) ;
	get_timer ( timer->explosion ) ;
	get_timer ( timer->fall ) ;

	return EXIT_SUCCESS ; 
}

bool limite_fps_expl ( timecontrol_t * time )
{
	if ( time->currentTime - time->previousTime >= 12 )
	{
		return true ;
	}
	return false ;
}

bool limite_fps_fall ( timecontrol_t * time )
{
	if ( time->currentTime - time->previousTime >= 0.5 )
	{
		return true ;
	}
	return false ;
}

void init_time_variable ( timecheck_t * timer )
{
	timer->launcher = ( timecontrol_t * ) malloc ( sizeof ( timecontrol_t ) ) ; 
	timer->ceiling = ( timecontrol_t * ) malloc ( sizeof ( timecontrol_t ) ) ;
	timer->explosion = ( timecontrol_t * ) malloc ( sizeof ( timecontrol_t ) ) ; 
	timer->fall = ( timecontrol_t * ) malloc ( sizeof ( timecontrol_t ) ) ; 
	timer->pause = ( timecontrol_t * ) malloc ( sizeof ( timecontrol_t ) ) ;

	init_timer ( timer->launcher ) ;  
	init_timer ( timer->ceiling ) ;
	init_timer ( timer->explosion ) ; 
	init_timer ( timer->fall ) ;
	init_timer ( timer->pause) ;
}

bool check_pause ( input_t * in, timecheck_t * timer )
{
	if ( timer->pause->currentTime - timer->pause->previousTime >= 1000 )
	{
		if ( in->key[SDLK_p] == 1 )
		{
			in->pause = 1 ;
			update_timer ( timer->pause ) ;
			return true ;
		}
	} 

	return false ;
}

void print_pause ( text_t * text, input_t * in, bubble_t * bub, init_t * window, timecheck_t * timer )
{
	get_timer ( timer->pause ) ;
	SDL_BlitSurface ( text->pause, NULL, window->screen, text->pause_pos ) ;

	if ( timer->pause->currentTime - timer->pause->previousTime >= 1000 )
	{
		HandleEvent ( in, bub ) ;
		if ( check_pause ( in, timer ) )
		{
			in->pause = 0 ;
			update_timer ( timer->pause ) ;
		}
	}

	SDL_UpdateRect ( window->screen, 0, 0, 0, 0 ) ; 

}

#endif