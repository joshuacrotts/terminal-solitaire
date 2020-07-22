#include "../include/deck.h"

#define RANK_COUNT 13
#define SUIT_COUNT 4

/**
 *
 */
struct foundation_deck_t *
create_foundation() {
  struct foundation_deck_t *f;
  f = malloc( sizeof( struct foundation_deck_t ) );

  if ( f == NULL ) {
    printf( "Error: could not allocate memory for foundation_deck_t struct.\n" );
    exit( EXIT_FAILURE );
  }

  memset( f, 0, sizeof( struct foundation_deck_t ) );

  f->deck = Stds_VectorCreate( sizeof( struct card_t ) );

  return f;
}

/**
 *
 */
struct stock_deck_t *
create_stock_deck() {
  struct stock_deck_t *s;
  s = malloc( sizeof( struct stock_deck_t ) );

  if ( s == NULL ) {
    printf( "Error: could not allocate memory for stock_deck_t struct.\n" );
    exit( EXIT_FAILURE );
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
 *
 */
struct waste_deck_t *
create_waste_deck() {
  struct waste_deck_t *w;
  w = malloc( sizeof( struct waste_deck_t ) );

  if ( w == NULL ) {
    printf( "Error: could not allocate memory for waste_deck_t struct.\n" );
    exit( EXIT_FAILURE );
  }

  memset( w, 0, sizeof( struct waste_deck_t ) );

  w->deck = Stds_VectorCreate( sizeof( struct card_t ) );

  return w;
}

/**
 *
 */
void
shuffle_deck( stds_vector_t *v, uint32_t shuffle_times ) {
  for ( uint32_t s = 0; s < shuffle_times; s++ ) {
    for ( uint32_t i = 0; i < Stds_VectorSize( v ); i++ ) {
      // Grab a random index.
      uint32_t idx = Stds_RandomInt( 0, Stds_VectorSize( v ) - 1 );
      Stds_VectorSwap( v, idx, i );
    }
  }
}

/**
 *
 */
struct card_t
peek_deck( stds_vector_t *v ) {
  return *( struct card_t * ) Stds_VectorGet( v, Stds_VectorSize( v ) - 1 );
}

/**
 *
 */
void
insert_card( stds_vector_t *v, struct card_t *c ) {
  Stds_VectorAppend( v, ( void * ) c );
}

/**
 *
 */
void
printw_deck_size( stds_vector_t *v ) {
  printw( "(%d Cards)", Stds_VectorSize( v ) );
}