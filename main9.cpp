#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <limits>
#include <regex>
#include <ctime>
// #include "D:/####sycoeptech/##DSCPProject_Database/Project in cpp/libharu-libharu-0c598be/include/hpdf.h" // Include libharu header

using namespace std;

string currentUser;

// Define a simple user class for authentication
class User {
private:
    string role;
    string password;

public:
    User(const string& r, const string& p) : role(r), password(p) {}

    const string& getRole() const  {
        return role;
    }

    const string& getPassword() const {
        return password;
    }
};


class Authentication {
private:
    unordered_map<string, User> users;

public:
    Authentication() {
        // Add default users (you can customize this based on your needs)
        users.emplace("admin", User("admin", "admin123"));
        users.emplace("user", User("user", "user123"));
    }

    User authenticate() const {
        while (true) {
            string role;
            cout << "Enter 'admin' or 'user': ";
            cin >> role;

            auto it = users.find(role);
            if (it != users.end()) {
                // cout << "Enter Password(3 attempts)" << endl;
                currentUser = role;

                int attempt = 4;
                string password;
                while(attempt>0) {
                    cout << "Enter password" << "(" << attempt << " attempts remaining): ";
                    getline(cin, password);

                    if (password == it->second.getPassword()) {
                        cout << "Login successful!\n";
                        system("CLS");
                        return it->second;
                    } else {
                        // cout << "Incorrect password. Please try again.\n";
                        attempt--;
                        system("CLS");
                        continue;
                    }
                }
            } else {
                // cout << "Invalid role. Please try again.\n";
                system("CLS");
            }
        }
    }
};

class Student {
private:
    string firstName;
    string middleName;
    string lastName;
    string mis;
    string yearOfAdmission;
    string email;
    string mobileNumber;
    string homeAddress;

public:
    Student(string& first, string& middle, string& last,
            string& yoa, string& e, string& mn, string& ha, string& m)
        : firstName(first), middleName(middle), lastName(last), yearOfAdmission(yoa),
          email(e), mobileNumber(mn), homeAddress(ha), mis(m) {}

    string& getFirstName() {
        return firstName;
    }

    string& getMiddleName() {
        return middleName;
    }

    string& getLastName() {
        return lastName;
    }

    string& getMis()  {
        return mis;
    }

    string& getYearOfAdmission() {
        return yearOfAdmission;
    }

    string& getEmail() {
        return email;
    }

    string& getMobileNumber() {
        return mobileNumber;
    }

    string& getHomeAddress() {
        return homeAddress;
    }

    void setFirstName(string& newFirstName) {
    firstName = newFirstName;
    }

    void setMiddleName(string& newMiddleName) {
        middleName = newMiddleName;
    }

    void setLastName(string& newLastName) {
        lastName = newLastName;
    }

    void setMis(string& newMis) {
        mis = newMis;
    }

    void setYearOfAdmission(string& newYearOfAdmission) {
        yearOfAdmission = newYearOfAdmission;
    }

    void setEmail(string& newEmail) {
        email = newEmail;
    }

    void setMobileNumber(string& newMobileNumber) {
        mobileNumber = newMobileNumber;
    }

    void setHomeAddress(string& newHomeAddress) {
        homeAddress = newHomeAddress;
    }


    void printDetails() {
        cout << "Name:\t\t\t" << firstName << " " << middleName << " " << lastName << endl;
        cout << "MIS:\t\t\t" << mis << endl;
        cout << "Year of Admission:\t" << yearOfAdmission << endl;
        cout << "Email: \t\t\t" << email << endl;
        cout << "Mobile Number:\t\t" << mobileNumber << endl;
        cout << "Home Address: \t\t" << homeAddress << endl << endl;
        // cout << "----------------------" << endl;
    }
};


class StudentDatabase {
private:
    unordered_map<string, Student> studentDatabase;

public:
    unordered_map<string, Student>& getStudentDatabase(){
        return studentDatabase;
    }

    void loadIntoMap() { //loading data from csv file into Data Structure
        ifstream file("data2.csv");
        if (!file.is_open()) {
            cerr << "Error opening file: data2.csv" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;

            getline(ss, token, ',');
            string mis = token;

            getline(ss, token, ',');
            string firstName = token;

            getline(ss, token, ',');
            string middleName = token;

            getline(ss, token, ',');
            string lastName = token;

            getline(ss, token, ',');
            string yearOfAdmission = token;

            getline(ss, token, ',');
            string email = token;

            getline(ss, token, ',');
            string mobileNumber = token;

            getline(ss, token, ',');
            string homeAddress = token;

            Student student(firstName, middleName, lastName, yearOfAdmission, email, mobileNumber, homeAddress, mis);
            studentDatabase.emplace(mis, student);
        }

        file.close();
    }

