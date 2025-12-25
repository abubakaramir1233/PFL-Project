#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

void waitForKey();
void printHeader();
bool isAlphabetic(const string &s);
bool isPhoneValid(const string &s);
bool isCNICValid(const string &s);

void initializeUsers();

void signUpPatient();
bool signInPatient(string &username);
void patientMenu(const string &username);

void adminMenu();
void staffMenu();

void addPatient();
void viewAllPatients();
void updatePatient();
void deletePatient();

void adminLoginController();
void staffLoginController();
void patientController();

//                                                        (MAIN FUNCTION)
int main()
{
    initializeUsers();

    string choice;

    while (true)
    {
        system("clear");
        printHeader();

        cout << "\n\n1. Admin\n\n2. Staff\n\n3. Patient\n\n4. Exit\n\nChoice: ";
        getline(cin, choice);

        if (choice == "1")
            adminLoginController();

        else if (choice == "2")
            staffLoginController();

        else if (choice == "3")
            patientController();

        else if (choice == "4")
            return 0;

        else
        {
            cout << "Invalid choice!";
            waitForKey();
        }
    }
}

//                                                          (FUNCTIONS)
void waitForKey()
{
    cout << "\nPress Enter to continue...";
    string t;
    getline(cin, t);
}

void printHeader()
{

    cout << " _    _  ____   _____  _____  _____ _______     _       _      \n";
    cout << "| |  | |/ __ \\ / ____||  __ \\|_   _|__   __|   / \\     | |     \n";
    cout << "| |__| | |  | | (___  | |__) | | |    | |     / _ \\    | |     \n";
    cout << "|  __  | |  | |\\___ \\ |  ___/  | |    | |    / ___ \\   | |     \n";
    cout << "| |  | | |__| |____) || |     _| |_   | |   / /   \\ \\  | |____ \n";
    cout << "|_|  |_|\\____/|_____/ |_|    |_____|  |_|  /_/     \\_\\ |______|\n";
    cout << endl;

    cout << " __  __           _   _           _____  ______  __  __  ______  _   _  _______ \n";
    cout << "|  \\/  |    /\\   | \\ | |    /\\   / ____||  ____||  \\/  ||  ____|| \\ | ||__   __|\n";
    cout << "| \\  / |   /  \\  |  \\| |   /  \\ | |  __ | |__   | \\  / || |__   |  \\| |   | |  \n";
    cout << "| |\\/| |  / /\\ \\ | . ` |  / /\\ \\| | |_ ||  __|  | |\\/| ||  __|  | . ` |   | |  \n";
    cout << "| |  | | / ____ \\| |\\  | / ____ \\ |__| || |____ | |  | || |____ | |\\  |   | |  \n";
    cout << "|_|  |_|/_/    \\_\\_| \\_|/_/    \\_\\_____||______||_|  |_||______||_| \\_|   |_|  \n";
    cout << endl;

    cout << "  _____ __     __ _____  _______  ______  __  __ \n";
    cout << " / ____|\\ \\   / // ____||__   __||  ____||  \\/  |\n";
    cout << "| (___   \\ \\_/ /| (___     | |   | |__   | \\  / |\n";
    cout << " \\___ \\   \\   /  \\___ \\    | |   |  __|  | |\\/| |\n";
    cout << " ____) |   | |   ____) |   | |   | |____ | |  | |\n";
    cout << "|_____/    |_|  |_____/    |_|   |______||_|  |_|\n";
    cout << endl;

}

bool isAlphabetic(const string &s)
{
    if (s == "")
        return false;
    for (int i = 0; s[i] != '\0'; i++)
        if (!isalpha(s[i]) && s[i] != ' ')
            return false;
    return true;
}

bool isPhoneValid(const string &s)
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!isdigit(s[i]))
            return false;
        count++;
    }
    return count == 11;
}

bool isCNICValid(const string &s)
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!isdigit(s[i]))
            return false;
        count++;
    }
    return count == 13;
}

