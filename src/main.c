#include "../include/main.h"

static void init_game( void );
static void init_ncurses( void );

int
main( int argc, char *argv[] ) {
  init_game();
  init_ncurses();
  init_stage();
  game_loop();

  return 0;
}

/**
 * Initializes the random time seed and 
 * sets the locale to allow for unicode symbols
 * in the ncurses window.
 * 
 * @param void.
 * 
 * @return void.
 */
static void
init_game( void ) {
  Stds_SetRandomSeed();
  setlocale( LC_CTYPE, "" );
}

/**
 * Initialies the ncurses screen and color components. We also
 * initialize the two color types for solitaire: red and black.
 * 
 * @param void.
 * 
 * @return void.
 */
static void
init_ncurses( void ) {
  initscr();

  if ( has_colors() == false ) {
    printf( "Colors are not supported by this terminal.\n" );
    endwin();
    // exit( EXIT_FAILURE );
  }

  start_color();
  raw();
  keypad( stdscr, true );
  init_pair( BLACK_PAIR, COLOR_BLACK, COLOR_BLACK );
  init_pair( RED_PAIR, COLOR_RED, COLOR_BLACK );
}