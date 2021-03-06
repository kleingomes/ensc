// ENSC482 - Set 2 Problem 1
// Created by Klein Gomes on 2018-05-27.
// Copyright © 2018 Klein Gomes. All rights reserved.
//

// Problem 1 (30) – By referring to any known public dataset(some examples are listed below but you are free to reference to any other known sources), 
// write a program in Visual C++ that takes the dataset as an input file and computes the histogram of the data.Visualize the histogram data using OpenGL.
// Compute the mean and the variance of the distribution and overlay and visualize the expression for its univariate Gaussian distribution.
// Given two such histogram, compute the Bhattacharyya distance between them. Include the selected input dataset as a part of your submission.
// Include a short write - up discussing the results.

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#define VALUE 30.0      
#define LEFT (VALUE - VALUE - 1) 
#define RIGHT VALUE
#define BOTTOM (VALUE - VALUE - 1)
#define TOP VALUE


using namespace std;

vector <vector <float>> histogramBuckets;

vector <float> ageColumn;

float avg;

float variance;

vector <vector <string>> readFile() {
	vector <vector <string>>  row;
	// Read the File

	ifstream infile("C:\\repo\\ensc-482\\Set2Problem1\\Debug\\titanic.csv");
	while (infile)
	{
		string s;
		if (!getline(infile, s))
		{
			break;
		}
		istringstream ss(s);
		vector <string> columns;
		while (ss)
		{
			string s;
			if (!getline(ss, s, ','))
			{
				break;
			}
			columns.push_back(s);
		}
		row.push_back(columns);
	}
	if (!infile.is_open())
	{
		cout << "Could not open file";
	}
	return row;
}

vector <float> getColumn(vector <vector <string>> rows, int col) {
	vector <float> column;
	for (int i = 0; i < rows.size(); i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (j == col)
			{
				string age = rows.at(i).at(j);
				if (age != "")
				{
					try
					{
						column.push_back(stof(age));
					}
					catch (...){}
					
				}
			}
		}
	}
	return column;
}

float getMean(vector<float> values) {
	float sum = 0;
	for (int i = 0; i < values.size(); i++)
	{
		sum += values.at(i);
	}
	return sum / values.size();
}

float getVariance(vector<float> values)
{
	float avg = getMean(values), sum = 0;
	for (float a : values)
	{
		sum += (a - avg)*(a - avg);
	}
	return sum / (values.size() - 1);
}

vector <vector <float>> putInBuckets(vector <float> data) {
	// Make 20 buckets for ages 0-100
	vector<vector <float>> histogramBuckets;
	int startPosition = 0;
	int bucketWidth = 5;

	for (int k = 0; k < 20; k++)
	{
		vector <float> bucket;
		for (int i = 0; i < data.size(); i++)
		{			
			float age = data.at(i);
			if ((age >= startPosition) && (age < (startPosition + bucketWidth)))
			{
				bucket.push_back(age);
			}
		}
		startPosition += bucketWidth;
		histogramBuckets.push_back(bucket);
	}
	return histogramBuckets;
}

void drawText(const char *string, int x, int y)
{
	glRasterPos2f(x, y);
	for (const char *character = string; *character != '\0'; character++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *character);
	}
}

void drawNormalLine()
{
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < ageColumn.size(); i = i + 1)
	{
		float x = (float)i;
		float y = ageColumn.size() * (exp((pow((i - avg), 2.0)) / - (2 * variance))) / (sqrt(2 * 3.14)*sqrt(variance));
		glVertex2f(x * .25, y);
	}
	glEnd();
	glutSwapBuffers();
}

void drawHistogram()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3d(255.0 / 255.0, 0, 0);
	drawNormalLine();
	float x = 0.0;
	float y = 1.0;
	float width = .1;
	float offset = 0.5;
	for (int i = 0; i < histogramBuckets.size(); i++) {
		x = (i * width) + i * 1.75;
		offset = i + 1.5;
		drawText(to_string(static_cast<int>(histogramBuckets.at(i).size())).c_str(), x, y - 1);
		glBegin(GL_POLYGON);
		glVertex2f(x, y);
		glVertex2f(x, y + histogramBuckets.at(i).size()/5);
		glVertex2f(x + width, y + histogramBuckets.at(i).size()/5);
		glVertex2f(x + width, y);
		glEnd();		
	}
	glFlush();
}


int main(int argc, char *argv[])
{
	vector <vector <string>>  titanicData = readFile();
	ageColumn = getColumn(titanicData, 6); // Get Ages
	avg = getMean(ageColumn);
	variance = getVariance(ageColumn);
	cout << "TITANIC DATASET - AGES OF PEOPLE" << endl;
	cout << "--------------------------------" << endl;
	cout << "Mean Age: " << getMean(ageColumn) << endl;
	cout << "Variance: " << getVariance(ageColumn) << endl;
	cout << "Standard Deviation: " << sqrt(getVariance(ageColumn)) << endl;
	histogramBuckets = putInBuckets(ageColumn);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(1000, 800);
	glutCreateWindow("Titanic Ages Histogram");
	glutDisplayFunc(drawHistogram);
	glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(LEFT, RIGHT, BOTTOM, TOP);
	glutMainLoop();

    return 0;
}

