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
      if (stringToInt != "")
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
    if (depths[i] > depths[i-1]){
    //  cout << i << " " << depths[i-1] << " " << depths[i] <<endl;
      count++;
    }
  
    return count;
}

int main()
{
  vector<int> depths;
  int count;
  depths = getDepthsFromFile();
  count = countIncreases(depths);
  cout << "Measurement increases " << count << " times.";

}

