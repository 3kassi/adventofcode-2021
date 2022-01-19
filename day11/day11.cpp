#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <set>

using namespace std;


vector<vector<int>> getDataFromInput()
{
  string line; 
  fstream inputData("input"); 
  vector<vector<int>> data;
  vector<int> energys;

  while (getline (inputData, line))
  {
    if (line != "") 
    {
      energys.clear();  
      for (std::string::size_type i = 0; i < line.size(); i++)
      { 
        int charToInt = line[i] - '0';
        energys.push_back(charToInt);
      }
      data.push_back(energys); 
    }
  }        
  return data;
}


vector<vector<int>> getNearCoords(int linesCount, int lineLength, int line, int element)
{
  vector<vector<int>> nearCoords;
  vector<int> Coords;
  if (line - 1 >= 0)
  {
    if (element - 1 >= 0)
    {
      Coords.push_back(line - 1);  
      Coords.push_back(element - 1);  
      nearCoords.push_back(Coords); 
      Coords.clear(); 
    }
    if (element + 1 < lineLength)
    {
      Coords.push_back(line - 1);  
      Coords.push_back(element + 1);  
      nearCoords.push_back(Coords);
      Coords.clear();  
    }
      Coords.push_back(line - 1);  
      Coords.push_back(element);  
      nearCoords.push_back(Coords);
      Coords.clear(); 
  }
  if (line + 1 < linesCount)
  {
    if (element - 1 >= 0)
    {
      Coords.push_back(line + 1);  
      Coords.push_back(element - 1);  
      nearCoords.push_back(Coords);
      Coords.clear();  
    }
    if (element + 1 < lineLength)
    {
      Coords.push_back(line + 1);  
      Coords.push_back(element + 1);  
      nearCoords.push_back(Coords);
      Coords.clear();  
    }
      Coords.push_back(line + 1);  
      Coords.push_back(element);  
      nearCoords.push_back(Coords);
      Coords.clear(); 
  }
  if (element - 1 >= 0)
  {
      Coords.push_back(line );  
      Coords.push_back(element - 1);  
      nearCoords.push_back(Coords);
      Coords.clear();  
  }
  if (element + 1 < lineLength)
  {
      Coords.push_back(line );  
      Coords.push_back(element + 1);  
      nearCoords.push_back(Coords);
      Coords.clear();  
  }

  return nearCoords;  
}


vector<vector<int>> stepEnd(vector<vector<int>> data)
{
  for (int i = 0; i < data.size(); i++)
  {
    for (int j = 0; j < data[i].size(); j++)
    {
      data[i][j]++;
      if (data[i][j] > 9) {data[i][j] = 0;}       
    }  
  }  
  return data;
}


int steps(vector<vector<int>> data, int stepCount, string part)
{
  vector<vector<int>> nearCoords;
  vector<vector<int>> flashed; 
  vector<int> flashCoords;
  int flashes = 0;
  bool thereWasFlash;
  bool alreadyFlashed;
  
  for (int i = 1; i <= stepCount; i++)
  {
    flashed.clear();
    thereWasFlash = true;  
    while (thereWasFlash)
    {  
      thereWasFlash = false;  
      
      for (int j = 0; j < data.size(); j++)
      {
        for (int k = 0; k < data[j].size(); k++)
        {
          if (data[j][k] >= 9)
          {
            alreadyFlashed = false;
            for (auto x : flashed)
            {
              if (x[0] == j && x[1] == k){alreadyFlashed = true;}    
            }
            if (!alreadyFlashed)  
            {
              thereWasFlash = true;
              flashes++;
              flashCoords.clear();
              flashCoords.push_back(j);
              flashCoords.push_back(k);
              flashed.push_back(flashCoords);
              data[j][k] = 10;
              nearCoords = getNearCoords(data.size(), data[j].size(), j, k);
              for(auto x : nearCoords)
              {
                data[x[0]][x[1]]++; 
                
              }
            }  
          }     
        }    
      }       
    }
    data = stepEnd(data);
    if (part == "part2" && flashed.size() == (data.size() * data[0].size())) {return i;}
  }    
  return flashes;
}


int main()
{
    int result;
    vector<vector<int>> data;
    data = getDataFromInput();
    result = steps(data, 1000, "part2");

    cout << "Answer is " << result;
}
