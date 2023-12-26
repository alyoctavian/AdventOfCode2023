#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

const int SIGN_VALUE = -1;

vector<pair<int, bool*>> curr;
vector<pair<int, bool*>> above;

int sum = 0;

bool IsValidNum(int pos, vector<pair<int, bool*>> v)
{
    if (v[pos].first <= 0)
    {
        return false;
    }

    if (pos > 0 && v[pos - 1].first > 0 && *v[pos].second == true)
    {
        return false;
    }

    *v[pos].second = true;

    return true;
}

void ProcessSign(int pos)
{
    if (pos > 0 && curr[pos - 1].first > 0)
    {
        cout << curr[pos - 1].first << endl;
        sum += curr[pos - 1].first;
    }

    if (pos > 0 && IsValidNum(pos - 1, above))
    {
        cout << above[pos - 1].first << endl;
        sum += above[pos - 1].first;
    }

    if (IsValidNum(pos, above))
    {
        cout << above[pos].first << endl;
        sum += above[pos].first;
    }

    if (pos < above.size() - 1 && IsValidNum(pos + 1, above))
    {
        cout << above[pos + 1].first << endl;
        sum += above[pos + 1].first;
    }
}

bool IsUnderSign(int pos)
{
    if (pos > 0 && above[pos - 1].first < 0)
    {
        return true;
    }

    if (above[pos].first < 0)
    {
        return true;
    }

    if (pos < above.size() - 1 && above[pos + 1].first < 0)
    {
        return true;
    }

    return false;
}

int ProcessNumber(int pos, string line)
{
    bool underSign = false;

    int index = pos + 1;

    int number = line[pos] - '0';

    bool* isChecked = new bool;

    *isChecked = false;

    curr[pos].second = isChecked;

    if (IsUnderSign(pos))
    {
        underSign = true;
    }

    while (isdigit(line[index]) && index < line.length())
    {
        number = number * 10 + line[index] - '0';

        curr[index].second = isChecked;

        if (IsUnderSign(index))
        {
            underSign = true;
        }

        index++;
    }

    if (pos > 0 && curr[pos - 1].first < 0)
    {
        cout << number << endl;
        sum += number;
    }
    else if (underSign)
    {
        cout << number << endl;
        sum += number;
    }

    return number;
}

void ProcessCurrent(string line)
{
    for (int i = 0; i < line.length(); i++)
    {
        if (!isdigit(line[i]) && line[i] != '.')
        {
            curr[i].first = SIGN_VALUE;

            ProcessSign(i);
        }
        else if (i > 0 && curr[i - 1].first > 0 && isdigit(line[i]))
        {
            curr[i] = curr[i - 1];
        }
        else if (isdigit(line[i]))
        {
            curr[i].first = ProcessNumber(i, line);
        }
    }
}

void PrintCurrent(string line)
{
    cout << line;

    cout << endl;

    for (int i = 0; i < curr.size(); i++)
    {
        cout << curr[i].first << endl;
    }

    cout << endl << endl;
}

int main()
{
    fstream newFile;

    newFile.open("input.txt", ios::in);

    string line;

    pair<int, bool*> standardPair;

    standardPair.first = 0;
    standardPair.second = nullptr;

    getline(newFile, line);

    curr.resize(line.length());
    std::fill(curr.begin(), curr.end(), standardPair);

    above.resize(line.length());
    std::fill(above.begin(), above.end(), standardPair);

    ProcessCurrent(line);

    while (getline(newFile, line))
    {
        above = curr;

        std::fill(curr.begin(), curr.end(), standardPair);

        ProcessCurrent(line);
    }

    cout << sum << endl;
}
