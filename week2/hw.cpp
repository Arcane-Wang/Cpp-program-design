#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Student
{ private:
    string name;
    double age;
    string id;
    vector<int> scores;
    int avg_score;
  
  public:
    Student(string name, double age, string id, vector<int> scores)
    {
        this->name = name;
        this->age = age;
        this->id = id;
        this->scores = scores;
        int sum = 0;
        for (int i = 0; i < scores.size(); i++)
        {
            sum += scores[i];
        }
        avg_score = sum / scores.size();
    }

    void print()
    {
        cout << name << "," << age << "," << id << "," << avg_score << endl;
    }
};

int main(){
    string name;
    double age;
    string id;
    vector<int> scores;

    // Get input separated by commas
    string input;
    getline(cin, input);
    stringstream ss(input);
    getline(ss, name, ',');
    ss >> age;
    if (ss.peek() == ',') {
            ss.ignore();
        }
    getline(ss, id, ',');
    int score;
    while (ss >> score) {
        scores.push_back(score);
        if (ss.peek() == ',') {
            ss.ignore();
        }
    }

    // Create student object and print
    Student student(name, age, id, scores);
    student.print();
    
    return 0;
}