// pw2BankVatsalMeet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "BankingFunctions.h"
using namespace std;

int main()
{

L1:displayUserOptions();
	selectUserInputAndProcess(readInput());
	goto L1;

	return 0;
}
