#include "../include/stage.h"

#define FOUNDATION_SIZE 4
#define HEADER_SIZE     7
#define COL_SIZE        14

static char *headers[] = {"Stock",        "Waste",       "", "Foundation 1", "Foundation 2",
                          "Foundation 3", "Foundation 4"};

static struct stock_deck_t *     stock_deck;
static struct waste_deck_t *     waste_deck;
static struct foundation_deck_t *foundation_decks[FOUNDATION_SIZE];

static void init_decks( void );
static void print_headers( void );
static void print_stock( void );
static void print_waste( void );
static void print_foundations( void );
static void cleanup_stage( void );

/**
 *
 */
void
init_stage( void ) {
  init_decks();
  atexit( cleanup_stage );
}

/**
 *
 */
void
game_loop( void ) {
  while ( 1 ) {
    print_headers();
    print_stock();
    print_waste();
    print_foundations();
    char c = getch();
    if ( c == 'q' ) {
      exit( EXIT_SUCCESS );
    }
    wrefresh(stdscr);

  }
}

/**
 *
 */
static void
init_decks( void ) {
  stock_deck = create_stock_deck();
  waste_deck = create_waste_deck();

  /* Create the four foundation decks. */
  for ( uint32_t i = 0; i < FOUNDATION_SIZE; i++ ) {
    foundation_decks[i] = create_foundation();
  }

  /* Shuffle the deck ten times. */
  shuffle_deck( stock_deck->deck, 10 );
}

/**
 *
 */
static void
print_headers( void ) {
  for ( uint32_t i = 0; i < HEADER_SIZE; i++ ) {
    move( 0, COL_SIZE * i );
    printw( "%s", headers[i] );
  }
}

/**
 *
 */
static void
print_stock( void ) {
  /* Print the top card on the stack. */
  move( 1, 0 );
  if ( Stds_VectorIsEmpty( stock_deck->deck ) ) {
    printw( "NULL" );
  } else {
    struct card_t c = peek_deck( stock_deck->deck );
    printw_card( &c );
  }

  /* Print the size of the stack. */
  move( 2, 0 );
  printw_deck_size( stock_deck->deck );
}

/**
 *
 */
static void
print_waste( void ) {
  /* Print the top card on the stack. */
  move( 1, 14 );
  if ( Stds_VectorIsEmpty( waste_deck->deck ) ) {
    printw( "NULL" );
  } else {
    struct card_t c = peek_deck( waste_deck->deck );
    printw_card( &c );
  }

  /* Print the size of the stack. */
  move( 2, 14 );
  printw_deck_size( waste_deck->deck );
}

/**
 *
 */
static void
print_foundations( void ) {
  /* Print foundations. */
  for ( int f = 0; f < FOUNDATION_SIZE; f++ ) {
    int    foundation_1_column = 3;
    size_t size                = Stds_VectorSize( foundation_decks[f]->deck );

    move( 1, ( foundation_1_column + f ) * COL_SIZE );
    if ( size == 0 ) {
      printw( "NULL" );
    } else {
      printw_card( Stds_VectorGet( foundation_decks[f]->deck, size ) );
    }
    move( 2, ( foundation_1_column + f ) * COL_SIZE );
    printw( "(%d Cards)", size );
  }
}

/**
 *
 */
static void
cleanup_stage( void ) {
  Stds_VectorDestroy( stock_deck->deck );
  free( stock_deck );

  Stds_VectorDestroy( waste_deck->deck );
  free( waste_deck );

  for ( int i = 0; i < FOUNDATION_SIZE; i++ ) {
    Stds_VectorDestroy( foundation_decks[i]->deck );
    free( foundation_decks[i] );
  }

  endwin();
}