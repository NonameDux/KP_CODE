#include "EncryptedNotes.h"



using namespace std;

int RegisterUser(unsigned int LW,const string& username, const string& password) {
    string u = username, p = password;
    int err = ShowRegistrationForm(LW,u,p);
    string hashedPassword = DeriveAESKeyFromPassword(p);
    if (err == 1) {
        cout << "������ ����� �� ����������" << endl;
        Sleep(5000);
        err = ShowRegistrationForm(LW, u, p);
    }
    else if (err == 0) { CreateUserFolder(u, hashedPassword); cout << "\n���������� ������, ��� ����� � ������� ���� ����������������� ���� \"" << u << "\"" << endl; }
    return 0;
}

int LoginUser(unsigned int LW, const string& username, const string& password) {
    string u = username, p = password;
    int err = ShowLoginForm(LW, u, p);
    if (err == 2) {
        cout << "������� ������, ����� ��������� � ��������� �����." << endl;
        Sleep(5000);
        err = ShowLoginForm(LW, u, p);
    }
    else if (err == 1) { cout << "����������� � ����� ������ �� ����." << endl; }
    else if (err == 0) { system("CLS"); cout << "\n���� �� ������ \"" << u << "\"" << endl; }
    return 0;
}
