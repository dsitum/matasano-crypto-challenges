#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

int DetectEcbMessage()
{
    int totalMessages = 0;
    string messageArray[512];
    string messageString = "";
    string block1;
    string block2;

    ifstream file("challenge08.txt");
    if(!file.is_open())
    {
       cout<<"File don't exist!";
       return -1;
    }

    while(!file.eof())
    {
        getline(file, messageString);
        messageArray[totalMessages++] =  messageString;
    }
    file.close();

    int repeatingBlockNumber[totalMessages];

    for(int i=0; i<totalMessages;i++)
    {
        block1 = "";
        repeatingBlockNumber[i] = 0;

        //we take one block and check for same blocks in encrypted message
        for(int j=0;j<messageArray[i].size();j+=32)
        {
            block1 = messageArray[i].substr(j,32);
            for(int k=j+32;k<(messageArray[i].size());k+=32)
            {
                block2 = messageArray[i].substr(k,32);
                if(block1.compare(block2) == 0)
                {
                    repeatingBlockNumber[i]++;
                    block2="";
                }
            }
        }

        if(repeatingBlockNumber[i]>0)
        {
            cout << "Possible ECB encrypted chiper!!\n\nMessage:\n\n";
            cout << messageArray[i]<<endl << endl;
            cout << "16 byte blocks:\n\n";

            for(int j=0;j<messageArray[i].size();j+=32)
            {
                cout<< messageArray[i].substr(j,32) << endl;
            }
        }

    }

    return 1;
}

int main()
{
    DetectEcbMessage();
    string s; cin >> s;

}
