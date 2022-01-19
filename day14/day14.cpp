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


string addChars(string polymer, map<int, char> positions)
{
  string newPolymer;
  for (int i = 0; i < polymer.size(); i++)
  {
    newPolymer = newPolymer + polymer[i];
    if (positions.count(i) > 0)
    {
      newPolymer = newPolymer + positions.find(i)->second;  
    }  
  }
  return newPolymer;    
}
map<string, unsigned long long> doStep1(string polymer, map<string, char> rules)
{

  map<int, char> positions;
  map<string, unsigned long long> store;
  vector<string> pairs;
  
    for (int pos = 0; pos < polymer.size()-1; pos++)
    {
      if (rules.count(polymer.substr(pos, 2)) > 0)
      {
        string firsthalf = polymer.substr(pos,1) + rules.find(polymer.substr(pos ,2))->second; 
        string secondhalf = rules.find(polymer.substr(pos ,2))->second +polymer.substr(pos+1,1); 
        pairs.push_back(firsthalf);
        pairs.push_back(secondhalf);
      }
      else{
          pairs.push_back(polymer.substr(pos, 2));
      }
    }
    for (int i=0; i < pairs.size(); i++)
    {
      if (store.count(pairs[i]) == 0)
      {
        store.insert({pairs[i], 1}); 
      } 
      else
      {
        store.at(pairs[i])++; 
      }    
    }
   
 
  return store;
}


unsigned long long getResult(map<string, unsigned long long> store, char c)
{
  map<char, unsigned long long> charCounts;
  unsigned long long smallest;
  unsigned long long biggest;
  unsigned long long result;
  
   for (auto const &pair: store)
   {
      
      if (charCounts.count(pair.first[0]) == 0)
      {
        charCounts.insert({pair.first[0], pair.second}); 
      } 
      else
      {
         charCounts.at(pair.first[0]) = charCounts.at(pair.first[0]) + pair.second; 
      }    
   }

   charCounts.at(c)++;
   biggest = 0;

  for (auto const &pair: charCounts)
   {
     
     if (pair.second > biggest){biggest = pair.second;}  
   }
   smallest = biggest;
   for (auto const &pair: charCounts)
   {
     if (pair.second < smallest){smallest = pair.second;} 
    if (pair.second < smallest){smallest = pair.second;}  
   }
  cout << biggest << " - " << smallest<< endl; 
  result = biggest - smallest;
  return result;
}


map<string, unsigned long long> otherSteps(map<string, unsigned long long> store, map<string, char> rules)
{

  vector<string> pairs;
   map<string, unsigned long long> tempStore;
  
  for (auto x: store)
  { 
      pairs.clear();
      if (rules.count(x.first) > 0)
      {
        string firsthalf = x.first.substr(0,1) + rules.find(x.first)->second; 
        string secondhalf = rules.find(x.first)->second + x.first.substr(1,1); 
        pairs.push_back(firsthalf);
        pairs.push_back(secondhalf);
      }
      else{
          pairs.push_back(x.first);
          }
      for (int i =0; i < pairs.size(); i++)
      {
        if (tempStore.count(pairs[i]) == 0)
      {
        tempStore.insert({pairs[i], x.second}); 
      } 
      else
      {
        tempStore.at(pairs[i]) = tempStore.at(pairs[i]) + x.second; 
      }    
      }    
  }
   
  store = tempStore;
  return store;
}


int main()
{
    vector<string> data;
    string polymer;
    map<string, char> rules;
    unsigned long long result;
    char lastCharofPolymer;
    data = getDataFromInput();
    polymer = data[0];
    lastCharofPolymer = polymer.back();
    
    int stepCount = 40;
    map<string, unsigned long long> store;

    for (int i =1; i < data.size(); i++)
    {
      rules.insert({data[i].substr(0,2), data[i].back()});
    }
    store = doStep1(polymer, rules);
    
    for (int i = 2; i <= stepCount; i++)
    {
      store = otherSteps(store, rules);
      cout << i << endl;
    }
    result = getResult(store, lastCharofPolymer);

    cout <<  "Answer is " << result;
}
/*
NNCB
After step 1: NCNBCHB
After step 2: NBCCNBBBCBHCB
After step 3: NBBBCNCCNBBNBNBBCHBHHBCHB
After step 4: NBBNBNBBCCNBCNCCNBBNBBNBBBNBBNBBCBHCBHHNHCBBCBHCB
              NBBNBNBBCCNBCNCCNBBNBBNBBBNBBNBBCBHCBHHNHCBBCBHCB
*/