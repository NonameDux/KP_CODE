#include "EncryptedNotes.h"

bool CheckUsersFolder(){

    fs::path folder = "./users";
    if (std::filesystem::exists(folder)) {
        return true;
    }
    else {
        fs::create_directories(folder);
    }

    return true;
}


bool CreateUserFolder(string login, string hashedPassword) {
    fs::path folder = "./users/" + login;
    fs::create_directories(folder); // создаёт директорию, если не существует
    fs::path filePath = folder / "Auth.txt";

    ofstream fout(filePath);
    fout << sha256(hashedPassword);//Зберігаємо хєш від хєшу паролю у файлі автентифікації щоб порівнювати його при вході у аккаунт
    fout.close();
return true;
}
bool SearchFS(string FileName, bool IsFile) {
    fs::path folder = "./users/" + FileName;
    fs::path File = FileName + ".txt";
    fs::path filePath = folder / File;
    if (IsFile == true) {
        if (std::filesystem::exists(filePath)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if (std::filesystem::exists(folder)) {
            return true;
        }
        else {
            return false;
        }
    }
    return true;
}
string ReadFile(string login, string FileName) {
    fs::path folder = "./users/" + login;
    fs::path File = FileName + ".txt";
    fs::path filePath = folder / File;
    string DATA;
    ifstream infile(filePath);
    infile >> DATA;//Зберігаємо хєш від хєшу паролю у файлі автентифікації щоб порівнювати його при вході у аккаунт
    infile.close();
return DATA;
}
vector<string> ShowAllFiles(string login) {
    fs::path folder = "./users/" + login ;
    size_t i = 1;
    vector<string> filenames;
    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.path().extension() == ".txt") {            
            filenames.push_back(entry.path().stem().string());
        }
    }
return filenames;
}
vector<string> InputFile(string login, string FileName) {
    fs::path folder = "./users/" + login;
    fs::path File = FileName + ".txt";
    fs::path filePath = folder / File;
    ifstream infile(filePath);
    string line;
    vector<string> lines;

    while (getline(infile, line)) {
        lines.push_back(line);
    }

    return lines;
}
bool WriteFile(string login, string FileName, string Data) {
    fs::path folder = "./users/" + login;
    fs::path File = FileName + ".txt";
    fs::path filePath = folder / File;
    ofstream fout(filePath, ios::app);
    fout << Data;//Зберігаємо хєш від хєшу паролю у файлі автентифікації щоб порівнювати його при вході у аккаунт
    fout.close();
    return true;
}