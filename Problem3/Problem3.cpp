// ENSC482 - Problem 2
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

std::tuple<int,int> find(int arr[ARRAY_SIZE], op op)
{
	int target = arr[0];
	int foundIndex = 0;
	for (int i = 0; i < ARRAY_SIZE; i++)
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
	return std::make_pair(foundIndex+1, target);
}

void maximin(int arr1[], int arr2[], int arr3[], int arr4[])
{
	int max;
	int mins[ARRAY_SIZE];

	// Worst of each array
	mins[0] = std::get<1>(find(arr1, FindMin));
	mins[1] = std::get<1>(find(arr2, FindMin));
	mins[2] = std::get<1>(find(arr3, FindMin));
	mins[3] = std::get<1>(find(arr4, FindMin));

	// Find the max
	max = std::get<0>(find(mins, FindMax));

	// Print output
	std::cout << std::endl << std::endl << "Maximin: a" << max;
}

void maximax(int arr1[], int arr2[], int arr3[], int arr4[])
{
	int max;
	int maxs[ARRAY_SIZE];

	// Best of each array
	maxs[0] = std::get<1>(find(arr1, FindMax));
	maxs[1] = std::get<1>(find(arr2, FindMax));
	maxs[2] = std::get<1>(find(arr3, FindMax));
	maxs[3] = std::get<1>(find(arr4, FindMax));

	// Find the max
	max = std::get<0>(find(maxs, FindMax));

	// Print output
	std::cout << std::endl << std::endl << "Maximax: a" << max;
}

void maximinRegret(int arr1[], int arr2[], int arr3[], int arr4[])
{
	int max;
	int mins[ARRAY_SIZE];

	// Worst of each array
	mins[0] = std::get<1>(find(arr1, FindMin));
	mins[1] = std::get<1>(find(arr2, FindMin));
	mins[2] = std::get<1>(find(arr3, FindMin));
	mins[3] = std::get<1>(find(arr4, FindMin));

	// Find the max
	max = std::get<0>(find(mins, FindMax));

	// Print output
	std::cout << std::endl << std::endl << "Maximin: a" << max;
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

	int x = 2;
	std::cin >> x;
    return 0;
}

