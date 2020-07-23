#include "../include/stage.h"

static char  input_buffer[SMALL_TEXT_BUFFER];
static char  output_buffer[SMALL_TEXT_BUFFER];
static char *headers[] = {"Stock",        "Waste",       "", "Foundation 1", "Foundation 2",
                          "Foundation 3", "Foundation 4"};

struct stock_deck_t *     stock_deck;
struct waste_deck_t *     waste_deck;
struct foundation_deck_t *foundation_decks[FOUNDATION_SIZE];
struct layout_deck_t *    layout_decks[LAYOUT_SIZE];

static void init_decks( void );
static void deal_decks( void );
static void deal_layouts( void );
static void print_headers( void );
static void print_stock( void );
static void print_waste( void );
static void print_layouts( void );
static void print_foundations( void );
static void prompt_input( void );
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
  while ( true ) {
    print_headers();
    print_layouts();
    print_stock();
    print_waste();
    print_foundations();

    move( 20, 0 );
    getstr( input_buffer );
    parse_pattern( input_buffer );
    memset( input_buffer, 0, sizeof( input_buffer ) );
    refresh();
    erase();
  }
}

/**
 * Initializes the four types of decks: stock, waste, foundation,
 * and layout. There are four foundation decks, with seven layout decks.
 * The stock deck is poplated, and shuffled. Then the remaining decks (particularly
 * the layouts) are populated.
 * 
 * @param void.
 * 
 * @return void.
 */
static void
init_decks( void ) {
  stock_deck = create_stock_deck();
  waste_deck = create_waste_deck();

  /* Create the four foundation decks. */
  for ( uint32_t i = 0; i < FOUNDATION_SIZE; i++ ) {
    foundation_decks[i] = create_foundation();
  }

  /* Create the seven layout decks. */
  for ( uint32_t i = 0; i < LAYOUT_SIZE; i++ ) {
    layout_decks[i] = create_layout_deck();
  }

  /* Shuffle the deck ten times. */
  shuffle_deck( stock_deck->deck, 10 );
  deal_decks();
}

/**
 * Creates the seven layout piles. Two for loops
 * iterate through and continuously build the pile
 * from the stock deck.
 *
 * @param void.
 *
 * @return void.
 */
static void
deal_decks( void ) {
  move( 10, 0 );
  stds_vector_t *sd = stock_deck->deck;
  for ( int32_t i = 0; i < LAYOUT_SIZE; i++ ) {
    for ( int32_t j = 1; j <= i + 1; j++ ) {
      size_t         idx = Stds_VectorSize( sd ) - 1;
      struct card_t *c   = ( struct card_t * ) Stds_VectorGet( sd, idx );

      /* Only show the card if it's the last one in the pile initially.*/
      c->is_hidden = j < i + 1;
      Stds_VectorRemove( sd, idx );
      Stds_VectorAppend( layout_decks[i]->deck, ( void * ) c );
    }
  }
}

/**
 * Prints the seven headers for each top column.
 * 
 * @param void.
 * 
 * @return void.
 */
static void
print_headers( void ) {
  for ( uint32_t i = 0; i < HEADER_SIZE; i++ ) {
    move( 0, COL_SIZE * i );
    printw( "%s", headers[i] );
  }
}

/**
 * Prints the top card of the stock deck.
 * 
 * @param void.
 * 
 * @return void.
 */
static void
print_stock( void ) {
  /* Print the top card on the stack. */
  move( 1, 0 );
  if ( Stds_VectorIsEmpty( stock_deck->deck ) ) {
    printw( "NULL" );
  } else {
    struct card_t c = peek_deck( stock_deck->deck );
    printw_card( &c, false );
  }

  /* Print the size of the stack. */
  move( 2, 0 );
  printw_deck_size( stock_deck->deck );
}

/**
 * Prints the top of the waste deck.
 * 
 * @param void.
 * 
 * @return void.
 */
static void
print_waste( void ) {
  stds_vector_t *wd = waste_deck->deck;
  /* Print the top card on the stack. */
  move( 1, 14 );
  if ( Stds_VectorIsEmpty( wd ) ) {
    printw( "NULL" );
  } else {
    struct card_t *c = ( struct card_t * ) Stds_VectorGet( wd, Stds_VectorSize( wd ) - 1 );
    printw_card( c, false );
  }

  /* Print the size of the stack. */
  move( 2, 14 );
  printw_deck_size( waste_deck->deck );
}

/**
 * Prints the foundations.
 * 
 * @param void.
 * 
 * @return void.
 */
static void
print_foundations( void ) {
  /* Print foundations. */
  for ( uint32_t f = 0; f < FOUNDATION_SIZE; f++ ) {
    int32_t foundation_1_column = 3;
    size_t  size                = Stds_VectorSize( foundation_decks[f]->deck );
    move( 1, ( foundation_1_column + f ) * COL_SIZE );

    /* If there are no cards in the foundation, just print NULL. Otherwise,
       print the top card. */
    if ( size == 0 ) {
      printw( "NULL" );
    } else {
      printw_card( Stds_VectorGet( foundation_decks[f]->deck, size - 1 ), false );
    }

    move( 2, ( foundation_1_column + f ) * COL_SIZE );
    printw( "(%d Cards)", size );
  }
}

/**
 * Prints the layouts and their cards. 
 * 
 * @param void.
 * 
 * @return void.
 */
static void
print_layouts( void ) {
  int32_t col_header_pos = 4;
  int32_t card_start_pos = 5;
  move( col_header_pos, 0 );

  /* Print the header names. */
  char *col_type = "Column ";
  for ( int32_t i = 0; i < LAYOUT_SIZE; i++ ) {
    memcpy( output_buffer, col_type, sizeof( col_type ) );
    char *col_name = Stds_StrCatIntArray( output_buffer, ( i + 1 ) );
    move( col_header_pos, i * COL_SIZE );
    printw( col_name );
    memset( output_buffer, 0, sizeof( output_buffer ) );
  }

  /* Now, print the actual cards. */
  for ( int32_t i = 0; i < LAYOUT_SIZE; i++ ) {
    stds_vector_t *d = layout_decks[i]->deck;
    for ( int32_t j = Stds_VectorSize( d ), y = card_start_pos; j > 0; j--, y++ ) {
      move( y, i * COL_SIZE );
      struct card_t *c = ( struct card_t * ) Stds_VectorGet( d, Stds_VectorSize( d ) - j );
      
      /* If a card is suddenly the last one on the pile, make it visible.*/
      if (j == 1) {
        c->is_hidden = false;
      }
      
      printw_card( c, c->is_hidden );
    }
  }
}

/**
 * Prompts the user to enter an input. This string
 * is read in via ncurses, and stored in a small buffer
 * for later parsing.
 * 
 * @param void.
 * 
 * @return void.
 */
static void
prompt_input( void ) {
  move( 20, 0 );
  getstr( input_buffer );
}

/**
 * Cleans up the stage and the pointers/decks associated with
 * the game.
 * 
 * @param void.
 * 
 * @return void.
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

  for ( uint32_t i = 0; i < LAYOUT_SIZE; i++ ) {
    Stds_VectorDestroy( layout_decks[i]->deck );
    free( layout_decks[i] );
  }

  endwin();
}