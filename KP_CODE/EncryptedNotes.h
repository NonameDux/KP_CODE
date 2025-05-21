#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <io.h>
#include <cryptlib.h>
#include "sha.h"
#include "hex.h"
#include "files.h"


using namespace std;

//Interface
void ShowHeader(unsigned int LW = 40, string text = "NULL");
int ShowStartMenu(unsigned int LW= 40);
int ShowMainMenu(unsigned int LW);
int ShowRegistrationForm(unsigned int, string& , string& );
int ShowLoginForm(unsigned int, string& , string& );
//AuthSystem
int RegisterUser(unsigned int,const string& username, const string& password);
int LoginUser(unsigned int, const string& username, const string& password);
//EncriptionModule
string DeriveAESKeyFromPassword(const string& password);
//Filemanager
bool CreateUserFolder(string login, string hashedPassword);

