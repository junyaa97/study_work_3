#include "StrClass.h"
#include <fstream>

StrClass::StrClass()
{
    str = "";
}

StrClass::StrClass(const string& s)
{
    str = s;
}

StrClass::StrClass(const StrClass& other)
{
    str = other.str;
}

StrClass::~StrClass()
{
}

StrClass& StrClass::operator=(const StrClass& other)
{
    if (this != &other)
    {
        str = other.str;
    }
    return *this;
}

ostream& operator<<(ostream& out, const StrClass& obj)
{
    out << obj.str;
    return out;
}

void StrClass::readFromFile(const char* filename)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "File open error" << endl;
        str = "";
        return;
    }

    str = "";
    string line;

    while (getline(fin, line))
    {
        if (!str.empty())
        {
            str += " ";
        }
        str += line;
    }

    fin.close();
}

string StrClass::getString() const
{
    return str;
}

string* StrClass::getWords(int& count) const
{
    string temp = str;

    while (!temp.empty() && temp[0] == ' ')
    {
        temp.erase(0, 1);
    }

    while (!temp.empty() && temp[temp.length() - 1] == ' ')
    {
        temp.erase(temp.length() - 1, 1);
    }

    if (temp.empty())
    {
        count = 0;
        return NULL;
    }

    count = 0;
    for (int i = 0; i < (int)temp.length(); i++)
    {
        if (temp[i] != ' ' && (i == 0 || temp[i - 1] == ' '))
        {
            count++;
        }
    }

    string* words = new string[count];

    int i = 0;
    int index = 0;

    while (i < (int)temp.length())
    {
        while (i < (int)temp.length() && temp[i] == ' ')
        {
            i++;
        }

        string word = "";

        while (i < (int)temp.length() && temp[i] != ' ')
        {
            word += temp[i];
            i++;
        }

        if (!word.empty())
        {
            words[index] = word;
            index++;
        }
    }

    return words;
}

bool StrClass::isNumber(const string& word) const
{
    if (word.empty())
    {
        return false;
    }

    int i = 0;

    if (word[i] == '+' || word[i] == '-')
    {
        i++;
    }

    if (i >= (int)word.length())
    {
        return false;
    }

    bool dot = false;
    int before = 0;
    int after = 0;

    for (; i < (int)word.length(); i++)
    {
        if (word[i] >= '0' && word[i] <= '9')
        {
            if (!dot)
            {
                before++;
            }
            else
            {
                after++;
            }
        }
        else if (word[i] == '.')
        {
            if (dot)
            {
                return false;
            }
            dot = true;
        }
        else
        {
            return false;
        }
    }

    if (!dot)
    {
        return false;
    }

    if (before == 0 || after == 0)
    {
        return false;
    }

    return true;
}

string* StrClass::getNumbers(int& count) const
{
    int n = 0;
    string* words = getWords(n);

    count = 0;

    if (words == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        if (isNumber(words[i]))
        {
            count++;
        }
    }

    if (count == 0)
    {
        delete[] words;
        return NULL;
    }

    string* nums = new string[count];
    int j = 0;

    for (int i = 0; i < n; i++)
    {
        if (isNumber(words[i]))
        {
            nums[j] = words[i];
            j++;
        }
    }

    delete[] words;
    return nums;
}

void StrClass::printWords(ostream& out) const
{
    int count = 0;
    string* words = getWords(count);

    out << "Words array:" << endl;

    if (words == NULL)
    {
        out << "Empty string" << endl;
        return;
    }

    for (int i = 0; i < count; i++)
    {
        out << words[i] << endl;
    }

    delete[] words;
}

void StrClass::printNumbers(ostream& out) const
{
    int count = 0;
    string* nums = getNumbers(count);

    out << "Fixed-point numbers:" << endl;

    if (nums == NULL)
    {
        out << "No such words" << endl;
        return;
    }

    for (int i = 0; i < count; i++)
    {
        out << nums[i] << endl;
    }

    delete[] nums;
}

void StrClass::writeToFile(const char* filename) const
{
    ofstream fout(filename);

    if (!fout)
    {
        cout << "File create error" << endl;
        return;
    }

    fout << "1. Original string:" << endl;
    fout << str << endl << endl;

    int count = 0;
    string* words = getWords(count);

    fout << "2. Words array:" << endl;
    if (words == NULL)
    {
        fout << "Empty string" << endl;
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            fout << words[i] << endl;
        }
    }

    fout << endl;

    int numCount = 0;
    string* nums = getNumbers(numCount);

    fout << "3. Fixed-point numbers:" << endl;
    if (nums == NULL)
    {
        fout << "No such words" << endl;
    }
    else
    {
        for (int i = 0; i < numCount; i++)
        {
            fout << nums[i] << endl;
        }
    }

    delete[] words;
    delete[] nums;

    fout.close();
}