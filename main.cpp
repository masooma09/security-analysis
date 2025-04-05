#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sqlite3.h>

using namespace std;

const char* USERNAME = "admin";
const char* PASSWORD = "1234";

bool login(const char* user, const char* pass) {
    if (strcmp(user, USERNAME) == 0 && strcmp(pass, PASSWORD) == 0) {
        return true;
    }
    return false;
}

void executeQuery(sqlite3* db, const char* userInput) {
    char sql[256];
    sprintf(sql, "SELECT * FROM users WHERE name='%s'", userInput); // SQL Injection risk
    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
    
    if (rc != SQLITE_OK) {
        cout << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Query executed successfully" << endl;
    }
}

void processInput() {
    char buffer[10];
    cout << "Enter input: ";
    cin >> buffer; // No boundary check, leads to buffer overflow
    cout << "You entered: " << buffer << endl;
}

int main() {
    sqlite3* db;
    sqlite3_open("test.db", &db);

    char username[50], password[50];
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (login(username, password)) {
        cout << "Login successful!" << endl;
    } else {
        cout << "Login failed!" << endl;
    }

    char userInput[100];
    cout << "Enter a name to search: ";
    cin >> userInput;
    executeQuery(db, userInput);

    processInput();

    sqlite3_close(db);
    return 0;
}
