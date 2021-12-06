#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <sstream>
#include <algorithm>


using namespace std;

vector<int> getDataFromFilePart1()
{
  string line;
  int howMany = 0;
  fstream inputData("input");
  vector<int> data(13);
  
  while (getline (inputData, line))
  {
    if (line != "") 
    {
      ++howMany;
      for (std::string::size_type i = 0; i < line.size(); i++)
      {
        
        int charToInt = line[i] - '0';
        data[i] = data[i] + charToInt;
      }
    
    }
  }   
  data[data.size()-1] = howMany/2;
  inputData.close();
  return data;

}

vector<string> getDataFromFilePart2()
{
  vector<string> data;
  string dataString;
  fstream inputData("input");

  while (getline (inputData, dataString)){
      if (dataString.size() != 0)
      {
        data.push_back(dataString);
      }
  }   

  inputData.close();
  return data;

}


int calculatePart1(vector<int> data)
{
  int result;
  string binaryGamma;
  string binaryEpsilon;

  for (int i = 0; i < data.size()-1; i++)
  {
    if (data[i] > data[data.size()-1])
    {
      binaryGamma = binaryGamma + "1";
      binaryEpsilon = binaryEpsilon + "0";
    }
    else 
    {
      binaryGamma = binaryGamma + "0";
      binaryEpsilon = binaryEpsilon + "1";
    }
  }
  
  result = stoi(binaryGamma, 0, 2) * stoi(binaryEpsilon, 0, 2);
  return result;
}


int getPopular(vector<string> data, int position)
{
  int popular = 0;
 for (int i = 0; i < data.size(); i++)
  {
    int charToInt = data[i][position] - '0';
    popular = popular + charToInt; 
  }
  if (popular > data.size()/2) {popular = 1;}
  else
  {
    if(data.size() % 2 == 0)
    {
      if (popular == data.size()/2) {popular = 1;}
      else {popular = 0;}   
    }
    else {popular = 0;}
  }
  return popular;
}


vector<string> resortData(vector<string>data, int position, int value)
{
  if (data.size() == 1){return data;}
  auto it = std::remove_if(data.begin(), data.end(), [position, value](string s)
  {
    int charToInt = s[position] - '0';
    if (charToInt == value) {
      return false;}
    return true;
  });
  data.erase(it, data.end());
  
  return data;   
}


int calculatePart2(vector<string> data)
{
  int result;
  int oxygenBit;
  int scrubberBit;
  string oxygen;
  string scrubber;
  int position;
  vector<string> dataOxygen;
  vector<string> dataScrubber;

  dataOxygen = data;
  dataScrubber = data;
  
  for (position = 0; position < 12; position++)
  {
    oxygenBit = getPopular(dataOxygen, position);
    scrubberBit = getPopular(dataScrubber, position);
    if (scrubberBit == 1) {scrubberBit = 0;}
    else {scrubberBit = 1;}

    if (dataOxygen.size() == 1) {oxygen = dataOxygen[0];  
    }
    else {dataOxygen = resortData(dataOxygen, position, oxygenBit);}
    
    if (dataScrubber.size() == 1) {scrubber = dataScrubber[0]; }
    else {dataScrubber = resortData(dataScrubber, position, scrubberBit);}
  
  }
  oxygen = dataOxygen[0];  
  
  result = stoi(oxygen, 0, 2) * stoi(scrubber, 0, 2);
  return result;
}


int main()
{
  vector<int> data;
  vector<string> data2;
  
  int result1;
  int result2;


  data = getDataFromFilePart1();
  result1 = calculatePart1(data);

  data2 = getDataFromFilePart2();
  result2 = calculatePart2(data2); 

  //cout << "Answer is " << result1;
  cout << "Answer is " << result2;
 
}

