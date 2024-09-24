#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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
    string email;  // Email field for pre-release mode
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
        inputFile.close();  // Close the file
    }
    else {
        cerr << "Error: Unable to open file." << endl;  // Error handling
        return 1;
    }

#ifdef _DEBUG
    cout << "DEBUG MODE: Printing student data" << endl;
    for (const auto& student : students) {
        cout << "First Name: " << student.firstName << " | Last Name: " << student.lastName << endl;
    }
#endif

    // Pre-release functionality - Assign emails to existing students
#ifdef PRE_RELEASE
    ifstream emailFile("StudentData_Emails.txt");
    if (emailFile.is_open()) {
        cout << "Pre-Release Mode: Printing student data with email" << endl;
        int i = 0;  // Use an index to assign emails to the correct students
        while (getline(emailFile, line)) {
            istringstream emailStream(line);
            string firstName, lastName, email;

            // Split by comma and extract the email
            if (getline(emailStream, firstName, ',') &&
                getline(emailStream, lastName, ',') &&
                getline(emailStream, email)) {
                if (i < students.size()) {
                    students[i].email = trim(email);  // Assign the email to the correct student
                }
                i++;  // Move to the next student
            }
        }
        emailFile.close();

        // Print the student data along with email
        for (const auto& student : students) {
            cout << "First Name: " << student.firstName << " | Last Name: " << student.lastName
                << " | Email: " << student.email << endl;
        }
    }
    else {
        cerr << "Error: Unable to open email file." << endl;
    }
#endif

    return 0;  // Return statement
}
