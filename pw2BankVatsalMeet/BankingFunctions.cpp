#include <iostream>
#include <iomanip>
#include <time.h> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm> 
using namespace std;

int getMaxAccountNumber() {
	ifstream accountDetailsOfAllUsers;
	accountDetailsOfAllUsers.open("accountDetailsOfAllUsers.txt", ios::app);//, ios::out | ios::in);
	int accountNumber, maxAccountNumber = 0;
	double availableBalance;
	string givenName, familyName;
	if (accountDetailsOfAllUsers.is_open()) {
		while (!accountDetailsOfAllUsers.eof() && accountDetailsOfAllUsers >> accountNumber >> givenName >> familyName >> availableBalance) {
			maxAccountNumber = (accountNumber > maxAccountNumber) ? accountNumber : maxAccountNumber;
		}
	}
	else {
		cout << "Error opening user account data file!." << endl;
	}
	accountDetailsOfAllUsers.close();
	return maxAccountNumber;
};

void createNewBankAccount(int accountNumber, string givenName, string familyName) {
	fstream createNewAccount;
	createNewAccount.open("accountDetailsOfAllUsers.txt", ios::app);//, ios::out | ios::in);
	if (createNewAccount.is_open()) {
		createNewAccount << accountNumber << " " << givenName << " " << familyName << " " << 0 << "\n";
		cout << "Account created successfully" << endl;
		cout << endl << endl << endl;
	}
	else {
		cout << "Error opening user account data file!." << endl;
	}
	createNewAccount.close();
}

void removeClientBankAccount(int accountNumber) {
	ifstream accountDetailsOfAllUsers;
	ofstream tempFile;
	tempFile.open("temp.txt", ios::app);

	string line;
	bool isAccountExists = false;
	accountDetailsOfAllUsers.open("accountDetailsOfAllUsers.txt", ios::app);
	if (accountDetailsOfAllUsers.is_open()) {
		while (getline(accountDetailsOfAllUsers, line))
		{
			string acn = to_string(accountNumber);
			size_t found = line.find(acn);
			if (found == string::npos) {
				tempFile << line << endl;
			}
			else {
				isAccountExists = true;
			}
		}
	}
	else {
		cout << "Error opening account data file." << endl;
	}

	tempFile.close();
	accountDetailsOfAllUsers.close();
	remove("accountDetailsOfAllUsers.txt");
	rename("temp.txt", "accountDetailsOfAllUsers.txt");
	cout << (isAccountExists ? "Successfully removed client account." : "Account not found!.") << endl;
}

void displayBankAccount(int accountNumber) {
	ifstream accountDetailsOfAllUsers;
	bool isAccountFound = false;
	string givenName, familyName;
	double availableAmtOfClient;
	int acn;
	accountDetailsOfAllUsers.open("accountDetailsOfAllUsers.txt", ios::app);
	if (accountDetailsOfAllUsers.is_open()) {
		while (!accountDetailsOfAllUsers.eof() && accountDetailsOfAllUsers >> acn >> givenName >> familyName >> availableAmtOfClient) {
			if (accountNumber == acn) {
				isAccountFound = true;
				cout << "Account Number: " << acn << endl;
				cout << "Given Name: " << givenName << endl;
				cout << "Family Name: " << familyName << endl;
				cout << "Available Balance: " << availableAmtOfClient << endl;
			}
			//while (std::getline(accountDetailsOfAllUsers, line))
			//{
			//	string acn = to_string(accountNumber);
			//	size_t found = line.find(acn);
			//	if (found != string::npos) {
			//		isAccountFound = true;
			//		//getline(accountDetailsOfAllUsers, line);
			//		cout << "Account Number" << " | " << "Given Name" << " | " << "Family Name" << " | " << "Total Balance" << endl;
			//		cout << line << endl;
			//		cout << "Successfully displayed detail." << endl;
			//	}
		}
		if (!isAccountFound) {
			cout << "Account not found." << endl;
		}
	}
	else {
		cout << "Error opening account data file." << endl;
	}
	accountDetailsOfAllUsers.close();
}

