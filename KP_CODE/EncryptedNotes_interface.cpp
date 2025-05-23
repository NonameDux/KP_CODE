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

	string text = "���� � �������";
	int answer = 0;

	ShowHeader(LW, text);

	cout << left <<setw(LW) << "\t1 - ����" << endl;
	cout << left << setw(LW) << "\t2 - ���������" << endl;
	cout << left << setw(LW) << "\t3 - �����" << endl;
	cout << left << "������ �����:";
	cin >> answer;

	return answer;
}
int ShowMainMenu(unsigned int LW) {
	system("CLS");

	string text = "������� ����";
	int answer = 0;

	ShowHeader(LW, text);

	cout << left <<setw(LW) << "\t1 - ����������� ��� �������" << endl;
	cout << left << setw(LW) << "\t2 - �������� ���� �������" << endl;
	cout << left << setw(LW) << "\t3 - �����" << endl;
	cout << left << "������ �����:";
	cin >> answer;
	if (answer >= 1 and answer <= 3) { return answer; }
	else { system("CLS"); cout << "������ ������� ������ �� ����!"; Sleep(3000); return answer; }
}
int ShowRegistrationForm(unsigned int LW, string& LOGIN,string& PASSWORD) {
	system("CLS");

	string text = "����������", pass1,pass2;
	int answer = 0, LenghtWidthMedium = LW - 20;

	ShowHeader(LW, text);

	cout << left << setw(LenghtWidthMedium) << "������ ����" << ":";
	cin >> LOGIN;
	cout << left << setw(LenghtWidthMedium) << "������ ������" << ":";
	cin >> pass1;
	cout << left << setw(LenghtWidthMedium) << "������ ������ �� ���" << ":";
	cin >> pass2;

	if (pass1 == pass2) { PASSWORD = pass1;}
	else { return 1; }

	return 0;
}
int ShowLoginForm(unsigned int LW, string& LOGIN) {
	system("CLS");
	string text = "���� � �������", PASSWORD;
	int answer = 0, LenghtWidthMedium = LW - 20;
	ShowHeader(LW, text);

	cout << left << setw(LenghtWidthMedium) << "������ ����" << ":";
	cin >> LOGIN;
	if (!SearchFS(LOGIN, false)) { return 1; }

	cout << left << setw(LenghtWidthMedium) << "������ ������" << ":";
	cin >> PASSWORD;
	if (sha256(sha256(PASSWORD)) != ReadFile(LOGIN, "Auth")) { return 2; }

	
	return 0;
}
int ShowNotesList(unsigned int LW, string& LOGIN) {
	system("CLS");
	string text = "���� �������", answer = "SEE";
	vector<string> files = ShowAllFiles(LOGIN);
	unsigned int LenghtWidthMedium = LW - 20, ChosedNote = 0;
	ShowHeader(LW, text);
	for (size_t i = 0; i <= files.size()-1; i++) { cout << i + 1 << ":" << files[i] << endl; }
	cout << setw(LW) << setfill('=') << "=" << setfill(' ') << endl;
	cout << left << setw(LenghtWidthMedium) << "������� ��(SEE,ADD)" << ":";
	cin >> answer;

	if (answer == "SEE" or answer == "see" or answer == "See" or answer == "sEE")	{
		cout << left << setw(LenghtWidthMedium) << "������ ����� ������� ��� ������� �����������" << ":";
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
	string text = "��������� �������", DATA = "",NoteName = "NoteName";
	unsigned int LenghtWidthMedium = LW;
	ShowHeader(LW + 20, text);
	cout << left << setw(LenghtWidthMedium) << "������ ����� �������" << ":";
	cin >> NoteName;
	cout << left << setw(LenghtWidthMedium) << "������ ����� �������(��� ����� ������ -1)" << ":";
	while (DATA != "-1") { cin >> DATA; WriteFile(LOGIN, NoteName, DATA); }
	return true;
}
int ShowNote(unsigned int LW, string FileName, string LOGIN) {
	system("CLS");
	string text = "������� \""+FileName+"\"", answer;
	unsigned int LenghtWidthMedium = LW - 20;
	vector<string> lines = InputFile(LOGIN, FileName);
	ShowHeader(LW, text);
	for (size_t i = 0; i <= lines.size() -1; i++) { cout << left << setw(LW) << lines[i] << endl; }
	cout << setw(LW) << setfill('=') << "=" << setfill(' ') << endl;
	cout << left << setw(LenghtWidthMedium) << "������� ��(EXIT,DEL)" << ":";
	cin >> answer;
	return 0;
}