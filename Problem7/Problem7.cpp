// ENSC482 - Problem 7
// Created by Klein Gomes on 2018-05-27.
// Copyright © 2018 Klein Gomes. All rights reserved.
//

// Problem 7 (25) – Write a program(in C++) in finding the mixed strategy Nash equilibrium of the following 2x2 game : first row : (2, -3); (1, 2), second row : (1, 1); (4, -1).
// Determine the payoffs of each player at this equilibrium.Similar to sample lecture problem, use OpenGL to visualize the results.

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include<process.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <ctime>
#include <random>
#include <iostream>
#include <cstdlib>
#include <conio.h>

// Takes a string and coordinate pair and draws on window
void drawText(const char *string, int x, int y)
{	
	glRasterPos2f(x, y);
	for (const char *character = string; *character != '\0'; character++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *character);
	}
}

// Prints using OpenGl
void print()
{
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(1.0, 0.0, 0.0);     
	int start = 150;
	drawText("     |         1,2           |", 5, start);
	drawText("     |    L     |    R       |", 5, start - 8);
	drawText("     |------------------------", 5, start - 16);
	drawText("  U  |   2,-3   |   1,2      |", 5, start - 24);
	drawText("  d  |   1,1    |   4,-1     |", 5, start - 32);

	drawText("P1 L probability 0.75 'R' probability 0.25", 5, start -50);
	drawText("P2 U probability 0.28 'D' probability 0.71", 5, start - 60);
	drawText("P1 1.75 ", 5, start - 70);
	drawText("P2 -0.142857 ", 5, start - 80);
	glFlush();
}


void main(int argc, char** argv)
{
	
	double row1[4] = { 2, -3, 1, 2 };
	double row2[4] = { 1, 1, 4, -1 };

	std::cout << "     |         1,2           |" << std::endl;
	std::cout << "     |    L     |    R" << std::endl;
	std::cout << "     |------------------------" << std::endl;
	std::cout << " U   |     " << row1[0] << "," << row1[1] << "|   " << row1[2] << "," << row1[3] << std::endl;
	std::cout << " D   |    " << row1[0] << "," << row1[1] << " |   " << row1[2] << "," << row1[3] << std::endl << std::endl;

	double p = (row2[2] - row1[2]) / ((row1[0] - row1[2]) - (row2[0] - row2[2]));
	double q = (row2[3] - row2[1]) / ((row1[1] - row2[1]) - (row1[3] - row2[3]));
	
	std::cout << "P1 L probability " << p << " using 'R' probability " << 1 - p << std::endl << std::endl;;
	std::cout << "P2 U probability " << q << " using 'D' probability " << 1 - q << std::endl << std::endl;;

	// Find Nash for both players
	double p1n = row1[0] * p + row1[2] * (1 - p);
	double p2n = row2[1] * q + row2[1] * (1 - q);

	std::cout << "P1: " << p1n << std::endl;
	std::cout << "P2: " << p2n << std::endl;
	glutInit(&argc, argv);                       
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowPosition(650, 200);     
	glutInitWindowSize(900, 600);         
	glutCreateWindow("Problem 7: Klein Gomes");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 300.0, 0.0, 250.0);
	glClearColor(1.0, 1.0, 1.0, 0.0);                              
	glutDisplayFunc(print);         
	glutMainLoop();                       
	
	int wait;
	std::cin >> wait;
}

