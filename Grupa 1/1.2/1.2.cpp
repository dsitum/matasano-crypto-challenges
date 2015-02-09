#include <iostream>
#include "..\Message.h"
using namespace std;

//function for calculating XOR sum
Message* Xor(Message* buffer1, Message* buffer2)
{
    string output;
    for (int i=0; i < buffer1->ByteLength; i++)
    {
        output += buffer1->ByteMessage[i] ^ buffer2->ByteMessage[i];
    }

    return new Message(output);
}

int main()
{
    string s1 = "1c0111001f010100061a024b53535009181c";
    string s2 = "686974207468652062756c6c277320657965";
    Message* buffer1 = new Message(s1, Message::BASE16);
    Message* buffer2 = new Message(s2, Message::BASE16);
    Message* resultBuffer = Xor(buffer1, buffer2);
    cout << "Result buffer:" << endl;
    cout << resultBuffer->Base16Output()<<endl<<endl;
    cout << "Message: " << endl;
    cout << resultBuffer->ByteMessageString << endl;

    string s; cin >> s;
}
