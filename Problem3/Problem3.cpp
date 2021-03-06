// ENSC482 - Problem 3
// Created by Klein Gomes on 2018-05-27.
// Copyright © 2018 Klein Gomes. All rights reserved.
//
// Problem 3 (50) 
// Write a program which determines which act(s) should be chosen in the decision problem below according to each of the following decision rule : 
// (a) The maximin rule; 
// (b) maximax; 
// (c) minimax regret; 
// (d) the optimism - pessimism rule(for alph > .25) 
// (e) the principle of insufficient reason.
// The 4 by 4 decision matrix is defined by the following row vectors corresponding to each of the acts: 
// a1=(20, 20, 0, 10); 
// a2=(10, 10, 10, 10); 
// a3=(0, 40, 0, 0); 
// a4=(10, 30, 0, 0). 
// For each of the decision rules, supply the commented source code (with instructions on how to link and compile) and sample results.

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

const int ARRAY_SIZE = 4;
enum op { FindMin, FindMax };
int a1[ARRAY_SIZE] = { 20,20,0,10 };
int a2[ARRAY_SIZE] = { 10,10,10,10 };
int a3[ARRAY_SIZE] = { 0,40,0,0 };
int a4[ARRAY_SIZE] = { 10,30,0,10 };

void print(int o, double opt[ARRAY_SIZE])
{
	if (o == opt[0])
		std::cout << "a1" << std::endl;
	else if (o == opt[1])
		std::cout << "a2" << std::endl;
	else if (o == opt[2])
		std::cout << "a3" << std::endl;
	else if (o == opt[3])
		std::cout << "a4" << std::endl;
}

