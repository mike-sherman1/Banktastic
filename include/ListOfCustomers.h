#pragma once
#include <vector>
#include <map>
//#include <hash_map>
//#include <unordered_map>
#include "Customer.h"
#include <fstream>
#include "misc.h"

using namespace std;


class ListOfCustomers
{
public:
	ListOfCustomers()
	{
		ifstream inFile("locData.txt");
		while (!inFile.eof())
		{
			string data;
			getline(inFile, data);
			vector<string> field = tokenize(data);
			if (field.size() != 0)
			{
				bool act = false;
				if (field[3] == "1")act = true;
				Customer readCus(stringToInt(field[0]), field[1], field[2], act);
				for (unsigned int i = 4; i < field.size(); i++)
				{
					readCus.accountIDs.push_back(stringToInt(field[i]));
				}
				vCustomer.push_back(readCus);
				indexByID[readCus.idNumber] = vCustomer.size() - 1;
			}
		}
		inFile.close();
	}

	~ListOfCustomers()
	{
		ofstream outFile("locData.txt");
		for each (Customer c in vCustomer)
		{
			outFile << c.idNumber << " ";
			outFile << c.name + ";";
			outFile << c.phoneNumber + ";";
			outFile << c.isActive;
			for each(int ai in c.accountIDs)
			{
				outFile << ";" << ai;
			}
			outFile << "\n";
		}
		outFile.close();
	}

	void addRand(int count)
	{
		for (int i = 0; i < count; i++)
		{
			add(randString(10), randNumberString(10));
		}
	}

	string add(string name, string phoneNum)
	{
		Customer nuCus(name, phoneNum);
		while (isIDUsed(nuCus.idNumber))
		{
			nuCus.getNewID();
		}

		vCustomer.push_back(nuCus);
		indexByID[nuCus.idNumber] = vCustomer.size() - 1;
		return "Customer " + nuCus.getIDstring() + " was added.";
	}
	string reactivateAll()
	{
		for (unsigned int i = 0; i < vCustomer.size(); i++)
		{
			vCustomer[i].isActive = true;
		}
		return "All customers are now reactivated.";
	}

	//string getList()
	//{
	//	string result;

	//	for each (Customer c in vCustomer)
	//	{
	//		result += c.name + "   ";
	//		result += c.phoneNumber + "   ";
	//		result += c.getIDstring() + "\n";
	//	}
	//	return result;
	//}

	string getList()
	{
		string result;

		result = getListHeader();

		for each (Customer c in vCustomer)
		{
			if (c.isActive)
			{
				result += padRight(c.name, ' ', 25) + " ";
				result += padRight(c.phoneNumber, ' ', 16) + " ";
				result += padLeft(c.getIDstring(), ' ', 9) + "\n";
			}
		}
		return result;
	}

	string makeInactive(int key)
	{
		getCusByID(key).isActive = false;
		return "Customer is now inactive.";
	}

#define FASTGET

	Customer & getCusByID(int key)
	{
#ifndef FASTGET
		for (unsigned int i = 0; i < vCustomer.size(); i++)
		{
			if (vCustomer[i].isActive)
			{
				if (key == vCustomer[i].idNumber) return vCustomer[i];
			}
		}
		throw "Invalid or Inactive ID:" + intToString(key);
#else
		map<int, int>::iterator fIter = indexByID.find(key);
		if (fIter == indexByID.end()) throw "Error: Invalid ID# " + intToString(key);
		return vCustomer[(*fIter).second];
#endif
	}

	bool isIDUsed(int key)
	{
#ifndef FASTGET
		for (unsigned int i = 0; i < vCustomer.size(); i++)
		{
			if (key == vCustomer[i].idNumber) return true;
		}
		return false;
#else
		map<int, int>::iterator fIter = indexByID.find(key);
		if (fIter == indexByID.end()) return false;
		return true;
#endif
	}
	string clear()
	{
		vCustomer.clear();
		return "All customers in list have been removed.";
	}
	void associateAct(int cKey, int aKey)
	{
		getCusByID(cKey).accountIDs.push_back(aKey);
	}
	void unassociateAct(int cKey, int aKey)
	{
		//getCusByID(cKey).accountIDs.push_back(aKey);
	}
private:

	string getListHeader()
	{
		string result;
		result += padRight("Name", ' ', 25) + " ";
		result += padRight("PhoneNumber", ' ', 16) + " ";
		result += padRight("ID#", ' ', 9) + "\n";
		result += padRight("", '_', 25) + " ";
		result += padRight("", '_', 16) + " ";
		result += padRight("", '_', 9) + "\n";
		return result;
	}


	vector<Customer> vCustomer;
	map<int, int> indexByID;
};