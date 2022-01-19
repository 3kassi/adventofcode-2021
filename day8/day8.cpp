/*
0  abcefg   6 chari
1  cf       2 chari 
2  acdeg    5 chari   
3  acdfg    5 chari 
4  bcdf     4 chari 
5  abdfg    5 chari 
6  abdefg   6 chari
7  acf      3 chari  
8  abcdefg  7 chari  
9  abcdfg   6 chari

2 chari  ->  c,f
3 chari - c,f  -> a
6 chari - 4 chari - a -> g
7 chari - 6 chari -> e
5 chari - 3chari  - g -> d
4 chari - c,f,d  - > b

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

int part1()
{  string line;
  regex regexLine("\\| .*");
  regex regexChars("[a-z]+");
  fstream inputData("input");
  smatch digitsLine;
  string digit;
  int count = 0;
  
  vector<int> data;
  
  while (getline (inputData, line))
  {
    if (line != "") 
    {
      regex_search(line, digitsLine, regexLine);
      line = digitsLine[0];
      stringstream str(line); 
	  while(getline(str, digit, ' '))
      {  
        if (digit.size() == 2) {count++;}
        if (digit.size() == 3) {count++;}
        if (digit.size() == 4) {count++;}
        if (digit.size() == 7) {count++;}
      }
    }
  }	
  
  return count;
}


vector<string> getDataFromFilePart2()
{
  string line;
  string stringHor;
  fstream inputData("input");
  vector<string> data;
  
  while (getline (inputData, line))
  {
    if (line != "") {data.push_back(line);}
  //    stringstream str(line);
 
//	  while(getline(str, stringHor, '|'))
 //     {
  //      intHor = stoi(stringHor);
//		data.push_back(intHor);   
  //    }  
  }   
  inputData.close();

  return data;
}


int main()
{
  int result1 = part1();
  vector<string> data;
  data = getDataFromFilePart2();
  for (auto x : data) 
  {
        
  }
  
  //cout << "Answer is " << result1;
  //cout << "Answer is " << result2;
 
}