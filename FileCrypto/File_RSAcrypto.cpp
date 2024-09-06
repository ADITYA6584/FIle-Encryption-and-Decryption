#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/base64.h>
#include <cryptopp/filters.h>
#include <iostream>
#include <fstream>

using namespace CryptoPP;
using namespace std;

void GenerateRSAKeys(const string& publicKeyFile, const string& privateKeyFile) {
    AutoSeededRandomPool rng;

    // Generate private key
    RSA::PrivateKey privateKey;
    privateKey.GenerateRandomWithKeySize(rng, 2048);

    // Generate corresponding public key
    RSA::PublicKey publicKey(privateKey);

    // Save public key
    Base64Encoder pubFile(new FileSink(publicKeyFile.c_str()), false);  // Add false to prevent newline characters
    publicKey.DEREncode(pubFile);
    pubFile.MessageEnd();

    // Save private key
    Base64Encoder privFile(new FileSink(privateKeyFile.c_str()), false);  // Add false to prevent newline characters
    privateKey.DEREncode(privFile);
    privFile.MessageEnd();
}

void RSAEncryptFile(const string& publicKeyFile, const string& inFile, const string& outFile) {
    AutoSeededRandomPool rng;

    // Load public key
    string publicKeyStr;
    FileSource(publicKeyFile.c_str(), true, new StringSink(publicKeyStr));
    StringSource pubFile(publicKeyStr, true, new Base64Decoder);
    RSA::PublicKey publicKey;
    publicKey.BERDecode(pubFile);

    // Encrypt data
    RSAES_OAEP_SHA_Encryptor encryptor(publicKey);
    string cipherStr;
    FileSource(inFile.c_str(), true, 
        new PK_EncryptorFilter(rng, encryptor,
            new StringSink(cipherStr)
        ) // PK_EncryptorFilter
    );

    // Encode ciphertext in Base64 and save to file
    Base64Encoder encoder(new FileSink(outFile.c_str()));
    StringSource(cipherStr, true, new Redirector(encoder));
    encoder.MessageEnd();
}

void RSADecryptFile(const string& privateKeyFile, const string& inFile, const string& outFile) {
    AutoSeededRandomPool rng;

    // Load private key
    string privateKeyStr;
    FileSource(privateKeyFile.c_str(), true, new StringSink(privateKeyStr));
    StringSource privFile(privateKeyStr, true, new Base64Decoder);
    RSA::PrivateKey privateKey;
    privateKey.BERDecode(privFile);

    // Decode Base64 ciphertext
    string cipherStr;
    FileSource(inFile.c_str(), true, new Base64Decoder(new StringSink(cipherStr)));

    // Decrypt data
    RSAES_OAEP_SHA_Decryptor decryptor(privateKey);
    StringSource(cipherStr, true,
        new PK_DecryptorFilter(rng, decryptor,
            new FileSink(outFile.c_str())
        ) // PK_DecryptorFilter
    );
}

int main() 
{
    try 
    {
        // File names
        string publicKeyFile = "public.key";
        string privateKeyFile = "private.key";
        string plainTextFile = "adi.txt";
        string cipherTextFile = "ciphertext.enc";
        string decryptedTextFile = "decrypted.txt";
        int option;
        // Generate RSA keys
        GenerateRSAKeys(publicKeyFile, privateKeyFile);
        cout << "RSA keys generated and saved to files.\n";

        cout<<"Choose the option to Encrypt or Decrypt file:"<<endl;
        
        int i =0;
        while(option <3)
        {
            cout<<"Entre 1 to Encrypt file:"<<endl;
            cout<<"Entre 2 to Decrypt file:"<<endl;
            cout<<"Entre 3 to End:"<<endl;
            cin>>option;
            if(option ==1)
            {
                    // Encrypt a file
                RSAEncryptFile(publicKeyFile, plainTextFile, cipherTextFile);
                cout << "File Encrypted.\n";
            }
            else if(option ==2)
            {
                // Decrypt the file
                RSADecryptFile(privateKeyFile, cipherTextFile, decryptedTextFile);
                cout << "File Decrypted.\n";
            }
            else if (option >3)
                { 
                    cout<<"Not a valid option..."<<endl;
                }
        }

    } 
    catch (const CryptoPP::Exception& e) 
    {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
