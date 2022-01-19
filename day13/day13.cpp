#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <set>
#include <map>

using namespace std;



vector<string> getDataFromInput()
{
  string line;
  vector<string> data;
  fstream inputData("input"); 

  while (getline (inputData, line))
  { 
    if (line != "") 
    {
      data.push_back(line); 
    }   
  }
  return data;
}


vector<vector<int>> getDotsCoords(vector<string> data)
{
  string strCoord;
  int intCoord;
  vector<int> coordToInt;
  vector<vector< int>> dotsCoords;
  for (auto x : data)
  { 
    if (isdigit(x[0]))
    {
      coordToInt.clear();
      stringstream str(x);
   
	    while(getline(str, strCoord, ','))
        {
          intCoord = stoi(strCoord);
          coordToInt.push_back(intCoord);		 
        }
      dotsCoords.push_back(coordToInt);
 
    }
  }
  return dotsCoords;
}


vector<map<string, int>> getFolds(vector<string> data)
{
  regex regex("(fold along )([xy])=([0-9]+)");
  vector<map<string, int>> folds;
  map<string, int> foldCoords;
  smatch smatch;
  for (auto x : data)
  {
    regex_match(x, smatch, regex);
    if (smatch.size()>0)
    {
      foldCoords.clear();
      foldCoords.insert({smatch[2], stoi(smatch[3])});
      folds.push_back(foldCoords);
    }
  
    
  }
  return folds;
}


vector<vector< int>> foldLeft(vector<vector< int>> dotsCoords, int left)
{
  for (int i = 0; i < dotsCoords.size(); i++)
 {
   if(left > dotsCoords[i][1]){dotsCoords[i][1] = left - 1 - dotsCoords[i][1];} 
   if(left < dotsCoords[i][1]){dotsCoords[i][1] = dotsCoords[i][1] - 1 - left;} 
 } 
 sort(dotsCoords.begin(), dotsCoords.end());
 dotsCoords.erase( unique( dotsCoords.begin(), dotsCoords.end() ), dotsCoords.end() );
 
 
 // part 1 return dotsCoords.size();
  return dotsCoords;
}


vector<vector< int>> foldUp(vector<vector< int>> dotsCoords, int up)
{
 for (int i = 0; i < dotsCoords.size(); i++)
 {
   if(up > dotsCoords[i][0]){dotsCoords[i][0] = up - 1 - dotsCoords[i][0];} 
   if(up < dotsCoords[i][0]){dotsCoords[i][0] = dotsCoords[i][0] - 1 - up;} 
 } 
 sort(dotsCoords.begin(), dotsCoords.end());
 dotsCoords.erase( unique( dotsCoords.begin(), dotsCoords.end() ), dotsCoords.end() );
 
 // part 1 return dotsCoords.size();
  return dotsCoords;
}


int getDotCountAfterFolds(vector<vector< int>> dotsCoords, vector<map<string, int>> folds)
{
  int count;
  //part1
  map<string,int> m;
  m = folds[0];
  for (auto x : m){
  //cout << x.first << " " << x.second;
 // if (x.first == "y") {count = foldLeft(dotsCoords, x.second);}
 // if (x.first == "x") {count = foldUp(dotsCoords, x.second);}
  }
  return count;
}


vector<vector< int>> doAllFolds(vector<vector< int>> dotsCoords, vector<map<string, int>> folds)
{
  map<string,int> map;
  for (int i =0; i < folds.size(); i++)
  {
    map = folds[i];
    for (auto x : map)
    {
      if (x.first == "y") {dotsCoords = foldLeft(dotsCoords, x.second);}
      if (x.first == "x") {dotsCoords = foldUp(dotsCoords, x.second);}
    }
  }
  return dotsCoords;  
}


int main()
{
  vector<string> data;
  vector<vector< int>> dotsCoords;
  vector<vector< int>> printout;
  vector<map<string, int>> folds;
  vector<int> reverse;
  vector<int> compare;
  int result1;
  bool exists;

  data = getDataFromInput();
  dotsCoords = getDotsCoords(data);
  
  folds = getFolds(data);
  result1 = getDotCountAfterFolds(dotsCoords, folds);
  dotsCoords = doAllFolds(dotsCoords, folds);

  for (auto x : dotsCoords)
  {
    reverse.clear();
    reverse.push_back(x[1]);
    reverse.push_back(x[0]);
    printout.push_back(reverse);
  }
  sort(printout.begin(), printout.end());

  for (int c = 0; c <= 5; c++)
  {
     for (int j = 0; j <= 39 ; j++)
     {
       exists = false;
       for (auto x : printout)
       {
         if(x[0] == c && x[1] == j){exists = true;}
       }
       if (exists){cout << "#";}
       else {cout << ".";}
     } 
     cout << endl;   
  }
 // cout << "Answer is " << result1;

}
