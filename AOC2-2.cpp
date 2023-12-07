#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

std::map<string, int> dataMap{ {"red", 0}, {"green", 1}, {"blue", 2} };

int CalculatePossibleGames()
{
    int sum = 0;

    fstream newFile;

    newFile.open("input.txt", ios::in);

    string line;

    while (getline(newFile, line))
    {
        int nums[3] = { 0, 0, 0 };

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

        for (int i = result.size() - 1; i >= 3; i -= 2)
        {
            if (stoi(result[i - 1]) > nums[dataMap[result[i]]])
            {
                nums[dataMap[result[i]]] = stoi(result[i - 1]);
            }
        }

        int product = 1;

        for (int j = 0; j < 3; j++)
        {
            if (nums[j] > 0)
            {
                product *= nums[j];
            }
        }

        sum += product;
    }

    newFile.close();

    return sum;
}

int main()
{
    cout << CalculatePossibleGames();
}
