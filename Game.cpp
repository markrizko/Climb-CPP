#include "Game.h"
// TODO fix endgame -- KEEP CHECKING IF FIXED
// TODO implement score mechanic (caluclate cards left at the end of run, +5 for king victory)
// TODO create rules README
Game::Game(){
redDeck = new Deck();
blackDeck = new Deck();

redDeck->FillRed();
blackDeck->FillBlack();

//fill playspace
Draw();
redNumIP = 0;
blackNumIP = 0;
ValidMove = false;
initFlag = true;
gameOver = false;
}

bool Game::finalEncounter() {
    Card King(13);
    std::cout << "\n\n\t\tTime to face the King\t\t\n\n";
    blackInPlay[1] = King;
    Draw();
    displayCards();
    select();
    if (compare() == 4 || compare() == 6 || compare() == 1){
        if (compare() == 6){
            std::cout << "\nKing Victory\t\t+5 Points\n";
        }
        return true;
    }
    return false;
}

void Game::endGame(){
    if (winner){
        if (finalEncounter()){
            std::cout << "You win!" << std::endl;
        }
        else{
            std::cout << "You lose!" << std::endl;
        }
    }
    else{
        std::cout << "You lose!" << std::endl;
    }
    return;
}

bool Game::blackWin(){
    if (redDeck->deckSize() > 0){
        return false; // assert
    }
    int rsum = 0, bsum = 0, rtag = 0, btag = 0;
    bool aceflag = false;
    for (int i = 0; i < 3; ++i){
        if (redInPlay[i].getTag() == 1){
            aceflag = true;
            break;
        }
        bsum += blackInPlay[i].getValue();
        btag += blackInPlay[i].getTag();
        rsum += redInPlay[i].getValue();
        rtag += redInPlay[i].getTag();
    }
    if (aceflag){
        return false; // red has chance on ace
    }
    else if (bsum > rsum){
        return true; // red has no chance mathematically
    }
    else if (rsum > bsum){
        return false; // red has a chance
    }
    else if (rsum == bsum){
        if (btag > rtag){
            return true; // red still has seniority
        }
        else{
            return false;
        }
    }
}


int Game::checkWin() {
    if (
            (blackInPlay[0] == NULL && blackInPlay[1] == NULL && blackInPlay[2] == NULL)
            && (blackDeck->deckSize() == 0)
            ){
        winner = true;
        gameOver = true;
        return 0; // red wins
    }
    else if (blackWin()){
        winner = false;
        gameOver = true;
        return 1; // black wins
    }
    else{
        return 7; // can be arbitrary, no win yet
    }
}

void Game::runGame(){
    while (!gameOver){
        ValidMove = false; // invalid until proven valid
        while(!ValidMove){
            displayCards();
            Turn();
        }
    }
    endGame();
    return;
}

void Game::Draw(){
        if (redDeck->deckSize() != 0){
            for (int i = 0; i < 3; i++){
                if (redInPlay[i] == NULL){
                    redInPlay[i] = redDeck->getCard();
                }
            }
        }
        if (blackDeck->deckSize() != 0) {
            for (int j = 0; j < 3; j++) {
                if (blackInPlay[j] == NULL) {
                    blackInPlay[j] = blackDeck->getCard();
                }
            }
        }
}



int Game::Tie(){ // 0 if tie again, 1 if win, 2 if lose
    if (blackDeck->deckSize() == 0){
        return 1;
    }
    Card red = redDeck->getCard();
    Card black = blackDeck->getCard();
    /*if (black == NULL){
        return 5;
    }*/
    std::cout << "\nTie: Red " << red << " vs. Black " << black << std::endl;
    if (red.getTag() == 1){
        return 4; // ace wipe in tie
    }
    if (red.getValue() == black.getValue()){
        if (red.getTag() > black.getTag()){
            return 1; // win by seniority
        }
        else if (red.getTag() < black.getTag()){
            blackDeck->push_front(black); // black card stays after winning tie
            return 2; // loss by seniority
        }
        else{
            return 0; //tie
        }
    }
    else if (red.getValue() < black.getValue()){
        blackDeck->push_front(black);
        return 2; // loss by value
    }
    else{
        return 1; // win
    }

	return 0;
}



