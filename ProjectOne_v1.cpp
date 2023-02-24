//============================================================================
// Name        : ProjectOne_v1.cpp
// Author      : Andrew Park
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold Course information
struct Course {
    string courseId;
    string name;
    string prereq1;
    string prereq2;
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the Course information to the console (std::out)
 *
 * @param Course struct containing the Course info
 */
void displayCourse(Course course) {
    cout << course.courseId << " | " << course.name << " ";
    if(course.prereq1 != "") {
        cout << "| " << course.prereq1 << " ";
        if (course.prereq2 != "") {
            cout << "| " << course.prereq2 << " ";
        }
    }
    cout << endl;
    return;
}


/**
 * Perform a selection sort on Course name
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param Course address of the vector<Course>
 *            instance to be sorted
 */
void sortCourse(vector<Course>& courses) {
    //define min as int (index of the current minimum bid)
    int min = 0;
    // check size of courses vector
    size_t i = courses.size();
    // set size_t platform-neutral result equal to bid.size()
    for (i = 0; i < courses.size() - 1; ++i) {
    // pos is the position within courses that divides sorted/unsorted
    // for size_t pos = 0 and less than size -1
        min = i;
        // set min = pos
        for (unsigned int j = i + 1; j < courses.size(); ++j) {
        // loop over remaining elements to the right of position
            if (courses.at(j).courseId < courses.at(min).courseId) {
            // if this element's course ID is less than minimum course ID
                min = j;
                // this element becomes the minimum
            }
        }
        swap(courses.at(i), courses.at(min));
        // swap the current minimum with smaller one found
        // swap is a built in vector method
    }
}


/**
 * Perform a selection sort on Course name
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param Course address of the vector<Course>
 *            instance to be sorted
 */
void findCourse(vector<Course>& courses, string course_id) {
    bool ifound = false;
    for (unsigned int i = 0; i < courses.size() - 1; ++i) {
        if (courses.at(i).courseId == course_id) {
            ifound = true;
            cout << "[INFO] Course found!\n";
            cout << courses.at(i).name << endl;
            if (courses.at(i).prereq1 != "") {
                cout << "Prerequisites:\n" << courses.at(i).prereq1 << endl;
                if (courses.at(i).prereq2 != "") {
                    cout << courses.at(i).prereq2 << endl;
                }
            }
            cout << endl << endl;
        }
    }
    if (!ifound) {
        cout << "[WARNING] Course not found!!!\n";
    }
}

/**
 * Load a CSV file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the courses read
 */
vector<Course> loadCourses(string csvPath) {
    cout << "Loading course information.... " << csvPath << endl;

    // Define a vector data structure to hold a collection of courses.
    vector<Course> courses;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of courses
            Course course;
            course.courseId = file[i][0];
            course.name = file[i][1];
            course.prereq1 = file[i][2];
            course.prereq2 = file[i][3];


            // for testing REMOVE WHEN DONE
            // cout << "ID: " << course.courseId << " | Name: " << course.name << " | Prereq: " << course.prereq1 << " | Prerq: " << course.prereq2  << endl;

            // push this Course to the end
            courses.push_back(course);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return courses;
}


/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "ProjectOneInput.csv";
    }

    // Define a vector to hold all the courses
    vector<Course> courses;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load courses" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print Course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading courses
            ticks = clock();

            // Complete the method call to load the courses
            courses = loadCourses(csvPath);

            cout << courses.size() << " courses read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Loop and display the courses read
            sortCourse(courses);
            for (int i = 0; i < courses.size(); ++i) {
                displayCourse(courses[i]);
            }
            cout << endl;

            break;

        case 3:
            string inputId;
            cin >> inputId;
            findCourse(courses, inputId);

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
