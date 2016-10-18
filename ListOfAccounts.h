#pragma once

#include <vector>
#include "Account.h"
#include <map>
#include "misc.h"

using namespace std;

class ListOfAccounts
{
public:
	ListOfAccounts()
	{
		ifstream inFile("actData.txt");
		while (!inFile.eof())
		{
			string data;
			getline(inFile, data);
			vector<string> field = tokenize(data);
			if (field.size() != 0)
			{
				bool act = false;
				if (field[3] == "1")act = true;
				Account readAct(stringToInt(field[0]), stringToInt(field[1]), field[2], act);
				for (unsigned int i = 4; i < field.size(); i++)
				{
					readAct.customerIDs.push_back(stringToInt(field[i]));
				}
				vAccounts.push_back(readAct);
				indexByID[readAct.idNumber] = vAccounts.size() - 1;
			}
		}
		inFile.close();
	}
	
	~ListOfAccounts()
	{
		ofstream outFile("actData.txt");
		for each (Account a in vAccounts)
		{
			outFile << a.idNumber << " ";
			outFile << intToString(a.balance) + ";";
			outFile << a.accountType + ";";
			outFile << a.isActive;
			for each(int ci in a.customerIDs)
			{
				outFile << ";" << ci;
			}
			outFile << "\n";
		}
		outFile.close();
	}
	
	string add(int bal, string type)
	{
		Account newAct(bal, type);
		while (isIDUsed(newAct.idNumber))
		{
			newAct.getNewID();
		}
		vAccounts.push_back(newAct);
		indexByID[newAct.idNumber] = vAccounts.size() - 1;
		return "Account " + newAct.getIDstring() + " was added.";
	}
	
	string makeInactive(int key)
	{
		if (getActByID(key).balance > 0)
			return "Cannot make this account inactive, there is a balance remaining.";
		else
		{
			getActByID(key).isActive = false;
			return "Account is now inactive.";
		}
	}
	
	bool isIDUsed(int key)
	{
		map<int, int>::iterator fIter = indexByID.find(key);
		if (fIter == indexByID.end()) return false;
		return true;
	}
	
	Account &getActByID(int key)
	{
		map<int, int>::iterator fIter = indexByID.find(key);
		if (fIter == indexByID.end()) throw "Error: Invalid ID# " + intToString(key);
		return vAccounts[(*fIter).second];
	}
	
	string getList()
	{
		string result;

		result = getListHeader();

		for each (Account a in vAccounts)
		{
			if (a.isActive)
			{
				result += padRight(intToString(a.idNumber), ' ', 11) + " ";
				result += padRight(a.accountType, ' ', 8) + " ";
				result += padLeft(intToString(a.balance), ' ', 10) + "\n";
			}
		}
		return result;
	}
	
	void addRand(int count)
	{
		for (int i = 0; i < count; i++)
		{
			add(randomInt(1000000000, 9999999999), "Savings");
		}
	}
	
	void associateCus(int cKey, int aKey)
	{
		getActByID(aKey).customerIDs.push_back(cKey);
	}
	
	void unassociateCus(int cKey, int aKey)
	{
		//stubbed
		//getActByID(aKey).customerIDs.push_back(cKey);
	}

private:
	
	string getListHeader()
	{
		string result;
		result += padRight("Account ID#", ' ', 10) + " ";
		result += padRight("Type", ' ', 8) + " ";
		result += padRight("Balance", ' ', 10) + "\n";
		result += padRight("", '_', 11) + " ";
		result += padRight("", '_', 8) + " ";
		result += padRight("", '_', 10) + "\n";
		return result;
	}
	
	vector<Account> vAccounts;
	map<int, int> indexByID;
};