void initializeUsers()
{
    ifstream check("users.txt");
    bool fileExists = false;
    string temp;
    if (check)
        fileExists = true;
    check.close();

    if (!fileExists)
    {
        ofstream create("users.txt");
        create << "admin admin123 admin\n";
        create << "staff staff123 staff\n";
        create.close();
    }
}

void signUpPatient()
{
    system("clear");
    printHeader();
    string username, password, fullname, phone, cnic;

    while (true)
    {
        cout << "Enter username: ";
        getline(cin, username);
        if (username != "")
            break;
        cout << "Username cannot be empty.\n";
    }

    while (true)
    {
        cout << "Enter password: ";
        getline(cin, password);
        if (password != "")
            break;
        cout << "Password cannot be empty.\n";
    }

    while (true)
    {
        cout << "Full Name: ";
        getline(cin, fullname);
        if (isAlphabetic(fullname))
            break;
        cout << "Name must contain letters only.\n";
    }

    while (true)
    {
        cout << "Phone (11 digits): ";
        getline(cin, phone);
        if (isPhoneValid(phone))
            break;
        cout << "Invalid phone number.\n";
    }

    while (true)
    {
        cout << "CNIC (13 digits): ";
        getline(cin, cnic);
        if (isCNICValid(cnic))
            break;
        cout << "Invalid CNIC.\n";
    }

    ofstream out("patients.txt", ios::app);
    out << username << " " << password << " " << fullname << " " << phone << " " << cnic << endl;
    out.close();

    cout << "\nPatient added successfully!";
    waitForKey();
}

bool signInPatient(string &username)
{
    system("clear");
    printHeader();
    string password;
    cout << "Patient Sign-In\nUsername: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);

    ifstream in("patients.txt");
    string u, p, n, ph, c;
    while (in >> u >> p >> n >> ph >> c)
    {
        if (u == username && p == password)
        {
            in.close();
            return true;
        }
    }
    in.close();

    cout << "Invalid credentials!";
    waitForKey();
    return false;
}

void patientMenu(const string &username)
{
    while (true)
    {
        system("clear");
        printHeader();
        cout << "------------------------------------------------------------\n";
        cout << "                    --- Patient Menu ---\n";
        cout << "------------------------------------------------------------\n";
        cout << "\n\n1. View Personal Details\n\n2. Logout\n ";
        cout << "------------------------------------------------------------\n";
        cout << "Choice : ";
        string choice;
        getline(cin, choice);

        if (choice == "1")
        {
            ifstream in("patients.txt");
            string u, p, n, ph, c;
            while (in >> u >> p >> n >> ph >> c)
            {
                if (u == username)
                {
                    cout << left << setw(15) << "\nFull Name" << setw(15) << " Phone" << setw(15) << "CNIC" << "\n";
                    cout << left << setw(15) << n << setw(15) << ph << setw(15) << c << "\n";
                    break;
                }
            }
            in.close();
            waitForKey();
        }
        else if (choice == "2")
            return;
    }
}

//                                             (ADMIN & STAFF FUNCTIONS)
void adminMenu()
{
    while (true)
    {
        system("clear");
        printHeader();
        cout << "------------------------------------------------------------\n";
        cout << "                     ADMIN MENU\n";
        cout << "------------------------------------------------------------\n";
        cout << " \n\n1. Add Patient\n\n2. View All Patients\n\n3. Update Patient\n\n4. Delete Patient\n\n5. Logout\n";
        cout << "------------------------------------------------------------\n";
        cout << "Choice : ";
        string choice;
        getline(cin, choice);

        if (choice == "1")
            addPatient();
        else if (choice == "2")
            viewAllPatients();
        else if (choice == "3")
            updatePatient();
        else if (choice == "4")
            deletePatient();
        else if (choice == "5")
            return;
    }
}

