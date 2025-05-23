#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <iomanip>
#include <io.h>
#include <string>
#include <cryptlib.h>
#include <sha.h>
#include <hex.h>
#include <filters.h>
#include <gcm.h>
#include <aes.h>
#include <secblock.h>
#include <base64.h>
#include <osrng.h>

/*============================================
|				 ŒÕ—“¿Õ“»					 |
============================================*/

const unsigned int LOGIN_MAX_LENGTH = 20,
					PASSWORD_MAX_LENGTH = 20,
					NOTE_TITLE_MAX_LENGTH = 40,
					NOTE_BODY_MAX_LENGTH = 3000;

using namespace std;
namespace fs = filesystem;
//Interface
void ShowHeader(unsigned int LW = 40, string text = "NULL");
int ShowStartMenu(unsigned int LW= 40);
int ShowMainMenu(unsigned int LW);
int ShowRegistrationForm(unsigned int, string& , string& );
int ShowLoginForm(unsigned int, string&);
int ShowNotesList(unsigned int LW, string& LOGIN);
int ShowCreateNoteForm(unsigned int LW, string& LOGIN);
int ShowNote(unsigned int LW, string FileName, string LOGIN);
//AuthSystem
int RegisterUser(unsigned int,const string& username, const string& password);
int LoginUser(unsigned int,string& username);
//EncriptionModule	
string sha256(const string& data);
string AES256GCM_Encrypt(const string hash, const CryptoPP::SecByteBlock& nonce, const string& plaintext);
string AES256GCM_Decrypt(const CryptoPP::SecByteBlock& key, CryptoPP::SecByteBlock& nonce, const string& ciphertext);
string ToBase64(const string& binary);
string FromBase64(const string& encoded);
bool EncryptAndSaveTXT(string hashedPassword, vector<string> Data, string login, string FileName);
//Filemanager
bool CreateUserFolder(string login, string hashedPassword);
bool SearchFS(string FileName, bool IsFile);
string ReadFile(string login, string FileName);
bool WriteFile(string login, string FileName, string Data);
vector<string> ShowAllFiles(string login);
vector<string> InputFile(string login,string filename);
