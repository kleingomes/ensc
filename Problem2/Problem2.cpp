// ENSC482 - Problem 2
// Created by Klein Gomes on 2018-05-20.
// Copyright © 2018 Klein Gomes. All rights reserved.
//
// Problem 2(20)  
// Write a sorting algorithm using the provided tutorial. Show the result of the algorithm using two examples. 
// For one of the examples, sort the letters of your full name given that you associated numerical values to the 
// alphabets (i.e. A=1, B=2, C=3, …). The other example is to sort and stack 4 graphical blocks according to their 
// R value in their RGB color deceleration. The initial screen is the user specified colors of the random stack of 
// block and the final screen is the sorted stack. Supply the source code and sample results.

#include "stdafx.h"
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

void quickSort(int arr[], int low, int high);
char alphabet[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

// Globals
int red1 = 0;
int red2 = 0;
int red3 = 0;
int red4 = 0;


// Provided tutorial: This function was taken from the Introduction to Decision Theory PDF
void quickSort(int arr[], int left, int right) {
	int i = left, j = right;
	int tmp;
	int pivot = arr[(left + right) / 2];
	// partition
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	// recursion
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

void drawBlock(double x1, double y1, GLdouble red)
{
	glColor3d(red/255.0, 0, 0);
	glBegin(GL_POLYGON);
	double side = 0.2;
	glVertex2d(x1 + side, y1 + side);
	glVertex2d(x1 + side, y1 - side);
	glVertex2d(x1 - side, y1 - side);
	glVertex2d(x1 - side, y1 + side);
	glEnd();
}

void drawBlocks(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Unsorted
	drawBlock(0.0, -0.8, (double)red1);
	drawBlock(0.0, -0.4, (double)red2);
	drawBlock(0.0, 0.0, (double)red3);
	drawBlock(0.0, 0.4, (double)red4);

	// Sorted
	int sorted[4] = { red1,red2,red3,red4 };
	quickSort(sorted, 0, 3);
	drawBlock(0.5, -0.8, (double)sorted[0]);
	drawBlock(0.5, -0.4, (double)sorted[1]);
	drawBlock(0.5, 0.0, (double)sorted[2]);
	drawBlock(0.5, 0.4, (double)sorted[3]);

	glFlush();
}

void part1() {
	int charsAsInt[26];
	int n = 0;
	char myName[19] = { 'K','L','E','I','N',' ','A','N','T','H','O','N','Y',' ','G','O','M','E','S' };
	std::system("cls");
	cout << "Example 1: Quick Sort Full Name" << endl << endl << "Full Name: Klein Anthony Gomes" << endl << endl;
	cout << "Initial Array:" << endl;

	// Loop will print my name
	for (int i = 0; i < 19; i++)
	{
		cout << myName[i] << " ";
	}
	cout << "" << endl << endl;

	// Loop will iterate through myName and assign an integer value for each character 
	for (int i = 0; myName[i] != '\0'; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (myName[i] == alphabet[j])
			{
				charsAsInt[n] = j;
				n++;
				break;
			}
		}
	}
	cout << "Initial Array As Integers:" << endl;

	// Loop will print my name as integers
	for (int i = 0; i < n; i++)
	{
		cout << charsAsInt[i] << " ";
	}
	cout << endl;

	quickSort(charsAsInt, 0, n - 1);
	cout << endl << "Sorted Array: " << endl;

	// Loop will print my name as sorted characters 
	for (int i = 0; i < n; i++)
	{
		cout << alphabet[charsAsInt[i]] << " ";
	}
	cout << endl;
}

void part2(int argc, char** argv)
{
	string block1;
	string block2;
	string block3;
	string block4;

	cout << endl << endl << "Enter RGB value now as int for block 1 e.g. 255255255: ";
	getline(cin, block1);
	cout << "Red Value: " << block1[0] << block1[1] << block1[2];
	cout << endl << endl << "Enter RGB value now as int for block 2 e.g. 255255255: ";
	getline(cin, block2);
	cout << "Red Value: " << block2[0] << block2[1] << block2[2];
	cout << endl << endl << "Enter RGB value now as int for block 3 e.g. 255255255: ";
	getline(cin, block3);
	cout << "Red Value: " << block3[0] << block3[1] << block3[2];
	cout << endl << endl << "Enter RGB value now as int for block 4 e.g. 255255255: ";
	getline(cin, block4);
	cout << "Red Value: " << block4[0] << block4[1] << block4[2];

	red1 = atoi(block1.substr(0, 3).c_str());
	red2 = atoi(block2.substr(0, 3).c_str());
	red3 = atoi(block3.substr(0, 3).c_str());
	red4 = atoi(block4.substr(0, 3).c_str());

	int redArray[4] = { red1, red2, red3, red4 };

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Problem 2: Klein Gomes");
	glutDisplayFunc(drawBlocks);
	glutMainLoop();
}

int main(int argc, char** argv)
{
	part1();
	part2(argc, argv);
	int wait;
	cin >> wait;
}