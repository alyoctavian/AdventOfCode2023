#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

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
    
    fstream newFile;

    newFile.open("input.txt", ios::in);

    string line;

    while (getline(newFile, line)) {
        sum += GetLineNumber(line);
    }

    newFile.close();
    
    cout << sum;
}
