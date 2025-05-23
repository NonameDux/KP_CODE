#include "EncryptedNotes.h"


int LineWidthFull = 50;
void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string LOGIN;
	string PASSWORD;
	int ERRORS = 1;
    while (ERRORS != 0) {
        switch (ShowStartMenu(LineWidthFull)) { //Стартове меню
        case 1:
            ERRORS = LoginUser(LineWidthFull, LOGIN);
            break;
        case 2:
            ERRORS = RegisterUser(LineWidthFull, LOGIN, PASSWORD);
            break;
        case 3:
            ERRORS = 0;
            cout << "EXIT" << endl;
            break;
        }
    }
    ERRORS = 1;
    while (ERRORS != 0) {
        switch (ShowMainMenu(LineWidthFull)) { //Стартове меню
        case 1:
            ERRORS = ShowNotesList(LineWidthFull, LOGIN);
            break;
        case 2:
            ERRORS = ShowCreateNoteForm(LineWidthFull, LOGIN);
            break;
        case 3:
            ERRORS = 0;
            cout << "EXIT" << endl;
            break;
        default: ERRORS = 1;
        }
    }    
}
