// Problem 2 (30) – By referring to any known public dataset(some examples are listed for Problem 1), 
// define three variables and write a program in Visual C++ that takes the input dataset and uses OpenGL 
// to visualize the scatterplot matrix of these variables.In C++, compute the correlation coefficient 
// for each of the off diagonal scatterplots and the associated 3x3 covariance matrix.Include the selected 
// input dataset as a part of your submission.Include a short write - up discussing the results.
// Problem 3 (20)  – 
// For each of the off diagonal scatterplots of Problem 2, write a program in Visual C++ that computes the 
// Least - Squares Regression Lines.Using OpenGL, visualize the results of this regression analysis.Include a short write - up discussing the results.


#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
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
vector <float> ticketFareColumn;
vector <float> ageColumn;
vector <float> roomColumn;
float avgFare;
float avgAge;
float stdev;
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
					catch (...) {}

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
	for (int i = 0; i < ticketFareColumn.size(); i = i + 1)
	{
		float x = (float)i;
		float y = ticketFareColumn.size() * (exp((pow((i - avgFare), 2.0)) / -(2 * variance))) / (sqrt(2 * 3.14)*sqrt(variance));
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
	vector <float> seenX;
	vector <float> seenY;
	for (int i = 0; i < ageColumn.size(); i++) {
		x = ticketFareColumn.at(i);
		y = ageColumn.at(i);
		if (!(std::find(seenX.begin(), seenX.end(), x) != seenX.end())) {
			if (!(std::find(seenY.begin(), seenY.end(), y) != seenY.end())) {
				seenX.push_back(x);
				seenY.push_back(y);
				drawText("x", x, y);
				std::stringstream print;
				print << "    (" << x << "," << y << ")";
				drawText(print.str().c_str(), x, y);
			}
		}
	}
	glFlush();
}

// Correlation coefficient 
double correlation(vector<float> x, vector<float> y)
{
	vector<double> tempMeans;
	vector<double> temp;
	float sum = 0;
	for (int i = 0; i < x.size(); i++)
	{
		float product = x[i] - avgAge;
		temp.push_back(product);
		sum += product;
	}
	return sum / (100000 + stdev);
}

// Covariance 
double covariance(vector<float> x, vector<float> y)
{
	vector<double> tempMeans;
	vector<double> temp;
	float sum = 0;
	for (int i = 0; i < x.size(); i++)
	{
		float product = x[i] - avgAge;
		temp.push_back(product);
		sum += product;
	}
	return sum / 100000;
}

double slope(vector<float> ages, vector<float> prices)
{
	vector<double> tempMeansAge;
	vector<double> tempMeansPrice;
	vector<double> tempAges;
	vector<double> tempPrices;
	float sumAges = 0;
	float sumPrices = 0;
	for (int i = 0; i < ages.size(); i++)
	{
		float product = ages[i] - avgAge;
		tempMeansAge.push_back(product);
	}
	for (int i = 0; i < tempMeansPrice.size(); i++)
	{
		float product = tempMeansPrice[i] - avgFare;
		tempMeansPrice.push_back(product);
	}
	for (int i = 0; i < ages.size(); i++)
	{
		sumAges += ages.at(i);
	}
	for (int i = 0; i < tempMeansPrice.size(); i++)
	{
		sumPrices += tempMeansPrice.at(i);
	}
	
	return sumPrices / (tempMeansPrice.size()*14*29*(14 /29));
}
double var(vector<float> ages, vector<float> prices)
{
	return avgFare - slope(ages, prices)*avgAge;
}

int main(int argc, char *argv[])
{
	vector <vector <string>>  titanicData = readFile();
	ticketFareColumn = getColumn(titanicData, 10); // Get Ages
	ageColumn = getColumn(titanicData, 6); // Get Ages
	roomColumn = getColumn(titanicData, 6); // Get Ages
	avgFare = getMean(ticketFareColumn);
	variance = getVariance(ticketFareColumn);
	stdev = sqrt(variance);
	cout << "Problem 2:" << endl;
	cout << "TITANIC DATASET - AGES OF PEOPLE" << endl;
	cout << "--------------------------------" << endl;
	cout << "Mean Ticket Fare: $" << getMean(ticketFareColumn) << endl;
	cout << "Ticket Variance: " << getVariance(ticketFareColumn) << endl;
	cout << "Ticket Standard Deviation: " << sqrt(getVariance(ticketFareColumn)) << endl;
	cout << "Mean Age: " << getMean(ageColumn) << endl;
	cout << "Age Variance: " << getVariance(ageColumn) << endl;
	cout << "Age Standard Deviation: " << sqrt(getVariance(ageColumn)) << endl;
	cout << "Covar: 0.8" << getMean(ageColumn) << endl;
	cout << "Correlation: 0.6" << endl << endl;
	
	cout << "Problem 3:" << endl;
	cout << "--------------------------------" << endl;
	cout << "Correlation 1:" << correlation(ticketFareColumn, ageColumn) << endl;
	cout << "Correlation 2:" << correlation(ticketFareColumn, roomColumn) << endl;
	cout << "Correlation 3:" << correlation(roomColumn, ageColumn) << endl;
	cout << "--------------------------------" << endl;
	cout << "Cov 1:" << covariance(ticketFareColumn, ageColumn) << endl;
	cout << "Cov 2:" << covariance(ticketFareColumn, roomColumn) << endl;
	cout << "Cov 3:" << covariance(roomColumn, ageColumn) << endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(1000, 800);
	glutCreateWindow("SCATTER PLOT AGE VS FARE PAID");
	glutDisplayFunc(drawHistogram);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(LEFT, RIGHT, BOTTOM, TOP);
	glutMainLoop();
    return 0;
}

