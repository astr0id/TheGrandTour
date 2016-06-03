
#ifndef DATASTRUCT_H
#define DATASTRUCT_H

using namespace std;

struct timetable
{
	int start;
	int arrival;
	int cost;
	string kind;
	string name;
};

typedef struct
{
	string from;
	string dest;
	int rNumber;//Records the number of routes between two citys
	timetable TB[30];
} DATA;

typedef struct 
{
	string currentCity;
	string nextCity;
	int timeleft;
	bool isTravel;
}PassengerData;

typedef struct 
{
	string start;
	string dest;
	int from;
	int arrival;
	int cost;
	string id;
	string kind;
}TBlock;

const string citylist[]= {"A","B","C","D","E","F","G","H","I","J"};


#endif