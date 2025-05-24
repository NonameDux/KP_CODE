#include "EncryptedNotes.h"



using namespace std;
int RegisterUser(unsigned int LW, const string& username, const string& password, string& hashedPassword) {
    string u = username, p = password;
    int err = 99;

     err = ShowRegistrationForm(LW, u, p, hashedPassword);
    if (err == 1) {
        cout << "Введені паролі не співпадають" << endl;
        Sleep(5000);
        err = ShowRegistrationForm(LW, u, p, hashedPassword);
    }
    else if (err == 0) {
        CreateUserFolder(u, hashedPassword);
        cout << "\nРегістрація успішна, для входу в аккаунт буде використовуватися логін \"" << u << "\"";
        AUTHORIZED = true;
    }
       
    
    return 0;
}

int LoginUser(unsigned int LW,string& username, string& hashedPassword) {
    int err = ShowLoginForm(LW, username, hashedPassword);
    if (err == 2) {
        cout << "Невірний пароль, трохи зачекайте і спробуйте знову." << endl;
        Sleep(5000);
        return 2;
    }
    else if (err == 1) { system("CLS"); cout << "Користувача з таким логіном не існує." << endl; Sleep(3000); return 1; }
    else if (err == 0) { system("CLS"); cout << "\nВхід під логіном \"" << username << "\"" << endl; }
    return 0;
}
