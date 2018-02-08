#pragma once
#include <string>
#include <vector>

using namespace std;



class Account
{
	friend class ListOfAccounts;

public:
	Account(int bal, string type)
	{
		balance = bal;
		accountType = type;
		getNewID();
		isActive = true;
	}
	Account(int ID, int bal, string type, bool iA)
	{
		idNumber = ID;
		balance = bal;
		accountType = type;
		isActive = iA;
	}

	void getNewID()
	{
		idNumber = randomInt(100000000, 900000000);
	}

	string getIDstring()
	{
		return intToString(idNumber);
	}

private:
	bool isActive;
	int balance;  // kept as the number of pennies in the account
	int idNumber;
	string accountType;  // "Checking" or "Savings"
	vector<int> customerIDs;
};
