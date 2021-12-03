#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <string>
#include <regex>


using namespace std;

vector<tuple<string, int>> getDirectionsFromFile()
{
  vector<tuple<string, int>> directions;
  string line;
  regex regexpString("[a-z]+");
  regex regexpDigit("[0-9]+");
  tuple<string, int> instruction; 
  smatch direction;
  smatch distance;
  fstream sonarDepths("input");
  
  while (getline (sonarDepths, line)){
      regex_search(line, direction,  regexpString);
      regex_search(line, distance,  regexpDigit);
      instruction = make_tuple(direction[0], std::stoi (distance[0]));
      directions.push_back(instruction);
  
  }   

  sonarDepths.close();
  return directions;

}

int parseDirections(vector<tuple<string, int>> directions)
{
  int result;
  int forward = 0;
  int horizontal = 0;

  for (int i = 0; i < directions.size(); i++)
  {
    if (get<0>(directions[i]) == "up") { horizontal = horizontal - get<1>(directions[i]);}
    if (get<0>(directions[i]) == "down") { horizontal = horizontal + get<1>(directions[i]);}
    if (get<0>(directions[i]) == "forward") { forward = forward + get<1>(directions[i]);}
  }
  result = horizontal * forward;
  return result;
}


int parseDirectionsPart2(vector<tuple<string, int>> directions)
{
  int result;
  int depth = 0;
  int aim = 0;
  int horizontal = 0;

  for (int i = 0; i < directions.size(); i++)
  {
    if (get<0>(directions[i]) == "up") { aim = aim - get<1>(directions[i]);}
    if (get<0>(directions[i]) == "down") { aim = aim + get<1>(directions[i]);}
    if (get<0>(directions[i]) == "forward") {
       horizontal = horizontal + get<1>(directions[i]);
       depth = depth + aim * get<1>(directions[i]); }
  }
  result = depth * horizontal;
  return result;
}

int main()
{
  vector<tuple<string, int>> directions;
  int result;
  directions = getDirectionsFromFile();
  //result = parseDirections(directions);
  result = parseDirectionsPart2(directions);
  cout << "Answer is " << result;
 
}

