#pragma once
#include <stack>
#include <iostream>
#include "Card.h"

class Game
{
public:
	Game();
	// bool init();
	void runGame();
	// void endGame();
		//Will take a card from the inputed deck
		//Then remove said card from deck, putting it into play
	//
	// Game Operations
	void Draw();
	int Tie(); // 0 if tie again, 1 if win, 2 if lose
	void Turn(); 
	int compare(); // compares cards - returns 0 if invalid move - 1 if win - 2 if draw
	void select();
	void endGame();
	int checkWin();
	void displayCards();
	bool blackWin(); // checks for invalid moves if deck is 0
private:
	int redTotal();
	int blackTotal();
	bool gameOver; // true when an end condition is met
	bool winner;
	Deck *redDeck;
	Deck *blackDeck;
	std::list <int> selectedRed;
	std::list <int> selectedBlack;
	//Deck of cards 
	Card redInPlay[3];
	int redNumIP; // # of red cards in play
	Card blackInPlay[3];
	int blackNumIP; // # of black cards in play
		//Card arrays to hold cards in play

	bool ValidMove;
	bool initFlag;
};