void Game::Turn(){
	// fill selectedArrays
	select();
    int tres;
	int result = compare();
	if (result == 2){ // if tie, call Tie()
		do {
			tres = Tie();
		}
		while(tres == 0);
	}
	else if (result == 0){ // if invalid clear and quit
	    selectedRed.clear();
	    selectedBlack.clear();
	    std::cout << "********INVALID MOVE********" << std::endl;
	    return;
	}
	if (result == 4 || tres == 4){
	    for (int x = 0; x < 3; ++x){
	        blackInPlay[x] = NULL;
	    }
	}
        // after that, remove cards from redInPlay and blackInPlay
        for (std::list<int>::iterator i = selectedRed.begin(); i != selectedRed.end(); ++i){
            redInPlay[*i] = NULL;
        }
        for (std::list<int>::iterator j = selectedBlack.begin(); j != selectedBlack.end(); ++j){
            blackInPlay[*j] = NULL;
        }
	selectedRed.clear();
	selectedBlack.clear();
	int q = checkWin();
	if (q == 0 || q == 1){
	    // if red wins or black wins
	    return;
	}
	else{
	    Draw();
	}
	return;
}




int Game::redTotal(){//dont  need an argument, turn is already a class variable
    int sum = 0;
    for (std::list<int>::iterator i = selectedRed.begin(); i != selectedRed.end(); ++i){
        // FIX with iterator for selectedRed/Black list
        sum+=(redInPlay[*i].getValue());
    }
    return sum;
}
int Game::blackTotal(){
    int sum = 0;
    for (std::list<int>::iterator i = selectedBlack.begin(); i != selectedBlack.end(); ++i){
        // FIX with iterator for selectedRed/Black list
        sum+=(blackInPlay[*i].getValue());
    }
    return sum;
}

int Game::compare(){
    if (redInPlay[*selectedRed.begin()].getTag() == 1){
        std::cout << "ACE WIPE\n";
        return 4; // ace wipe
    }
    else if (redInPlay[*selectedRed.begin()].getTag() == 13 && blackInPlay[*selectedBlack.begin()].getTag() == 13){
        return 6; // king tie, no tie is played both cards are discarded, return value arbitrary
    }
    if ((redTotal() < blackTotal())){
        // invalid move
        return 0;
    }
    else if ((redTotal() == blackTotal())){
        // getting highest tag
        int r_tag = 0, b_tag = 0;
        for(std::list<int>::iterator i = selectedRed.begin(); i != selectedRed.end(); ++i){
            if (redInPlay[*i].getTag() > r_tag){
                r_tag = redInPlay[*i].getTag();
            }
        }
        for(std::list<int>::iterator i = selectedBlack.begin(); i != selectedBlack.end(); ++i){
            if (blackInPlay[*i].getTag() > b_tag){
                b_tag = blackInPlay[*i].getTag();
            }
        }
        if (r_tag > 10 || b_tag > 10){
            if (r_tag == b_tag){
                return 2; // tie
            }
            else if (r_tag > b_tag){
                return 1; // win
            }
            else{
                return 0; // invalid move
            }
        }
        else{
            return 2;
        }
    }

    else if ((redTotal() > blackTotal())){
        ValidMove = true;
        return 1; // win
    }
    else{
        return 0; // if any of these cases don't fit (which may be impossible but just in case)
    }
}

void Game::select(){
    char input;
    bool flag = true;
    std::cout << "\nSelect Red: ";
        while (flag){
        std::cin >> input;
        switch(input){
            case '1':
                selectedRed.push_back(0);
                redNumIP++;
                break;
            case '2':
                selectedRed.push_back(1);
                redNumIP++;
                break;
            case '3':
                selectedRed.push_back(2);
                redNumIP++;
                break;
            case '.':
                flag = false;
                break;
            case 'x':
                blackDeck->clearDeck();
                break;
            default:
                std::cout << "Invalid\n";
                break;

        }
    }
    flag = true;
    std::cout << "Select Black: ";
    while (flag){
        std::cin >> input;
        switch(input){
            case '1':
                selectedBlack.push_back(0);
                blackNumIP++;
                break;
            case '2':
                selectedBlack.push_back(1);
                blackNumIP++;
                break;
            case '3':
                selectedBlack.push_back(2);
                blackNumIP++;
                break;
            case '.':
                flag = false;
                break;
            case 'x':
                redDeck->clearDeck();
                break;
            default:
                std::cout << "Invalid\n";
                break;

        }
    }
    return;
}
void Game::displayCards() {
    std::cout<< "\t\tK\t\t\tBlack Cards Left: " << blackDeck->deckSize() << std::endl;
    std::cout << "Black: " << std::endl;
    std::cout <<"\t" << blackInPlay[0] << "\t" << blackInPlay[1] << "\t" << blackInPlay[2] << std::endl;
    std::cout << "Red: " << std::endl;
    std::cout << "\t" << redInPlay[0] << "\t" << redInPlay[1] << "\t" << redInPlay[2] << std::endl;
    std::cout << "\nRed Cards Left: " << redDeck->deckSize() << std::endl;
}

