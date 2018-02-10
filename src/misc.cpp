// ***********************************************************************
//
// (c) Copyright 2011 Dr. Thomas Fernandez
//
//  All rights reserved.
//
//  thomas@cse.fau.edu
//
// ***********************************************************************

#include "stdio.h"
#include "stdlib.h"
#include <sstream>
#include "../include/misc.h"

using namespace std;

RandGen randGen;

int randomInt(int lo, int hi)
{
	return randGen.getInt(lo, hi);
}

double randomDouble(double lo, double hi)
{
	return randGen.getDouble(lo, hi);
}

bool matchFirst(string s1, string s2)
{
	if (s1.length() <= s2.length())
	{
		if (s1 == s2.substr(0, s1.length()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return matchFirst(s2, s1);
	}
}

vector<string> tokenize(string com)
{
	istringstream is(com);
	vector<string> vs;
	com = stripLeadingBlanks(com);
	if (com.length() == 0)return vs;
	if ((com[0] == '/') && (com[1] == '/')) return vs;
	string s;
	while (!is.eof())
	{
		if (vs.size() == 0)
		{
			getline(is, s, ' ');
		}
		else
		{
			getline(is, s, ';');
		}
		vs.push_back(s);
	}
	return vs;
}

void stringToLower(string & s)
{
	for (unsigned int i = 0; i<s.length(); i++)
	{
		s[i] = tolower(s[i]);
	}
}

void stringToUpper(string & s)
{
	for (unsigned int i = 0; i<s.length(); i++)
	{
		s[i] = toupper(s[i]);
	}
}


string padLeft(string s, char fill, unsigned int size)
{
	while (s.length()<size)
	{
		s = fill + s;
	}
	return s;
}

string padRight(string s, char fill, unsigned int size)
{
	while (s.length()<size)
	{
		s = s + fill;
	}
	return s;
}

string intToString(int x)
{
	string result;
	char temp[256];
	_itoa_s(x, temp, 255, 10);
	result = temp;
	return result;
}

string doubleToString(double d)
{
	ostringstream os;
	os << d;
	return os.str();
}

double stringToDouble(string s)
{
	return atof(s.c_str());
}

int stringToInt(string s)
{
	return atoi(s.c_str());
}

int dollarStringToInt(string s)
{
	string s1 = s.erase(s.length() - 3, 1);
	return stringToInt(s1);
}

string intToDollarString(int x)
{
	string result = intToString(x);
	result = padLeft(result, '0', 3);
	result.insert(result.length() - 2, ".");
	return result;
}

string randString(int numOfChars)
{
	string result;
	for (int i = 0; i<numOfChars; i++)
	{
		result += 'A' + rand() % 26;
	}
	return result;
}

string randNumberString(int numOfChars)
{
	string result;
	for (int i = 0; i<numOfChars; i++)
	{
		result += '0' + rand() % 10;
	}
	return result;
}

string stripTrailingBlanks(string s)
{
	while ((s.size()>0) && (s[s.size() - 1] == ' '))
	{
		s = s.substr(0, s.size() - 1);
	}
	return s;
}

string stripLeadingBlanks(string s)
{
	while ((s.size()>0) && (s[0] == ' '))
	{
		s = s.substr(1);
	}
	return s;
}
