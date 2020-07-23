#include "../include/parser.h"

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

  /* Get the number of cards we want to move. */
  char no_cards_str[2];
  no_cards_str[0] = input[2];
  no_cards_str[1] = input[3];
  int8_t no_cards = atoi( no_cards_str );

  /* Get the source of the movement. */
  char src_id = input[5];
  int  src_no = input[6] - '0';

  /* Get the destination of the movement. */
  char dest_id = input[8];
  int  dest_no = input[9] - '0';

  move( 23, 0 );
  printw( "Command: %c --- Number of cards: %d --- Src: %c%d Dest: %c%d", cmd, no_cards, src_id,
          src_no, dest_id, dest_no );

  /* Parse the pattern. */
  if ( cmd == 'm' ) {

    /* If the source is the stock pile.*/
    if ( src_id == 's' && src_no == 0 ) {

      /* If the dest is the waste... */
      if ( no_cards == 1 && dest_id == 'w' && dest_no == 0 ) {
        struct card_t *c = ( struct card_t * ) Stds_VectorGet(
            stock_deck->deck, Stds_VectorSize( stock_deck->deck ) - 1 );
        Stds_VectorRemove( stock_deck->deck, Stds_VectorSize( stock_deck->deck ) - 1 );
        Stds_VectorAppend( waste_deck->deck, ( void * ) c );
      } else {
        move( 14, 0 );
        /* Will not print due to refresh! */
        printw( "Invalid command." );
      }
    }

    /* Else if the source comes from the waste. */
    else if ( src_id == 'w' && src_no == 0 ) {

      /* For now, just assume one card is being transferred... */
      struct card_t *c = ( struct card_t * ) Stds_VectorGet(
          waste_deck->deck, Stds_VectorSize( waste_deck->deck ) - 1 );
      Stds_VectorRemove( waste_deck->deck, Stds_VectorSize( waste_deck->deck ) - 1 );

      /* If the dest goes to the foundation. */
      if ( dest_id == 'f' && dest_no >= 1 && dest_no <= 4 ) {
                move(30, 0);
        printw("%d\n", dest_no);
        Stds_VectorAppend( foundation_decks[dest_no - 1]->deck, ( void * ) c );
      }
      /* If the dest goes to a column. */
      else if ( dest_id == 'c' && dest_no >= 1 && dest_no <= 7 ) {
        Stds_VectorAppend( layout_decks[dest_no - 1]->deck, ( void * ) c );
      }
    }

    /* Else if the source comes from the layout cards. */
    else if ( src_id == 'c' && src_no >= 1 && src_no <= 7 ) {
      /* For now, just assume one card is being transferred... */
      struct card_t *c = ( struct card_t * ) Stds_VectorGet(
          layout_decks[src_no - 1]->deck, Stds_VectorSize( layout_decks[src_no - 1]->deck ) - 1 );
      Stds_VectorRemove( layout_decks[src_no - 1]->deck, Stds_VectorSize( layout_decks[src_no - 1]->deck ) - 1 );

      /* If the dest goes to the foundation. */
      if ( dest_id == 'f' && dest_no >= 1 && dest_no <= 4 ) {
        Stds_VectorAppend( foundation_decks[dest_no - 1]->deck, ( void * ) c );
      }
      /* If the dest goes to a column. */
      else if ( dest_id == 'c' && dest_no >= 1 && dest_no <= 7 ) {
        Stds_VectorAppend( layout_decks[dest_no - 1]->deck, ( void * ) c );
      }
    }
  }
}