    void saveToCSV() {
        // Open the CSV file for writing
        ofstream file("data2.csv");
        if (!file.is_open()) {
            cerr << "Error opening file: data2.csv" << endl;
            return;
        }

        // Iterate through each student in the hashmap and write their data to the file
        for (auto& entry : studentDatabase) {
            Student& student = entry.second;

            // cout << "adding student with mis " << student.getMis() << endl;

            // Write student data to the file
            file << student.getMis() << ","
                << student.getFirstName() << ","
                << student.getMiddleName() << ","
                << student.getLastName() << ","
                << student.getYearOfAdmission() << ","
                << student.getEmail() << ","
                << student.getMobileNumber() << ","
                << student.getHomeAddress() << "\n";
        }

        // Close the file after writing
        file.close();
    }




    void printAllStudents(){
        cout << "Printing all students' data:" << endl;

        for (auto& entry : studentDatabase) {
            Student& student = entry.second;
            student.printDetails(); 
        }

        cout << "End of student data." << endl;
    }
};

class StudentMenu {
private:
    StudentDatabase database;

    void clearInputBuffer() {
        while (getchar() != '\n'); //famous way to clear input buffer!
    }

    bool validateMIS(const string& mis) {
        regex pattern("(612205|642305)\\d{3}");
        return regex_match(mis, pattern);
    }

    bool validateName(const string& name) {
        return !name.empty() && name.find(' ') == string::npos;
    }

    bool validateYearOfAdmission(const string& year) {
        return year == "2022" || year == "2023";
    }

    bool validateEmail(const string& email) {
        regex pattern(R"([a-zA-Z0-9._%+-]+@coeptech\.ac\.in)");
        return regex_match(email, pattern);
    }

    bool validateMobileNumber(const string& mobile) {
        return mobile.size() == 10 && all_of(mobile.begin(), mobile.end(), ::isdigit);
    }

    string trim(const string& str) { //for trimming string
        // Find the first non-whitespace character
        auto start = str.find_first_not_of(" \t\n\r");

        // If all characters are whitespace, return an empty string
        if (start == string::npos) {
            return "";
        }

        // Find the last non-whitespace character
        auto end = str.find_last_not_of(" \t\n\r");

        // Return the trimmed substring
        return str.substr(start, end - start + 1);
    }

    void writeToLogFile(const string& filename, const string& logEntry) {
        // Open the file in append mode
        ofstream file(filename, ios::app);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        // Write the log entry to the file
        file << logEntry << endl;

        // Close the file
        file.close();
    }

    void displayLogFile(const string& filename) {
        // Open the file
        ifstream file(filename);
        if (!file.is_open()) {
            // cerr << "Error opening file: " << filename << endl;
            cout << "No recent log history for User" << endl;
            return;
        }

        // Read and display the non-blank contents line by line
        string line;
        int count = 1;
        while (getline(file, line)) {
            if (!line.empty()) {  // Check if the line is not empty
                cout << count << ". " << line << endl;
                count++;
            }
        }
        // cout << "This is me" << endl;

        // Close the file
        file.close();
    }

    void displayUserLogFileInMenu() {
        if(currentUser=="admin") {
            cout << endl << "Log history for User Profile: " << endl << endl;
            displayLogFile(".\\userLogFile.txt");
            cout << endl << endl;
        }     
    }

    void removeBlankLinesFromUserLogFile(const string& filename) {
        // Open the input file
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cerr << "Error opening input file: " << filename << endl;
            return;
        }

        // Create a temporary file for writing
        ofstream tempFile("temp.txt");
        if (!tempFile.is_open()) {
            cerr << "Error creating temporary file." << endl;
            inFile.close();
            return;
        }

        // Read each line from the input file
        string line;
        while (getline(inFile, line)) {
            // Write non-blank lines to the temporary file
            if (!line.empty()) {
                tempFile << line << endl;
            }
        }

        // Close both files
        inFile.close();
        tempFile.close();

        // Remove the original file
        if (remove(filename.c_str()) != 0) {
            cerr << "Error removing original file." << endl;
            return;
        }

