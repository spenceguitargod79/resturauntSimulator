//Restaurant Class Header File==============================>>>>

//Author: Spencer Healy

//Course: CIST2362

// Specification file for the Restaurant class
#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iomanip>
#include <iostream>
#include <list>
#include <string>

using namespace std;


class Restaurant
{
private:
	string restName;
	string busyLevel2;//holds the string value of the business level.
	int busyLevel;    //holds the int value of the business level.
	int restType;
	string menuTier;//holds the string value for the menu Tier, for displaying to user
	int cookTime; // this will hold a value based on the menu tier
	bool restIsFull;
	int numServers;
	int numTables;

public:
	//default constructor: initialize member variables
	Restaurant()
	{ 
		restName      = "";
		busyLevel2    = "";
		busyLevel     = 0;
		restType      = 0;
		menuTier      = "";
		cookTime      = 0;
		restIsFull    = false;
		numServers    = 0;
		numTables     = 0;

	}

	//constructor
	Restaurant(string rName, int bLevel, int rType, 
		       int nServers, int nTables)
	{
		restName   = rName;
		busyLevel  = bLevel;
		restType   = rType;
		numServers = nServers;
		numTables  = nTables;

	}

	//accessors and methods/ defined in-line
	void setRestName(string rn)
	{
		restName = rn;
	}

	string getRestName()
	{
		return restName;
	}

	void setBusyLevel(int bl)
	{
		busyLevel = bl;
	}

	void setBusyLevel2(string bl2)
	{
		busyLevel2 = bl2;
	}

	string getBusyLevel2()
	{

		return busyLevel2;
	}

	int getBusyLevel()
	{

		return busyLevel;
	}

	void setRestType(int rt)
	{
		restType = rt;
	}

	int getRestType()
	{
		return restType;
	}


	void setIsFull(bool f)
	{
		restIsFull = f;
	}

	bool getIsFull()
	{
		return restIsFull;
	}

	void setNumServers(int ns)
	{
		numServers = ns;
	}

	int getNumServers()
	{
		return numServers;
	}

	void setNumTables(int nt)
	{
		numTables = nt;
	}

	int getNumTables()
	{
		return numTables;
	}

	void setMenuTier(string mt)
	{
		menuTier = mt;
	}

	string getMenuTier()
	{
		return menuTier;
	}

	void printStuff()
	{
		cout << "Resturaunt Name: \t"     << getRestName()      << endl;
		cout << "Total Tables:    \t"     << getNumTables()     << endl;
		cout << "Total Servers:   \t"     << getNumServers()    << endl;
	}
	

};
#endif