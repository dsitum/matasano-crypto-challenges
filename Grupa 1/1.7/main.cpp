#include <iostream>
#include <iomanip>
#include <openssl/aes.h>
#include <fstream>
#include <cstring>
#include "..\Message.h"
using namespace std;

unsigned char* DecryptAESecb(unsigned char* key, int keylength)
{

    AES_KEY dec_key;
    char* B64encryptedText;

    AES_set_decrypt_key((const unsigned char *) key, keylength, &dec_key);

    ifstream file("encrypted07.txt");
    if(!file.is_open())
    {
       cout<<"File doesn't exist!";
       return NULL;
    }

    file.seekg(0, ios::end);
    int messageLengthB64 = file.tellg();
    B64encryptedText = new char[messageLengthB64];

    file.seekg(0, ios::beg);
    file.read(B64encryptedText, messageLengthB64);
    string B64Message(B64encryptedText);

    file.close();

    Message* encryptedMessage = new Message(B64Message, Message::BASE64);
    unsigned char* originalMessage = new unsigned char[encryptedMessage->ByteLength];
    unsigned char* encryptedMessagePart = new unsigned char[16];
    unsigned char* originalMessagePart = new unsigned char [16];

    for (int i=0; i < encryptedMessage->ByteLength; i++)
    {
        originalMessage[i] = '\0';
    }

    for (int i=0; i < encryptedMessage->ByteLength / 16; i++)
    {
        for (int j=0; j<16; j++)
        {
            encryptedMessagePart[j] = encryptedMessage->ByteMessage[i * 16 + j];
        }

        AES_decrypt((const unsigned char *) encryptedMessagePart, originalMessagePart, (const AES_KEY *) &dec_key);

        for (int j=0; j<16; j++)
        {
            //in last iteration/block
            if(i == ((encryptedMessage->ByteLength / 16)-1))
            {
                //taking care about redundant chars in last block
                int lastBlockBytes =  encryptedMessage->ByteLength % 16;
                if(lastBlockBytes > 0)
                {
                    for(int h = 16-lastBlockBytes; h <16;h++)
                    {
                        originalMessagePart[h] = '\0';
                    }
                }
            }

            originalMessage[i * 16 + j] = originalMessagePart[j];
        }
    }


    return originalMessage;
}

int main()
{
    unsigned char key[16] = {'Y', 'E', 'L', 'L', 'O', 'W', ' ', 'S', 'U', 'B', 'M', 'A', 'R', 'I', 'N', 'E'};
    cout << "Decrypted message:\n\n" << DecryptAESecb(key, 128);
    string s; cin >> s;

    return 0;
}
