/*

FILE NAME: card.cpp
Written by: Nik Srinivas
Date: 4/17/2020

*/

#include "card.h"
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

Card::Card() {
	mySuit = spades;
	myRank = 1;
}

Card::Card(int rank, Suit s) {
	mySuit = s;
	myRank = rank;
}

int Card::getRank() const {
	return myRank;
}
int Card::getSuit() const {
	return mySuit;
}
string Card::suitString(Suit s) const {
	if (s == spades)
		return "s";
	else if (s == hearts)
		return "h";
	else if (s == diamonds)
		return "d";
	else if (s == clubs)
		return "c";
}
string Card::rankString(int r) const {
	if (r == 1)
		return "A";
	else if (r == 2)
		return "2";
	else if (r == 3)
		return "3";
	else if (r == 4)
		return "4";
	else if (r == 5)
		return "5";
	else if (r == 6)
		return "6";
	else if (r == 7)
		return "7";
	else if (r == 8)
		return "8";
	else if (r == 9)
		return "9";
	else if (r == 10)
		return "10";
	else if (r == 11)
		return "J";
	else if (r == 12)
		return "Q";
	else if (r == 13)
		return "K";
}
string Card::toString() const {
	return (rankString(myRank) + suitString(mySuit));
}
bool Card::sameSuitAs(const Card& c) const{
	if (mySuit == c.mySuit) {    
		return true;
	}
	else {
		return false;
	}
}

bool Card::operator== (const Card& rhs) const {
	if ((myRank == rhs.myRank) && (mySuit == rhs.mySuit))
		return true;
	else
		return false;
};
// I don't know why we need both of these, seems like != is redundant 
bool Card::operator!= (const Card& rhs) const {
	if ((myRank == rhs.myRank) && (mySuit == rhs.mySuit))
		return false;
	else
		return true;
};


ostream& operator << (ostream& out, const Card& c)
{
	out << c.toString();
	return out;
}



