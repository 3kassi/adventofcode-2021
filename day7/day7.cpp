#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <functional>


using namespace std;


vector<int> getDataFromFilePart1()
{
  string line;
  string stringHor;
  int intHor;
  fstream inputData("input");
  vector<int> data;
  
  while (getline (inputData, line))
  {
    if (line != "") 
    {
      stringstream str(line);
 
	  while(getline(str, stringHor, ','))
      {
        intHor = stoi(stringHor);
		data.push_back(intHor);   
      }  
    }
  }   
  inputData.close();

  return data;

}


int getDistancePart1(vector<int> data, int cheapest)
{
  int distance = 0;  
  for (auto x : data)
  {
    distance = distance + abs(cheapest - x); 
  }
  return distance;
}


double getCheapestPart2(vector<int>data)
{
  double average = accumulate(data.begin(), data.end(), 0);
  average = average/data.size();
  return average;
}

int getFuel(int distance)
{
  int fuel = 0;
  for (int i =1; i <= distance; i++)
  {
    fuel = fuel + i;    
  }

  return fuel;
}


int getDistancePart2(vector<int> data, int cheapest)
{
  int distance = 0;
  for (auto x : data)
  {
    int fuel = getFuel(abs(cheapest - x));
    distance = distance + fuel; 
  }
  return distance;
}


int main()
{
  vector<int> data;  
  data = getDataFromFilePart1();
  sort(data.begin(), data.end());
  int cheapestPart1 = data[ceil((double)data.size()/2) -1];
  int distancePart1 = getDistancePart1(data, cheapestPart1);
  double cheapestPart2 = getCheapestPart2(data);  
  int distancePart2Ceil = getDistancePart2(data, ceil(cheapestPart2));
  int distancePart2Floor = getDistancePart2(data, floor(cheapestPart2));
  if (distancePart2Ceil < distancePart2Floor) { cout << "Answer is "  << distancePart2Ceil;}
  else { cout << "Answer is "  << distancePart2Floor;}
 // cout << "Answer is "  << distancePart1;
}