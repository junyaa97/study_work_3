#ifndef STRCLASS_H
#define STRCLASS_H

#include <iostream>
#include <string>

using namespace std;

class StrClass
{
private:
    string str;

public:
    StrClass();
    StrClass(const string& s);
    StrClass(const StrClass& other);
    ~StrClass();

    StrClass& operator=(const StrClass& other);

    friend ostream& operator<<(ostream& out, const StrClass& obj);

    void readFromFile(const char* filename);
    string getString() const;

    string* getWords(int& count) const;
    string* getNumbers(int& count) const;

    bool isNumber(const string& word) const;

    void printWords(ostream& out) const;
    void printNumbers(ostream& out) const;

    void writeToFile(const char* filename) const;
};

#endif