        // Rename the temporary file to the original filename
        if (rename("temp.txt", filename.c_str()) != 0) {
            cerr << "Error renaming temporary file." << endl;
            return;
        }
    }

    // Function to erase the last line on the terminal
    void eraseLastLine(int i) {
        // Move the cursor up one line
        std::cout << "\x1b[1A";
        
        // Clear the line
        std::cout << "\x1b[2K";
        if(i==1) {
            // Move the cursor up one line
            std::cout << "\x1b[1A";
            // Clear the line
            std::cout << "\x1b[2K";
        }
    }

    void emptyUserLogFile(const string& filename) {
        ofstream ofs(filename, ofstream::out | ofstream::trunc); // Open file in truncation mode to clear its contents
        ofs.close();
        cout << "User profile log history has been cleared." << endl;
        
        cout << endl <<endl <<endl <<endl << endl;
        cout << "Press Any key/ENTER twice to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // cout << "CSV file " << filename << " has been emptied." << endl;
    }

    // bool validateInput(string& input, const string& fieldName, int& attempt, bool (*validationFunction)(const string&)) {
    //     while (attempt > 0) {
    //         cout << "Enter " << fieldName << " (" << attempt << " attempts remaining): ";
    //         getline(cin, input);
    //         input = trim(input);

    //         if (validationFunction(input)) {
    //             return true; // Input is valid
    //         } else {
    //             cout << "Invalid " << fieldName << " format." << endl << endl;
    //             attempt--;
    //         }
    //     }

    //     // Maximum attempts reached
    //     cout << "Maximum attempts reached. Exiting." << endl;
    //     return false;
    // }



    // Function to generate PDF with student details
    // void generateStudentPDF(const vector<string>& studentDetails) {
    //     // Create PDF document
    //     HPDF_Doc pdf = HPDF_New(NULL, NULL);
    //     if (!pdf) {
    //         cerr << "Error: Cannot create PDF document." << endl;
    //         return;
    //     }

    //     // Add a new page
    //     HPDF_Page page = HPDF_AddPage(pdf);
    //     if (!page) {
    //         cerr << "Error: Cannot add page." << endl;
    //         HPDF_Free(pdf);
    //         return;
    //     }

    //     // Set font and font size
    //     HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
    //     HPDF_Page_SetFontAndSize(page, font, 12);

    //     // Write student details to PDF
    //     float x = 50, y = 750;
    //     for (const auto& detail : studentDetails) {
    //         HPDF_Page_TextOut(page, x, y, detail.c_str());
    //         y -= 20; // Move to next line
    //     }

    //     // Save the PDF to a file
    //     if (HPDF_SaveToFile(pdf, "student_details.pdf") != HPDF_OK) {
    //         cerr << "Error: Cannot save PDF to file." << endl;
    //     }

    //     // Clean up
    //     HPDF_Free(pdf);
    // }

