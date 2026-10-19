# Encrypted Notes / Зашифрованные заметки

🌍 *[Русская версия ниже](#русская-версия)*

> **Disclaimer:** This project is a college term paper (coursework). The entire C++ application was coded manually by the author. Artificial Intelligence (AI) was **only** used to generate this `README.md` file and to assist with the integration and syntax of the `Crypto++` encryption library. 

## 📝 About the Project
**Encrypted Notes** is a secure, offline console application written in C++ that allows users to store confidential text information (such as personal notes, passwords, and business ideas). The app ensures privacy by utilizing modern symmetric encryption algorithms, saving all data locally without any internet connection or third-party cloud servers.

## ✨ Features
*   **Local User Management:** Secure registration and authorization system.
*   **End-to-End Local Encryption:** Passwords are never stored in plain text.
*   **Note Management:** Create, view, and safely delete encrypted notes.
*   **Completely Offline:** No external servers, APIs, or internet connection required.

## 🔒 Security & Cryptography
*   **AES-256-GCM:** Notes are encrypted using the Advanced Encryption Standard (256-bit key) in Galois/Counter Mode, ensuring both data confidentiality and authenticity.
*   **SHA-256:** Passwords are hashed using the Secure Hash Algorithm to generate the 256-bit AES encryption key. 
*   **Base64 Encoding:** Encrypted binary data (Nonce + Authentication Tag + Ciphertext) is encoded into Base64 for safe storage in standard `.txt` files.

## 🛠 Technologies Used
*   **Language:** C++ (C++17 standard)
*   **IDE:** Microsoft Visual Studio
*   **Cryptography Library:** [Crypto++ (v8.9.0)](https://www.cryptopp.com/)
*   **Architecture:** Structured, modular design (`AuthSystem`, `EncryptionModule`, `FileManager`, `Interface`).

## 🚀 How to Build and Run
1. Clone the repository.
2. Download and compile the **Crypto++** library (v8.9.0) for your system architecture (x64/x86 Release).
3. Open the `.sln` file in Visual Studio.
4. Go to Project Properties -> C/C++ -> General -> **Additional Include Directories** and add the path to the Crypto++ folder.
5. Go to Linker -> General -> **Additional Library Directories** and add the path to the compiled Crypto++ output folder.
6. Go to Linker -> Input -> **Additional Dependencies** and add `cryptlib.lib`.
7. Go to C/C++ -> Code Generation -> **Runtime Library** and set it to `Multi-threaded (/MT)`.
8. Build the project in Release mode and run the `.exe`.

---

# <a name="русская-версия"></a> Зашифрованные заметки

> **Примечание:** Данный проект является курсовой работой для колледжа. Код программы был написан вручную. Искусственный интеллект (ИИ) использовался **исключительно** для создания этого файла `README.md` и для помощи в работе с библиотекой шифрования `Crypto++`. 

## 📝 О проекте
**Зашифрованные заметки** — это безопасное автономное консольное приложение на C++, предназначенное для хранения конфиденциальной текстовой информации (личных записей, паролей, бизнес-идей и т.д.). Приложение обеспечивает конфиденциальность за счет использования современных методов симметричного шифрования. Все данные хранятся локально и не требуют подключения к интернету или сторонним серверам.

## ✨ Функционал
*   **Локальное управление пользователями:** Безопасная система регистрации и авторизации.
*   **Надежное шифрование:** Пароли никогда не хранятся в открытом виде.
*   **Управление заметками:** Создание, просмотр и безопасное удаление зашифрованных заметок.
*   **Полная автономность:** Для работы не требуются внешние серверы, API или доступ в интернет.

## 🔒 Безопасность и криптография
*   **AES-256-GCM:** Текст заметок шифруется с помощью Advanced Encryption Standard (ключ 256 бит) в режиме Galois/Counter Mode, что гарантирует не только конфиденциальность, но и целостность (аутентичность) данных.
*   **SHA-256:** Пароли пользователей хешируются с помощью SHA-256, и этот хеш используется в качестве ключа шифрования AES.
*   **Base64:** Зашифрованные бинарные данные (Nonce + Тег аутентичности + Шифротекст) кодируются в формат Base64 для удобного хранения в обычных `.txt` файлах.

## 🛠 Используемые технологии
*   **Язык:** C++ (стандарт C++17)
*   **Среда разработки (IDE):** Microsoft Visual Studio
*   **Криптографическая библиотека:** [Crypto++ (v8.9.0)](https://www.cryptopp.com/)
*   **Архитектура:** Модульная структура (`AuthSystem`, `EncryptionModule`, `FileManager`, `Interface`).

## 🚀 Как запустить (Сборка)
1. Склонируйте репозиторий.
2. Скачайте и скомпилируйте библиотеку **Crypto++** (v8.9.0) под архитектуру вашей системы (Release x64/x86).
3. Откройте файл решения `.sln` в Visual Studio.
4. В свойствах проекта перейдите в C/C++ -> General -> **Additional Include Directories** и укажите путь к папке с исходниками Crypto++.
5. В разделе Linker -> General -> **Additional Library Directories** укажите путь к папке со скомпилированной библиотекой.
6. В разделе Linker -> Input -> **Additional Dependencies** добавьте `cryptlib.lib`.
7. В разделе C/C++ -> Code Generation -> **Runtime Library** установите значение `Multi-threaded (/MT)`.
8. Соберите проект в конфигурации Release и запустите полученный `.exe` файл.
```eof
