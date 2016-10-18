#pragma once

#include "ListOfCustomers.h"
#include "ListOfAccounts.h"

class Bank
{
public:
	string getCustomerList()
	{
		return listOfCus.getList();
	}
	string addCustomer(string name, string phoneNum)
	{
		return listOfCus.add(name, phoneNum);
	}
	string makeCustomerInactive(int key)
	{
		return listOfCus.makeInactive(key);
	}
	string reactivateAllCustomers()
	{
		return listOfCus.reactivateAll();
	}
	string clearCustomers()
	{
		return listOfCus.clear();
	}
	string addRandCus(int count)
	{
		listOfCus.addRand(count);
		return intToString(count) + " random customers added.";
	}
	string addAccount(int initialBal, string type)
	{
		return listOfActs.add(initialBal, type);
	}
	string makeAccountInactive(int key)
	{
		return listOfActs.makeInactive(key);
	}
	string showAccountList()
	{
		return listOfActs.getList();
	}
	string addRandActs(int count)
	{
		listOfActs.addRand(count);
		return intToString(count) + " random accounts added.";
	}
	string associate(int cKey, int aKey)
	{
		listOfActs.associateCus(cKey, aKey);
		listOfCus.associateAct(cKey, aKey);
		return "Customer #" + intToString(cKey) + " has been associated with account #" + intToString(aKey) + ".";
	}
	string unassociate(int cKey, int aKey)
	{
		listOfActs.unassociateCus(cKey, aKey);
		listOfCus.unassociateAct(cKey, aKey);
		return "Stubbed.";
	}
private:
	ListOfCustomers listOfCus;
	ListOfAccounts listOfActs;
};
