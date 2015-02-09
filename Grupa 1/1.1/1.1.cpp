#include <iostream>
#include "../Message.h"
using namespace std;

int main()
{
    string msg = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

    //"Message" class is in the Message.h and contains methods implemented for the required data manipulation
    //class constructor converts original hex message to raw bytes
    Message* message = new Message(msg, Message::BASE16);

    //Base64Output is method for converting raw bytes to b64 encoded string
    cout << "Base64 output:" << endl;
    cout << message->Base64Output() << endl << endl;

    //Base16Output() is method for converting raw bytes to hex encoded string
    cout << "Base16 output:" << endl ;
    cout << message->Base16Output() << endl;

    string p; cin >> p;

}
