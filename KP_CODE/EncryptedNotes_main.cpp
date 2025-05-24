#include "EncryptedNotes.h"


int LineWidthFull = 50;
void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string LOGIN;
	string PASSWORD;
	string hashedPassword;
	int ERRORS = 1;
    while (ERRORS != 0) {
        switch (ShowStartMenu(LineWidthFull)) { //Стартове меню
        case 1:
            ERRORS = LoginUser(LineWidthFull, LOGIN, hashedPassword);
            break;
        case 2:
            ERRORS = RegisterUser(LineWidthFull, LOGIN, PASSWORD, hashedPassword);
            break;
        case 3:
            ERRORS = 0;
            exit(0);
            break;

        }
        
    }
    ERRORS = 1;
    while (ERRORS != 0) {
        switch (ShowMainMenu(LineWidthFull)) { //Стартове меню
        case 1:
            ERRORS = ShowNotesList(LineWidthFull, LOGIN,hashedPassword);
            break;
        case 2:
            ERRORS = 1;
            ShowCreateNoteForm(LineWidthFull, LOGIN, hashedPassword);
            break;
        case 3:
            ERRORS = 0;
            exit(0);
            break;
        default: ERRORS = 1;
        }
    }    
}