void depositMoney(int accountNumber) {
	double moneyDeposit, availableAmtOfClient;
	string givenName, familyName;
	int acn;
	bool isAccountExists = false;
	cout << "Enter amount to be deposited: ";
	cin >> moneyDeposit;
	ifstream accountDetailsOfAllUsers;
	ofstream tempFile;
	tempFile.open("temp.txt", ios::app);
	accountDetailsOfAllUsers.open("accountDetailsOfAllUsers.txt", ios::app);
	if (accountDetailsOfAllUsers.is_open()) {
		while (!accountDetailsOfAllUsers.eof() && accountDetailsOfAllUsers >> acn >> givenName >> familyName >> availableAmtOfClient) {
			if (acn == accountNumber) {
				isAccountExists = true;
				availableAmtOfClient += moneyDeposit;
				cout << "Amount deposited successfully." << endl;
				cout << "New available balance for the account number " << acn << " is: " << availableAmtOfClient << endl;

			}
			tempFile << acn << " " << givenName << " " << familyName << " " << availableAmtOfClient << "\n";
		}
		if (!isAccountExists) {
			cout << "Account not found!." << endl;
		}
	}
	else {
		cout << "Error opening user account data file!." << endl;
	}
	tempFile.close();
	accountDetailsOfAllUsers.close();
	remove("accountDetailsOfAllUsers.txt");
	rename("temp.txt", "accountDetailsOfAllUsers.txt");
}

void withdrawMoney(int accountNumber) {
	double withdrawMoneyAmt, availableAmtOfClient;
	string givenName, familyName;
	int acn;
	bool isAccountExists = false;
	cout << "Enter amount to withdraw: ";
	cin >> withdrawMoneyAmt;
	ifstream accountDetailsOfAllUsers;
	ofstream tempFile;
	tempFile.open("temp.txt", ios::app);
	accountDetailsOfAllUsers.open("accountDetailsOfAllUsers.txt", ios::app);
	if (accountDetailsOfAllUsers.is_open()) {
		while (!accountDetailsOfAllUsers.eof() && accountDetailsOfAllUsers >> acn >> givenName >> familyName >> availableAmtOfClient) {
			if (acn == accountNumber) {
				isAccountExists = true;
				if (availableAmtOfClient > 0 && withdrawMoneyAmt <= availableAmtOfClient) {
					availableAmtOfClient = availableAmtOfClient - withdrawMoneyAmt;
					cout << "Amount withdrawn successfully!." << endl;
					cout << "New available balance for the account number " << acn << " is: " << availableAmtOfClient << endl;
				}
				else {
					cout << "Insufficient balance!." << endl;
				}
			}
			tempFile << acn << " " << givenName << " " << familyName << " " << availableAmtOfClient << "\n";
		}
		if (!isAccountExists) {
			cout << "Account not found!." << endl;
		}
	}
	else {
		cout << "Error opening user account data file!." << endl;
	}
	tempFile.close();
	accountDetailsOfAllUsers.close();
	remove("accountDetailsOfAllUsers.txt");
	rename("temp.txt", "accountDetailsOfAllUsers.txt");
}

void averageOfBalancesOfAllAccounts() {
	double withdrawMoneyAmt, availableAmtOfClient, sum = 0;
	string givenName, familyName;
	int acn, counter = 0;
	bool isAccountExists = false;
	ifstream accountDetailsOfAllUsers;
	accountDetailsOfAllUsers.open("accountDetailsOfAllUsers.txt", ios::app);
	if (accountDetailsOfAllUsers.is_open()) {
		while (!accountDetailsOfAllUsers.eof() && accountDetailsOfAllUsers >> acn >> givenName >> familyName >> availableAmtOfClient) {
			isAccountExists = true;
			counter++;
			sum = sum + availableAmtOfClient;
		}
	}
	sum = sum / counter;
	cout << "Total number of money in bank is: " << sum << endl;
	accountDetailsOfAllUsers.close();
}

void sumOfTotalBalanceOfAllAccounts() {
	double withdrawMoneyAmt, availableAmtOfClient, sum = 0;
	string givenName, familyName;
	int acn;
	bool isAccountExists = false;
	ifstream accountDetailsOfAllUsers;
	accountDetailsOfAllUsers.open("accountDetailsOfAllUsers.txt", ios::app);
	if (accountDetailsOfAllUsers.is_open()) {
		while (!accountDetailsOfAllUsers.eof() && accountDetailsOfAllUsers >> acn >> givenName >> familyName >> availableAmtOfClient) {
			isAccountExists = true;
			sum = sum + availableAmtOfClient;
		}
	}
	cout << "Sum of total balance of all the accounts in is: " << sum << endl;
	accountDetailsOfAllUsers.close();
	//cout << endl << endl << endl;
}