void staffMenu()
{
    while (true)
    {
        system("clear");
        printHeader();
        cout << "------------------------------------------------------------\n";
        cout << "                     STAFF MENU\n";
        cout << "------------------------------------------------------------\n";
        cout << "\n\n1. View All Patients\n\n2. Logout\n";
        cout << "------------------------------------------------------------\n";
        cout << "Choice : ";
        string choice;
        getline(cin, choice);

        if (choice == "1")
            viewAllPatients();
        else if (choice == "2")
            return;
    }
}

//                                          ( CRUD FUNCTIONS )
void addPatient()
{
    system("clear");
    printHeader();

    cout << "------------------------------------------------------------\n";
    cout << "                 --- Add New Patient ---\n";
    cout << "------------------------------------------------------------\n";

    string username;
    string password;
    string fullName;
    string phone;
    string cnic;

    // Username
    while (true)
    {
        cout << "Enter Username: ";
        getline(cin, username);
        if (username != "")
            break;
        cout << "Username cannot be empty.\n";
    }

    // Password
    while (true)
    {
        cout << "Enter Password: ";
        getline(cin, password);
        if (password != "")
            break;
        cout << "Password cannot be empty.\n";
    }

    // Full Name
    while (true)
    {
        cout << "Enter Full Name: ";
        getline(cin, fullName);
        if (isAlphabetic(fullName))
            break;
        cout << "Name must contain alphabets only.\n";
    }

    // Replace spaces with _
    for (int i = 0; fullName[i] != '\0'; i++)
    {
        if (fullName[i] == ' ')
            fullName[i] = '_';
    }

    // Phone
    while (true)
    {
        cout << "Enter Phone (11 digits): ";
        getline(cin, phone);
        if (isPhoneValid(phone))
            break;
        cout << "Invalid phone number.\n";
    }

    // CNIC
    while (true)
    {
        cout << "Enter CNIC (13 digits): ";
        getline(cin, cnic);
        if (isCNICValid(cnic))
            break;
        cout << "Invalid CNIC.\n";
    }

    ofstream outFile("patients.txt", ios::app);
    outFile << username << " "
            << password << " "
            << fullName << " "
            << phone << " "
            << cnic << endl;
    outFile.close();

    cout << "\nPatient added successfully!";
    waitForKey();
}

void viewAllPatients()
{
    system("clear");
    printHeader();
    cout << "------------------------------------------------------------\n";
    cout << "                  --- All Patients ---\n";
    cout << "------------------------------------------------------------\n";
    cout << left << setw(15) << "Username" << setw(15) << "Full Name" << setw(15) << "Phone" << setw(15) << "CNIC" << "\n";
    cout << "------------------------------------------------------\n";

    ifstream in("patients.txt");
    string u, p, n, ph, c;
    while (in >> u >> p >> n >> ph >> c)
        cout << left << setw(15) << u << setw(15) << n << setw(15) << ph << setw(15) << c << "\n";
    in.close();
    waitForKey();
}

