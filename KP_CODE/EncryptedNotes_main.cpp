#include "EncryptedNotes.h"


int LineWidthFull = 50;
void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string LOGIN = "User";
	string PASSWORD = "Password";
	int ERRORS = 0;
	switch (ShowStartMenu(LineWidthFull)) {
	case 1:
		ERRORS = LoginUser(LineWidthFull,LOGIN, PASSWORD);
		break;
	case 2:
		ERRORS = RegisterUser(LineWidthFull,LOGIN, PASSWORD);
		break;
	case 3:
		cout << "EXIT" << endl;
		break;
	}

}