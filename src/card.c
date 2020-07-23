#include "../include/card.h"

static char output_buffer[SMALL_TEXT_BUFFER];

/**
 * Create a card_t pointer with a supplied SUIT and RANK.
 * 
 * @param enum SUIT suit (HEART, DIAMOND, CLUB, SPADE).
 * @param enum RANK rank (0-12).
 * 
 * @return struct card_t * pointer to card.
 */
struct card_t *
create_card( enum SUIT suit, enum RANK rank ) {
  struct card_t *c;
  c = malloc( sizeof( struct card_t ) );
  memset( c, 0, sizeof( struct card_t ) );

  c->suit = suit;
  c->rank = rank;
  c->is_hidden = false;

  return c;
}

/**
 * Determines if the card is black via its suit.
 * 
 * @param struct card_t *c pointer to card.
 * 
 * @return true if it's a SPADE or CLUB, false otherwise.
 */
bool
is_black( struct card_t *c ) {
  return c->suit == SPADE || c->suit == CLUB;
}

/**
 * Determines if the card is red via its suit.
 * 
 * @param struct card_t *c pointer to card.
 * 
 * @return true if it's a DIAMOND or HEART, false otherwise.
 */
bool
is_red( struct card_t *c ) {
  return c->suit == DIAMOND || c->suit == HEART;
}

/**
 * Determines if the colors of the two cards are opposite.
 * 
 * @param struct card_t * pointer to first card.
 * @param struct card_t * pointer to second card.
 * 
 * @return true if they are opposite, false otherwise.
 */
bool
is_alternate_color( struct card_t *c1, struct card_t *c2 ) {
  return ( is_black( c1 ) && is_red( c2 ) ) || ( is_black( c2 ) && is_red( c1 ) );
}

/**
 * Checks to see if the rank of the card currently on the deck.
 * There are two possibilities for this to be true: either there is nothing on 
 * the deck and the first card is an ace, or the lower card (e.g. already on the deck)
 * has the same rank as the higher card if we increment [lower's rank] by 1. If they are the
 * same, this means they are sequential.
 * 
 * @param struct card_t * pointer to lower card (NULL for blank deck).
 * @param struct card_t * pointer to higher card.
 * 
 * @return true if the cards are in sequence, false otherwise.
 */
bool
is_in_sequence( struct card_t *lower, struct card_t *higher ) {
  return (lower == NULL && higher->rank == 0) || (lower->rank + 1 == higher->rank);
}

/**
 * Determines if the child card is a valid placement for the layout. The parent is the 
 * card that is already on the deck, and the child is the one being transferred from
 * another source.
 * 
 * @param struct card_t * pointer to parent card.
 * @param struct card_t * pointer to child card.
 * 
 * @return true if the two are opposite colors and are in sequence. False otherwise.
 */
bool
is_valid_child_card( struct card_t *parent, struct card_t *child ) {
  return is_alternate_color( parent, child ) && is_in_sequence( child, parent );
}

/**
 * Checks to see if the two cards share the same suit.
 * 
 * @param struct card_t * pointer to first card.
 * @param struct card_t * pointer to second card.
 * 
 * @return true if they share suits, false otherwise.
 */
bool
is_same_suit( struct card_t *c1, struct card_t *c2 ) {
  return c1->suit == c2->suit;
}

/**
 * Determines if a card can be placed on a foundation. The only two conditions for this are 
 * that they share suits, and are in sequential order.
 * 
 * @param struct card_t * pointer to first (new) card.
 * @param struct card_t * pointer to the card already on the stack (this can be NULL for a blank foundation).
 * 
 * @return true if it is placeable, false otherwise.
 */
bool
is_placeable_on_foundation( struct card_t *new_card, struct card_t *top_of_stack_card ) {
  return is_same_suit( new_card, top_of_stack_card ) &&
         is_in_sequence( top_of_stack_card, new_card );
}

/**
 * Gets the unicode symbol associated with the respective suit.
 * 
 * @param enum SUIT suit.
 * 
 * @return const char * pointer to unicode char for suit. Fails if it's invalid.
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
 * Returns the alphanumeric symbol associated with the respective rank.
 * 
 * @param enum RANK rank
 * 
 * @return const char * pointer to alphanumeric rank. 0 is ACE, 1<=x<=9 is the number plus one,
 *         10 = J, 11 = Q, K = 12.
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
 * Prints out the card with its respective const char * versions of the suit and rank.
 * 
 * @param struct card_t * pointer to card.
 * @param bool variable to tell if the card is hidden or not (mostly used in layouts).
 * 
 * @return void.
 */
void
printw_card( struct card_t *c, bool is_hidden ) {
  if ( is_red( c ) ) {
    wattron( stdscr, COLOR_PAIR( RED_PAIR ) );
  }

  if ( is_hidden ) {
    //printw( "(%s%s)", get_suit_char( c->suit ), get_rank_char( c->rank ) );
    printw( "(\u2047)");
  } else {
    printw( "%s%s", get_suit_char( c->suit ), get_rank_char( c->rank ) );
  }

  wattroff( stdscr, COLOR_PAIR( RED_PAIR ) );
}