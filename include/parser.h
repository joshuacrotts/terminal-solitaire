#ifndef PARSER_H
#define PARSER_H

#include "card.h"
#include "deck.h"
#include "game_defs.h"

#include "../lib/stds/include/stds.h"

extern struct stock_deck_t *     stock_deck;
extern struct waste_deck_t *     waste_deck;
extern struct foundation_deck_t *foundation_decks[FOUNDATION_SIZE];
extern struct layout_deck_t *    layout_decks[LAYOUT_SIZE];

/**
 * Parsing pattern:
 * 
 * cmd ::= <type>
 * 
 * <type> ::= <m>|<q>
 * 
 * <mv> ::= mv + <space><number_of_cards><space><src_type><space><dest_type>
 * <q> ::= q (quit)
 * <number_of_cards> ::= (0 + (1-9)) | (10-13)
 * 
 * <src_type> ::= <f> | <w> | <c> | <s>
 * <dest_type> ::= <f> | <w> | <c>
 * 
 * <f> ::= f + (1-4) 
 * <w> ::= w0
 * <c> ::= c + (1-7)
 * <s> ::= s0
 */
extern void parse_pattern(const char* input);

#endif