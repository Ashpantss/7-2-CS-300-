// Ashlee Wood 
// 6/20/2024 
//Project Two - Vector from psuedocode pick 


#include <iostream>  // Header files 
#include <fstream>   
#include <vector>    
#include <algorithm>  
#include <sstream> // included for strings 
// read from the string as if it were a stream (like cin).

using namespace std;

// opted for class 
class Course {
public:
    string courseNum;
    string courseName;
    vector<string> prereqs;

    Course(string number, string name, vector<string> prereqs) {
        courseNum = number;
        courseName = name;
        prereqs = prereqs;
    }
};

vector<Course> courseData;

// data from the file into the data structure
void loadDataStruct(string fileName) {
    ifstream file(fileName);
    string lines;

    while (getline(file, lines)) {
        stringstream sim(lines);
        string courseNum, courseName, prereq;

        getline(sim, courseNum, ',');
        getline(sim, courseName, ',');
        
        vector<string> prereqs;
        while (getline(sim, prereq, ',')) {
            prereqs.push_back(prereq);
        }

        Course newCourse(courseNum, courseName, prereqs);
        courseData.push_back(newCourse);
    }

    cout << "Data loaded into the data structure successfully." << endl;
}

// Function to print an alphanumeric list of all the courses
void printCourseList() {
    sort(courseData.begin(), courseData.end(), [](const Course& a, const Course& b) {   // using sorting algorithm  //
        return a.courseNum < b.courseNum;
        });

    cout << "Alphanumeric List of Courses:" << endl;
    for (const Course& course : courseData) {
        cout << course.courseNum<< ": " << course.courseName << endl;
    }
}

// Prints the course info 
void printCourseInfo(string courseNum) {
    auto it = find_if(courseData.begin(), courseData.end(), [&](const Course& course) {  // equate auto //
        return course.courseNum == courseNum;
        });

    if (it != courseData.end()) {
        cout << "Course Information for " << courseNum << ":" << endl;
        cout << "Title: " << it->courseName << endl;
        cout << "Prerequisites: ";

        if (it->prereqs.empty()) {
            cout << "None";
        }
        else {
            for (const string& prereq : it->prereqs) {
                cout << prereq << " ";
            }
        }

        cout << endl;
    }
    else {
        cout << "Course not found." << endl;
    }
}
// main function 
int main() {
    cout << "ABCU Advising Program: Course Planner" << endl;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Load Data Structure\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course Information\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";

        int decisions;
        cin >> decisions;
        // cases functions 

        switch (decisions) {
        case 1: {
            cout << "Enter the file name containing the course data: ";
            string fileName;
            cin >> fileName;
            loadDataStruct(fileName);
            break;
        }
        case 2:
            printCourseList();
            break;
        case 3: {
            cout << "What course would you like to know about? ";
            string courseNum;
            cin >> courseNum;
            printCourseInfo(courseNum);
            break;
        }
        case 9:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    return 0;
}