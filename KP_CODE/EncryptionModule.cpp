#include "EncryptedNotes.h"
using namespace CryptoPP;
string DeriveAESKeyFromPassword(const string& password) {
    string digest;

    SHA256 hash;
    StringSource s(password, true,new HashFilter(hash,new HexEncoder(new StringSink(digest), false)));
	return digest;
}