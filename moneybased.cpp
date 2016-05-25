#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include "Datastruct.h"
#include "moneybased.h"
using namespace std;

extern DATA Data[1000];
extern int routecount;

void MoneyBased(string city_start, string city_end, int &starttime, int &totaltime, int &totalmoney, string path[], int &num)
{
	set<string> S;
	set<string> City(citylist, citylist + sizeof(citylist) / sizeof(*citylist));//set of unvisted nodes
	map<string, int> V;
	map<string, int> ST;
	map<string, int> RM;
	map<string, string>prev;
	set<string>::iterator it;
	map<string, int>::iterator mapit;
	string minC;
	int min = 32766;
	for (it = City.begin(); it != City.end(); it++)
	{
		V.insert(pair<string, int>(*it, 32767));
		RM[*it] = min;
	}
	mapit = V.find(city_start);
	if (mapit != V.end())mapit->second = 0;
	S.insert(city_start);
	City.erase(city_start);
	ST[city_start] = starttime % 24;
	RM[city_start] = 0;
	while (!City.empty())
	{
		for (int i = 1; i <= routecount; i++)
		{

			if (S.count(Data[i].from))
			{
				for (int j = 0; j<Data[i].rNumber; j++)
				{
					if (!S.count(Data[i].dest))
					{
						if (Data[i].TB[j].cost<RM[Data[i].dest] && Data[i].TB[j].start >= ST[Data[i].from])
						{
							ST[Data[i].dest] = Data[i].TB[j].arrival;
							prev[Data[i].dest] = Data[i].from;
							RM[Data[i].dest] = Data[i].TB[j].cost;
							if (RM[Data[i].dest] + V[prev[Data[i].dest]]<V[Data[i].dest])
								V[Data[i].dest] = RM[Data[i].dest] + V[prev[Data[i].dest]];
							//cout << "UPDATE Route from " << Data[i].from << " to " << Data[i].dest << endl;
							//cout << "Start at " << Data[i].TB[j].start << " Arive at " << Data[i].TB[j].arrival << endl;
							//cout << "Moneycost is " << V[Data[i].dest] << endl;
						}
					}
				}
			}
		}
		mapit = V.begin();
		for (; mapit != V.end(); mapit++)
		{

			if (!S.count(mapit->first))//find a node which isn't belongs to set S
			{
				if (V[mapit->first]<min)
				{
					minC = mapit->first;
					min = V[mapit->first];
				}
			}
		}
		min = 32766;
		if (City.count(minC))
		{
			it = City.find(minC);
			S.insert(*it);
			City.erase(*it);
		}
		else
		{
			it = City.begin();
			S.insert(*it);
			City.erase(*it);
		}
		//cout << "City include " << endl;
		//for (it = City.begin(); it != City.end(); it++) //initialize
		//{
		//	cout << *it << " ";//set every node to start node 's distance is INFINITY
		//}
		//cout << endl;
	}
	//system("CLS");
	//mapit = V.begin();
	//for (; mapit != V.end(); mapit++)
	//{
	//	cout << mapit->first << " is " << mapit->second << endl;
	//}
	string temp;
	temp = city_end;
	//cout<<"the route is : ";
	while (temp != city_start)
	{
		//cout<<temp<<"<-";
		temp = prev[temp];
		num++;
	}
	int j = num;
	temp = city_end;
	while (temp != city_start)
	{
		path[j--] = temp;
		temp = prev[temp];
	}
	path[j] = city_start;
	//cout<<city_start<<endl<<"total time is : "<<V[city_end]<<endl;
	totalmoney += V[city_end];
	totaltime += (ST[city_end] - starttime);
}
