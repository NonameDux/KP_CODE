#include "EncryptedNotes.h"
#include <filesystem>
namespace fs = filesystem;
bool CreateUserFolder(string login,string hashedPassword) {
    fs::path folder = "./" + login;
    fs::create_directories(folder); // ������ ����������, ���� �� ����������

    fs::path filePath = folder / "Auth.txt";

    // ������ ������ ���� (���� �����):
    ofstream fout(filePath);
    fout << hashedPassword;
    fout.close();

    return true;

return true;
}