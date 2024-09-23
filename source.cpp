#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm> // For trim function

using namespace std;

// Function to trim leading and trailing spaces
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";  // No content
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

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
                student.firstName = trim(firstName);  // Remove any leading/trailing spaces
                student.lastName = trim(lastName);    // Remove any leading/trailing spaces

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

    // Debug printing - Only in DEBUG mode
#ifdef _DEBUG
    cout << "DEBUG MODE: Printing student data" << endl;
    for (const auto& student : students) {
        cout << "First Name: " << student.firstName << " | Last Name: " << student.lastName << endl;
    }
#endif

    return 1; // Basic main function that returns 1
}