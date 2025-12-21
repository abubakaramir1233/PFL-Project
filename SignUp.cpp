#include <iostream>
#include <string>
using namespace std;
//========== Users ========
const int MAX_USERS = 50;

string usernames[MAX_USERS];
string passwords[MAX_USERS];
string roles[MAX_USERS];
int userCount = 0;


// ========= patients ========
const int MAX_PATIENTS = 100;

string patientName[MAX_PATIENTS];
int patientAge[MAX_PATIENTS];
string patientGender[MAX_PATIENTS];
string patientDisease[MAX_PATIENTS];
int patientRoom[MAX_PATIENTS];
int totalPatients = 0;

int countChars(string s);
bool isValidRole(string role);

void mainMenu();
void adminMenu();
void staffMenu();
void signUp();
void signIn();

/* ================= MAIN ================= */
int main()
{
    mainMenu();
    return 0;
}

/* ============== MENUS =================== */

void mainMenu()
{
    string choiceStr;
    int choice;

    for (;;)
    {
        system("cls");
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

        cout << "1. Sign Up\n";
        cout << "2. Sign In\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";

        getline(cin, choiceStr);

        if (choiceStr[0] < '1' || choiceStr[0] > '3' || countChars(choiceStr) > 1)
        {
            cout << "Invalid input. Press Enter to continue...";
            string t;
            getline(cin, t);
            continue;
        }

        if (choice == 1)
            signUp();
        else if (choice == 2)
            signIn();
        else if (choice == 3)
            break;
    }
}

void adminMenu()
{
    cout << "------------------------------------------------------------\n";
    cout << "                     ADMIN MENU\n";
    cout << "------------------------------------------------------------\n";
    cout << "1. Add New Patient\n";
    cout << "2. View All Patients\n";
    cout << "3. Search Patient\n";
    cout << "4. Discharge Patient\n";
    cout << "5. Calculate Bill\n";
    cout << "6. Sort by Age\n";
    cout << "7. View History\n";
    cout << "8. Update Patient\n";
    cout << "9. Medicine Cost\n";
    cout << "10. Doctor recommendation\n";
    cout << "11. Log out\n";
    cout << "------------------------------------------------------------\n";
    cout << "Enter your choice: ";
    string t;
    getline(cin, t);
}

void staffMenu()
{
    cout << "------------------------------------------------------------\n";
    cout << "                     STAFF MENU\n";
    cout << "------------------------------------------------------------\n";
    cout << "1. View Patients\n";
    cout << "2. Search Patient\n";
    cout << "3. Bill Calculator\n";
    cout << "4. Medicine Cost\n";
    cout << "5. Recommend Doctor\n";
    cout << "6. Logout\n";


    string t;
    getline(cin, t);
}

/* ============== AUTH ==================== */

void signUp()
{
    if (userCount >= MAX_USERS)
    {
        cout << "User limit reached.\n";
        cout << "Press Enter to continue...";
        string t;
        getline(cin, t);
        return;
    }

    string uname, pass, role;

    cout << "\n--- SIGN UP ---\n";
    for (;;)
    {
        cout << "Enter role (admin/staff): ";
        getline(cin, role);

        if (isValidRole(role))
            break;
        else
            cout << "Only admin or staff allowed.\n";
    }

    for (;;)
    {
        cout << "Enter username: ";
        getline(cin, uname);

        int len = countChars(uname);
        int exists = 0;

        for (int i = 0; i < userCount; i++)
        {
            if (usernames[i] == uname)
            {
                exists = 1;
                break;
            }
        }

        if (len < 3)
            cout << "Username must be at least 3 characters.\n";
        else if (exists)
            cout << "Username already exists.\n";
        else
            break;
    }

    for (;;)
    {
        cout << "Enter password: ";
        getline(cin, pass);

        if (countChars(pass) < 4)
            cout << "Password must be at least 4 characters.\n";
        else
            break;
    }

    usernames[userCount] = uname;
    passwords[userCount] = pass;
    roles[userCount] = role;
    userCount++;

    cout << "Sign up successful.\n";
    cout << "Press Enter to continue...";
    string t;
    getline(cin, t);
}

void signIn()
{
    string role, uname, pass;
    int found = 0;

    cout << "\n--- SIGN IN ---\n";

    cout << "Enter role (admin/staff): ";
    getline(cin, role);

    if (!isValidRole(role))
    {
        cout << "Invalid role.\n";
        cout << "Press Enter to continue...";
        string t;
        getline(cin, t);
        return;
    }

    cout << "Enter username: ";
    getline(cin, uname);

    cout << "Enter password: ";
    getline(cin, pass);

    for (int i = 0; i < userCount; i++)
    {
        if (usernames[i] == uname &&
            passwords[i] == pass &&
            roles[i] == role)
        {
            cout << "Login successful.\n";

            if (role == "admin")
                adminMenu();
            else
                staffMenu();

            return;
        }
    }

    cout << "Invalid credentials.\n";
    cout << "Press Enter to continue...";
    string t;
    getline(cin, t);
}

/* ============== HELPERS ================= */

int countChars(string s)
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
        count++;
    return count;
}

bool isValidRole(string role)
{
    if (role == "admin" || role == "staff")
        return true;
    return false;
}
