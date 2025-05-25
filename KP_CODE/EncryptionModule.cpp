#include "EncryptedNotes.h"
using namespace CryptoPP;

CryptoPP::SecByteBlock generateNonce() {
    std::vector<CryptoPP::byte> nonce(12);
    if (BCryptGenRandom(nullptr, nonce.data(), (ULONG)12, BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0) {
        throw std::runtime_error("BCryptGenRandom failed");
    }
    CryptoPP::SecByteBlock cppNonce(nonce.data(), nonce.size());
    return cppNonce;
}


string sha256(const std::string& data) {
    CryptoPP::SHA256 hash;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];

    hash.CalculateDigest(digest, reinterpret_cast<const CryptoPP::byte*>(data.c_str()), data.length());

    std::string output;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return output;
}
// Возвращает бинарный ключ длиной 32 байта для AES-256
string AES256GCM_Encrypt(const string hash, const CryptoPP::SecByteBlock& nonce, const string& plaintext) {
    string ciphertext;
    CryptoPP::SecByteBlock key(reinterpret_cast<const CryptoPP::byte*>(hash.data()), hash.size());

    CryptoPP::GCM< CryptoPP::AES >::Encryption encryptor;
    encryptor.SetKeyWithIV(key, key.size(), nonce, nonce.size());

    CryptoPP::AuthenticatedEncryptionFilter ef(encryptor,
        new CryptoPP::StringSink(ciphertext),
        false, 16  // тег автентичності 16 байт
    );

    ef.ChannelPut(CryptoPP::DEFAULT_CHANNEL, reinterpret_cast<const CryptoPP::byte*>(plaintext.data()), plaintext.size());
    ef.ChannelMessageEnd(CryptoPP::DEFAULT_CHANNEL);

    std::string result(reinterpret_cast<const char*>(nonce.BytePtr()), nonce.SizeInBytes());
    result += ciphertext;
    return result;
}
string AES256GCM_Decrypt(const SecByteBlock& key, SecByteBlock& nonce, const string& ciphertext) {
    string decrypted;

    GCM< CryptoPP::AES >::Decryption decryptor;
    decryptor.SetKeyWithIV(key, key.size(), nonce, nonce.size());

    AuthenticatedDecryptionFilter df(decryptor,
        new CryptoPP::StringSink(decrypted),
        CryptoPP::AuthenticatedDecryptionFilter::THROW_EXCEPTION, 16
    );

    try {
        df.ChannelPut(CryptoPP::DEFAULT_CHANNEL, reinterpret_cast<const CryptoPP::byte*>(ciphertext.data()), ciphertext.size());
        df.ChannelMessageEnd(CryptoPP::DEFAULT_CHANNEL);
    }
    catch (const CryptoPP::Exception& e) {
        throw runtime_error("Decryption failed: " + string(e.what()));
    }

    return decrypted;
}

string ToBase64(const string& binary) {
    string encoded;
    CryptoPP::StringSource s(binary, true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encoded), false));// false = без переносу рядка
    return encoded;
}
string FromBase64(const string& encoded) {
    string decoded;
    CryptoPP::StringSource s(encoded, true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(decoded)));
    return decoded;
}
CryptoPP::SecByteBlock HexToBytes(const std::string& hex) {
    std::string raw;
    CryptoPP::StringSource(hex, true,
        new CryptoPP::HexDecoder(
            new CryptoPP::StringSink(raw)
        )
    );
    return CryptoPP::SecByteBlock(reinterpret_cast<const CryptoPP::byte*>(raw.data()), raw.size());
}
bool EncryptAndSaveTXT(string hashedPassword, string Data, string login, string FileName) {
    // Преобразуем hex-строку в 32-байтный ключ
    CryptoPP::SecByteBlock key = HexToBytes(hashedPassword);

    // Генерируем nonce
    CryptoPP::SecByteBlock nonce = generateNonce();

    // Шифруем
    string encrypted = AES256GCM_Encrypt(std::string(reinterpret_cast<const char*>(key.data()), key.size()), nonce, Data);

    // Сохраняем
    WriteFile(login, FileName, ToBase64(encrypted));

    return true;
}
string DecryptNote(string data, string Password) {
    string decoded = FromBase64(data);
    SecByteBlock key = HexToBytes(Password);
    SecByteBlock nonce(reinterpret_cast<const CryptoPP::byte*>(decoded.data()), 12);  // первые 12 байт
    string ciphertext = decoded.substr(12);  // остальное: шифр + тег
    string decrypted;
    try {
        GCM<AES>::Decryption decryptor;
        decryptor.SetKeyWithIV(key, key.size(), nonce, nonce.size());

        AuthenticatedDecryptionFilter df(decryptor,
            new StringSink(decrypted),
            AuthenticatedDecryptionFilter::THROW_EXCEPTION, 16  // 16 байт GCM-тега
        );

        df.ChannelPut(DEFAULT_CHANNEL, reinterpret_cast<const CryptoPP::byte*>(ciphertext.data()), ciphertext.size());
        df.ChannelMessageEnd(DEFAULT_CHANNEL);
    }
    catch (const Exception& e) {
        cerr << "Ошибка расшифровки: " << e.what() << endl;
        return "";
    }

    return decrypted;
}


