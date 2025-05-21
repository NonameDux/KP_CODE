#include "EncryptedNotes.h"

//ShowStartMenu
//ShowMainMenu
//ShowRegistrationForm
//ShowLoginForm
//ShowCreateNoteForm
//ShowNotesList
//ShowNoteContent
//ShowError
void ShowHeader(unsigned int LW, string text)
{
	size_t LenToCenter = (LW + size(text)) / 2;
	cout << setw(LW) << setfill('=') << "=" << endl;
	cout << setw(LenToCenter) << setfill(' ') << text << endl;
	cout << setw(LW) << setfill('=') << "=" << setfill(' ') << endl;
}
int ShowStartMenu(unsigned int LW) {
	string text = "¬х≥д у систему";
	int answer = 0;
	ShowHeader(LW, text);
	cout << left <<setw(LW) << "\t1 - ¬х≥д" << endl;
	cout << left << setw(LW) << "\t2 - –еЇстрац≥€" << endl;
	cout << left << setw(LW) << "\t3 - ¬их≥д" << endl;
	cout << left << "ќбер≥ть опц≥ю:";
	cin >> answer;
	return answer;
}
int ShowMainMenu(unsigned int LW) {
	string text = "√оловне меню";
	int answer = 0;
	ShowHeader(LW, text);
	cout << left <<setw(LW) << "\t1 - ѕерегл€нути своњ нотатки" << endl;
	cout << left << setw(LW) << "\t2 - —творити нову нотатку" << endl;
	cout << left << setw(LW) << "\t3 - ¬их≥д" << endl;
	cout << left << "ќбер≥ть опц≥ю:";
	cin >> answer;
	return answer;
}
int ShowRegistrationForm(unsigned int LW, string& LOGIN,string& PASSWORD) {
	system("CLS");
	string text = "–ег≥страц≥€", pass1,pass2;
	int answer = 0, LenghtWidthMedium = LW - 20;
	ShowHeader(LW, text);
	cout << left << setw(LenghtWidthMedium) << "¬вед≥ть лог≥н" << ":";
	cin >> LOGIN;
	cout << left << setw(LenghtWidthMedium) << "¬вед≥ть пароль" << ":";
	cin >> pass1;
	cout << left << setw(LenghtWidthMedium) << "¬вед≥ть пароль ще раз" << ":";
	cin >> pass2;
	if (pass1 == pass2) { PASSWORD = pass1;}
	else { return 1; }
	return 0;
}
int ShowLoginForm(unsigned int LW, string& LOGIN,string& PASSWORD) {
	system("CLS");
	string text = "¬х≥д у аккаунт", pass1,pass2;
	int answer = 0, LenghtWidthMedium = LW - 20;
	ShowHeader(LW, text);
	cout << left << setw(LenghtWidthMedium) << "¬вед≥ть лог≥н" << ":";
	cin >> LOGIN;
	cout << left << setw(LenghtWidthMedium) << "¬вед≥ть пароль" << ":";
	cin >> pass1;
	if (_access(LOGIN.c_str(), 0) == 0) { return 0; }
	else { return 1; }
	return 0;
}
