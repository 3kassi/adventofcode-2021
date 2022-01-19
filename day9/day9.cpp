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
  fstream inputData("testinput"); 
  vector<vector<int>> data;
  vector<int> depths;

  while (getline (inputData, line))
  {
    if (line != "") 
    {
      depths.clear();  
      for (std::string::size_type i = 0; i < line.size(); i++)
      { 
        int charToInt = line[i] - '0';
        depths.push_back(charToInt);
      }
      data.push_back(depths); 
    }
  }        
  return data;
}


vector<vector<int>> calcLowPoints(vector<vector<int>> data)
{
  vector<vector<int>> lows;
  vector<int> lowPointXY;
  vector<int> x;
  for (int v = 0; v < data.size(); v++)
  {
    x.clear();
    x = data[v];  
    for (int i = 0; i < x.size(); i++)
    {
      if (v == 0) // first row
      { 
        if (i == 0)  //first row first element
        {
          if ( x[i] < x[i+1]  && x[i] < data[v+1][i]) 
          {
              lowPointXY.clear();
              lowPointXY.push_back(x[i]);
              lowPointXY.push_back(v);
              lowPointXY.push_back(i);
              lows.push_back(lowPointXY);
          }  
        }
        else if (i == x.size() - 1)          // first row last element
        {
          if ( x[i] < x[i-1]  && x[i] < data[v+1][i]) 
          {
            lowPointXY.clear();
            lowPointXY.push_back(x[i]);
            lowPointXY.push_back(v);
            lowPointXY.push_back(i);
            lows.push_back(lowPointXY);
          }    
        }
        // other first row    
        else if(x[i] < x[i-1]  && x[i] < x[i+1]  && x[i] < data[v+1][i]) 
        {
            lowPointXY.clear();
            lowPointXY.push_back(x[i]);
            lowPointXY.push_back(v);
            lowPointXY.push_back(i);
            lows.push_back(lowPointXY);
        }       
      }

      else if ( v == data.size()-1)  // last row
      {
        if (i == 0)  //last row first element
        {
          if ( x[i] < x[i+1]  && x[i] < data[v-1][i]) 
          {
            lowPointXY.clear();
            lowPointXY.push_back(x[i]);
            lowPointXY.push_back(v);
            lowPointXY.push_back(i);
            lows.push_back(lowPointXY);
          }    
        }
        else if (i == x.size() - 1)          // last row last element
        {
          if ( x[i] < x[i-1]  && x[i] < data[v-1][i]) 
          {
            lowPointXY.clear();
            lowPointXY.push_back(x[i]);
            lowPointXY.push_back(v);
            lowPointXY.push_back(i);
            lows.push_back(lowPointXY);
          }    
        }
        // other last row
        else if (x[i] < x[i-1]  && x[i] < x[i+1]  && x[i] < data[v-1][i])
        {
          lowPointXY.clear();
          lowPointXY.push_back(x[i]);
          lowPointXY.push_back(v);
          lowPointXY.push_back(i);
          lows.push_back(lowPointXY);
        }          
      }

      else //  other rows
      {
        if (i == 0)  //other rows first element
        {
          if ( x[i] < x[i+1]  && x[i] < data[v-1][i] && x[i] < data[v+1][i]) 
          {
            lowPointXY.clear();
            lowPointXY.push_back(x[i]);
            lowPointXY.push_back(v);
            lowPointXY.push_back(i);
            lows.push_back(lowPointXY);
          }   
        }
        else if (i == x.size() - 1)          // other rows last element
        {
          if ( x[i] < x[i-1]  && x[i] < data[v-1][i] && x[i] < data[v+1][i]) 
          {
            lowPointXY.clear();
            lowPointXY.push_back(x[i]);
            lowPointXY.push_back(v);
            lowPointXY.push_back(i);
            lows.push_back(lowPointXY);
          }      
        }
        // other in the middle
        else if(x[i] < x[i-1]  && x[i] < x[i+1]  && x[i] < data[v-1][i] && x[i] < data[v+1][i]) 
        {
          lowPointXY.clear();
          lowPointXY.push_back(x[i]);
          lowPointXY.push_back(v);
          lowPointXY.push_back(i);
          lows.push_back(lowPointXY);
        }    
      }   
    }      
  }
  return lows;
}


