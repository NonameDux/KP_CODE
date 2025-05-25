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
	size_t LenToCenter = (LW + size(text)) / 4;
	cout << setw(LW) << setfill('=') << "=" << endl;
	cout << string(LenToCenter, ' ') << text << endl;
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
	if (cin.fail()) {
		cin.clear(); // ���������� ���� ������
		cin.ignore(10000, '\n'); // ������� ����
		cout << "[ERROR]���������� ��������! ��������� �� ���.\n";
		Sleep(1000);
	}
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
	if (cin.fail()) {
		cin.clear(); // ���������� ���� ������
		cin.ignore(10000, '\n'); // ������� ����
		cout << "[ERROR]���������� ��������! ��������� �� ���.\n";
		Sleep(1000);
	}
	return answer;
}
int ShowRegistrationForm(unsigned int LW, string& LOGIN,string& PASSWORD,string& hashedPassword) {
	system("CLS");

	string text = "����������", pass1,pass2;
	int answer = 0, LenghtWidthMedium = LW - 20;

	ShowHeader(LW, text);

	cout << left << setw(LenghtWidthMedium) << "������ ����" << ":";
	cin >> LOGIN;
	if (LOGIN.size() >= LOGIN_MAX_LENGTH) { cout << "������� ������ ����!"; Sleep(2000); return 2; }
	if (SearchFS(LOGIN, false)) { cout <<"���������� � ����� ��'�� ��� ����!"; Sleep(2000); return 2; }
	cout << left << setw(LenghtWidthMedium) << "������ ������" << ":";
	cin >> pass1;
	cout << left << setw(LenghtWidthMedium) << "������ ������ �� ���" << ":";
	cin >> pass2;

	if (pass1 == pass2) { PASSWORD = pass1;}
	else { return 1; }
	hashedPassword = sha256(PASSWORD);
	return 0;
}
int ShowLoginForm(unsigned int LW, string& LOGIN, string& hashedPassword) {
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

	hashedPassword = sha256(PASSWORD);
	return 0;
}
int ShowNotesList(unsigned int LW, string& LOGIN, string& hashedPassword) {
	system("CLS");
	string text = "���� �������", answer = "SEE";
	vector<string> files = ShowAllFiles(LOGIN);
	unsigned int LenghtWidthMedium = LW - 20, ChosedNote = 0, err = 0;
	ShowHeader(LW, text);
	for (size_t i = 0; i <= files.size()-1; i++) { cout << i + 1 << ":" << files[i] << endl; }
	cout << setw(LW) << setfill('=') << "=" << setfill(' ') << endl;
	cout << left << setw(LenghtWidthMedium) << "������� ��(SEE,ADD)" << ":";
	cin >> answer;

	if (answer == "SEE" or answer == "see" or answer == "See" or answer == "sEE")	{
		cout << left << setw(LenghtWidthMedium) << "������ ����� ������� ��� ������� �����������" << ":";
		cin >> ChosedNote;
		err = ShowNote(LW,files[ChosedNote-1],LOGIN, hashedPassword);
	}

	else if (answer == "ADD" or answer == "add" or answer == "Add" or answer == "aDD") {
		ShowCreateNoteForm(LW, LOGIN, hashedPassword);
	}
	else { cout << "������ ������� ������ �� ����!" << endl; Sleep(1000); return 1; }

	return err;
}
int ShowCreateNoteForm(unsigned int LW, string& LOGIN,string hashedPassword) {
	system("CLS");
	string text = "��������� �������", DATA = " ",NoteName = "NoteName";
	unsigned int LenghtWidthMedium = LW;
	ShowHeader(LW + 20, text);
	cout << left << setw(LenghtWidthMedium) << "������ ����� �������(��� ��������!)" << ":";
	cin >> NoteName;
	cout << left << setw(LenghtWidthMedium) << "������ ����� �������(��� ����� ������ �������� CTRL + Z)" << ":";
	string all;
	char ch;
	while (cin.get(ch)) {
		all += ch;		
	}
	if (cin.eof()) {
		cout << "\n[INFO] ������� �������� (Ctrl + Z).\n";
	}
	else {
		cerr << "[ERROR] ������� ��� ������ �����.\n";
		return 1;
	}
	cout << "\n�� �����:\n" << all << endl;
	EncryptAndSaveTXT(hashedPassword, all, LOGIN, NoteName);
	// ��������� ������������...
	cout << "[OK]" << endl;
	return true;
}
int ShowNote(unsigned int LW, string FileName, string LOGIN,string Password) {
	system("CLS");
	string text = "������� \""+FileName+"\"", answer;
	unsigned int LenghtWidthMedium = LW - 20;
	vector<string> lines = InputFile(LOGIN, FileName);
	ShowHeader(LW, text);
	for (size_t i = 0; i <= lines.size() - 1; i++) { 
		
		cout << left << setw(LW) << DecryptNote(lines[i],Password) << endl;
	}
	cout << setw(LW) << setfill('=') << "=" << setfill(' ') << endl;
	cout << left << setw(LenghtWidthMedium) << "������� ��(EXIT,DEL)" << ":";
	cin >> answer;
	if (answer == "BACK" or answer == "back" or answer == "Back" or answer == "bACK") {
		cout << left << setw(LenghtWidthMedium) << "������ ����� ������� ��� ������� �����������" << ":";
	}

	else if (answer == "DEL" or answer == "del" or answer == "dEL" or answer == "Del") {
		cout << "�� �������? �� �� �������� �� �������!(�/�):";
		cin >> answer;
		if (answer == "�") { cout << "������� ���� ��������"; }
		else { return 0; }
	}
	else { cout << "������ ������� ������ �� ����!" << endl; Sleep(1000); return 1; }
	return 0;
}