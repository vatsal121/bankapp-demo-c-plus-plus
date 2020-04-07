#pragma once

#include <iostream>
#include <string>

using namespace std;

void displayUserOptions();
int readInput();
void selectUserInputAndProcess(int optionNumber);
int getMaxAccountNumber();
int generateUniqueAccountNumber();
void createNewBankAccount(int accountNumber, string givenName, string familyName);
void removeClientBankAccount(int accountNumber);
void displayBankAccount(int accountNumber);
void depositMoney(int accountNumber);
void withdrawMoney(int accountNumber);
void sortAndDisplayClients(string sortOrder = "desc", string key = "Name");
void averageOfBalancesOfAllAccounts();
void sumOfTotalBalanceOfAllAccounts();