void updatePatient()
{
    system("clear");
    printHeader();

    cout << "------------------------------------------------------------\n";
    cout << "                   --- Update Patient ---\n";
    cout << "------------------------------------------------------------\n";

    string targetUsername;
    cout << "Enter patient username to update: ";
    getline(cin, targetUsername);

    ifstream inFile("patients.txt");

    string username[100];
    string password[100];
    string name[100];
    string phone[100];
    string cnic[100];

    int total = 0;
    bool found = false;

    while (inFile >> username[total] >> password[total] >> name[total] >> phone[total] >> cnic[total])
    {
        if (username[total] == targetUsername)
            found = true;

        total++;
    }
    inFile.close();

    if (!found)
    {
        cout << "Patient not found!";
        waitForKey();
        return;
    }

    string newName, newPhone, newCNIC;

    while (true)
    {
        cout << "New Full Name: ";
        getline(cin, newName);
        if (isAlphabetic(newName))
            break;
        cout << "Name must contain letters only.\n";
    }

    for (int i = 0; newName[i] != '\0'; i++)
        if (newName[i] == ' ')
            newName[i] = '_';

    while (true)
    {
        cout << "New Phone (11 digits): ";
        getline(cin, newPhone);
        if (isPhoneValid(newPhone))
            break;
        cout << "Invalid phone number.\n";
    }

    while (true)
    {
        cout << "New CNIC (13 digits): ";
        getline(cin, newCNIC);
        if (isCNICValid(newCNIC))
            break;
        cout << "Invalid CNIC.\n";
    }

    for (int i = 0; i < total; i++)
    {
        if (username[i] == targetUsername)
        {
            name[i] = newName;
            phone[i] = newPhone;
            cnic[i] = newCNIC;
        }
    }

    ofstream outFile("patients.txt");
    for (int i = 0; i < total; i++)
    {
        outFile << username[i] << " "
                << password[i] << " "
                << name[i] << " "
                << phone[i] << " "
                << cnic[i] << endl;
    }
    outFile.close();

    cout << "Patient updated successfully!";
    waitForKey();
}
void deletePatient()
{
    system("clear");
    printHeader();
    cout << "------------------------------------------------------------\n";
    cout << "              --- Delete Patient ---\n";
    cout << "------------------------------------------------------------\n";
    string target;
    cout << "Enter patient username to delete: ";
    getline(cin, target);

    ifstream in("patients.txt");
    string lines[100];
    int count = 0;
    string u, p, n, ph, c;
    bool found = false;

    while (in >> u >> p >> n >> ph >> c)
    {
        if (u == target)
        {
            found = true;
            continue;
        }
        lines[count] = u + " " + p + " " + n + " " + ph + " " + c;
        count++;
    }
    in.close();

    if (!found)
    {
        cout << "Patient not found!";
        waitForKey();
        return;
    }

    ofstream out("patients.txt");
    for (int i = 0; i < count; i++)
        out << lines[i] << endl;
    out.close();

    cout << "Patient deleted successfully!";
    waitForKey();
}
void adminLoginController()
{
    system("clear");
    printHeader();

    string username, password;
    cout << "------------------------------------------------------------\n";
    cout << "                   Admin Sign-In\n";
    cout << "------------------------------------------------------------\n";
    cout << "\n\nUsername: ";
    getline(cin, username);
    cout << "\n\nPassword: ";
    getline(cin, password);

    ifstream inFile("users.txt");
    string u, p, r;
    bool loggedIn = false;

    while (inFile >> u >> p >> r)
    {
        if (u == username && p == password && r == "admin")
        {
            loggedIn = true;
            break;
        }
    }
    inFile.close();

    if (loggedIn)
        adminMenu();
    else
    {
        cout << "Invalid credentials!";
        waitForKey();
    }
}
void staffLoginController()
{
    system("clear");
    printHeader();

    string username, password;
    cout << "------------------------------------------------------------\n";
    cout << "                 Staff Sign-In\n";
    cout << "------------------------------------------------------------\n";
    cout << "\n\nUsername: ";
    getline(cin, username);
    cout << "\n\nPassword: ";
    getline(cin, password);

    ifstream inFile("users.txt");
    string u, p, r;
    bool loggedIn = false;

    while (inFile >> u >> p >> r)
    {
        if (u == username && p == password && r == "staff")
        {
            loggedIn = true;
            break;
        }
    }
    inFile.close();

    if (loggedIn)
        staffMenu();
    else
    {
        cout << "Invalid credentials!";
        waitForKey();
    }
}
void patientController()
{
    system("clear");
    printHeader();

    string choice, username;
    cout << "\n\n1. Sign-Up\n\n2. Sign-In\n\nChoose: ";
    getline(cin, choice);

    if (choice == "1")
        signUpPatient();

    else if (choice == "2")
    {
        if (signInPatient(username))
            patientMenu(username);
    }
    else
    {
        cout << "Invalid choice!";
        waitForKey();
    }
}