#include <iostream>
#include "StrClass.h"

using namespace std;

int main(int argc, char* argv[])
{

    if (argc < 2)
    {
        cout << "No input file" << endl;
        cout << "Pass file name from command line" << endl;
        cout << "Example: input.txt" << endl;
        return 1;
    }

    StrClass a;
    a.readFromFile(argv[1]);

    StrClass b(a);
    StrClass c;
    c = a;

    cout << "Original string:" << endl;
    cout << a << endl << endl;

    a.printWords(cout);
    cout << endl;

    a.printNumbers(cout);
    cout << endl;

    a.writeToFile("decision.txt");

    cout << "Result saved to decision.txt" << endl;
    cout << endl;

    cout << "Copy constructor test:" << endl;
    cout << b << endl << endl;

    cout << "Assignment operator test:" << endl;
    cout << c << endl;

    return 0;
}