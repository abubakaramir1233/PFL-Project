//   CREDENTIALS FOR SIGN UP  | ADMIN=admin admin123  (CRUD)
//                            | PHARMACIST =pharmacist pharma123 (CRUD)
//                            | STAFF=staff staff123

// sign up is only for patients
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

bool isDoctorPhoneUnique(const string &phone, string doctors[][4], int total);
bool isPatientPhoneOrCNICUnique(const string &phone, const string &cnic, string patients[][5], int total);
bool isPatientUsernameUnique(const string &username);
void addPatient();
void viewAllPatients();
void updatePatient();
void deletePatient();
void addDoctor();
void searchPatient();
void viewAllDoctors();
void updateDoctor();
void deleteDoctor();
void adminLoginController();
void staffLoginController();
void patientController();

void pharmacistLoginController();
void pharmacistMenu();

void addMedicine();
void viewAllMedicines();
void updateMedicine();
void deleteMedicine();
void searchMedicineByID();

bool isNumeric(const string &s);
bool isMedicineIDUnique(const string &id);
void lines();
void error();
//                                                        (MAIN FUNCTION)
int main()
{
    initializeUsers();

    string choice;

    while (true)
    {
        system("cls");
        printHeader();
        lines();
        cout << "\n\n1. Admin\t\t(Sign-in)\n\n2. Staff\t\t(Sign-in)\n\n3. Pharmacist\t\t(Sign-in)\n\n4. Patient\t\t(Sign-UP/Sign-in)\n\n5. Exit";
        lines();
        cout << "\nChoice: ";
        getline(cin, choice);

        if (choice == "1")
            adminLoginController();

        else if (choice == "2")
            staffLoginController();

        else if (choice == "3")
            pharmacistLoginController();

        else if (choice == "4")
            patientController();

        else if (choice == "5")
        {
            const string YELLOW = "\033[33m";
            cout << YELLOW;
            cout << "THANKS FOR USING HOSPITAL MANAGEMENT SYSTEM";
            return 0;
        }
        else
        {
            error();
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
void error()

{
    const string RED = "\033[31m";
    cout << RED;
}
void lines()
{

    const string CYAN = "\033[35m";
    const string RESET = "\033[0m";
    cout << CYAN;
    cout << "\n############################################################################################\n";
    cout << RESET << endl;
}
void printHeader()

{
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN = "\033[36m";
    const string RESET = "\033[0m";

    cout << CYAN;
    cout << "############################################################################################\n";
    cout << RESET << endl;
    cout << YELLOW;
    cout << " _    _  ____   _____  _____  _____ _______     _       _      \n";
    cout << "| |  | |/ __ \\ / ____||  __ \\|_   _|__   __|   / \\     | |     \n";
    cout << "| |__| | |  | | (___  | |__) | | |    | |     / _ \\    | |     \n";
    cout << "|  __  | |  | |\\___ \\ |  ___/  | |    | |    / ___ \\   | |     \n";
    cout << "| |  | | |__| |____) || |     _| |_   | |   / /   \\ \\  | |____ \n";
    cout << "|_|  |_|\\____/|_____/ |_|    |_____|  |_|  /_/     \\_\\ |______|\n";
    cout << RESET << endl;

    cout << BLUE;
    cout << " __  __           _   _           _____  ______  __  __  ______  _   _  _______ \n";
    cout << "|  \\/  |    /\\   | \\ | |    /\\   / ____||  ____||  \\/  ||  ____|| \\ | ||__   __|\n";
    cout << "| \\  / |   /  \\  |  \\| |   /  \\ | |  __ | |__   | \\  / || |__   |  \\| |   | |  \n";
    cout << "| |\\/| |  / /\\ \\ | . ` |  / /\\ \\| | |_ ||  __|  | |\\/| ||  __|  | . ` |   | |  \n";
    cout << "| |  | | / ____ \\| |\\  | / ____ \\ |__| || |____ | |  | || |____ | |\\  |   | |  \n";
    cout << "|_|  |_|/_/    \\_\\_| \\_|/_/    \\_\\_____||______||_|  |_||______||_| \\_|   |_|  \n";
    cout << RESET << endl;

    cout << GREEN;
    cout << "  _____ __     __ _____  _______  ______  __  __ \n";
    cout << " / ____|\\ \\   / // ____||__   __||  ____||  \\/  |\n";
    cout << "| (___   \\ \\_/ /| (___     | |   | |__   | \\  / |\n";
    cout << " \\___ \\   \\   /  \\___ \\    | |   |  __|  | |\\/| |\n";
    cout << " ____) |   | |   ____) |   | |   | |____ | |  | |\n";
    cout << "|_____/    |_|  |_____/    |_|   |______||_|  |_|\n";
    cout << RESET << endl;

    cout << CYAN;
    cout << "############################################################################################\n";
    cout << RESET << endl;
}

bool isNumeric(const string &s)
{
    if (s == "")
        return false;

    for (int i = 0; s[i] != '\0'; i++)
        if (!isdigit(s[i]))
            return false;

    return true;
}
bool isDoctorPhoneUnique(const string &phone, string doctors[][4], int total)
{
    for (int i = 0; i < total; i++)
    {
        if (doctors[i][3] == phone)
            return false;
    }
    return true;
}
bool isPatientPhoneOrCNICUnique(const string &phone, const string &cnic, string patients[][5], int total)
{
    for (int i = 0; i < total; i++)
    {
        if (patients[i][3] == phone || patients[i][4] == cnic)
            return false;
    }
    return true;
}

bool isMedicineIDUnique(const string &id)
{
    ifstream in("medicines.txt");
    string mid, name, category, price, quantity, expiry;

    while (in >> mid >> name >> category >> price >> quantity >> expiry)
    {
        if (mid == id)
        {
            in.close();
            return false;
        }
    }
    in.close();
    return true;
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
bool isValidExpiryDate(string d)
{
    int count = 0;
    while (d[count] != '\0')
        count++;

    if (count != 8)
        return false;

    for (int i = 0; i < 8; i++)
        if (d[i] < '0' || d[i] > '9')
            return false;

    int year =
        (d[0] - '0') * 1000 +
        (d[1] - '0') * 100 +
        (d[2] - '0') * 10 +
        (d[3] - '0');

    int month =
        (d[4] - '0') * 10 +
        (d[5] - '0');

    int day =
        (d[6] - '0') * 10 +
        (d[7] - '0');

    if (month < 1 || month > 12)
        return false;

    if (day < 1)
        return false;

    bool isLeapYear = false;

    if (year % 400 == 0)
        isLeapYear = true;
    else if (year % 100 == 0)
        isLeapYear = false;
    else if (year % 4 == 0)
        isLeapYear = true;

    int maxDays;

    if (month == 2)
    {
        if (isLeapYear)
            maxDays = 29;
        else
            maxDays = 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        maxDays = 30;
    }
    else
    {
        maxDays = 31;
    }

    if (day > maxDays)
        return false;

    return true;
}
void initializeUsers()
{
    ofstream out("users.txt");
    out << "admin admin123 admin\n";
    out << "staff staff123 staff\n";
    out << "pharmacist pharma123 pharmacist\n";
    out.close();
}
bool isPatientUsernameUnique(const string &username)
{
    ifstream in("patients.txt");
    string u, p, n, ph, c;

    while (in >> u >> p >> n >> ph >> c)
    {
        if (u == username)
        {
            in.close();
            return false;
        }
    }
    in.close();
    return true;
}
//                                                               (SIGN UP / SIGN IN)
void adminLoginController()
{
    system("cls");
    printHeader();

    string username, password;
    lines();
    cout << "                   Admin Sign-In\n";
    lines();
    cout << "\t\t\t\t\t\t//(TRIPLE Click 'ENTER' if you want to EXIT)";
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
        error();
        cout << "Invalid credentials!";
        waitForKey();
    }
}
void staffLoginController()
{
    system("cls");
    printHeader();

    string username, password;
    lines();
    cout << "                 Staff Sign-In\n";
    lines();
    cout << "\t\t\t\t\t\t//(TRIPLE Click 'ENTER' if you want to EXIT)";
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
        error();
        cout << "Invalid credentials!";
        waitForKey();
    }
}
void patientController()
{
    system("cls");
    printHeader();

    string choice, username;
    lines();
    cout << "            ------PATIENT SIGN IN/UP ------             \n";
    lines();
    cout << "\n\n1. Sign-Up\n\n2. Sign-In\n\n3. Exit\n\nChoose: ";
    getline(cin, choice);

    if (choice == "1")
        signUpPatient();

    else if (choice == "2")
    {
        if (signInPatient(username))
            patientMenu(username);
    }
    else if (choice == "3")
    {
        return;
    }
    else
    {

        cout << "Invalid choice!";
        waitForKey();
    }
}
void signUpPatient()
{
    const int FIELDS = 5;
    string patients[100][FIELDS];
    int total = 0;

    ifstream in("patients.txt");
    while (in >> patients[total][0] >> patients[total][1] >> patients[total][2] >> patients[total][3] >> patients[total][4])
    {
        total++;
    }
    in.close();
    system("cls");
    printHeader();
    string username, password, fullname, phone, cnic;
    lines();
    cout << "                   PATIENT SIGN UP ";
    lines();
    while (true)
    {
        cout << "Enter username: ";
        getline(cin, username);

        if (username == "")
        {

            cout << "Username cannot be empty.\n";
        }
        else if (!isPatientUsernameUnique(username))
        {

            cout << "Username already exists.\n";
        }
        else
            break;
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

        if (!isPhoneValid(phone))
        {
            cout << "Invalid phone number.\n";
        }
        else
        {
            bool exists = false;
            for (int i = 0; i < total; i++)
            {
                if (patients[i][3] == phone)
                {
                    exists = true;
                    break;
                }
            }

            if (exists)
                cout << "Phone number already exists!\n";
            else
                break;
        }
    }

    while (true)
    {
        cout << "CNIC (13 digits): ";
        getline(cin, cnic);

        if (!isCNICValid(cnic))
        {
            cout << "Invalid CNIC.\n";
        }
        else
        {
            bool exists = false;
            for (int i = 0; i < total; i++)
            {
                if (patients[i][4] == cnic)
                {
                    exists = true;
                    break;
                }
            }

            if (exists)
                cout << "CNIC already exists!\n";
            else
                break;
        }
    }

    ofstream out("patients.txt", ios::app);
    out << username << " " << password << " " << fullname << " " << phone << " " << cnic << endl;
    out.close();

    cout << "\nPatient added successfully!";
    waitForKey();
}

bool signInPatient(string &username)
{
    system("cls");
    printHeader();
    string password;
    lines();
    cout << "Patient Sign-In\n";
    lines();
    cout << "\nUsername: ";
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
void pharmacistLoginController()
{
    system("cls");
    printHeader();

    string username, password;
    lines();
    cout << "               Pharmacist Sign-In\n";
    lines();
    cout << "\t\t\t\t\t\t//(TRIPLE Click 'ENTER' if you want to EXIT)";
    cout << "\nUsername: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);

    ifstream in("users.txt");
    string u, p, role;
    bool loggedIn = false;

    while (in >> u >> p >> role)
    {
        if (u == username && p == password && role == "pharmacist")
        {
            loggedIn = true;
            break;
        }
    }
    in.close();

    if (loggedIn)
        pharmacistMenu();
    else
    {

        cout << "Invalid credentials!";
        waitForKey();
    }
}
//                                                           (PHARMACIST MENU AND MEDECINE CRUD)
void pharmacistMenu()
{
    while (true)
    {
        system("cls");
        printHeader();
        lines();
        cout << "                 PHARMACIST MENU\n";
        lines();
        cout << "\n1. Add Medicine\n2. View Medicines\n3. Update Medicine\n4. Delete Medicine\n5. Search Medicine\n6. Logout\n";
        lines();
        cout << "Choice: ";

        string choice;
        getline(cin, choice);

        if (choice == "1")
            addMedicine();
        else if (choice == "2")
            viewAllMedicines();
        else if (choice == "3")
            updateMedicine();
        else if (choice == "4")
            deleteMedicine();
        else if (choice == "5")
            searchMedicineByID();
        else if (choice == "6")
            return;
        else
        {
            error();
            cout << "\n INVALID CHOICE";
            waitForKey();
        }
    }
}
void addMedicine()
{
    system("cls");
    printHeader();
   lines();
   cout<<"        ADD  MEDICINE   \n";
   lines();
    string medicineID, medicineName, category, price, quantity, expiryDate;

    while (true)
    {
        cout << "Medicine ID: ";
        getline(cin, medicineID);
        if (medicineID != "" && isMedicineIDUnique(medicineID))
            break;

        cout << "Invalid or duplicate ID.\n";
    }

    while (true)
    {
        cout << "Medicine Name: ";
        getline(cin, medicineName);
        if (isAlphabetic(medicineName))
            break;

        cout << "Invalid name.\n";
    }

    while (true)
    {
        cout << "Category: ";
        getline(cin, category);
        if (isAlphabetic(category))
            break;

        cout << "Invalid category.\n";
    }

    while (true)
    {
        cout << "Price: ";
        getline(cin, price);
        if (isNumeric(price))
            break;

        cout << "Price must be numeric.\n";
    }

    while (true)
    {
        cout << "Quantity: ";
        getline(cin, quantity);
        if (isNumeric(quantity))
            break;

        cout << "Quantity must be numeric.\n";
    }

    while (true)
    {
        cout << "Expiry Date (YYYYMMDD): ";
        getline(cin, expiryDate);

        if (isValidExpiryDate(expiryDate))
            break;

        cout << "Invalid expiry date.\n";
    }

    ofstream out("medicines.txt", ios::app);
    out << medicineID << " "
        << medicineName << " "
        << category << " "
        << price << " "
        << quantity << " "
        << expiryDate << endl;
    out.close();

    cout << "\nMedicine added successfully!";
    waitForKey();
}
void viewAllMedicines()
{
    system("cls");
    printHeader();
    lines();
    cout << left << setw(10) << "ID"
         << setw(15) << "Name"
         << setw(15) << "Category"
         << setw(10) << "Price"
         << setw(10) << "Qty"
         << setw(12) << "Expiry" << endl;

    lines();

    ifstream in("medicines.txt");
    string mid, name, category, price, qty, expiry;

    while (in >> mid >> name >> category >> price >> qty >> expiry)
        cout << left << setw(10) << mid
             << setw(15) << name
             << setw(15) << category
             << setw(10) << price
             << setw(10) << qty
             << setw(12) << expiry << endl;

    in.close();
    waitForKey();
}
void updateMedicine()
{
    system("cls");
    printHeader();
lines();
cout <<"                      UPADTE MEDICINE\n";
lines();
    string targetID;
    cout << "Enter Medicine ID to update: ";
    getline(cin, targetID);

    string mid[100], name[100], category[100], price[100], qty[100], expiry[100];
    int count = 0;
    bool found = false;

    ifstream in("medicines.txt");
    while (in >> mid[count] >> name[count] >> category[count] >> price[count] >> qty[count] >> expiry[count])
    {
        if (mid[count] == targetID)
            found = true;
        count++;
    }
    in.close();

    if (!found)
    {

        cout << "Medicine not found!";
        waitForKey();
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (mid[i] == targetID)
        {
            cout << "New Price: ";
            getline(cin, price[i]);
            cout << "New Quantity: ";
            getline(cin, qty[i]);
        }
    }

    ofstream out("medicines.txt");
    for (int i = 0; i < count; i++)
        out << mid[i] << " " << name[i] << " " << category[i] << " "
            << price[i] << " " << qty[i] << " " << expiry[i] << endl;
    out.close();

    cout << "Medicine updated successfully!";
    waitForKey();
}
void deleteMedicine()
{
    system("cls");
    printHeader();
lines();
cout <<"                          DELETE MEDICINE\n";
lines();
    string targetID;
    cout << "Enter Medicine ID to delete: ";
    getline(cin, targetID);

    ifstream in("medicines.txt");
    string line[100];
    int count = 0;
    string mid, name, category, price, qty, expiry;
    bool found = false;

    while (in >> mid >> name >> category >> price >> qty >> expiry)
    {
        if (mid == targetID)
        {
            found = true;
            continue;
        }
        line[count++] = mid + " " + name + " " + category + " " + price + " " + qty + " " + expiry;
    }
    in.close();

    if (!found)
    {

        cout << "Medicine not found!";
        waitForKey();
        return;
    }

    ofstream out("medicines.txt");
    for (int i = 0; i < count; i++)
        out << line[i] << endl;
    out.close();

    cout << "Medicine deleted successfully!";
    waitForKey();
}
void searchMedicineByID()
{
    system("cls");
    printHeader();
    lines();
cout <<"                          SEARCH MEDICINE\n";
lines();

    string searchID;
    cout << "Enter Medicine ID to search: ";
    getline(cin, searchID);

    if (searchID == "")
    {

        cout << "ID cannot be empty!";
        waitForKey();
        return;
    }

    ifstream in("medicines.txt");
    string mid, name, category, price, qty, expiry;
    bool found = false;

    while (in >> mid >> name >> category >> price >> qty >> expiry)
    {
        if (mid == searchID)
        {
            cout << "\nMedicine Found:\n";
            cout << "ID: " << mid << endl;
            cout << "Name: " << name << endl;
            cout << "Category: " << category << endl;
            cout << "Price: " << price << endl;
            cout << "Quantity: " << qty << endl;
            cout << "Expiry: " << expiry << endl;
            found = true;
            break;
        }
    }
    in.close();

    if (!found)
    {

        cout << "\nMedicine not found!";
    }

    waitForKey();
}
//                                                                          (ADMIN MENU AND PATIENT CRUD)
void adminMenu()
{
    while (true)
    {
        system("cls");
        printHeader();
        lines();
        cout << "                     ADMIN MENU\n";
        lines();
        cout << " \n\n1. Add Patient\n2. View All Patients\n3. Update Patient\n4. Delete Patient\n5. Add Doctor\n6. View Doctors\n7. Update Doctor\n8. Delete Doctor\n9. Logout\n";
        lines();
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
            addDoctor();
        else if (choice == "6")
            viewAllDoctors();
        else if (choice == "7")
            updateDoctor();
        else if (choice == "8")
            deleteDoctor();
        else if (choice == "9")
            return;
        else
        {
            error();

            cout << "\nINVALID CHOICE";
            waitForKey();
        }
    }
}

void addPatient()
{
    system("cls");
    printHeader();

    lines();
    cout << "                 --- Add New Patient ---\n";
    lines();

    const int FIELDS = 5;
    string patients[100][FIELDS];
    int total = 0;

    
    ifstream in("patients.txt");
    while (in >> patients[total][0] >> patients[total][1] >> patients[total][2] >> patients[total][3] >> patients[total][4])
    {
        total++;
    }
    in.close();

    string username, password, fullName, phone, cnic;

    
    while (true)
    {
        cout << "Enter username: ";
        getline(cin, username);
        if (username == "")
            cout << "Username cannot be empty.\n";
        else
        {
            bool exists = false;
            for (int i = 0; i < total; i++)
                if (patients[i][0] == username)
                    exists = true;

            if (exists)
                cout << "Username already exists.\n";
            else
                break;
        }
    }


    while (true)
    {
        cout << "Enter Password: ";
        getline(cin, password);
        if (password != "")
            break;
        cout << "Password cannot be empty.\n";
    }


    while (true)
    {
        cout << "Enter Full Name: ";
        getline(cin, fullName);
        if (isAlphabetic(fullName))
            break;
        cout << "Name must contain letters only.\n";
    }
    for (int i = 0; fullName[i] != '\0'; i++)
        if (fullName[i] == ' ')
            fullName[i] = '_';

   
    while (true)
    {
        cout << "Enter Phone (11 digits): ";
        getline(cin, phone);

        if (!isPhoneValid(phone))
            cout << "Invalid phone number.\n";
        else
        {
            bool exists = false;
            for (int i = 0; i < total; i++)
                if (patients[i][3] == phone)
                    exists = true;

            if (exists)
                cout << "Phone already exists!\n";
            else
                break;
        }
    }
    while (true)
    {
        cout << "Enter CNIC (13 digits): ";
        getline(cin, cnic);

        if (!isCNICValid(cnic))
            cout << "Invalid CNIC.\n";
        else
        {
            bool exists = false;
            for (int i = 0; i < total; i++)
                if (patients[i][4] == cnic)
                    exists = true;

            if (exists)
                cout << "CNIC already exists!\n";
            else
                break;
        }
    }


    patients[total][0] = username;
    patients[total][1] = password;
    patients[total][2] = fullName;
    patients[total][3] = phone;
    patients[total][4] = cnic;
    total++;

    ofstream out("patients.txt");
    for (int i = 0; i < total; i++)
    {
        out << patients[i][0] << " " << patients[i][1] << " "
            << patients[i][2] << " " << patients[i][3] << " " << patients[i][4] << endl;
    }
    out.close();

    cout << "\nPatient added successfully!";
    waitForKey();
}
void viewAllPatients()
{
    system("cls");
    printHeader();

    lines();
    cout << "                  --- All Patients ---\n";
    lines();

    const int FIELDS = 5;
    string patients[100][FIELDS];
    int total = 0;

    ifstream in("patients.txt");
    while (in >> patients[total][0] >> patients[total][1] >> patients[total][2] >> patients[total][3] >> patients[total][4])
        total++;
    in.close();

    cout << left << setw(15) << "Username" << setw(15) << "Full Name"
         << setw(15) << "Phone" << setw(15) << "CNIC" << "\n";
    lines();

    for (int i = 0; i < total; i++)
    {
       
        string displayName = patients[i][2];
        for (int j = 0; displayName[j] != '\0'; j++)
            if (displayName[j] == '_')
                displayName[j] = ' ';

        cout << left << setw(15) << patients[i][0]  // Username
             << setw(15) << displayName             // Full Name
             << setw(15) << patients[i][3]          // Phone
             << setw(15) << patients[i][4] << "\n"; // CNIC
    }

    waitForKey();
}
void updatePatient()
{
    system("cls");
    printHeader();

    lines();
    cout << "                   --- Update Patient ---\n";
    lines();

    string targetUsername;
    cout << "Enter patient username to update: ";
    getline(cin, targetUsername);

    const int FIELDS = 5;
    string patients[100][FIELDS];
    int total = 0;
    bool found = false;

    ifstream in("patients.txt");
    while (in >> patients[total][0] >> patients[total][1] >> patients[total][2] >> patients[total][3] >> patients[total][4])
    {
        if (patients[total][0] == targetUsername)
            found = true;
        total++;
    }
    in.close();

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

        if (!isPhoneValid(newPhone))
        {
            cout << "Invalid phone number.\n";
        }
        else
        {
            bool exists = false;
            for (int i = 0; i < total; i++)
            {
                if (patients[i][3] == newPhone &&
                    patients[i][0] != targetUsername)
                {
                    exists = true;
                    break;
                }
            }

            if (exists)
                cout << "Phone already exists for another patient!\n";
            else
                break;
        }
    }
    while (true)
    {
        cout << "New CNIC (13 digits): ";
        getline(cin, newCNIC);

        if (!isCNICValid(newCNIC))
        {
            cout << "Invalid CNIC.\n";
        }
        else
        {
            bool exists = false;
            for (int i = 0; i < total; i++)
            {
                if (patients[i][4] == newCNIC &&
                    patients[i][0] != targetUsername)
                {
                    exists = true;
                    break;
                }
            }

            if (exists)
                cout << "CNIC already exists for another patient!\n";
            else
                break;
        }
    }


    for (int i = 0; i < total; i++)
    {
        if (patients[i][0] == targetUsername)
        {
            patients[i][2] = newName;
            patients[i][3] = newPhone;
            patients[i][4] = newCNIC;
            break;
        }
    }

    ofstream out("patients.txt");
    for (int i = 0; i < total; i++)
        out << patients[i][0] << " " << patients[i][1] << " "
            << patients[i][2] << " " << patients[i][3] << " " << patients[i][4] << endl;
    out.close();

    cout << "Patient updated successfully!";
    waitForKey();
}
void searchPatient()
{
    system("cls");
    printHeader();
    lines();
    cout << "                 --- Search Patient ---\n";
    lines();

    cout << "Search by:\n1. Username\n2. Phone\n3. CNIC\nChoice: ";
    string choice;
    getline(cin, choice);

    string searchTerm;
    if (choice == "1")
        cout << "Enter Username: ";
    else if (choice == "2")
        cout << "Enter Phone: ";
    else if (choice == "3")
        cout << "Enter CNIC: ";
    else
    {
        error();
        cout << "Invalid choice!";
        waitForKey();
        return;
    }

    getline(cin, searchTerm);

    const int FIELDS = 5;
    string patients[100][FIELDS];
    int total = 0;

    ifstream in("patients.txt");
    while (in >> patients[total][0] >> patients[total][1] >> patients[total][2] >> patients[total][3] >> patients[total][4])
        total++;
    in.close();

    bool found = false;
    for (int i = 0; i < total; i++)
    {
        string value;
        if (choice == "1")
            value = patients[i][0];
        else if (choice == "2")
            value = patients[i][3];
        else
            value = patients[i][4];

        if (value == searchTerm)
        {
            string displayName = patients[i][2];
            for (int j = 0; displayName[j] != '\0'; j++)
                if (displayName[j] == '_')
                    displayName[j] = ' ';

            lines();
            cout << left << setw(15) << "Username"
                 << setw(15) << "Full Name"
                 << setw(15) << "Phone"
                 << setw(15) << "CNIC" << "\n";
            lines();
            cout << left << setw(15) << patients[i][0]
                 << setw(15) << displayName
                 << setw(15) << patients[i][3]
                 << setw(15) << patients[i][4] << "\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nPatient not found!\n";

    waitForKey();
}
void deletePatient()
{
    system("cls");
    printHeader();

    lines();
    cout << "              --- Delete Patient ---\n";
    lines();

    string target;
    cout << "Enter patient username to delete: ";
    getline(cin, target);

    const int FIELDS = 5;
    string patients[100][FIELDS];
    int total = 0;
    bool found = false;

    ifstream in("patients.txt");
    while (in >> patients[total][0] >> patients[total][1] >> patients[total][2] >> patients[total][3] >> patients[total][4])
    {
        if (patients[total][0] == target)
            found = true;
        else
            total++;
    }
    in.close();

    if (!found)
    {

        cout << "Patient not found!";
        waitForKey();
        return;
    }

    ofstream out("patients.txt");
    for (int i = 0; i < total; i++)
        out << patients[i][0] << " " << patients[i][1] << " "
            << patients[i][2] << " " << patients[i][3] << " " << patients[i][4] << endl;
    out.close();

    cout << "Patient deleted successfully!";
    waitForKey();
}
void addDoctor()
{
    system("cls");
    printHeader();

    lines();
    cout << "                   --- Add Doctor ---\n";
    lines();

    const int FIELDS = 4;
    string doctors[100][FIELDS];
    int total = 0;

    ifstream in("doctors.txt");
    while (in >> doctors[total][0] >> doctors[total][1] >> doctors[total][2] >> doctors[total][3])
    {
        total++;
    }
    in.close();

    string doctorID, doctorName, specialization, phone;


    while (true)
    {
        cout << "Doctor ID: ";
        getline(cin, doctorID);

        if (doctorID == "")
        {
            cout << "ID cannot be empty.\n";
        }
        else
        {
            bool exists = false;
            for (int i = 0; i < total; i++)
            {
                if (doctors[i][0] == doctorID)
                {
                    exists = true;
                    break;
                }
            }

            if (exists)
                cout << "Doctor ID already exists!\n";
            else
                break;
        }
    }

   
    while (true)
    {
        cout << "Doctor Name: ";
        getline(cin, doctorName);
        if (isAlphabetic(doctorName))
            break;
        cout << "Invalid name.\n";
    }


    while (true)
    {
        cout << "Specialization: ";
        getline(cin, specialization);
        if (isAlphabetic(specialization))
            break;
        cout << "Invalid specialization.\n";
    }


    while (true)
    {
        cout << "Phone (11 digits): ";
        getline(cin, phone);

        if (!isPhoneValid(phone))
        {
            cout << "Invalid phone number.\n";
        }
        else
        {
            bool exists = false;
            for (int i = 0; i < total; i++)
            {
                if (doctors[i][3] == phone)
                {
                    exists = true;
                    break;
                }
            }

            if (exists)
                cout << "Phone number already exists!\n";
            else
                break;
        }
    }

  
    for (int i = 0; doctorName[i] != '\0'; i++)
        if (doctorName[i] == ' ')
            doctorName[i] = '_';

    for (int i = 0; specialization[i] != '\0'; i++)
        if (specialization[i] == ' ')
            specialization[i] = '_';


    ofstream out("doctors.txt", ios::app);
    out << doctorID << " " << doctorName << " "
        << specialization << " " << phone << endl;
    out.close();

    cout << "\nDoctor added successfully!";
    waitForKey();
}
void viewAllDoctors()
{
    system("cls");
    printHeader();

    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(20) << "Specialization"
         << setw(15) << "Phone" << endl;

    lines();

    ifstream in("doctors.txt");
    string id, name, spec, phone;
    while (in >> id >> name >> spec >> phone)
    {
        for (int i = 0; name[i] != '\0'; i++)
            if (name[i] == '_')
                name[i] = ' ';
        for (int i = 0; spec[i] != '\0'; i++)
            if (spec[i] == '_')
                spec[i] = ' ';

        cout << left << setw(10) << id
             << setw(20) << name
             << setw(20) << spec
             << setw(15) << phone << endl;
    }

    in.close();
    waitForKey();
}
void updateDoctor()
{
    system("cls");
    printHeader();

    lines();
    cout << "                 --- Update Doctor ---\n";
    lines();

    string targetID;
    cout << "Enter Doctor ID to update: ";
    getline(cin, targetID);

    const int FIELDS = 4;
    string doctors[100][FIELDS];
    int total = 0;
    bool found = false;

    
    ifstream in("doctors.txt");
    while (in >> doctors[total][0] >> doctors[total][1] >> doctors[total][2] >> doctors[total][3])
    {
        if (doctors[total][0] == targetID)
            found = true;
        total++;
    }
    in.close();

    if (!found)
    {
        cout << "Doctor not found!";
        waitForKey();
        return;
    }

    string newName, newSpec, newPhone;


    
    while (true)
    {
        cout << "New Name: ";
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
        cout << "New Specialization: ";
        getline(cin, newSpec);
        if (isAlphabetic(newSpec))
            break;
        cout << "Invalid specialization.\n";
    }
    for (int i = 0; newSpec[i] != '\0'; i++)
        if (newSpec[i] == ' ')
            newSpec[i] = '_';

   
    while (true)
    {
        cout << "New Phone (11 digits): ";
        getline(cin, newPhone);
        bool unique = true;
        for (int i = 0; i < total; i++)
            if (doctors[i][3] == newPhone && doctors[i][0] != targetID)
                unique = false;

        if (!isPhoneValid(newPhone))
            cout << "Invalid phone number.\n";
        else if (!unique)
            cout << "Phone number already exists!\n";
        else
            break;
    }

 
    for (int i = 0; i < total; i++)
    {
        if (doctors[i][0] == targetID)
        {
            doctors[i][1] = newName;
            doctors[i][2] = newSpec;
            doctors[i][3] = newPhone;
            break;
        }
    }


    ofstream out("doctors.txt");
    for (int i = 0; i < total; i++)
        out << doctors[i][0] << " " << doctors[i][1] << " "
            << doctors[i][2] << " " << doctors[i][3] << endl;
    out.close();

    cout << "Doctor updated successfully!";
    waitForKey();
}
void deleteDoctor()
{
    system("cls");
    printHeader();

    lines();
    cout << "                 --- Delete Doctor ---\n";
    lines();

    string targetID;
    cout << "Enter Doctor ID to delete: ";
    getline(cin, targetID);

    const int FIELDS = 4;
    string doctors[100][FIELDS];
    int total = 0;
    bool found = false;


    ifstream in("doctors.txt");
    while (in >> doctors[total][0] >> doctors[total][1] >> doctors[total][2] >> doctors[total][3])
    {
        if (doctors[total][0] == targetID)
            found = true;
        else
            total++;
    }
    in.close();

    if (!found)
    {
        cout << "Doctor not found!";
        waitForKey();
        return;
    }


    ofstream out("doctors.txt");
    for (int i = 0; i < total; i++)
        out << doctors[i][0] << " " << doctors[i][1] << " "
            << doctors[i][2] << " " << doctors[i][3] << endl;
    out.close();

    cout << "Doctor deleted successfully!";
    waitForKey();
}
int stringToInt(const string &s)
{
    int num = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        num = num * 10 + (s[i] - '0');
    }
    return num;
}

void generateBill()
{
    system("cls");
    printHeader();
    lines();
cout <<"                          GENERATE BILL\n";
lines();

    string input;
    int numMedicines = 0;

    while (true)
    {
        cout << "Enter number of medicines: ";
        getline(cin, input);
        if (isNumeric(input))
        {
            numMedicines = stringToInt(input);
            break;
        }
        cout << "Invalid input! Enter a number.\n";
    }

    int total = 0;
    for (int i = 0; i < numMedicines; i++)
    {
        int price = 0, qty = 0;

        while (true)
        {
            cout << "Enter price of medicine " << (i + 1) << ": ";
            getline(cin, input);
            if (isNumeric(input))
            {
                price = stringToInt(input);
                break;
            }
            cout << "Invalid input! Enter a number.\n";
        }

        while (true)
        {
            cout << "Enter quantity of medicine " << (i + 1) << ": ";
            getline(cin, input);
            if (isNumeric(input))
            {
                qty = stringToInt(input);
                break;
            }
            cout << "Invalid input! Enter a number.\n";
        }

        total += price * qty;
    }

    int consultationFee = 0;
    while (true)
    {
        cout << "Enter consultation fee: ";
        getline(cin, input);
        if (isNumeric(input))
        {
            consultationFee = stringToInt(input);
            break;
        }
        cout << "Invalid input! Enter a number.\n";
    }

    total += consultationFee;

    cout << "\nTotal Bill: " << total << endl;
    waitForKey();
}
//                                                                          (STAFF  MENU)
void staffMenu()
{
    while (true)
    {
        system("cls");
        printHeader();
        lines();
        cout << "                     STAFF MENU\n";
        lines();

        cout << "1. View All Patients\n";
        cout << "2. View Doctors\n";
        cout << "3. View Medicines\n";
        cout << "4. Search Patient\n";
        cout << "5. Generate Bill\n";
        cout << "6. Logout\n";
        lines();
        cout << "Choice : ";
        string choice;
        getline(cin, choice);

        if (choice == "1")
            viewAllPatients();
        else if (choice == "2")
            viewAllDoctors();
        else if (choice == "3")
            viewAllMedicines();
        else if (choice == "4")
            searchPatient();
        else if (choice == "5")
            generateBill();
        else if (choice == "6")
            return;
        else
        {
            error();
            cout << "INVALID CHOICE";
            waitForKey();
        }
    }
}

//                                                                            (PATIENT MENU)
void patientMenu(const string &username)
{
    while (true)
    {
        system("cls");
        printHeader();
        lines();
        cout << "                    --- Patient Menu ---\n";
        lines();
        cout << "\n1. View Personal Details\n2. View Doctors\n3. Logout\n";
        lines();
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
                    string displayName = n;
                    for (int i = 0; displayName[i] != '\0'; i++)
                        if (displayName[i] == '_')
                            displayName[i] = ' ';
                    system("cls");
                    printHeader();
                    lines();
                    cout << left << setw(15) << "Full Name"
                         << setw(15) << "Phone"
                         << setw(15) << "CNIC" << "\n";
                    lines();
                    cout << left << setw(15) << displayName
                         << setw(15) << ph
                         << setw(15) << c << "\n";
                    break;
                }
            }
            in.close();
            waitForKey();
        }
        else if (choice == "2")
        {
            viewAllDoctors();
        }
        else if (choice == "3")
            return;
        else
        {
            error();
            cout << "\nINVALID CHOICE";
            waitForKey();
        }
    }
}
