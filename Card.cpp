#include "Card.h"
#include <iostream>
#include <algorithm>
#include <windows.h>
/*
Card::~Card(){
    value = NULL;
    cardTag = NULL;
}
*/

Card::Card(){
	cardTag = NULL;
	value = NULL;
	//std::cout << "Uh Oh..." << std::endl;
}

Card::Card(const Card& source) {
	cardTag = source.cardTag;
	value = source.value;
}

Card::Card(int tag){
	//std::cout << tag << std::endl << ++counter << std::endl;
    cardTag = tag;
    if (tag >= 2 && tag <= 10){
        value = tag;
    }
    else if(tag == 1){
        value = 11;
    }
    else if(tag >= 11 && tag <= 13){
        value = 10;
    }
    else{
        //std::cout << "Invalid Tag!" << std::endl;
        //exit(1);
    }
}

int Card::getValue(){
    return value;
}

int Card::getTag(){
    return cardTag;
}

bool Card::isAce(){
    if (cardTag == 1){
        return true;
    }
    return false;
}

Deck::Deck(){
	//cDeck.clear();
    cardsLeft = 0;
}

int Deck::countDeck(){
    int i, count = 0;
    for (i = 0; i < this->deckSize(); ++i){
        if (cDeck[i].getTag() != 1){ // not counting ace
            count+= cDeck[i].getValue();
        }
    }
    return count;
}

void Deck::FillRed(){
    int i; 
    for (i = 1; i < 14; ++i){
        Card *in = new Card(i);
        cDeck.push_back(*in);
        cDeck.push_back(*in);
    }
    cardsLeft = 26;
    ShuffleDeck();
}

// had to separate fill deck functions because black deck plays king at very end
void Deck::FillBlack(){
    int i;
    for (i = 1; i < 14; ++i){
        Card *in = new Card(i);
        cDeck.push_back(*in);
        if (i != 13){
            cDeck.push_back(*in);
        }
    }
    cardsLeft = 25;
    ShuffleDeck();
}

Deck::Deck(const Deck& source) {
	cDeck = source.cDeck;
	cardsLeft = source.cardsLeft;
}

void Deck::clearDeck(){
    cardsLeft = 0;
}

void Deck::ShuffleDeck(){
    assert(cardsLeft > 0 && cardsLeft <= 26);
    random_shuffle(cDeck.begin(), cDeck.end());
}

Card Deck::getCard(){
    if (cardsLeft == 0){
        std::cout << "No cards left" << std::endl;
        return NULL;
    }
    else{
		auto it = cDeck.begin();
		Card card = *it;
        std::swap(*cDeck.begin(), cDeck.back());
		cDeck.pop_back();
		cardsLeft--;
        return card;
    }
}

int Deck::deckSize(){
    return cardsLeft;
}

bool operator==(const Card& c1, const Card& c2){ //this should work for NULL checks
    if (c1.cardTag == c2.cardTag){ // just wanted to see if that would change anything since operator is declared as Card::operator== 
        return true;
    }
    return false;
}


/*
void Deck::operator=(const Deck& source){
    copy(source.cDeck.begin(), source.cDeck.end(), cDeck);
    cardsLeft = source.cardsLeft;
}
*/
bool operator!=(const Card& c1, const Card& c2){
    return !(c1 == c2);
}

Card Card::operator=(const Card& source){
    if (source == NULL){ 
        value = NULL;
        cardTag = NULL;
        return *this;
    }
    else if (this == nullptr){
        return NULL;
    }
    else{
        //std::cout << source.value << std::endl;
        value = source.value; //this causes a memory access exception
        cardTag = source.cardTag;
        return *this;
    }

}

Deck Deck::operator= (const Deck& source)
{
	//copy(source.cDeck.begin(), source.cDeck.end(), cDeck);
	cDeck = source.cDeck;
	cardsLeft = source.cardsLeft;
	return *this;
}

std::ostream& operator << (std::ostream& out, const Card c){
    switch(c.cardTag){
        case 1:
            out << "A";
            break;
        case 2:
            out << "2";
            break;
        case 3:
            out << "3";
            break;
        case 4:
            out << "4";
            break;
        case 5:
            out << "5";
            break;
        case 6:
            out << "6";
            break;
        case 7:
            out << "7";
            break;
        case 8:
            out << "8";
            break;
        case 9:
            out << "9";
            break;
        case 10:
            out << "10";
            break;
        case 11:
            out << "J";
            break;
        case 12:
            out << "Q";
            break;
        case 13:
            out << "K";
            break;
        default:
            out << "X";
            break;
    }
    return out;
}
void Deck::push_front(const Card& c) { // push card to front of deck for tie
    auto it = cDeck.begin();
    cDeck.insert(it,c);
}


