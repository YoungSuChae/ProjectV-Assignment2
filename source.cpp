#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct STUDENT_DATA {
    string firstName;
    string lastName;
};

int main() {
    vector<STUDENT_DATA> students;  // Vector to store student data
    ifstream inputFile("StudentData.txt"); 
    string line;

    // Check if the file is open
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {  // Read each line from the file
            istringstream iss(line);
            string firstName, lastName;

            // Split the line by comma
            if (getline(iss, firstName, ',') && getline(iss, lastName)) {
                STUDENT_DATA student;
                student.firstName = firstName;
                student.lastName = lastName;

                // Add the student to the vector
                students.push_back(student);
            }
        }
        inputFile.close();
    }
    else {
        cerr << "Error: Unable to open file." << endl;  // Error handling
        return 1;
    }

    // Print the student data to verify
    for (const auto& student : students) {
        cout << "First Name: " << student.firstName << "Last Name: " << student.lastName << endl;
    }

    return 1; // Basic main function that returns 1
}