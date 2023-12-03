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
    int first = -1;

    int min_pos = line.length() + 1;

    for (int i = 0; i < size(digits); i++)
    {
        size_t pos = line.find(digits[i]);

        if (pos != string::npos)
        {
            if (pos < min_pos)
            {
                min_pos = pos;

                first = i;
            }
        }
    }

    for (int i = 0; i < min_pos; i++)
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

    int j;

    for (j = line.length() - 1; j >= 0; j--)
    {
        if (isdigit(line[j]))
        {
            last = line[j] - '0';

            break;
        }
    }

    int last_pos = j + 1;

    string newStr = line.substr(last_pos, string::npos);

    int max_pos = j;

    for (int i = 0; i < size(digits) && newStr.length() > 0; i++)
    {
        while (newStr.length() > 0)
        {
            size_t pos = newStr.find(digits[i]);

            if (pos != string::npos)
            {
                    last = i;

                    newStr = newStr.substr(pos + 1, string::npos);
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

        cout << line << " " << first << " " << last << endl;

        sum += first * 10 + last;
    }

    cout << sum;

    newFile.close();
}
