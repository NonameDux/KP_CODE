#include "EncryptedNotes.h"



using namespace std;
int RegisterUser(unsigned int LW, const string& username, const string& password, string& hashedPassword) {
    string u = username, p = password;
    int err = 99;

     err = ShowRegistrationForm(LW, u, p, hashedPassword);
    if (err == 1) {
        cout << "������ ����� �� ����������" << endl;
        Sleep(5000);
        err = ShowRegistrationForm(LW, u, p, hashedPassword);
    }
    else if (err == 0) {
        CreateUserFolder(u, hashedPassword);
        cout << "\n���������� ������, ��� ����� � ������� ���� ����������������� ���� \"" << u << "\"";
        AUTHORIZED = true;
    }
       
    
    return 0;
}

int LoginUser(unsigned int LW,string& username, string& hashedPassword) {
    int err = ShowLoginForm(LW, username, hashedPassword);
    if (err == 2) {
        cout << "������� ������, ����� ��������� � ��������� �����." << endl;
        Sleep(5000);
        return 2;
    }
    else if (err == 1) { system("CLS"); cout << "����������� � ����� ������ �� ����." << endl; Sleep(3000); return 1; }
    else if (err == 0) { system("CLS"); cout << "\n���� �� ������ \"" << username << "\"" << endl; }
    return 0;
}
