#include "../include/deck.h"

#define RANK_COUNT 13
#define SUIT_COUNT 4

/**
 * Creates the foundation decks. The foundation decks are the top
 * four decks where the A-K cards are progressively laid based on suit.
 * 
 * @param void.
 * 
 * @return struct foundation_deck_t * pointer to foundation.
 */
struct foundation_deck_t *
create_foundation( void ) {
  struct foundation_deck_t *f;
  f = malloc( sizeof( struct foundation_deck_t ) );

  if ( f == NULL ) {
    printf( "Error: could not allocate memory for foundation_deck_t struct.\n" );
    // exit( EXIT_FAILURE );
  }

  memset( f, 0, sizeof( struct foundation_deck_t ) );

  f->deck = Stds_VectorCreate( sizeof( struct card_t ) );

  return f;
}

/**
 * Creates the stock deck. The stock deck is the starting deck with all
 * fifty-two cards initially.
 * 
 * @param void.
 * 
 * @return struct stock_deck_t * pointer to stock.
 */
struct stock_deck_t *
create_stock_deck( void ) {
  struct stock_deck_t *s;
  s = malloc( sizeof( struct stock_deck_t ) );

  if ( s == NULL ) {
    printf( "Error: could not allocate memory for stock_deck_t struct.\n" );
    // exit( EXIT_FAILURE );
  }

  memset( s, 0, sizeof( struct stock_deck_t ) );

  s->deck = Stds_VectorCreate( sizeof( struct card_t ) );

  /* Fills the deck. */
  for ( uint32_t rank = 0; rank < RANK_COUNT; rank++ ) {
    for ( uint32_t suit = 0; suit < SUIT_COUNT; suit++ ) {
      struct card_t *c;
      c = create_card( suit, rank );
      insert_card( s->deck, c );
    }
  }

  return s;
}

/**
 * Creates the waste deck. The waste deck is the deck where cards that
 * are not wanted for the current turn go.
 * 
 * @param void.
 * 
 * @return struct waste_deck_t pointer to waste deck.
 */
struct waste_deck_t *
create_waste_deck( void ) {
  struct waste_deck_t *w;
  w = malloc( sizeof( struct waste_deck_t ) );

  if ( w == NULL ) {
    printf( "Error: could not allocate memory for waste_deck_t struct.\n" );
    // exit( EXIT_FAILURE );
  }

  memset( w, 0, sizeof( struct waste_deck_t ) );

  w->deck = Stds_VectorCreate( sizeof( struct card_t ) );

  return w;
}

/**
 * Creates a layout deck. A layout deck is one of the seven randomly-generated
 * decks at the start of the game, ranging from 1 to 7 cards initially.
 * 
 * @param void.
 * 
 * @return layout_deck_t pointer to struct.
 */
struct layout_deck_t *
create_layout_deck( void ) {
  struct layout_deck_t *l;
  l = malloc( sizeof( struct layout_deck_t ) );

  if ( l == NULL ) {
    printf( "Error: could not allocate memory for layout_deck_t struct.\n" );
    // exit( EXIT_FAILURE );
  }

  memset( l, 0, sizeof( struct layout_deck_t ) );

  l->deck = Stds_VectorCreate( sizeof( struct card_t ) );

  return l;
}

/**
 * Randomizes a vector. It's probably not the best random function there is,
 * but it gets the job done. Each iteration through, a random index is polled,
 * and the current index is swapped with it.
 */
void
shuffle_deck( stds_vector_t *v, uint32_t shuffle_times ) {
  for ( uint32_t s = 0; s < shuffle_times; s++ ) {
    for ( uint32_t i = 0; i < Stds_VectorSize( v ); i++ ) {
      /* Grab a random index. */
      uint32_t idx = Stds_RandomInt( 0, Stds_VectorSize( v ) - 1 );
      Stds_VectorSwap( v, idx, i );
    }
  }
}

/**
 * Returns the top card of a vector. Useful for foundations, waste and stock decks.
 * 
 * @param stds_vector_v * pointer to vector deck.
 * 
 * @return card_t structure to card on top.
 */
struct card_t
peek_deck( stds_vector_t *v ) {
  return *( struct card_t * ) Stds_VectorGet( v, Stds_VectorSize( v ) - 1 );
}

/**
 * Inserts a card pointer into the vector.
 * 
 * @param struct stds_vector_t * pointer to vector.
 * @param struct card_t * pointer to card.
 * 
 * @return void.
 */
void
insert_card( stds_vector_t *v, struct card_t *c ) {
  Stds_VectorAppend( v, ( void * ) c );
}

/**
 * Prints out the deck size provided by the backing vector.
 * 
 * @param stds_vector_t * pointer to vector.
 * 
 * @return void.
 */
void
printw_deck_size( stds_vector_t *v ) {
  printw( "(%d Cards)", Stds_VectorSize( v ) );
}