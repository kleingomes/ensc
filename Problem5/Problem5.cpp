// ENSC482 - Problem 5
// Created by Klein Gomes on 2018-05-27.
// Copyright © 2018 Klein Gomes. All rights reserved.
//

// Problem 5 (20)  
// You are indifferent between receiving A for sure and a lottery that gives you B with a 
// probability of 0.9 and C with a probability of 0.1.You are also indifferent between receiving A for sure 
// and a lottery that gives you B with a probability of 0.6 and D with a probability of 0.4.All of your 
// preferences satisfy the von Neumann - Morgenstern axioms.
// a) what do you prefer most, C or D ? 
// b) Calculate the(relative) difference in utility between B and C, and between B and D; 
// c) If we stipulate that your utility of B is 1 and your utility of C is 0, what are then your utilities of A and D ?

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

int main()
{
	// a) 
	std::cout << "Part A)" << std::endl;
	std::cout << "I prefer D more than c because probability of D is .4 which is greater than probability of C which is .1" << std::endl << std::endl;

	// b)
	std::cout << "Part B)" << std::endl;
	std::cout << "For Between B and D, set equations equal" << std::endl;
	std::cout << "=> c = 0.9-0.1 = 0.8" << std::endl;
	std::cout << "=> d = 0.6-0.4 = 0.2" << std::endl;
	std::cout << "=> Relative difference is 0.6 or c is 4x greater" << std::endl << std::endl;
	// c)
	std::cout << "Part C)" << std::endl;
	std::cout << "Let b=1 and c=0:" << std::endl;
	std::cout << "=> 0.9(1) + 0.1(0) = 0.6(1) + 0.4d" << std::endl;
	std::cout << "=> 0.9(1) + 0.1(0) = 0.6(1) + 0.4d" << std::endl;
	std::cout << "=> 0.9 = 0.6 + 0.4d" << std::endl;
	std::cout << "=> d = 0.75" << std::endl << std::endl;
	std::cout << "Since d = 0.75 we know that a is 1-d or 0.25." << std::endl;
	std::cout << "Utility A: 0.25" << std::endl;
	std::cout << "Utility D: 0.75" << std::endl;
	int wait;
	std::cin >> wait;
    return 0;
}

