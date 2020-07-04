#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <unordered_set>
#include <vector>
#include <list>

static int counter = 0;

class Card{
    public:
        Card();
        Card(int tag); // initializes tag-value pair
		Card(const Card& source); // copy constructor for card
        bool isAce();
        //~Card();
        int getValue();
        int getTag();
        void setTag();
        // std::string getName();
        friend bool operator==(const Card& c1, const Card& c2);
		//bool operator ==(const Card& other); // it gave me an error when I tried to pass one param :(
		//bool operator==(const Card& c1, const Card& c2);
        friend bool operator!=(const Card& c1, const Card& c2);
        Card operator=(const Card& source);
        Card operator [](int index){
                return this[index];
        }
        friend std::ostream& operator << (std::ostream&out, const Card c);

    private:
        int value; // value of card 2-10
        int cardTag; // card tag for seniority
        //std::string cardName; 


};

class Deck{
    public:
        Deck();
		Deck(const Deck& source); // copy constructor for deck
        void ShuffleDeck();
        void FillRed();
        void FillBlack();
        Card getCard();
        int deckSize();
        void push_front(const Card& c);
        Deck operator=(const Deck& source);
        void cardSwap();
        void clearDeck(); // clear for debugging

    private:
        std::vector<Card> cDeck;
        int cardsLeft; // cards left unDRAWN
        
};
