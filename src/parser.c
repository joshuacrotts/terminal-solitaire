#include "../include/parser.h"

static void stock_to_waste( void );
static void handle_waste_src( int8_t src_id, int8_t src_no, int8_t dest_id, int8_t dest_no );
static void handle_layout_src( int8_t src_id, int8_t src_no, int8_t dest_id, int8_t dest_no );

/**
 * Parses the input from the user. This input is
 * read in via the grammar described in the header file.
 * This will change, hopefully...
 *
 * @param const char * pointer to input string.
 *
 * @return void.
 */
void
parse_pattern( const char *input ) {
  /* Read the pattern. */
  char cmd = input[0];

  if ( cmd == 'q' ) {
    exit( EXIT_SUCCESS );
  }

  /* If we are able to move a stock to the waste, do it. */
  else if ( cmd == 'd' && Stds_VectorSize( stock_deck->deck ) != 0 ) {
    stock_to_waste();
  }

  else if ( cmd == 'm' ) {
    /* Get the number of cards we want to move. */
    char no_cards_str[2];
    no_cards_str[0] = input[2];
    no_cards_str[1] = input[3];
    int8_t no_cards = atoi( no_cards_str );

    /* Get the source of the movement. */
    char   src_id = input[5];
    int8_t src_no = input[6] - '0';

    /* Get the destination of the movement. */
    char   dest_id = input[8];
    int8_t dest_no = input[9] - '0';

    move( 10, 0 );

    /* If the source comes from the waste. */
    handle_waste_src( src_id, src_no, dest_id, dest_no );

    /* Else if the source comes from the layout cards. */
    handle_layout_src( src_id, src_no, dest_id, dest_no );
  }
}

/**
 *
 */
static void
handle_waste_src( int8_t src_id, int8_t src_no, int8_t dest_id, int8_t dest_no ) {
  if ( src_id == 'w' && src_no == 0 ) {

    /* For now, just assume one card is being transferred... */
    struct card_t *c = ( struct card_t * ) Stds_VectorGet(
        waste_deck->deck, Stds_VectorSize( waste_deck->deck ) - 1 );
    Stds_VectorRemove( waste_deck->deck, Stds_VectorSize( waste_deck->deck ) - 1 );

    /* If the dest goes to the foundation. */
    if ( dest_id == 'f' && dest_no >= 1 && dest_no <= 4 ) {
      move( 30, 0 );
      printw( "%d\n", dest_no );
      Stds_VectorAppend( foundation_decks[dest_no - 1]->deck, ( void * ) c );
    }
    /* If the dest goes to a column. */
    else if ( dest_id == 'c' && dest_no >= 1 && dest_no <= 7 ) {
      Stds_VectorAppend( layout_decks[dest_no - 1]->deck, ( void * ) c );
    }
  }
}

/**
 *
 */
static void
handle_layout_src( int8_t src_id, int8_t src_no, int8_t dest_id, int8_t dest_no ) {
  if ( src_id == 'c' && src_no >= 1 && src_no <= 7 ) {
    /* For now, just assume one card is being transferred... */
    struct card_t *c = ( struct card_t * ) Stds_VectorGet(
        layout_decks[src_no - 1]->deck, Stds_VectorSize( layout_decks[src_no - 1]->deck ) - 1 );
    Stds_VectorRemove( layout_decks[src_no - 1]->deck,
                       Stds_VectorSize( layout_decks[src_no - 1]->deck ) - 1 );

    /* If the dest goes to the foundation. */
    if ( dest_id == 'f' && dest_no >= 1 && dest_no <= 4 ) {
      stds_vector_t *fd         = foundation_decks[dest_no - 1]->deck;
      struct card_t *top_f_card = Stds_VectorGet( fd, Stds_VectorSize( fd ) - 1 );
      Stds_VectorAppend( fd, ( void * ) c );
    }
    /* If the dest goes to a column. */
    else if ( dest_id == 'c' && dest_no >= 1 && dest_no <= 7 ) {
      Stds_VectorAppend( layout_decks[dest_no - 1]->deck, ( void * ) c );
    }
  }
}

/**
 *
 */
static void
stock_to_waste( void ) {
  struct card_t *c = ( struct card_t * ) Stds_VectorGet( stock_deck->deck,
                                                         Stds_VectorSize( stock_deck->deck ) - 1 );
  Stds_VectorRemove( stock_deck->deck, Stds_VectorSize( stock_deck->deck ) - 1 );
  Stds_VectorAppend( waste_deck->deck, ( void * ) c );
}