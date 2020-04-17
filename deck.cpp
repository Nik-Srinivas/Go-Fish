/*

FILE NAME: deck.cpp
Written by: Nik Srinivas

*/

#include "deck.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <time.h>
#include <stdlib.h>

using namespace std;

Deck::Deck() {
	myIndex = 0;

	//Creates playable deck
	for (int i = 0; i < 4; i++) { // for each suit
		for (int j = 0; j < 13; j++) { // for each number
			Card c(j + 1, Card::Suit(i)); //creates card with number and suit
			myCards[myIndex] = c;
			myIndex++;
		}
	}
	myIndex = 0; //resets index so it doesn't keep old card amount number
}
void Deck::shuffle() {
	srand(time(NULL));
	for (int i = 0; i < SIZE; i++) {
		int r_n = rand() % SIZE;

		Card temp = myCards[r_n];
		myCards[r_n] = myCards[i];
		myCards[i] = temp;
	}

}
Card Deck::dealCard() {
	if (size() != 0) {
		Card c = myCards[myIndex];
		myIndex++;
		return c;
	}
}
int Deck::size() const {
	return (52 - myIndex);

}


