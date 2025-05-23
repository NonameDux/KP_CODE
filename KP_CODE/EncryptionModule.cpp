#include "EncryptedNotes.h"
using namespace CryptoPP;

AutoSeededRandomPool prn;
CryptoPP::SecByteBlock nonce(12);
prn.GenerateBlock(nonce, nonce.size());


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
bool EncryptAndSaveTXT(string hashedPassword, vector<string> Data,string login,string FileName) {
    for (size_t i = 0; i <= Data.size() - 1; i++) {
        WriteFile(login, FileName, AES256GCM_Encrypt(hashedPassword, nonce, Data[i]));

    }
    

}