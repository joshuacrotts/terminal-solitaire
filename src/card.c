#include "../include/card.h"

static char output_buffer[SMALL_TEXT_BUFFER];

/**
 *
 */
struct card_t *
create_card( enum SUIT suit, enum RANK rank ) {
  struct card_t *c;
  c = malloc( sizeof( struct card_t ) );
  memset( c, 0, sizeof( struct card_t ) );

  c->suit = suit;
  c->rank = rank;

  return c;
}

/**
 *
 */
bool
is_black( struct card_t *c ) {
  return c->suit == SPADE || c->suit == CLUB;
}

/**
 *
 */
bool
is_red( struct card_t *c ) {
  return c->suit == DIAMOND || c->suit == HEART;
}

/**
 *
 */
bool
is_alternate_color( struct card_t *c1, struct card_t *c2 ) {
  return ( is_black( c1 ) && is_red( c2 ) ) || ( is_black( c2 ) && is_red( c1 ) );
}

/**
 *
 */
bool
is_in_sequence( struct card_t *lower, struct card_t *higher ) {
  return lower->rank + 1 == higher->rank;
}

/**
 *
 */
bool
is_valid_child_card( struct card_t *parent, struct card_t *child ) {
  return is_alternate_color( parent, child ) && is_in_sequence( child, parent );
}

/**
 *
 */
bool
is_same_suit( struct card_t *c1, struct card_t *c2 ) {
  return c1->suit == c2->suit;
}

/**
 *
 */
bool
is_placeable_on_foundation( struct card_t *new_card, struct card_t *top_of_stack_card ) {
  return is_same_suit( new_card, top_of_stack_card ) &&
         is_in_sequence( new_card, top_of_stack_card );
}

/**
 *
 */
const char *
get_suit_char( enum SUIT suit ) {
  switch ( suit ) {
  case HEART:
    return "\u2665";
  case SPADE:
    return "\u2660";
  case CLUB:
    return "\u2663";
  case DIAMOND:
    return "\u2666";
  default:
    printf( "Invalid suit: %d.\n", suit );
    exit( EXIT_FAILURE );
  }
}

/**
 *
 */
const char *
get_rank_char( enum RANK rank ) {
  if ( rank == 0 ) {
    return "A";
  } else if ( rank <= 9 ) {
    // Return one extra due to the offset.
    return Stds_StrCatIntArray( output_buffer, rank + 1 );
  }

  switch ( rank ) {
  case 10:
    return "J";
  case 11:
    return "Q";
  case 12:
    return "K";
  default:
    printf( "Invalid rank: %d.\n", rank );
    exit( EXIT_FAILURE );
  }
}

/**
 *
 */
void
printw_card( struct card_t *c ) {
  if ( is_red( c ) ) {
    wattron(stdscr, COLOR_PAIR( RED_PAIR ) );
    printf("It's red bitch");
  }
  printw( "(%s%s)", get_suit_char( c->suit ), get_rank_char( c->rank ) );
  wattroff( stdscr, COLOR_PAIR( RED_PAIR ) );

}