void sortAndDisplayClients(string sortOrder = "desc", string key = "Name") {
	vector<string> names = {}, listContent = {};
	vector<double> balancelist = {};
	vector<int> accountIds = {};
	//vector<string> listContent = {};
	double averageBalance = 0, availableAmtOfClient, totalBalance = 0;
	string givenName, familyName;
	int acn;
	ifstream accountDetailsOfAllUsers;
	accountDetailsOfAllUsers.open("accountDetailsOfAllUsers.txt", ios::app);
	if (accountDetailsOfAllUsers.is_open()) {
		while (!accountDetailsOfAllUsers.eof() && accountDetailsOfAllUsers >> acn >> givenName >> familyName >> availableAmtOfClient) {
			if (key == "Name" || key == "Familyname") {
				string derivedName = (key == "Name") ? givenName : familyName;
				names.push_back(derivedName);
			}
			else if (key == "Balance") {
				balancelist.push_back(availableAmtOfClient);
			}
			/*else if (key == "familyname") {
				names.push_back(familyName);
			}*/
		}
		if (sortOrder == "desc" || sortOrder == "asc") {
			if (key != "Balance") {
				sort(names.begin(), names.end());
				if (sortOrder == "desc") {
					reverse(names.begin(), names.end());
				}
			}
			else {
				sort(balancelist.begin(), balancelist.end());
				if (sortOrder == "desc") {
					reverse(balancelist.begin(), balancelist.end());
				}
			}
		}
	}
	accountDetailsOfAllUsers.close();
	if (key == "Balance") {
		for (int i = 0; i < balancelist.size(); i++) {
			accountDetailsOfAllUsers.open("accountDetailsOfAllUsers.txt", ios::app);
			if (accountDetailsOfAllUsers.is_open()) {
				while (!accountDetailsOfAllUsers.eof() && accountDetailsOfAllUsers >> acn >> givenName >> familyName >> availableAmtOfClient) {

					bool isExist = false;
					if (balancelist[i] == availableAmtOfClient) {
						if (accountIds.size() != 0) {
							for (int i = 0; i < accountIds.size(); i++) {
								if (accountIds[i] == acn) {
									isExist = true;
								}
							}
							if (!isExist) {
								accountIds.push_back(acn);
								cout << acn << " " << givenName << " " << familyName << " " << availableAmtOfClient << endl;
							}
						}
						else {
							accountIds.push_back(acn);
							cout << acn << " " << givenName << " " << familyName << " " << availableAmtOfClient << endl;
						}
					}
				}
				accountDetailsOfAllUsers.close();
			}
			accountDetailsOfAllUsers.close();
		}
	}
	else {
		for (int i = 0; i < names.size(); i++) {
			accountDetailsOfAllUsers.open("accountDetailsOfAllUsers.txt", ios::app);
			if (accountDetailsOfAllUsers.is_open()) {
				while (!accountDetailsOfAllUsers.eof() && accountDetailsOfAllUsers >> acn >> givenName >> familyName >> availableAmtOfClient) {
					if (givenName == names[i] && key == "Name") {
						cout << acn << " " << givenName << " " << familyName << " " << availableAmtOfClient << endl;
					}
					else if (familyName == names[i] && key == "Familyname") {
						cout << acn << " " << givenName << " " << familyName << " " << availableAmtOfClient << endl;
					}
				}
				accountDetailsOfAllUsers.close();
			}
		}
	}
}

int generateUniqueAccountNumber() {
	const int MIN_ACCOUNT_NUMBER = 10000, MAX_ACCOUNT_NUMBER = 10099;
	int uniqueNewAccountNumber = 0;
	uniqueNewAccountNumber = getMaxAccountNumber();
	if (uniqueNewAccountNumber == 0) {
		uniqueNewAccountNumber = MIN_ACCOUNT_NUMBER;
	}
	else if (uniqueNewAccountNumber >= 10000 && uniqueNewAccountNumber < MAX_ACCOUNT_NUMBER)
	{
		uniqueNewAccountNumber += 1;
	}
	else {
		cout << "Maximum account number reached." << endl;
		uniqueNewAccountNumber = -1;
	}
	return uniqueNewAccountNumber;
}

