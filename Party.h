// RESTURAUNT SIMULATION
// Party class header file

//Author: Spencer Healy

//C++2 Final Project

// Specification file for the Party class
#ifndef PARTY_H
#define PARTY_H

#include <string>
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

class Server;//forward declaration

// class Party
// a single Party waiting in line to be sat
class Party
{
public:
	// constructors
	Party (int at) 
	{
		arrivalTime	= at;
		processTime = 2 + (rand() % 6);
	} 		

	Party () : arrivalTime(0), processTime(0) 
	{ 
	}
	
	// operations
	bool done () 
	{ 
		return --processTime == 0; 
	} 
	int arrival () 
	{ 
		return arrivalTime; 
	}
	
	int remain() 
	{ 
		return processTime; 
	}
	
	// order by arrival time 
	bool operator<(const Party & c) 
	{ 
		return arrivalTime < c.arrivalTime; 
	}

	// no two Partys are alike
	bool operator==(const Party & c) 
	{ 
		return false; 
	}
	
	// friend ops
	friend ostream& operator<<(ostream&, Party&);
	
protected:
	unsigned int arrivalTime; 
	unsigned int processTime;
};
#endif