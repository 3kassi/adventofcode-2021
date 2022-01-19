#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <set>
#include <map>

using namespace std;



map<string, set<string>> getDataFromInput()
{
  string line; 
  fstream inputData("input"); 
  string s;
  map<string, set<string>> data;
  vector<string> matches;
  set<string> paths;
  
  while (getline (inputData, line))
  { 
    matches.clear();  
    if (line != "") 
    {
       stringstream str(line);
 
	   while(getline(str, s, '-'))
       {
		 matches.push_back(s);   
       }  
    }
    data[matches[0]].insert(matches[1]);
    data[matches[1]].insert(matches[0]);
  }
  
  
  
  return data;
}


vector<vector<string> getDataFromInput(map<string, set<string>> data)
{
        
}


int main()
{
  map<string, set<string>> data;
  vector<vector<string>  paths;
  data = getDataFromInput(); 
  paths = findPaths(data);
  return 0;  

}