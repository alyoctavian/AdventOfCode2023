#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

std::map<string, int> dataMap{ {"blue", 14}, {"green", 13}, {"red", 12}};

int CalculatePossibleGames()
{
    int sum = 0;

    fstream newFile;

    newFile.open("input.txt", ios::in);

    string line;

    int index = 1;

    while (getline(newFile, line))
    {
        // Process each line
        stringstream ssLine(line);

        vector<string> result;

        std::size_t prev = 0, pos;
        while ((pos = line.find_first_of(" ,:;", prev)) != std::string::npos)
        {
            if (pos > prev)
                result.push_back(line.substr(prev, pos - prev));
            prev = pos + 1;
        }

        if (prev < line.length())
        {
            result.push_back(line.substr(prev, std::string::npos));
        }

        bool valid = true;

        for (int i = result.size() - 1; i >= 3; i -= 2)
        {
            if (stoi(result[i - 1]) > dataMap[result[i]])
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            sum += index;
        }

        // Increase the index of the game
        index++;
    }

    newFile.close();

    return sum;
}

int main()
{
    cout << CalculatePossibleGames();
}