set<vector<int>> getCoords(set<vector<int>> coords, vector<vector<int>> data)
{
  
  vector<int> xy; 
  bool existsCoord = false;
  for (auto x: coords)
  { 
    cout << "size on " << coords.size();
    cout << x[0] << " " << x[1] << endl;  
    xy.clear();  
    if (x[0] - 1 >= 0 && data[x[0]-1][x[1]] < 9)
    {
      xy.push_back(x[0]-1);
      xy.push_back(x[1]);
      for (auto x :coords) { if (x == xy) {existsCoord = true;}}
      if (!existsCoord) 
      {
        cout << "yles" << endl;
        coords.insert(xy);
        coords = getCoords(coords, data);
      } 
      existsCoord = false;     
    }
    if (x[0] + 1 <= data.size()  && data[x[0]+1][x[1]] < 9)
    {
      xy.push_back(x[0]+1);
      xy.push_back(x[1]);
      for (auto x :coords) { if (x == xy) {existsCoord = true;}}
      if (!existsCoord) 
      {
         cout << "alla" << endl;
        coords.insert(xy);
        coords = getCoords(coords, data);
      } 
      existsCoord = false;     
    }
    if (x[1] - 1 >= 0 && data[x[0]][x[1]-1] < 9)
    {
      xy.push_back(x[0]);
      xy.push_back(x[1]-1);
      for (auto x :coords) { if (x == xy) {existsCoord = true;}}
      if (!existsCoord) 
      {
         cout << "vasakule" << endl;
        coords.insert(xy);
        coords = getCoords(coords, data);
      } 
      existsCoord = false;     
    }
    if (x[1] + 1 <= data[x[0]].size()  && data[x[0]][x[1]+1] < 9)
    {
      cout << " tulem " << data[x[0]][x[1]+1];
      cout << x[0] << " " << x[1];
      xy.push_back(x[0]);
      xy.push_back(x[1]+1);
      for (auto x :coords) {
           if (x == xy) {existsCoord = true;}
           cout << x[0] << " " << x[1] << endl;
           }
      if (!existsCoord) 
      {
        cout<< "xy" << xy[0] << " "<< xy[1];
        cout << "paremale" << endl;
        coords.insert(xy);
        coords = getCoords(coords, data);
      } 
      existsCoord = false;     
    }            
  }
  cout << "pizza" << coords.size() ;
  return coords;
}


int calcSize(vector<vector<int>> data, int x, int y)
{
  int size;
  set<vector<int>> coords;
  vector<int> lowpoint;
  lowpoint.push_back(x);
  lowpoint.push_back(y);
  coords.insert(lowpoint);
  coords = getCoords(coords, data);
  size = coords.size();
  return size;  
}


int calcBasins(vector<vector<int>> data, vector<vector<int>> lows)
{
  int result;
  int basinSize;
  vector<int> sizes;
  for (auto x :lows)
  { 
    cout << x[0]<< x[1]<< x[2];  
    basinSize = calcSize(data, x[1], x[2]);
    sizes.push_back(basinSize);
  }
  sort(sizes.begin(), sizes.end(), greater<int>());
  result = sizes[0] * sizes[1] * sizes[2];
  return result;  
}


int main()
{
  int resultPart1;
  int resultPart2;
  vector<vector<int>> lows;
  vector<vector<int>> data;
  data = getDataFromInput();
  lows = calcLowPoints(data);
  resultPart2 = calcBasins(data, lows);
 // for (auto x : lows) {resultPart1 = resultPart1 + x[0] + 1;}
 // cout << "Answer is " << resultPart1;  
  cout << "Answer is " << resultPart2;  
}