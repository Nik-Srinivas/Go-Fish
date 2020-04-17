/*

FILE NAME: player.cpp
Written by: Nik Srinivas

*/

#include "player.h"
#include "card.h"
#include "deck.h"

#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <string>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <vector>

Player::Player() {
	myName = "";
}

//adds a card to the hand
void Player::addCard(Card c) {
	myHand.push_back(c);
}

//makes a book or pair of cards if possible
//adds to the book vector for that player
void Player::bookCards(Card c1, Card c2) {

	//add the cards to the myBooks vector
	myBook.push_back(c1);
	myBook.push_back(c2);

	
}


//this function will check a players hand for a pair. 
//If a pair is found, it returns true and populates the two variables with the cards tha make the pair.
bool Player::checkHandForBook(Card& c1, Card& c2) {
	for (int i = 0; i < myHand.size(); i++) {
		Card c = myHand[i];//card 1
		if (rankInHand(c)) { 
			for (int j = 0; j < myHand.size(); j++) { 
				Card n = myHand[j];// card 2
				if (n.getRank() == c.getRank() && n != c) {
					c1 = c;
					c2 = n;
					return true;
				}
			}
		}
	}
	return false;
}; 

// comment out if you decide to not use it    
//Does the player have a card with the same rank as c in her hand?
bool Player::rankInHand(Card c) const {
	for (int i = 0; i < myHand.size(); i++) { 
		Card j = myHand[i];
		if ((j.getRank() == c.getRank()) && (j != c)) {
			return true;
		}
	}	
	return false;	
}; 


//uses some strategy to choose one card from the player's
//hand so they can say "Do you have a 4?"
Card Player::chooseCardFromHand() const {
	srand(time(NULL)); 
	Card c;  
	int counter = 0;
	
	if (myHand.size() != 0) {
		counter = rand() % myHand.size();
		c = myHand.at(counter);
	}
	return (c);

};


//Does the player have the card c in her hand?
bool Player::cardInHand(Card c) const {
	for (int i = 0; i < myHand.size(); i++) {
		if (myHand[i] == c) {
			return true;
		}
	}

	return false;
};


//Remove the card c from the hand and return it to the caller
Card Player::removeCardFromHand(Card c) {
	Card seeking;

	for (vector<Card>::iterator it = myHand.begin(); it != myHand.end(); it++) {
		if (it->getRank() == c.getRank() && it->sameSuitAs(c)) {
			seeking = *it;  //assignment operator for card needed
			myHand.erase(it);
			return seeking;
		}
	}
}
//make edits

string Player::showHand() const {
	string hand = "";
	for (int i = 0; i < myHand.size(); i++) {
		hand = hand + myHand[i].toString() + " ";//add space every time
	}
	return hand;
}

string Player::showBooks() const {
	string Book = ""; //starts empty
	for (int i = 0; i < myBook.size(); i++) {
		Book = Book + myBook[i].toString() + " "; //same deal, gotta have a space
	}
	return Book;
}


//returns the number of cards in hand vector
int Player::getHandSize() const {
	return myHand.size();
}


//returns the number of books in book vector
int Player::getBookSize() const {
	return myBook.size() / 2;
}


//OPTIONAL
// comment out if you decide to not use it
//this function will check a players hand for a pair. 
//If a pair is found, it returns true and populates the two variables with the cards tha make the pair.

//bool Player::checkHandForPair(Card& c1, Card& c2) {};

//OPTIONAL
// comment out if you decide to not use it    
//Does the player have a card with the same rank as c in her hand?
//e.g. will return true if the player has a 7d and the parameter is 7c

//bool Player::sameRankInHand(Card c) const {};