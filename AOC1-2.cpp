// AOC2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

string digits[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

int GetFirstDigit(string line)
{
    string original = line;

    int first = -1;

    int min_pos = line.length() + 1;

    for (const auto& digit : digits)
    {
        auto pos = line.find(digit);
        if (pos != string::npos && pos < min_pos)
        {
            min_pos = pos;
            first = distance(begin(digits), find(begin(digits), end(digits), digit));
        }
    }

    for (size_t i = 0; i < min_pos && i < line.length(); ++i)
    {
        if (isdigit(line[i]))
        {
            first = line[i] - '0';
            break;
        }
    }

    return first;
}

int GetLastDigit(string line)
{
    int last = 0;

    for (int j = line.length() - 1; j >= 0; j--)
    {
        if (isdigit(line[j]))
        {
            last = line[j] - '0';

            break;
        }
    }

    string newStr = line.substr(j + 1);

    size_t max_pos = j;

    for (const auto& digit : digits)
    {
        while (!newStr.empty())
        {
            size_t pos = newStr.find(digit);
            if (pos != string::npos)
            {
                last = distance(begin(digits), find(begin(digits), end(digits), digit));
                newStr = newStr.substr(pos + 1);
            }
            else
            {
                break;
            }
        }
    }

    return last;
}

int main()
{
    long sum = 0;

    fstream newFile;

    newFile.open("input.txt", ios::in);

    string line;

    while (getline(newFile, line)) 
    {
        int first = GetFirstDigit(line);

        int last = GetLastDigit(line);

        // Debug output
        //cout << line << " " << first << " " << last << endl;

        sum += first * 10 + last;
    }

    cout << sum;

    newFile.close();
}
