#ifndef DECK_H
#define DECK_H

#include "card.h"

#include "../lib/stds/include/stds.h"
#include "../lib/structures/include/stds_vector.h"

struct stock_deck_t {
  stds_vector_t *deck;
};

struct waste_deck_t {
  stds_vector_t *deck;
};

struct foundation_deck_t {
  stds_vector_t *deck;
};

extern struct stock_deck_t *create_stock_deck();

extern struct foundation_deck_t *create_foundation();

extern struct waste_deck_t *create_waste_deck();

extern void shuffle_deck( stds_vector_t *v, uint32_t shuffle_times );

extern struct card_t peek_deck( stds_vector_t *v );

extern void insert_card( stds_vector_t *v, struct card_t *c );

extern void printw_deck_size( stds_vector_t *v );

#endif // DECK_H