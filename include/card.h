#ifndef CARD_H
#define CARD_H

#define BLACK_PAIR 1
#define RED_PAIR   2

#include "../lib/stds/include/stds.h"

enum SUIT { HEART, SPADE, CLUB, DIAMOND };

enum RANK { R_A, R_2, R_3, R_4, R_5, R_6, R_7, R_8, R_9, R_10, R_J, R_Q, R_K };

struct card_t {
  enum SUIT suit;
  enum RANK rank;
  bool      is_hidden;
};

extern struct card_t *create_card( enum SUIT suit, enum RANK rank );

extern bool is_black( struct card_t *c );

extern bool is_red( struct card_t *c );

extern bool is_alternate_color( struct card_t *c1, struct card_t *c2 );

extern bool is_in_sequence( struct card_t *lower, struct card_t *higher );

extern bool is_valid_child_card( struct card_t *parent, struct card_t *child );

extern bool is_same_suit( struct card_t *c1, struct card_t *c2 );

extern bool is_placeable_on_foundation( struct card_t *new_card, struct card_t *top_of_stack_card );

extern const char *get_suit_char( enum SUIT suit );

extern const char *get_rank_char( enum RANK rank );

extern void printw_card( struct card_t *c, bool is_hidden );

#endif // CARD_H