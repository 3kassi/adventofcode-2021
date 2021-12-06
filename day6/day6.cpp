#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <sstream>
#include <algorithm>


using namespace std;


vector<unsigned long long> getDataFromFilePart1()
{
  string line;
  int charToInt;
  fstream inputData("input");
  vector<unsigned long long> data(9);
  
  while (getline (inputData, line))
  {
    if (line != "") 
    {
      for (std::string::size_type i = 0; i < line.size(); i++)
      { 
        if (isdigit(line[i]))
        {   
          int charToInt = int(line[i]) - 48;
          data[charToInt]++;
        }
      }
    
    }
  }   
  inputData.close();
  return data;

}



vector<unsigned long long> day(vector<unsigned long long> data)
{
  vector<unsigned long long> newData(9);
  for (int i =1; i < data.size(); i++)
    {
      newData[i-1] = data[i];
    } 
  newData[6] = newData[6] + data[0];
  newData[8] = data[0];
  return newData;  
}


int main()
{
  vector<unsigned long long> lanternFish;
  unsigned long long count = 0;
  lanternFish = getDataFromFilePart1();

  for (int i = 1; i <= 256; i++)
  {
   lanternFish = day(lanternFish); 
  }
  for (int i =0; i < lanternFish.size(); i++)
  {
    count = count + lanternFish[i];
  }
 cout << "Answer is " << count ;
 
}

