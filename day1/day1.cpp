#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

vector<int> getDepthsFromFile()
{
  vector<int> depths;
  string depthString;
  std::stringstream stringToInt;
  int    depthInt;  
  fstream sonarDepths("input");

  while (getline (sonarDepths, depthString)){
      stringToInt.clear();
      stringToInt.str(depthString);
      if (stringToInt.rdbuf()->in_avail() != 0)
      {
        stringToInt >> depthInt;
      }  
      depths.push_back(depthInt);
  }   

  sonarDepths.close();
  return depths;

}


int countIncreases(vector<int> depths)
{
  int count = 0;
  
  for (int i = 1; i < depths.size(); i++)
  {
    if (depths[i] > depths[i-1]){count++;}
  }
  
  return count;
}


int getLimitForDepthWindows(int size){
  int limit;
  limit = size - 3;
  return limit;
}


int threeDepthsIncreases(vector<int> depths)
{
  int count = 0;
  int limit = getLimitForDepthWindows(depths.size());
  for (int i = 0; i < limit; i++)
  {
    int sumA = depths[i] + depths[i+1] + depths[i+2];
    int sumB = depths[i+1] + depths[i+2] + depths[i+3];
    if (sumB > sumA){count++;}
  }

    return count;
}


int main()
{
  vector<int> depths;
  int count;
  depths = getDepthsFromFile();
  //count = countIncreases(depths);
  count = threeDepthsIncreases(depths);
  cout << "Measurement increases " << count << " times.";
 
}

