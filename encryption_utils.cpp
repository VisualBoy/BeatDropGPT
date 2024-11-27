#include <windows.h>
#include <wincrypt.h>
#include <string>
#include <vector>

class EncryptionUtils {
public:
    static std::string Encrypt(const std::string& plaintext) {
        DATA_BLOB DataIn;
        DATA_BLOB DataOut;
        DATA_BLOB DataEntropy;
        std::string entropy = "SomeEntropy"; // Use a secure entropy value
        DataEntropy.pbData = (BYTE*)entropy.data();
        DataEntropy.cbData = entropy.size();

        DataIn.pbData = (BYTE*)plaintext.data();
        DataIn.cbData = plaintext.size();

        if (CryptProtectData(&DataIn, NULL, &DataEntropy, NULL, NULL, 0, &DataOut)) {
            std::string encrypted((char*)DataOut.pbData, DataOut.cbData);
            LocalFree(DataOut.pbData);
            return encrypted;
        }
        return "";
    }

    static std::string Decrypt(const std::string& encrypted) {
        DATA_BLOB DataIn;
        DATA_BLOB DataOut;
        DATA_BLOB DataEntropy;
        std::string entropy = "SomeEntropy"; // Use the same entropy value
        DataEntropy.pbData = (BYTE*)entropy.data();
        DataEntropy.cbData = entropy.size();

        DataIn.pbData = (BYTE*)encrypted.data();
        DataIn.cbData = encrypted.size();

        if (CryptUnprotectData(&DataIn, NULL, &DataEntropy, NULL, NULL, 0, &DataOut)) {
            std::string decrypted((char*)DataOut.pbData, DataOut.cbData);
            LocalFree(DataOut.pbData);
            return decrypted;
        }
        return "";
    }
};
