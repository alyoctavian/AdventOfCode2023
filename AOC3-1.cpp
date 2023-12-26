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
vector<pair<int, bool*>> last;

int sum = 0;

bool IsValidNum(int pos, vector<pair<int, bool*>> vect)
{
    if (vect[pos].first <= 0)
    {
        return false;
    }

    if (pos > 0 && vect[pos - 1].first > 0 && *vect[pos].second == true)
    {
        return false;
    }

    *vect[pos].second = true;

    return true;
}

void ProcessSign(int pos)
{
    if (pos > 0 && curr[pos - 1].first > 0)
    {
        cout << curr[pos - 1].first << endl;
        sum += curr[pos - 1].first;
    }

    if (pos > 0 && IsValidNum(pos - 1, last))
    {
        cout << last[pos - 1].first << endl;
        sum += last[pos - 1].first;
    }

    if (IsValidNum(pos, last))
    {
        cout << last[pos].first << endl;
        sum += last[pos].first;
    }

    if (pos < last.size() - 1 && IsValidNum(pos + 1, last))
    {
        cout << last[pos + 1].first << endl;
        sum += last[pos + 1].first;
    }
}

bool IsUnderSign(int pos)
{
    if (pos > 0 && last[pos - 1].first < 0)
    {
        return true;
    }

    if (last[pos].first < 0)
    {
        return true;
    }

    if (pos < last.size() - 1 && last[pos + 1].first < 0)
    {
        return true;
    }

    return false;
}

int ProcessNumber(int pos, string line)
{
    int number = line[pos] - '0';

    bool* isChecked = new bool;

    *isChecked = false;

    curr[pos].second = isChecked;

    bool underSign = false;

    if (IsUnderSign(pos))
    {
        underSign = true;
    }

    int index = pos + 1;

    // Create the number while the line continues with digits
    while (isdigit(line[index]) && index < line.length())
    {
        number = number * 10 + line[index] - '0';

        curr[index].second = isChecked;

        if (!underSign && IsUnderSign(index))
        {
            underSign = true;
        }

        index++;
    }

    // It has a sign to the left
    if (pos > 0 && curr[pos - 1].first < 0)
    {
        cout << number << endl;
        sum += number;
    }
    // It has a symbol on the line above
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

    last.resize(line.length());
    std::fill(last.begin(), last.end(), standardPair);

    ProcessCurrent(line);

    while (getline(newFile, line))
    {
        last = curr;

        std::fill(curr.begin(), curr.end(), standardPair);

        ProcessCurrent(line);
    }

    cout << sum << endl;
}