void displayUserOptions() {
	cout << "Welcome to the banking application!!.." << endl;
	cout << "Select one of the following options: " << endl;
	cout << "1. Add a new bank account." << endl;
	cout << "2. Remove a bank account." << endl;
	cout << "3. Search client information by bank number." << endl;
	cout << "4. Deposit money to account." << endl;
	cout << "5. Withdraw money from account." << endl;
	cout << "6. Display clients by their balance, family name, given name and sort them by ascending or descending order." << endl;
	cout << "7. Display the average balance value of the accounts." << endl;
	cout << "8. Display the total balance value of the accounts." << endl;
	cout << "9. Exit." << endl;
}

int readInput()
{
	int value;
	cout << "Enter the option number you want to select: ";
	cin >> value;
	while (cin.fail() || cin.peek() != '\n' || value <= 0 && value > 9)
	{
		cin.clear();
		cin.ignore(512, '\n');
		cout << "Warning - Enter numerical input from 1 to 9 only!." << endl;
		cout << "Enter the option number you want to select: ";
		cin >> value;
	}
	cin.ignore(512, '\n');
	return value;
}

void selectUserInputAndProcess(int optionNumber) {
	string givenName = "", familyName = "", sortOrder = "desc", key = "Name";
	int accountNumber = 0;
	if (optionNumber > 0 && optionNumber <= 9) {
		switch (optionNumber)
		{
		case 1:
			cout << "You have selected option '1. Add a new bank account.'" << endl;
			cout << "Enter the client's given name: ";
			cin >> givenName;
			cout << "Enter the client's family name: ";
			cin >> familyName;
			accountNumber = generateUniqueAccountNumber();
			if (accountNumber != -1) {
				createNewBankAccount(accountNumber, givenName, familyName);
			}
			cout << endl << endl << endl;
			break;
		case 2:
			cout << "You have selected option '2. Remove a bank account.'" << endl;
			cout << "Enter the client's account number: ";
			cin >> accountNumber;
			removeClientBankAccount(accountNumber);
			cout << endl << endl << endl;
			break;
		case 3:
			cout << "You have selected option '3. Display the detail of account.'" << endl;
			cout << "Enter the client's account number: ";
			cin >> accountNumber;
			displayBankAccount(accountNumber);
			cout << endl << endl << endl;
			break;
		case 4:
			cout << "You have selected option '4. Enter amount to deposit money in account.'" << endl;
			cout << "Enter the client's account number: ";
			cin >> accountNumber;
			depositMoney(accountNumber);
			cout << endl << endl << endl;
			break;
		case 5:
			cout << "You have selected option '5. Withdraw money from account.'" << endl;
			cout << "Enter the client's account number: ";
			cin >> accountNumber;
			withdrawMoney(accountNumber);
			cout << endl << endl << endl;
			break;
		case 6:
			cout << "You have selected option '6. Display clients by their balance, family name, given name and sort them by ascending or descending order.'" << endl;
			cout << "Enter the sorting order ('asc/desc'): ";
			cin >> sortOrder;
			cout << "Enter the Property name for that you want to apply sorting(Choose any one from Name, Balance, Familyname): ";
			cin >> key;
			sortAndDisplayClients(sortOrder, key);
			cout << endl << endl << endl;
			break;
		case 7:
			cout << "You have selected option '7. Display the average balance value of the accounts.'" << endl;
			averageOfBalancesOfAllAccounts();
			cout << endl << endl << endl;
			break;
		case 8:
			cout << "You have selected option '8. Display the total balance value of the accounts.'" << endl;
			sumOfTotalBalanceOfAllAccounts();
			cout << endl << endl << endl;
			break;
		case 9:
			cout << endl << endl << "Exiting the bank application!." << endl << endl;
			exit(0);
		default:
			break;
		}
	}
	else {
		cout << "Please select options from 1 to 9." << endl;
		cout << endl << endl << endl;
	}
}

