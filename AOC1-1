// AOC1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int GetLineNumber(string line)
{
    int first = 0;
    int last = 0;

    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] >= '0' && line[i] <= '9')
        {
            first = line[i] - '0';

            break;
        }
    }

    for (int j = line.length() - 1; j >= 0 ; j--)
    {
        if (line[j] >= '0' && line[j] <= '9')
        {
            last = line[j] - '0';

            break;
        }
    }

    // Debug output
    // cout << first << " " << last << endl;

    int result = first * 10 + last;

    return result;
}

int main()
{
    long sum = 0;

#pragma region Input String
    std::string input = "";

    istringstream stream(input);
#pragma endregion

    string line = "";

    while (getline(stream, line)) {
        sum += GetLineNumber(line);
    }

    cout << sum;
}