void printArray(int arr[ARRAY_SIZE]) {
	for (int i = 0; i < 4; i ++)
	{
		if (arr[i] < 10)
		{
			std::cout << " ";
		}
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

std::tuple<int, int> find(double arr[], op op, int size)
{
	double target = arr[0];
	int foundIndex = 0;
	for (int i = 0; i < size; i++)
	{
		if (op == FindMax) {
			if (arr[i] > target) {
				target = arr[i];
				foundIndex = i;
			}
		}
		else if (op == FindMin) {
			if (arr[i] < target) {
				target = arr[i];
				foundIndex = i;
			}
		}
	}
	return std::make_pair(foundIndex + 1, target);
}

std::tuple<int,int> find(int arr[], op op,int size)
{
	double temp[ARRAY_SIZE];
	for (int i = 0; i < size; i++)
	{
		temp[i] = (double)arr[i];
	}
	return find(temp, op, size);
}

void maximin(int arr1[], int arr2[], int arr3[], int arr4[])
{
	int max;
	int mins[ARRAY_SIZE];

	// Worst of each array
	mins[0] = std::get<1>(find(arr1, FindMin, ARRAY_SIZE));
	mins[1] = std::get<1>(find(arr2, FindMin, ARRAY_SIZE));
	mins[2] = std::get<1>(find(arr3, FindMin, ARRAY_SIZE));
	mins[3] = std::get<1>(find(arr4, FindMin, ARRAY_SIZE));

	// Find the max
	max = std::get<0>(find(mins, FindMax, ARRAY_SIZE));

	// Print output
	std::cout << std::endl << std::endl << "Maximin: a" << max;
}

void maximax(int arr1[], int arr2[], int arr3[], int arr4[])
{
	int max;
	int maxs[ARRAY_SIZE];

	// Best of each array
	maxs[0] = std::get<1>(find(arr1, FindMax, ARRAY_SIZE));
	maxs[1] = std::get<1>(find(arr2, FindMax, ARRAY_SIZE));
	maxs[2] = std::get<1>(find(arr3, FindMax, ARRAY_SIZE));
	maxs[3] = std::get<1>(find(arr4, FindMax, ARRAY_SIZE));

	// Find the max
	max = std::get<0>(find(maxs, FindMax, ARRAY_SIZE));

	// Print output
	std::cout << std::endl << std::endl << "Maximax: a" << max;
}

void maximinRegret(int arr1[], int arr2[], int arr3[], int arr4[])
{
	int min;
	int maxs[ARRAY_SIZE];
	int maxRegrets[ARRAY_SIZE];
	int regret1[4];
	int regret2[4];
	int regret3[4];
	int regret4[4];
	int regretMaxs1[4];
	int regretMaxs2[4];
	int regretMaxs3[4];
	int regretMaxs4[4];

	// Max of each column
	maxs[0] = a1[0];
	maxs[1] = a2[0];
	maxs[2] = a3[0];
	maxs[3] = a4[0];
	regretMaxs1[0] = std::get<1>(find(maxs, FindMax, ARRAY_SIZE));
	regret1[0] = regretMaxs1[0] - a1[0];
	regret2[0] = regretMaxs1[0] - a2[0];
	regret3[0] = regretMaxs1[0] - a3[0];
	regret4[0] = regretMaxs1[0] - a4[0];

	maxs[0] = a1[1];
	maxs[1] = a2[1];
	maxs[2] = a3[1];
	maxs[3] = a4[1];
	regretMaxs2[1] = std::get<1>(find(maxs, FindMax, ARRAY_SIZE));
	regret1[1] = regretMaxs2[1] - a1[1];
	regret2[1] = regretMaxs2[1] - a2[1];
	regret3[1] = regretMaxs2[1] - a3[1];
	regret4[1] = regretMaxs2[1] - a4[1];

	maxs[0] = a1[2];
	maxs[1] = a2[2];
	maxs[2] = a3[2];
	maxs[3] = a4[2];
	regretMaxs3[2] = std::get<1>(find(maxs, FindMax, ARRAY_SIZE));
	regret1[2] = regretMaxs3[2] - a1[2];
	regret2[2] = regretMaxs3[2] - a2[2];
	regret3[2] = regretMaxs3[2] - a3[2];
	regret4[2] = regretMaxs3[2] - a4[2];

	maxs[0] = a1[3];
	maxs[1] = a2[3];
	maxs[2] = a3[3];
	maxs[3] = a4[3];
	regretMaxs4[3] = std::get<1>(find(maxs, FindMax, ARRAY_SIZE));
	regret1[3] = regretMaxs4[3] - a1[3];
	regret2[3] = regretMaxs4[3] - a2[3];
	regret3[3] = regretMaxs4[3] - a3[3];
	regret4[3] = regretMaxs4[3] - a4[3];

	// Best of each array
	maxs[0] = std::get<1>(find(regret1, FindMax, ARRAY_SIZE));
	maxs[1] = std::get<1>(find(regret2, FindMax, ARRAY_SIZE));
	maxs[2] = std::get<1>(find(regret3, FindMax, ARRAY_SIZE));
	maxs[3] = std::get<1>(find(regret4, FindMax, ARRAY_SIZE));

	// Find the min regret
	min = std::get<0>(find(maxs, FindMin, ARRAY_SIZE));

	// Print output
	std::cout << std::endl << std::endl << "Maximin Regret: a" << min;
}

void optimismPessimismRule(int arr1[], int arr2[], int arr3[], int arr4[], float alpha)
{
	int maxs[4], mins[4], o;
	double opt[4];
	// Find the largest value for each A
	maxs[0] = std::get<1>(find(arr1, FindMax, ARRAY_SIZE));
	maxs[1] = std::get<1>(find(arr2, FindMax, ARRAY_SIZE));
	maxs[2] = std::get<1>(find(arr3, FindMax, ARRAY_SIZE));
	maxs[3] = std::get<1>(find(arr4, FindMax, ARRAY_SIZE));
	
	//Find the smallest value for each A
	mins[0] = std::get<1>(find(arr1, FindMin, ARRAY_SIZE));
	mins[1] = std::get<1>(find(arr2, FindMin, ARRAY_SIZE));
	mins[2] = std::get<1>(find(arr3, FindMin, ARRAY_SIZE));
	mins[3] = std::get<1>(find(arr4, FindMin, ARRAY_SIZE));


	// Calculate Optimism-pessimism array
	for (int i = 0; i < 4; i++)
	{
		opt[i] = alpha * maxs[i] + (1 - alpha) * mins[i];
	}

	// Find the largest value of the largest values found above
	o = std::get<1>(find(opt, FindMax, ARRAY_SIZE));
	// Print
	std::cout << std::endl << std::endl << "Optimism-Pessimism: ";
	print(o, opt);
}


void insufficientReason(int arr1[], int arr2[], int arr3[], int arr4[])
{
	int i;
	double prob[4];
	double max;

	//Find expected value with equal probability
	prob[0] = (1 / 4)*arr1[0] + (1 / 4)*arr1[1] + (1 / 4)*arr1[2] + (1 / 4)*arr1[3];
	prob[1] = (1 / 4)*arr2[0] + (1 / 4)*arr2[1] + (1 / 4)*arr2[2] + (1 / 4)*arr2[3];
	prob[2] = (1 / 4)*arr3[0] + (1 / 4)*arr3[1] + (1 / 4)*arr3[2] + (1 / 4)*arr3[3];
	prob[3] = (1 / 4)*arr4[0] + (1 / 4)*arr4[1] + (1 / 4)*arr4[2] + (1 / 4)*arr4[3];

	max = std::get<1>(find(prob, FindMin, ARRAY_SIZE));
	// Print
	std::cout << std::endl << "Insufficient Reason: ";
	print(max, prob);
}

int main()
{
	std::cout << "a1: ";
	printArray(a1);
	
	std::cout << "a2: ";
	printArray(a2);

	std::cout << "a3: ";
	printArray(a3);

	std::cout << "a4: ";
	printArray(a4);

	maximin(a1, a2, a3, a4);
	maximax(a1, a2, a3, a4);
	maximinRegret(a1, a2, a3, a4);
	optimismPessimismRule(a1, a2, a3, a4, 0.5);
	insufficientReason(a1, a2, a3, a4);

	int x = 2;
	std::cin >> x;
    return 0;
}