public:
    

    void displayMenu(const string& userType) {
        cout << "==== " << userType << " Menu ====" << endl;
        cout << "1. Display Student Details" << endl;
        cout << "2. Add Student" << endl; 
        if (userType == "admin") {
            cout << "3. Edit Student" << endl; 
            cout << "4. Delete Student" << endl;
            cout << "5. Clear user log history" << endl;
        }
        cout << "0. Exit" << endl;
        // cout << "-1. Logout" << endl;
        
    }

    void executeMenu(const string& userType) {
        database.loadIntoMap(); //Store existing data in map first
        removeBlankLinesFromUserLogFile(".\\userLogFile.txt");
        
        string input;
        int choice;
        while (true) {
            system("CLS");
            //DISPLAYING USER LOG FILE
            displayUserLogFileInMenu();

            displayMenu(userType); //displaying the menu according to userType

            
            // int choice;
            // cout << "Enter your choice: ";
            // if (!(cin >> choice)) {
            //     cout << "Invalid Input. Please enter a valid option." << endl;
            //     cin.clear();
            //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
            //     continue;
            // }

            cout << "Enter your choice: ";
            getline(cin, input); // Read the entire line as a string

            // Check if the input is empty or contains non-numeric characters
            if (input.empty() || !all_of(input.begin(), input.end(), ::isdigit)) {
                cout << "Invalid Input. Please enter a valid option." << endl;
                continue; // Prompt the user to enter a choice again
            }

            // Convert the input string to an integer
            choice = stoi(input);

            // Check if the choice is within the valid range
            if (choice < 0 || choice > 5) {
                cout << "Invalid Input. Please enter a valid option." << endl;
                continue; // Prompt the user to enter a choice again
            }


            system("CLS");
            //debug-tempo-1
            // cout << "User Choice: " << choice << ", UserType: " << userType << endl;

        
            switch (choice) {
                case 1:
                    displayStudentDetails();
                    break;
                case 2:
                    addStudent();
                    break;
                case 3:
                    if (userType == "admin") {
                        editStudent();
                    } else {
                        cout << "Invalid choice. Please enter a valid option." << endl;
                    }
                    break;
                case 4:
                    if (userType == "admin") {
                        deleteStudent();
                    } else {
                        cout << "Invalid choice. Please enter a valid option." << endl;
                    }
                    break;
                case 5:
                    emptyUserLogFile(".\\userLogFile.txt");
                    break;
                case 0:
                    cout << "Exiting the Database. Thank you!" << endl;
                    // removeBlankLinesFromUserLogFile(".\\userLogFile.txt");
                    //dont call remove blank lines function after calling display log file function
                    return;
                default:
                    cout << "Invalid choice. Please enter a valid option." << endl;
            }

            clearInputBuffer();
            // clearScreen();
            // break;
        }
    }

    void displayStudentDetails() {
        // string misToDisplay;
        // cout << "Enter the MIS of the student to display details: ";
        // cin >> misToDisplay;
        // system("CLS");
        
        string misToDisplay;
        bool validMIS = false;

        int attempt = 3;
        while (attempt > 0) {
            cout << "Enter MIS to display details " << "(" << attempt << " attempts remaining): ";
            getline(cin, misToDisplay);
            misToDisplay = trim(misToDisplay);
            
            if (validateMIS(misToDisplay)) {
                validMIS = true;
                break;
            } else {
                system("CLS");
                cout << "Invalid MIS format." << endl << endl;
                // cout << "Enter MIS to add" << "(" << attempt << " attempts remaining): ";
                attempt--;
            }
        }

        if (!validMIS) {
            cout << "Maximum attempts reached. Exiting." << endl;
            return;
        }
        // Check if the student with the provided MIS exists
        auto it = database.getStudentDatabase().find(misToDisplay);
        if (it != database.getStudentDatabase().end()) {
            system("CLS");
            // Display the details of the student
            cout << "Student Details for MIS " << misToDisplay << ":" << endl << endl;
            // cout << endll
            // cout << "Working" << endl;
            it->second.printDetails();

            time_t now = time(nullptr);
            // Convert time to string
            string dateTime = ctime(&now);
            dateTime.pop_back();
            if(currentUser=="user"){
                writeToLogFile(".\\userLogFile.txt", dateTime + ": Display details for mis: " + misToDisplay);
                removeBlankLinesFromUserLogFile(".\\userLogFile.txt");
            } 
            
        } else {
            cout << endl << "Student with MIS " << misToDisplay << " not found." << endl;
        }    

        // Prompt the user to press any key to continue
        cout << endl <<endl <<endl <<endl << endl;
        cout << "Press Any key/ENTER twice to continue...";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get(); // Wait for user to press any key
        system("CLS");

        
    }


    void addStudent() {
        string firstName, middleName, lastName, mis, yearOfAdmission, email, mobileNumber, homeAddress;

        bool validMIS = false;
        // string mis;
        int attempt = 3;
        while (attempt > 0) {
            cout << "Enter MIS to add " << "(" << attempt << " attempts remaining): ";
            getline(cin, mis);
            mis = trim(mis);
            
            if (validateMIS(mis)) {
                validMIS = true;
                break;
            } else {
                system("CLS");
                cout << "Invalid MIS format." << endl << endl;
                // cout << "Enter MIS to add" << "(" << attempt << " attempts remaining): ";
                attempt--;
            }
        }

        if (!validMIS) {
            cout << "Maximum attempts reached. Exiting." << endl;
            return;
        }

        auto& studentDatabase = database.getStudentDatabase();
        if (studentDatabase.find(mis) != studentDatabase.end()) {
            system("CLS");
            cout << "Student with MIS " << mis << " already exists. Cannot add duplicate student." << endl;
            
            cout << endl <<endl <<endl <<endl << endl;
            cout << "Press Any key/ENTER twice to continue...";
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get(); // Wait for user to press any key
            system("CLS");           
        
            return;
        }

        // Prompt user for first name
        // cout << "Enter First Name: ";
        // cin >> firstName;
        // firstName = trim(firstName);
        // if (!validateName(firstName)) {
        //     cout << "Invalid first name format." << endl;
        //     return;
        // }
        // Validate First Name
        bool validFirstName = false;
        attempt = 3;
        // string firstName;
        while (attempt > 0) {
            cout << endl << "Enter First Name" << "\t\t" << "(" << attempt << " attempts remaining): ";
            getline(cin , firstName);
            firstName = trim(firstName);

            if (validateName(firstName)) {
                validFirstName = true;
                break;
            } else {
                // cout << "Invalid First Name format." << endl << endl;
                attempt--;
                eraseLastLine(1);
            }
        }

        if (!validFirstName) {
            cout << endl << "Maximum attempts reached. Exiting." << endl;
            return;
        }


        // Prompt user for middle name
        // cout << "Enter Middle Name: ";
        // cin >> middleName;
        // middleName = trim(middleName);
        // if (!validateName(middleName)) {
        //     cout << "Invalid middle name format." << endl;
        //     return;
        // }
        bool validMiddleName = false;
        attempt = 3;
        // string middleName;
        while (attempt > 0) {
            cout << "Enter Middle Name" << "\t\t"  << "(" << attempt << " attempts remaining): ";
            // cin >> middleName;
            getline(cin, middleName);
            middleName = trim(middleName);

            if (validateName(middleName)) {
                validMiddleName = true;
                break;
            } else {
                // system("CLS");
                // cout << "Invalid Middle Name format." << endl << endl;
                attempt--;
                eraseLastLine(0);
            }
        }

        if (!validMiddleName) {
            cout <<endl<< "Maximum attempts reached. Exiting." << endl;
            return;
        }

        // Prompt user for last name
        // cout << "Enter Last Name: ";
        // cin >> lastName;
        // lastName = trim(lastName);
        // if (!validateName(lastName)) {
        //     cout << "Invalid last name format." << endl;
        //     return;
        // }

        bool validLastName = false;
        attempt = 3;
        // string lastName;
        while (attempt > 0) {
            cout << "Enter Last Name"  << "\t\t\t" << "(" << attempt << " attempts remaining): ";
            // cin >> lastName;
            getline(cin, lastName);
            lastName = trim(lastName);

            if (validateName(lastName)) {
                validLastName = true;
                break;
            } else {
                attempt--;
                eraseLastLine(0);
            }
        }

        if (!validLastName) {
            cout <<endl<< "Maximum attempts reached. Exiting." << endl;
            return;
        }


        // Prompt user for year of admission
        // cout << "Enter Year of Admission: ";
        // cin >> yearOfAdmission;
        // yearOfAdmission = trim(yearOfAdmission);
        // if (!validateYearOfAdmission(yearOfAdmission)) {
        //     cout << "Invalid year of admission." << endl;
        //     return;
        // }
        bool validYearOfAdmission = false;
        attempt = 3;
        // string yearOfAdmission;
        while (attempt > 0) {
            cout << "Enter Year of Admission"  << "\t\t" << "(" << attempt << " attempts remaining): ";
            // cin >> yearOfAdmission;
            getline(cin, yearOfAdmission);
            yearOfAdmission = trim(yearOfAdmission);

            if (validateYearOfAdmission(yearOfAdmission)) {
                validYearOfAdmission = true;
                break;
            } else {
                attempt--;
                eraseLastLine(0);
            }
        }

        if (!validYearOfAdmission) {
            cout <<endl<< "Maximum attempts reached. Exiting." << endl;
            return;
        }

        // Prompt user for email
        // cout << "Enter Email: ";
        // cin >> email;
        // email = trim(email);
        // if (!validateEmail(email)) {
        //     cout << "Invalid email format." << endl;
        //     return;
        // }
        bool validEmail = false;
        attempt = 3;
        // string email;
        while (attempt > 0) {
            cout << "Enter Email" << "\t\t\t"  << "(" << attempt << " attempts remaining): ";
            // cin >> email;
            getline(cin, email);
            email = trim(email);

            if (validateEmail(email)) {
                validEmail = true;
                break;
            } else {
                attempt--;
                eraseLastLine(0);
            }
        }

        if (!validEmail) {
            cout <<endl<< "Maximum attempts reached. Exiting." << endl;
            return;
        }

        // Prompt user for mobile number
        // cout << "Enter Mobile Number: ";
        // cin >> mobileNumber;
        // mobileNumber = trim(mobileNumber);
        // if (!validateMobileNumber(mobileNumber)) {
        //     cout << "Invalid mobile number." << endl;
        //     return;
        // }
        bool validMobileNumber = false;
        attempt = 3;
        // string mobileNumber;
        while (attempt > 0) {
            cout << "Enter Mobile Number" << "\t\t"  << "(" << attempt << " attempts remaining): ";
            // cin >> mobileNumber;
            getline(cin, mobileNumber);
            mobileNumber = trim(mobileNumber);

            if (validateMobileNumber(mobileNumber)) {
                validMobileNumber = true;
                break;
            } else {
                attempt--;
                eraseLastLine(0);
            }
        }

        if (!validMobileNumber) {
            cout <<endl<< "Maximum attempts reached. Exiting." << endl;
            return;
        }


        // Prompt user for home address
        // cout << "Enter Home Address: ";
        // cin.ignore(); // Ignore newline character from previous input
        // getline(cin, homeAddress);
        // homeAddress = trim(homeAddress);
        // if (homeAddress.length() < 5) {
        //     cout << "Home address must be at least 5 characters long." << endl;
        //     return;
        // }
        bool validHomeAddress = false;
        attempt = 3;
        // string homeAddress;
        while (attempt > 0) {
            cout << "Enter Home Address"  << "\t\t" << "(" << attempt << " attempts remaining): ";
            cin.ignore(); // Ignore newline character from previous input
            getline(cin, homeAddress);
            homeAddress = trim(homeAddress);

            if (homeAddress.length() >= 5) {
                validHomeAddress = true;
                break;
            } else {
                attempt--;
                eraseLastLine(0);
            }
        }

        if (!validHomeAddress) {
            cout <<endl<< "Maximum attempts reached. Exiting." << endl;
            return;
        }

        // Create a new Student object
        Student newStudent(firstName, middleName, lastName, yearOfAdmission, email, mobileNumber, homeAddress, mis);

        // Add the new student to the hashmap
        studentDatabase.emplace(mis, newStudent);

        // Append the new student to the CSV file
        database.saveToCSV();
        cout << endl << "Student with MIS: " << mis << " added successfully." << endl;
        
        time_t now = time(nullptr);
        // Convert time to string
        string dateTime = ctime(&now);
        dateTime.pop_back();
        if(currentUser=="user") {
            writeToLogFile(".\\userLogFile.txt",dateTime +  ": Added Student details with mis: " + mis);
            removeBlankLinesFromUserLogFile(".\\userLogFile.txt");
        }

        // cout << "Adding student with details:" << endl;
        // cout << "Name: " << firstName << " " << middleName << " " << lastName << endl;
        // cout << "MIS: " << mis << endl;
        // cout << "Year of Admission: " << yearOfAdmission << endl;
        // cout << "Email: " << email << endl;
        // cout << "Mobile Number: " << mobileNumber << endl;
        // cout << "Home Address: " << homeAddress << endl;
        // cout << "----------------------" << endl;

         
        cout << endl <<endl <<endl <<endl << endl;
        cout << "Press Any key/ENTER twice to continue...";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get(); // Wait for user to press any key
        system("CLS");     
    }
    

    
    void deleteStudent() {
        string misToDelete;
        bool validMIS = false;

        int attempt = 3;
        while (attempt > 0) {
            cout << "Enter MIS of student to delete details " << "(" << attempt << " attempts remaining): ";
            // cin >> misToDelete;
            getline(cin, misToDelete);
            misToDelete = trim(misToDelete);
            
            if (validateMIS(misToDelete)) {
                validMIS = true;
                break;
            } else {
                system("CLS");
                cout << "Invalid MIS format." << endl << endl;
                // cout << "Enter MIS to add" << "(" << attempt << " attempts remaining): ";
                attempt--;
            }
        }

        if (!validMIS) {
            cout << "Maximum attempts reached. Exiting." << endl;
            return;
        }
        // Check if the student with the provided MIS exists
        auto it = database.getStudentDatabase().find(misToDelete);
        if (it != database.getStudentDatabase().end()) {
            // Remove the student from the map
            // Print student details
            string input;
            int confirmation;
            
            while(true) {
                system("CLS");
                cout << "Student Details for MIS " << misToDelete << ":" << endl << endl;
                it->second.printDetails();

                // Prompt for confirmation
                cout << endl << "Are you sure you want to delete student with above details? (1 for yes, 0 for no): ";
                // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, input);

                // Check if the input is empty or contains non-numeric characters
                if (input.empty() || !all_of(input.begin(), input.end(), ::isdigit)) {
                    cout << "Invalid Input. Please enter a valid option." << endl;
                    continue; // Prompt the user to enter a choice again
                }

                // Convert the input string to an integer
                confirmation = stoi(input);

                // Check if the choice is within the valid range
                if (confirmation < 0 || confirmation > 1) {
                    cout << "Invalid Input. Please enter a valid option." << endl;
                    continue; // Prompt the user to enter a choice again
                } else break;

            }

            time_t now = time(nullptr);
            // Convert time to string
            string dateTime = ctime(&now);
            dateTime.pop_back();

            switch (confirmation) {
                case 1:
                    // Remove the student from the map
                    database.getStudentDatabase().erase(it);
                    
                    // Rewrite the CSV file with the updated map data in the original order
                    database.saveToCSV();

                    cout << endl << "Student with MIS " << misToDelete << " deleted successfully." << endl;
                    
                    
                    if(currentUser=="user") writeToLogFile(".\\userLogFile.txt",dateTime +  ": Delete Student details with mis: " + misToDelete);


                    // Prompt the user to press any key to continue
                    cout << endl <<endl <<endl <<endl << endl;
                    cout << "Press Any key/ENTER twice to continue...";
                    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get(); // Wait for user to press any key
                    system("CLS");

                    return;
                case 0:
                    cout << endl << "Deletion canceled." << endl;

                    // Prompt the user to press any key to continue
                    cout << endl <<endl <<endl <<endl << endl;
                    cout << "Press Any key/ENTER twice to continue...";
                    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get(); // Wait for user to press any key
                    system("CLS");
                    
                    
                    return;
                default:
                    cout << endl << "Invalid choice. Deletion canceled." << endl;
                    
                    // Prompt the user to press any key to continue
                    cout << endl <<endl <<endl <<endl << endl;
                    cout << "Press Any key/ENTER twice to continue...";
                    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get(); // Wait for user to press any key
                    system("CLS");
                    
                    return;
            }
        } else {
            cout << endl << "Student with MIS " << misToDelete << " not found." << endl;
            
            // Prompt the user to press any key to continue
            cout << endl <<endl <<endl <<endl << endl;
            cout << "Press Any key/ENTER twice to continue...";
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get(); // Wait for user to press any key
            system("CLS");
        }
    }

    void editStudent() {
        string misToEdit;
        bool validMIS = false;

        int attempt = 3;
        while (attempt > 0) {
            cout << "Enter MIS of student to edit details " << "(" << attempt << " attempts remaining): ";
            // cin >> misToEdit;
            getline(cin ,misToEdit);
            misToEdit = trim(misToEdit);
            
            if (validateMIS(misToEdit)) {
                validMIS = true;
                break;
            } else {
                system("CLS");
                cout << "Invalid MIS format." << endl << endl;
                // cout << "Enter MIS to add" << "(" << attempt << " attempts remaining): ";
                attempt--;
            }
        }

        if (!validMIS) {
            cout << "Maximum attempts reached. Exiting." << endl;
            return;
        }

        // Check if the student with the provided MIS exists
        auto it = database.getStudentDatabase().find(misToEdit);
        if (it != database.getStudentDatabase().end()) {
            
            // Prompt the user for updated information
            string input;
            int editChoice;
            do {
                while(true) {
                    system("CLS");

                    cout << "Student Details for MIS " << misToEdit << ":" << endl << endl;
                    it->second.printDetails();

                    cout << endl << "Choose the detail to edit:" << endl;
                    cout << "1. First Name" << endl;
                    cout << "2. Middle Name" << endl;
                    cout << "3. Last Name" << endl;
                    cout << "4. Year of Admission" << endl;
                    cout << "5. Email" << endl;
                    cout << "6. Mobile Number" << endl;
                    cout << "7. Home Address" << endl;
                    cout << "0. Done Editing" << endl;
                    cout << "Enter your choice: ";
                    // getline(cin , editChoice);

                    // Check if the input is valid
                    // if (cin.fail()) {
                    //     // Clear the error flag
                    //     cin.clear();
                    //     // Clear the input buffer
                    //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    //     cout << "Invalid Input. Please enter a valid option." << endl;
                    //     continue; // Prompt the user to enter a choice again
                    // }

                    getline(cin, input); // Read the entire line as a string

                    // Check if the input is empty or contains non-numeric characters
                    if (input.empty() || !all_of(input.begin(), input.end(), ::isdigit)) {
                        cout << "Invalid Input. Please enter a valid option." << endl;
                        continue; // Prompt the user to enter a choice again
                    }

                    // Convert the input string to an integer
                    editChoice = stoi(input);

                    // Check if the choice is within the valid range
                    if (editChoice < 0 || editChoice > 7) {
                        cout << "Invalid Input. Please enter a valid option." << endl;
                        continue; // Prompt the user to enter a choice again
                    } else break;
                }

                string newValue;

                time_t now = time(nullptr);
                // Convert time to string
                string dateTime = ctime(&now);
                dateTime.pop_back();
                
                switch (editChoice) {
                    case 1:
                        cout << "Enter new First Name (press 0 to cancel this edit): ";
                        getline(cin, newValue);
                        newValue = trim(newValue);

                        if (newValue == "0") {
                            cout << endl;
                            break;
                        }

                        if (!validateName(newValue)) {
                            cout << endl << "Invalid first name format." << endl << endl;
                            continue;
                        }

                        it->second.setFirstName(newValue);
                        if(currentUser=="user") writeToLogFile(".\\userLogFile.txt", dateTime +  ": Edited Student \"First Name\" with mis: " + misToEdit);
                        break;
                    case 2:
                        cout << "Enter new Middle Name(press 0 to cancel this edit): ";
                        getline(cin, newValue);
                        newValue = trim(newValue);

                        if (newValue == "0") {
                            cout << endl;
                            break;
                        }

                        if (!validateName(newValue)) {
                            cout << endl << "Invalid middle name format." << endl << endl;
                            continue;
                        }

                        it->second.setMiddleName(newValue);
                        if(currentUser=="user") writeToLogFile(".\\userLogFile.txt", dateTime +  ": Edited Student \"Middle Name\" with mis: " + misToEdit);
                        break;
                    case 3:
                        cout << "Enter new Last Name(press 0 to cancel this edit): ";
                        getline(cin, newValue);
                        newValue = trim(newValue);

                        if (newValue == "0") {
                            cout << endl;
                            break;
                        }

                        if (!validateName(newValue)) {
                            cout << endl << "Invalid middle name format." << endl << endl;
                            continue;
                        }

                        it->second.setLastName(newValue);
                        if(currentUser=="user") writeToLogFile(".\\userLogFile.txt", dateTime +  ": Edited Student \"Last Name\" with mis: " + misToEdit);
                        break;
                    case 4:
                        cout << "Enter new Year of Admission(press 0 to cancel this edit): ";
                        getline(cin, newValue);
                        newValue = trim(newValue);

                        if (newValue == "0") {
                            cout << endl;
                            break;
                        }

                        if (!validateYearOfAdmission(newValue)) {
                            cout << endl << "Invalid year of admission." << endl << endl;
                            continue;
                        }

                        it->second.setYearOfAdmission(newValue);
                        if(currentUser=="user") writeToLogFile(".\\userLogFile.txt", dateTime +  ": Edited Student \"Year of admission\" with mis: " + misToEdit);
                        break;
                    case 5:
                        cout << "Enter new Email(press 0 to cancel this edit): ";
                        getline(cin, newValue);
                        newValue = trim(newValue);

                        if (newValue == "0") {
                            cout << endl;
                            break;
                        }

                        if (!validateEmail(newValue)) {
                            cout << endl << "Invalid email format." << endl << endl;
                            continue;
                        }

                        it->second.setEmail(newValue);
                        if(currentUser=="user") writeToLogFile(".\\userLogFile.txt", dateTime +  ": Edited Student \"Email\" with mis: " + misToEdit);
                        break;
                    case 6:
                        cout << "Enter new Mobile Number(press 0 to cancel this edit): ";
                        getline(cin, newValue);
                        newValue = trim(newValue);

                        if (newValue == "0") {
                            cout << endl;
                            break;
                        }

                        if (!validateMobileNumber(newValue)) {
                            cout << endl << "Invalid mobile number." << endl << endl;
                            continue;
                        }

                        it->second.setMobileNumber(newValue);
                        if(currentUser=="user") writeToLogFile(".\\userLogFile.txt", dateTime +  ": Edited Student \"Mobile Number\" with mis: " + misToEdit);
                        break;
                    case 7:
                        cout << "Enter new Home Address(press 0 to cancel this edit): ";
                        getline(cin, newValue);
                        newValue = trim(newValue);

                        if (newValue == "0") {
                            cout << endl;
                            break;
                        }

                        // if (!validateName(newValue)) {
                        //     cout << endl << "Invalid first name format." << endl << endl;
                        //     continue;
                        // }

                        it->second.setHomeAddress(newValue);
                        if(currentUser=="user") writeToLogFile(".\\userLogFile.txt", dateTime +  ": Edited Student \"Home Address\" with mis: " + misToEdit);
                        break;
                    

                    case 0:
                        break;
                    default:
                        cout << endl << "Invalid choice. Please enter a valid option." <<endl << endl;
                }
            } while (editChoice != 0);

            // Rewrite the CSV file with the updated map data
            database.saveToCSV();

            cout << endl << "Student with MIS " << misToEdit << " updated successfully." << endl;

            // Prompt the user to press any key to continue
            cout << endl <<endl <<endl <<endl << endl;
            cout << "Press Any key/ENTER twice to continue...";
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get(); // Wait for user to press any key
            system("CLS");

        } else {
            cout << endl << "Student with MIS " << misToEdit << " not found." << endl;

            // Prompt the user to press any key to continue
            cout << endl <<endl <<endl <<endl << endl;
            cout << "Press Any key/ENTER twice to continue...";
            // cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get(); // Wait for user to press any key
            system("CLS");
        }
    }


// private:
    
};

int main() {

    Authentication auth;
    User currentUser = auth.authenticate();
    StudentMenu menu;
    // cout << "Before executing menu for " << currentUser.getRole() << endl;
    menu.executeMenu(currentUser.getRole());
    // cout << "After executing menu" << endl;
    // removeBlankLinesFromUserLogFile(".\\userLogFile.txt");
    return 0;
}
