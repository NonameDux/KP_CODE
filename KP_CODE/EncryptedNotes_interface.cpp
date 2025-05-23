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
	system("CLS");

	string text = "Вхід у систему";
	int answer = 0;

	ShowHeader(LW, text);

	cout << left <<setw(LW) << "\t1 - Вхід" << endl;
	cout << left << setw(LW) << "\t2 - Реєстрація" << endl;
	cout << left << setw(LW) << "\t3 - Вихід" << endl;
	cout << left << "Оберіть опцію:";
	cin >> answer;

	return answer;
}
int ShowMainMenu(unsigned int LW) {
	system("CLS");

	string text = "Головне меню";
	int answer = 0;

	ShowHeader(LW, text);

	cout << left <<setw(LW) << "\t1 - Переглянути свої нотатки" << endl;
	cout << left << setw(LW) << "\t2 - Створити нову нотатку" << endl;
	cout << left << setw(LW) << "\t3 - Вихід" << endl;
	cout << left << "Оберіть опцію:";
	cin >> answer;
	if (answer >= 1 and answer <= 3) { return answer; }
	else { system("CLS"); cout << "Такого варіанту відповіді не існує!"; Sleep(3000); return answer; }
}
int ShowRegistrationForm(unsigned int LW, string& LOGIN,string& PASSWORD) {
	system("CLS");

	string text = "Регістрація", pass1,pass2;
	int answer = 0, LenghtWidthMedium = LW - 20;

	ShowHeader(LW, text);

	cout << left << setw(LenghtWidthMedium) << "Введіть логін" << ":";
	cin >> LOGIN;
	cout << left << setw(LenghtWidthMedium) << "Введіть пароль" << ":";
	cin >> pass1;
	cout << left << setw(LenghtWidthMedium) << "Введіть пароль ще раз" << ":";
	cin >> pass2;

	if (pass1 == pass2) { PASSWORD = pass1;}
	else { return 1; }

	return 0;
}
int ShowLoginForm(unsigned int LW, string& LOGIN) {
	system("CLS");
	string text = "Вхід у аккаунт", PASSWORD;
	int answer = 0, LenghtWidthMedium = LW - 20;
	ShowHeader(LW, text);

	cout << left << setw(LenghtWidthMedium) << "Введіть логін" << ":";
	cin >> LOGIN;
	if (!SearchFS(LOGIN, false)) { return 1; }

	cout << left << setw(LenghtWidthMedium) << "Введіть пароль" << ":";
	cin >> PASSWORD;
	if (sha256(sha256(PASSWORD)) != ReadFile(LOGIN, "Auth")) { return 2; }

	
	return 0;
}
int ShowNotesList(unsigned int LW, string& LOGIN) {
	system("CLS");
	string text = "Ваші нотатки", answer = "SEE";
	vector<string> files = ShowAllFiles(LOGIN);
	unsigned int LenghtWidthMedium = LW - 20, ChosedNote = 0;
	ShowHeader(LW, text);
	for (size_t i = 0; i <= files.size()-1; i++) { cout << i + 1 << ":" << files[i] << endl; }
	cout << setw(LW) << setfill('=') << "=" << setfill(' ') << endl;
	cout << left << setw(LenghtWidthMedium) << "Виберіть дію(SEE,ADD)" << ":";
	cin >> answer;

	if (answer == "SEE" or answer == "see" or answer == "See" or answer == "sEE")	{
		cout << left << setw(LenghtWidthMedium) << "Введіть номер нотатки яку бажаете переглянути" << ":";
		cin >> ChosedNote;
		cout << ShowNote(LW,files[ChosedNote-1],LOGIN);
	}

	else if (answer == "ADD" or answer == "add" or answer == "Add" or answer == "aDD") {
		ShowCreateNoteForm(LW, LOGIN);
	}

	return 0;
}
int ShowCreateNoteForm(unsigned int LW, string& LOGIN) {
	system("CLS");
	string text = "Створення нотатки", DATA = "",NoteName = "NoteName";
	unsigned int LenghtWidthMedium = LW;
	ShowHeader(LW + 20, text);
	cout << left << setw(LenghtWidthMedium) << "Введіть назву нотатки" << ":";
	cin >> NoteName;
	cout << left << setw(LenghtWidthMedium) << "Введіть текст нотатки(щоб вийти введіть -1)" << ":";
	while (DATA != "-1") { cin >> DATA; WriteFile(LOGIN, NoteName, DATA); }
	return true;
}
int ShowNote(unsigned int LW, string FileName, string LOGIN) {
	system("CLS");
	string text = "Нотатка \""+FileName+"\"", answer;
	unsigned int LenghtWidthMedium = LW - 20;
	vector<string> lines = InputFile(LOGIN, FileName);
	ShowHeader(LW, text);
	for (size_t i = 0; i <= lines.size() -1; i++) { cout << left << setw(LW) << lines[i] << endl; }
	cout << setw(LW) << setfill('=') << "=" << setfill(' ') << endl;
	cout << left << setw(LenghtWidthMedium) << "Виберіть дію(EXIT,DEL)" << ":";
	cin >> answer;
	return 0;
}