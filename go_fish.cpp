// This is the main driver file for GoFish
// Nik Srinivas


#include "card.h"
#include "player.h"
#include "deck.h"

#include <iostream>   
#include <cstdlib>     
#include <fstream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

// need a standard dealHand function
void dealHand(Deck& d, Player& p, int handSize);


int main() {

	// Output log file and variable initializations
	ofstream gameLog("gofish_results.txt");

	int handSize = 7; 
	int turnFlag;
	bool truthCondition;

	Card c1; //playing cards
	Card c2; 

	Card n1; //logic cards
	Card swap;
	Card n2;

	// This is to debug basically
	if (gameLog.is_open()) {
		cout << "Nik and Michael are playing go fish, check log after 5 seconds" << endl;
	}
	else {
		// Common error was file name or location was wrong
		cout << "Error: Check name of output file in directory" << endl;
	}

	//Initialize players
	Player p1("Nik"); 
	gameLog << "player 1 is: " << p1.getName() << "\n";
	Player p2("Michael");
	gameLog << "player 2 is: " << p2.getName() << "\n\n";

	 //create shuffled game deck,new game statements
	gameLog << "Welcome to high stakes (my grade lol) Go Fish!  ";
	gameLog << "The cards are all shuffled... \n";
	
	Deck d; 
	d.shuffle();
	
	dealHand(d, p1, handSize); 
	dealHand(d, p2, handSize);
	gameLog << "Each player has been dealt their starting 7 cards! \n";

	gameLog << p1.getName() << "'s cards are: " << p1.showHand() << "\n"; 
	gameLog << p2.getName() << "'s cards are: " << p2.showHand() << "\n";

	gameLog <<  "\nBoth players are booking their dealt pairs\n\n";
	
	// 2 loops to book OG pairs
	while (p1.checkHandForBook(c1, c2)) { 
		p1.bookCards(p1.removeCardFromHand(c1), p1.removeCardFromHand(c2)); 
	}
	while (p2.checkHandForBook(c1, c2)) { 
		p2.bookCards(p2.removeCardFromHand(c1), p2.removeCardFromHand(c2)); 
	}

	// 1st Display State
	gameLog << p1.getName() << "'s remaining cards are: " << p1.showHand() << "\n"; 
	gameLog << p2.getName() << "'s remaining cards are: " << p2.showHand() << "\n";
	gameLog << p1.getName() << "'s starting books are: " << p1.showBooks() << "\n"; 
	gameLog << p2.getName() << "'s starting books are: " << p2.showBooks() << "\n";

	while ((d.size() > 0) && (p1.getHandSize() > 0) && (p2.getHandSize() > 0)) { // Loop conditons: deck not empty or hand size not empty

		gameLog << p1.getName() << "'s turn\n";
		turnFlag = 0;

		// Player 1 logic
		do {
			if (turnFlag == 1) {
				gameLog << p1.getName() << " gets to draw again!\n";
			}
			if (p1.getHandSize() > 0) {

				n1 = p1.chooseCardFromHand(); 
				turnFlag = 0; 
				gameLog << p1.getName() << " asks - Do you have a " << n1.rankString(n1.getRank()) << "?\n";

				truthCondition = p2.cardInHand(n1); 

				if (truthCondition == true) { 

					gameLog << p2.getName() << " says - Yes. I have a " << n1.rankString(n1.getRank()) << "\n";
					swap = p2.removeCardFromHand(n1); 
					p1.addCard(swap); 

					if (p1.checkHandForBook(c1, c2)) { 

						gameLog << p1.getName() << " books the " << n1.rankString(n1.getRank()) << "\n";
						p1.bookCards(p1.removeCardFromHand(c1), p1.removeCardFromHand(c2)); 
					}

					gameLog << "\n" << p1.getName() << "'s hand is: " << p1.showHand() << "\n";
					gameLog << p2.getName() << "'s hand is: " << p2.showHand() << "\n";
					gameLog << p1.getName() << "'s books: " << p1.showBooks() << "\n";
					gameLog << p2.getName() << "'s books: " << p2.showBooks() << "\n\n";
					
					// can play again
					turnFlag = 1; 
				}
			}
		} while (turnFlag == 1 && p1.getHandSize() > 0); //doWhile runs loop at least once before checking condition

		if (p1.getHandSize() > 0 && truthCondition == false) {
			gameLog << p2.getName() << " says - Go Fish!\n";

			if (d.size() > 0) {
				n2 = d.dealCard();
				p1.addCard(n2); 
				gameLog << p1.getName() << " draws " << n2.toString() << "\n";
			}
			else {
				gameLog << p1.getName() << ": No cards left to draw\n";
				break;
			}

		}
		while (p1.checkHandForBook(c1, c2)) { 
			p1.bookCards(p1.removeCardFromHand(c1), p1.removeCardFromHand(c2));
		}
		if (p1.getHandSize() == 0) {
			gameLog << p1.getName() << " has no cards left in hand\n";

			if (d.size() > 0) {
				n2 = d.dealCard();
				p1.addCard(n2); 
				gameLog << p1.getName() << " draws " << n2.toString() << "\n";
			}
			else {

				gameLog << p1.getName() << ": No cards left to draw\n";
				break;
			}

		}
		while (p1.checkHandForBook(c1, c2)) { 
			p1.bookCards(p1.removeCardFromHand(c1), p1.removeCardFromHand(c2)); 
		}

		gameLog << "\n" << p1.getName() << "'s hand is: " << p1.showHand() << "\n";
		gameLog << p2.getName() << "'s hand is: " << p2.showHand() << "\n";
		gameLog << p1.getName() << "'s books: " << p1.showBooks() << "\n";
		gameLog << p2.getName() << "'s books: " << p2.showBooks() << "\n\n";

		// Player 2 logic      
		turnFlag = 0; //resets flag
		gameLog << p2.getName() << "'s turn\n";

		do {
			if (turnFlag == 1) {
				gameLog << p2.getName() << " goes again\n";
			}
			if (p2.getHandSize() > 0) {
				n1 = p2.chooseCardFromHand(); 
				turnFlag = 0; 
				gameLog << p2.getName() << " asks - Do you have a " << n1.rankString(n1.getRank()) << "?\n";

				truthCondition = p1.cardInHand(n1); // check

				if (truthCondition == true) { 

					gameLog << p1.getName() << " says - Yes. I have a " << n1.rankString(n1.getRank()) << "\n";
					swap = p1.removeCardFromHand(n1); 
					p2.addCard(swap); 

					if (p2.checkHandForBook(c1, c2)) { 

						gameLog << p2.getName() << " books the " << n1.rankString(n1.getRank()) << "\n";
						p2.bookCards(p2.removeCardFromHand(c1), p2.removeCardFromHand(c2)); 
					}
					gameLog <<"\n"<< p1.getName() << "'s hand is: " << p1.showHand() << "\n";
					gameLog << p2.getName() << "'s hand is: " << p2.showHand() << "\n";
					gameLog << p1.getName() << "'s books: " << p1.showBooks() << "\n";
					gameLog << p2.getName() << "'s books: " << p2.showBooks() << "\n\n";

					turnFlag = 1; 
				}
			}
		} while (turnFlag == 1 && p2.getHandSize() > 0);

		if (p2.getHandSize() > 0 && truthCondition == false) {

			gameLog << p1.getName() << " says - Sux 2 suck, Go Fish!\n";

			if (d.size() > 0) {
				n2 = d.dealCard();
				p2.addCard(n2); 
				gameLog << p2.getName() << " draws " << n2.toString() << "\n";
			}
			else {
				gameLog << p2.getName() << ": No cards left in pile\n";
				break;
			}
		}
		while (p2.checkHandForBook(c1, c2)) { 
			p2.bookCards(p2.removeCardFromHand(c1), p2.removeCardFromHand(c2)); 
		}
		if (p2.getHandSize() == 0) {

			gameLog << p2.getName() << " has no cards left in hand\n";

			if (d.size() > 0) {
				n2 = d.dealCard();
				p2.addCard(n2); 
				gameLog << p2.getName() << " draws " << n2.toString() << "\n";
			}
			else {
				gameLog << p2.getName() << ": No cards left in stack\n";
				break;
			}
		}
		while (p2.checkHandForBook(c1, c2)) { 
			p2.bookCards(p2.removeCardFromHand(c1), p2.removeCardFromHand(c2)); 
		}

		gameLog << "\n" << p1.getName() << "'s hand is: " << p1.showHand() << "\n";
		gameLog << p2.getName() << "'s hand is: " << p2.showHand() << "\n";
		gameLog << p1.getName() << "'s books: " << p1.showBooks() << "\n";
		gameLog << p2.getName() << "'s books: " << p2.showBooks() << "\n\n";

	}

	// GAME OVER Output   
	cout << "Game is over, gameLog is in output file -> 'gofish_results.txt'\n\n";

	// Player 1 Endgame Output
	if (p1.getBookSize() > p2.getBookSize()) { 
		gameLog << p1.getName() << " is the winner!" << endl;
	}

	// Player 2 Endgame Output
	if (p1.getBookSize() < p2.getBookSize()) { 
		gameLog << p2.getName() << " is the winnner!" << endl;
	}

	// Condtions for a tie
	if (p1.getBookSize() == p2.getBookSize()) {
		gameLog << "The game between " << p1.getName() << " and " << p2.getName() << " ends in a draw!" << endl;
	}

	gameLog.close();
	return EXIT_SUCCESS;
}
void dealHand(Deck& d, Player& p, int handSize) {
	for (int i = 0; i < handSize; i++) {
		p.addCard(d.dealCard());
	}
}



