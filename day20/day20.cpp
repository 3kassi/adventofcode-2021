#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <set>
#include <map>
#include <algorithm>

using namespace std;



vector<vector<char>> getImageFrominput()
{
    string filename("input");
    FILE* input_file = fopen(filename.c_str(), "r");
    char c;
    vector<vector<char>> image;
    vector<char> line;
    while ((c = fgetc(input_file)) != '\n') 
    {}
    while ((c = fgetc(input_file)) != EOF) 
    {
       cout << c;
       if (c == '\n')
       {
           image.push_back(line);
           line.clear();
       }
       else
       {
        line.push_back(c);
       } 
    }
    image.push_back(line);
    fclose(input_file);
    return image;
}


map<int, char> getAlgoFrominput()
{
    string filename("input");
    FILE* input_file = fopen(filename.c_str(), "r");
    char c;
    map<int, char> algo;
    int i = 0;
    while ((c = fgetc(input_file)) != '\n') 
    {
       algo.insert({i, c});
       i++;   
    }
    fclose(input_file);
    return algo;
}


char enhanceChar(vector<vector<char>> image, map<int, char> algorythm, int lineNumber, int charNumber)
{
  string binary = "";
  char enhancedChar;
  int algoInt;
  
  cout << image[0][1];
  binary += image[lineNumber-1][charNumber-1];
  cout << binary;
  binary = binary + image[lineNumber-1][charNumber];
  binary = binary + image[lineNumber-1][charNumber+1];
  binary = binary + image[lineNumber  ][charNumber-1];
  binary = binary + image[lineNumber  ][charNumber];
  binary = binary + image[lineNumber  ][charNumber+1];
  binary = binary + image[lineNumber+1][charNumber-1];
  binary = binary + image[lineNumber+1][charNumber];
  binary = binary + image[lineNumber+1][charNumber+1];
  
  replace(binary.begin(), binary.end(), '.', '0');
  replace(binary.begin(), binary.end(), '#', '1');
  algoInt = stoi(binary, 0, 2);
  enhancedChar = algorythm.at(algoInt);
   cout << "test";
  return enhancedChar;
}


vector<char> enhanceLine (vector<vector<char>> image, map<int, char> algorythm, int lineNumber)
{
  vector<char> line;
  char enhanced;
 
  for (int c = 0; c < image[lineNumber].size(); c++)
  {
      if( c == 0 || c == image[lineNumber].size() -1)
      {
          line.push_back( image[lineNumber][c]);
      }
      else
      {
         enhanced =  enhanceChar(image, algorythm, lineNumber, c);
         line.push_back(enhanced);
      }
  }
  return line;
}


vector<vector<char>> enhanceImage(vector<vector<char>> image, map<int, char> algorythm, int times)
{
  vector<vector<char>> temp;
  vector<char> line;

  for (int i = 0; i < times; i++)
  {
      temp.clear();
      for (int lineNumber = 0; lineNumber < image.size(); lineNumber++)
      {
        if(lineNumber == 0 || lineNumber == image.size()-1)
        {
            line = image[lineNumber];
            temp.push_back(line);
            line.clear();
        }
        else
        {
            line = enhanceLine(image, algorythm, lineNumber);
            temp.push_back(line);
            line.clear();
        }   
      }
      image = temp;
  }
  return image;     
}


int countLight (vector<vector<char>> image)
{
    int result = 0;
    for (int i = 0; i < image.size(); i++)
    {
        for (int j = 0; j < image[i].size(); j++)
        {
            if ( image[i][j]== '#')
            {
                result++;
            }
        }
    }
    return result;
}


int main()
{
    int result;
    map<int, char> algorythm;
    vector<vector<char>> image;
    int times = 2;

    algorythm = getAlgoFrominput();
    image = getImageFrominput();
    image = enhanceImage(image, algorythm, times);
    result = countLight(image);
    
    cout << " Answer is " << result;
}