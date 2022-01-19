#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <set>

using namespace std;


vector<string> getDataFromInput()
{
  string line; 
  fstream inputData("input"); 
  vector<string> data;

  while (getline (inputData, line))
  {
    if (line != "") 
    {
      data.push_back(line); 
    }
  }        
  return data;
}


char checkForError1(string line)
{ 
  stack <char> s;
  char error;  
  for (auto x : line)
  {
    if (x == '<' || x == '(' || x == '[' || x == '{')
    {s.push(x);}
    else if ((x == '>' && s.top() == '<') || (x == ')' && s.top() == '(') ||
      (x == '}' && s.top() == '{') || (x == ']' && s.top() == '['))
      { s.pop();}
    else 
    {
       return x;
    }           
  }
  return '0'; 
}


int part1 (vector<string> data)
{
  char error;
  int result;
  for (auto x : data)
     {
       error = checkForError1(x);
       switch (error)
       {
         case ')':
           result = result + 3;
           break;
         case '>':
           result = result + 25137;
           break;
         case '}':
           result = result + 1197;
           break;
         case ']':
           result = result + 57;
           break;
         case '0': 
           break;
       }   
     }
  return result;     
}


string checkForError2(string line)
{ 
  stack <char> s;
  char error;  
  string finishLine;
  for (auto x : line)
  {
    if (x == '<' || x == '(' || x == '[' || x == '{')
    {s.push(x);}
    else if ((x == '>' && s.top() == '<') || (x == ')' && s.top() == '(') ||
      (x == '}' && s.top() == '{') || (x == ']' && s.top() == '['))
      { s.pop();}
    else 
    {
      return "";
    }           
  }
  while (!s.empty())
  {
    finishLine = finishLine + s.top();
    s.pop();    
  }
  return finishLine; 
}


unsigned long long calcPoints(string line)
{
  unsigned long long result = 0;
  unsigned long long five = 5;
  unsigned long long four = 4;
  unsigned long long three = 3;
  unsigned long long two = 2;
  unsigned long long one = 1;
  for (auto x : line)
  {
    unsigned long long resultold = result;
    result = five * result;
         
    switch (x)
       {
         case '(':
           result = result + one;
           break;
         case '<':
           result = result + four;
           break;
         case '{':
           result = result + three;
           break;
         case '[':
           result = result + two;
           break;
       }   
  }
  return result;
}


int part2 (vector<string> data)
{
  unsigned long long result;
  int middle;
  string finishLine;
  vector<unsigned long long> points;
  unsigned long long resultPoints;
  for (auto x : data)
     {
       finishLine = checkForError2(x);
       if (finishLine != "")
       {
         resultPoints = calcPoints(finishLine);
         points.push_back(resultPoints);
       }  
     }
   sort(points.begin(), points.end(), greater<unsigned long long >());
   
   middle = points.size()/2;
   result = points[middle];  
   return result;     
}


int main()
{
    int resultPart1;
    unsigned long long resultPart2;
    
    vector<string> data;
    data = getDataFromInput();
    resultPart1 = part1(data);
    resultPart2 = part2(data);
    
     cout << "Part1 is " << resultPart1 << endl;
     cout << "Part2 is " ;
     printf("%lu", resultPart2);
}