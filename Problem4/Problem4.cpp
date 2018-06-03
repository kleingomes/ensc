// ENSC482 - Problem 4
// Created by Klein Gomes on 2018-05-27.
// Copyright © 2018 Klein Gomes. All rights reserved.
//
// Problem 4 (20) 
// If you play roulette and bet on a single number, the probability of winning is 1 / 38. If the ball lands on the number you have chosen the 
// croupier will pay you 35 times the amount betted, and return the bet.Write a program which can simulate this game.
// Formalize and visualize the decision problem in decision matrix.
// Formalize and visualize the decision problem in a decision tree.
// Draw the decision tree using OpenGL and proposed a visualization approach which can 
// show the results of the game as a function of the amount betted. Supply the source code and sample results.



#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <ctime>
#include <Random>

int spin()
{
	return rand() % (38 - 1 + 1) + 1;
}

double getWinAmount(double betAmount)
{
	return betAmount * 35;
}

void printDecisionTree()
{

}

int main()
{
	double betAmount;
	int numberChosen;
	srand(time(0));
	std::cout << "How much would you like to bet: ";
	std::cin >> betAmount;
	do
	{
		std::cout << std::endl << "Enter a number between 1 and 38 (For 0 enter 37. For 00 enter 38): ";
		std::cin >> numberChosen;
	} while (numberChosen <= 0 || numberChosen > 38);

	std::cout << std::endl << "Wheel is Spinning!";
	int result = spin();
	if (numberChosen == result)
	{
		std::cout << std::endl << std::endl << "You win! Payout: $" << getWinAmount(betAmount);
	}
	else
	{
		std::cout << std::endl << std::endl << "Landed on " << result << ". You lose!";
	}
	
	// Part A) Decision Matrix
	std::cout << std::endl << std::endl << "Decision Matrix:";
	std::cout << std::endl << "Lands on picked number | Bet Amount | Profit";
	std::cout << std::endl << "-------------------------------------------------------------------";
	std::cout << std::endl << "true                   | " << betAmount << "         | " << getWinAmount(betAmount);
	std::cout << std::endl << "false                  | " << betAmount << "         |-" << betAmount;
	std::cout << std::endl << "-------------------------------------------------------------------";

	// Part B) Decision Tree


	std::cin >> numberChosen;
    return 0;
}

