//
// Created by thecharlesblake on 10/11/17.
//

#ifndef SOLITAIRE_PIP_CARD_H
#define SOLITAIRE_PIP_CARD_H

#include <string>
#include <map>

class card {
public:
    // Types & typedefs
    enum class suit_t {Clubs, Diamonds, Hearts, Spades};
    enum class colour_t {Black, Red};
    typedef uint8_t rank_t;

    // Converts a number (0-3) to a suit (Clubs-Spades)
    static suit_t to_suit(uint8_t);

    // A card can either be created using two int values (rank & suit), or
    // using a string (e.g. "AS")
    card(suit_t, rank_t);
    explicit card(const char*);

    suit_t get_suit() const;
    colour_t get_colour() const;
    rank_t get_rank() const;

private:
    static suit_t suit_from_str(const char* c);
    static rank_t rank_from_str(const char* c);

    suit_t suit;
    rank_t rank : 4;
};

bool operator==(const card&, const card&);
bool operator!=(const card&, const card&);


#endif //SOLITAIRE_PIP_CARD_H
