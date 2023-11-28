#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <map>
#include <fstream>

#define USE_INPUT_FILE 0

using namespace std;

int main()
{
     #if USE_INPUT_FILE
    ifstream inputFile("in.txt"); // Open the input file
    if (!inputFile.is_open())
    {
        cout << "Error opening the file!" << endl;
        return 1;
    }

    int n;
    inputFile >> n;
    map<int, list<int> > a;

    for (int i = 0; i < n; i++)
    {
        string s;
        inputFile >> s;
        if (s == "new")
        {
            int id;
            inputFile >> id;
            a[id] = list<int>();
        }
        else if (s == "add")
        {
            int id, num;
            inputFile >> id >> num;
            a[id].push_back(num);
        }
        else if (s == "merge")
        {
            int id1, id2;
            inputFile >> id1 >> id2;
            if (id1 == id2) continue;
            a[id1].merge(a[id2]);
            // a.erase(id2);
        }
        else if (s == "unique")
        {
            int id;
            inputFile >> id;
            a[id].sort();
            a[id].unique();
        }
        else if (s == "out")
        {
            int id;
            inputFile >> id;
            a[id].sort();
            for (list<int>::iterator i = a[id].begin(); i != a[id].end(); i++)
            {
                cout << *i << " ";
            }
            cout << endl;
        }
    }

    #else
    int n;
    cin >> n;
    map<int, list<int> > a;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        if (s == "new")
        {
            int id;
            cin >> id;
            a[id] = list<int>();
        }
        else if (s == "add")
        {
            int id, num;
            cin >> id >> num;
            a[id].push_back(num);
        }
        else if (s == "merge")
        {
            int id1, id2;
            cin >> id1 >> id2;
            if (id1 == id2) continue;
            a[id1].merge(a[id2]);
            a.erase(id2);
        }
        else if (s == "unique")
        {
            int id;
            cin >> id;
            a[id].sort();
            a[id].unique();
        }
        else if (s == "out")
        {
            int id;
            cin >> id;
            a[id].sort();
            for (list<int>::iterator i = a[id].begin(); i != a[id].end(); i++)
            {
                cout << *i << " ";
            }
            cout << endl;
        }
    }
    #endif


    return 0;
}