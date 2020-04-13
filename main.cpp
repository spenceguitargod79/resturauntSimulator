//++++++++++++++++++++++++++++++++++++++
// RESTURAUNT SIMULATION
// Author: Spencer Healy
// C++2 Final Project
//++++++++++++++++++++++++++++++++++++++

//INCLUDES
#include <list>
#include <vector>
#include <stack>
#include <string>
#include <queue> 
#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>

//HEADER FILES
#include "Restaurant.h"
#include "Party.h"
#include "Server.h"

using namespace std;


//FUNCTION PROTOTYPES
ostream& operator<<(ostream&, Party&);
bool restartMenu(char reply);//send in users Y or N answer
int getInput(int, int); //this will check for valid user input



int main() 
{
	
	//VARIABLES
	int firstChoice; // used to determine file input or manual input.
	string fileName; // this will hold the users filename
	string name;//User name
	string rName;//restaurant name
	int bLevel;//level of business
	int rType;//type of resturaunt
	int nTables;//total tables in the resturaunt
	int numberOfServers = 0;
	int numberOfMinutes = 180;
	double totalWait = 0;
	int numberOfParties = 0;
	int partySize; //the size can be from 1 - 4 people (random).
	static int totalOfPartySizes = 0; // this will be used to divide by the numberOfParties to get an average party size.
	string serverSkill = "";
	char answer;//to hold the yes or no answer from user, for restarting the program
	static double totalProcessTime; // this will hold the result of processTime / numOfParties
	static int partiesWaiting = 0; // this will be used to store a total of the number of waiting parties each time / numberOfParties
	static int playCount = 0; //this variable will hold the amount of times the user runs the program in one session
	static int hrsPassed = 0;// add 24 each tim a sim is ran.

	

	//create an array of strings to hold complaints
	const int ARRAY_SIZE = 6;
	string complaints[ARRAY_SIZE] = {"\"My steak tastes like chicken.\"", "\"There's a grasshopper in my coke.\"", 
									 "\"I dont mean to complain, but the food here sucks.\"", "\"This ketchup tastes like ketchup.\"",
									 "\"I don't mean to be a $%^&*, but the last few times i ate here the food was horrible.\"", 
									 "\"Why is there a chicken feather in my tomato soup?\""};
									
	
	//file object
	ifstream inFile;

	srand(time(NULL));//time setup

	bool keepGoing = true;//used to restart the program
	while(keepGoing == true)//runs this loop the first time, and then again when the user sends 'Y' or 'y' into answer.
	{
		//reset these values for when the loop is ran again
		numberOfParties = 0;
		partiesWaiting = 0;

		//add 24 each time the sim is ran
		hrsPassed += 24;

		playCount += 1; //add 1 each time this while loop is ran

		int customerComplaintCount = 0 + rand() % 6;// a random number of complaints

		//GET USER INPUT+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		cout << "\nWELCOME TO RESTAURANT SIMULATOR 1.0!\n";
		cout << "Designed by Spencer Healy\n";
		cout << "************************************************\n\n";

		//let the user decide to load in a file, or input configuration manually
		cout << "Enter 1 to load configuration from a file\n";
		cout << "Enter 2 to enter configuration manually\n";
		firstChoice = getInput(1, 2); // check for valid input
		cout << "\n";

		//load file, set appropriate variables line by line
		if (firstChoice == 1)
		{
			cout << "Your file must be set up like this...\n\n";
			cout << "Your Name\n";
			cout << "Resturaunt Name\n";
			cout << "Business Level: 1 = slow, 2= busy, 3 = slammed\n";
			cout << "Resturaunt Type: 1 = continental, 2 = bistro, 3 = gourmet\n";
			cout << "Total Tables in the resturaunt\n";
			cout << "# of servers working today\n\n";
			cout << "Now enter the filename: (example: restaurant.txt)";
			cin  >> fileName;

			//open the file
			inFile.open(fileName.c_str());

			//if the file successfully opened, process it
			if (inFile)
			{
				//read in lines from the file and assign them to variables 
				getline (inFile, name);
				getline (inFile, rName);
				inFile >> bLevel;
				inFile >> rType;
				inFile >> nTables;
				inFile >> numberOfServers;

				inFile.close();//close the file

			}
			else 
			{
				//display an error message if the file doesn't exist
				cout << "\nError Opening the File!\n";
				cout << "Restart the program and try again.\n\n";
				return 0;
			}
		}
		else
		{
			cout <<"\nEnter your name please\n";
			getline (cin, name);
			cout << "\n";

			cout << "Hi, " << name << " !\n";
			cout << "Enter your restaurant's name.\n";
			getline (cin, rName);
			cout << "\n";

			//check to make sure the user enters the proper number 
			//before sending it to the class.
			cout << "BUSINESS LEVEL:\n";
			cout << "Enter 1 for SLOW, 2 for BUSY, or 3 for SLAMMED ";
			bLevel = getInput(1, 3); // check for valid input
			cout << "\n";

			//check to make sure the user enters the proper number 
			//before sending it to the class.
			cout << "RESTAURANT TYPE:\n";
			cout << "Enter 1 for Continental, 2 for Bistro, or 3 for Gourmet ";
			rType = getInput(1, 3); // check for valid input
			cout << "\n";

			cout << "How many total tables are there in this " << rName << " location?\n";
			nTables = getInput(1, 100); // check for valid input
			cout << "\n";

			cout << "How many servers are working today?\n";
			numberOfServers = getInput(1, 20); // check for valid input
			cout << "\n";
		}


		//Initialize configuration+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		//create an instance of the class and send it arguments from user or file input
		Restaurant restaurant(rName, bLevel, rType, numberOfServers, nTables);

		totalOfPartySizes = 0; //reset this value 

		//create a vector for the Server class
		vector<Server> server(numberOfServers); 

		//create a queue for the party class and name it line.
		queue<Party, list<Party> > line;


		// maintain simulation time 
		for (int time = 0; time < numberOfMinutes; time++) 
		{ 
			cout << "Time " << time << ":" << endl;
		
			// a new Party may arrive 5% of the time each minute
			if ((rand() % 5) < 9)	
			{ 
				//first party
				Party newParty(time);
				line.push(newParty);

				//do this to make output a little more realistic
				if (numberOfServers > 4)
				{
					totalWait+= 10 + rand() % 25;
				}

				// a random party size from 1-4
				partySize = 1 + rand() % 4;
				totalOfPartySizes += partySize; // add the current partySize to this static int variable, later divide by the total number of parties.
				cout << "Party Size: " << partySize << endl;
				cout << "\t++Party Arrives " << newParty << endl;
			
			}	
		
			// check the status of each Server. If one is available and
			// a party is waiting then they should be helped.
			for (int i = 0; i < numberOfServers; i++)
			{
				if (server[i].isFree() & ! line.empty())
				{ 
					//add one party to the server
					Party frontCustomer = line.front();
					numberOfParties++;
					partiesWaiting += numberOfParties;
					totalWait += (time - frontCustomer.arrival()); 

					cout << "\t**Party serviced " << frontCustomer;
					cout << "by Server #" << i << endl;

					totalProcessTime = frontCustomer.remain() * 5;
					cout << "\n\t**Process Time for this party: " << totalProcessTime << " minutes" << endl << endl;
					
					server[i].addParty(frontCustomer); 

					line.pop();

				} 
			}
		}


		cout << "\n******** CONFIGURATION *******************\n";
		cout << "\nManager: " << "\t\t" << name << endl;
		//display data that was just sent into the class constructor
		restaurant.printStuff();

		//set the string value of busyLevel2 in the Resturaunt class,
		//based on what the user enters for busyLevel.
		if (restaurant.getBusyLevel() == 1)
			{
				restaurant.setBusyLevel2("Slow");
				totalWait -= 5 + rand() % 10; // subtract from the total wait time if slow
			}
			else if (restaurant.getBusyLevel() == 2)
			{
				restaurant.setBusyLevel2("Busy");
				totalWait += 10 + rand() % 15; //add to total wait time if Busy
			}
			else if (restaurant.getBusyLevel() == 3)
			{
				restaurant.setBusyLevel2("Slammed");
				totalWait += 15 + rand() % 25; //add to total wait time if slammed
				customerComplaintCount+= 2; //add a litle to the complaint count if slammed


			}
		cout << "Business Level: \t" <<  restaurant.getBusyLevel2() << endl;

		//set the string value of menuTier in the Resturaunt class,
		//based on what the user enters for restType.
		if (restaurant.getRestType() == 1)
			{
				restaurant.setMenuTier("Continental");
				totalProcessTime += 1 + rand() % 5;
			}
			else if (restaurant.getRestType() == 2)
			{
				restaurant.setMenuTier("Bistro");
				totalProcessTime += 10 + rand() % 12;
			}
			else if (restaurant.getRestType() == 3)
			{
				restaurant.setMenuTier("Gourmet");
				totalProcessTime += 15 + rand() % 30;
			}
		cout << "Menu Tier: \t\t" <<  restaurant.getMenuTier() << endl;

		//set the string value of serverSkill from main(),
		//based on what the user enters for restType.
		if (restaurant.getRestType() == 1)
			{
				serverSkill = "Noob";
				totalProcessTime += 1 + rand() % 5;
			}
			else if (restaurant.getRestType() == 2)
			{
				serverSkill = "Seasoned";
				totalProcessTime += 3 + rand() % 5;
			}
			else if (restaurant.getRestType() == 3)
			{
				serverSkill = "Expert";
				totalProcessTime += 1 + rand() % 2;
			}
		cout << "Overall Server Skill: \t" <<  serverSkill << endl;


		cout <<"\n************ TODAY's STATISTICS ******************************\n"; 
		// output stats related to average waiting time and others
		cout << fixed << setprecision(2);
		cout << "\nTotal Simulations Completed: \t" << playCount << endl;
		cout << "Total Hours: \t\t\t" << hrsPassed << endl;
		cout <<	"Average wait per Party: "  << "\t" << (totalWait / numberOfParties) << " minutes\n";
		cout << "Total Number of Parties:        "  <<  numberOfParties << endl;
		cout << "Average Parties Waiting:        "  <<  (partiesWaiting / numberOfParties) / 4    <<   endl;
		cout << "Average Party Size:             "  <<  totalOfPartySizes / numberOfParties       << endl;
		cout << "Average Turnaround Time:        "  << (totalProcessTime * 100) / numberOfParties << " minutes" << endl;
		cout << "Total Customer Complaints:      "  << customerComplaintCount << endl;
		cout << "Drunkards removed:              "  << 0 + rand() % 2  << endl;

		//print a random customer complaint if a complaint exists
		if (customerComplaintCount > 0)
		{
			cout << "Complaint of the day:           "  << complaints[0 + rand() % ARRAY_SIZE] << endl << endl;
		}
		else
			cout << "Complaint of the day:           "  << "No complaint's today!" << endl << endl;

		cout << "\n" << rName << " is officially closed for the day.\n";

		//ask the user if they want to run the simulation again
		//send the answer into the restartMenu function for testing
		cout << "\n\nWould you like to start over?";
		cout << "\nPress Y to restart, or any other key to exit. ";
		cin  >> answer;
		keepGoing = restartMenu(answer);
	}

	
	return 0;
}



//********** FUNCTION DEFINITIONS ******************************

ostream& operator<<(ostream& os, Party& c) 
{
	os << "{ Arrival Time= " << c.arrival() << ", Wait Time= " << c.remain() << "} ";		
	return os;
}


//send in users Y or N answer, rerun main if yes, exit program if no.
bool restartMenu(char reply)
{
	char answer = reply;

	if (answer == 'Y' || answer == 'y')
	{
		cout << "\nINITIALIZING RESTART....\n";
		return true;
	}
	else 
		cout << "\nTERMINATING PROGRAM.... \n" << endl;
		exit(1);
}

//send in begin and end, test input, and returns input if valid
int getInput(int begin, int end)
{

		string str = "";
		int input = 0;
		getline(cin, str); 
		
			 
			 while (true) 
			 {
			   //Converts from string to number safely.
			   stringstream myStream(str);
			   if (myStream >> input)
				   if (input <= end && input >= begin)
					break;
				   
			   cout << "Invalid Input, try again.";
			   getline(cin, str); 
			 }
			 return input;

}

