#include <iostream>
#include "..\Message.h"
using namespace std;


string RepeatingXOR(Message* message, string key)
{
    string encryptedMessage;
    int keySize = key.size();
    int keyIndex = 0;

    for (int i = 0; i < message->ByteLength; i++)
    {
        encryptedMessage += message->ByteMessage[i] ^ key[((keyIndex++) % keySize)];
    }

    return encryptedMessage;
}

int main()
{
    string text = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    string key = "ICE";
    Message* message = new Message(text);
    Message* encryptedMessage = new Message(RepeatingXOR(message,key));

    cout << "Original Message:\n\n" << text << endl << endl;
    cout << "Key: " << key  << endl << endl;
    cout << "Encrypted message:\n\n" << encryptedMessage->Base16Output() << endl;

    string s; cin >> s;

}
