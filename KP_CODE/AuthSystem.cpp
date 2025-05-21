#include "EncryptedNotes.h"



using namespace std;

int RegisterUser(unsigned int LW,const string& username, const string& password) {
    string u = username, p = password;
    int err = ShowRegistrationForm(LW,u,p);
    string hashedPassword = DeriveAESKeyFromPassword(p);
    if (err == 1) {
        cout << "Введені паролі не співпадають" << endl;
        Sleep(5000);
        err = ShowRegistrationForm(LW, u, p);
    }
    else if (err == 0) { CreateUserFolder(u, hashedPassword); cout << "\nРегістрація успішна, для входу в аккаунт буде використовуватися логін \"" << u << "\"" << endl; }
    return 0;
}

int LoginUser(unsigned int LW, const string& username, const string& password) {
    string u = username, p = password;
    int err = ShowLoginForm(LW, u, p);
    if (err == 2) {
        cout << "Невірний пароль, трохи зачекайте і спробуйте знову." << endl;
        Sleep(5000);
        err = ShowLoginForm(LW, u, p);
    }
    else if (err == 1) { cout << "Користувача з таким логіном не існує." << endl; }
    else if (err == 0) { system("CLS"); cout << "\nВхід під логіном \"" << u << "\"" << endl; }
    return 0;
}
