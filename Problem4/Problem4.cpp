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
#include <random>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

double amount = 10;
int chosen = 15;

int spin()
{
	return rand() % (38 - 1 + 1) + 1;
}

double getWinAmount(double betAmount)
{
	return betAmount * 35;
}

void drawBlock(double x1, double y1, GLdouble red)
{
	glColor3d(red / 255.0, 0, 0);
	glBegin(GL_POLYGON);
	double side = 0.05;
	glVertex2d(x1 + side, y1 + side);
	glVertex2d(x1 + side, y1 - side);
	glVertex2d(x1 - side, y1 - side);
	glVertex2d(x1 - side, y1 + side);
	glEnd();
}

void printDecisionTree(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Start Point
	drawBlock(-0.75, 0.0, 255);


	glFlush();
}


int main(int argc, char** argv)
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
	std::cout << std::endl << "Lands on picked number | Bet Amount | $ Rturned";
	std::cout << std::endl << "-------------------------------------------------------------------";
	std::cout << std::endl << "true                   | " << betAmount << "         | " << getWinAmount(betAmount) + betAmount;
	std::cout << std::endl << "false                  | " << betAmount << "         |-" << betAmount;
	std::cout << std::endl << "-------------------------------------------------------------------";
	amount = betAmount;
	chosen = numberChosen;

	// Part B) Decision Tree
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Problem 4: Klein Gomes");
	glutDisplayFunc(printDecisionTree);
	glutMainLoop();
	int x;
	std::cin >> x;
    return 0;
}

