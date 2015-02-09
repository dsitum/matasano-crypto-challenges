#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

class FindXorKey
{
    private:
        static float CalculateScore(string message, int messageLength)
        {
            const int TESTED_CHARACTERS_NUM = 26;
            struct CharacterFrequency
            {
                char c;  // character
                float f;  // frequency
            };
            CharacterFrequency* characterFrequency = new CharacterFrequency[TESTED_CHARACTERS_NUM];
            characterFrequency[0].c = 'e'; characterFrequency[0].f = 12.02;
            characterFrequency[1].c = 't'; characterFrequency[1].f = 9.1;
            characterFrequency[2].c = 'a'; characterFrequency[2].f = 8.12;
            characterFrequency[3].c = 'o'; characterFrequency[3].f = 7.68;
            characterFrequency[4].c = 'i'; characterFrequency[4].f = 7.31;
            characterFrequency[5].c = 'n'; characterFrequency[5].f = 6.95;
            characterFrequency[6].c = 's'; characterFrequency[6].f = 6.28;
            characterFrequency[7].c = 'r'; characterFrequency[7].f = 6.02;
            characterFrequency[8].c = 'h'; characterFrequency[8].f = 5.92;
            characterFrequency[9].c = 'd'; characterFrequency[9].f = 4.32;
            characterFrequency[10].c = 'l'; characterFrequency[10].f = 3.98;
            characterFrequency[11].c = 'u'; characterFrequency[11].f = 2.88;
            characterFrequency[12].c = 'c'; characterFrequency[12].f = 2.71;
            characterFrequency[13].c = 'm'; characterFrequency[13].f = 2.61;
            characterFrequency[14].c = 'f'; characterFrequency[14].f = 2.30;
            characterFrequency[15].c = 'y'; characterFrequency[15].f = 2.11;
            characterFrequency[16].c = 'w'; characterFrequency[16].f = 2.09;
            characterFrequency[17].c = 'g'; characterFrequency[17].f = 2.03;
            characterFrequency[18].c = 'p'; characterFrequency[18].f = 1.82;
            characterFrequency[19].c = 'b'; characterFrequency[19].f = 1.49;
            characterFrequency[20].c = 'v'; characterFrequency[20].f = 1.11;
            characterFrequency[21].c = 'k'; characterFrequency[21].f = 0.69;
            characterFrequency[22].c = 'x'; characterFrequency[22].f = 0.17;
            characterFrequency[23].c = 'q'; characterFrequency[23].f = 0.11;
            characterFrequency[24].c = 'j'; characterFrequency[24].f = 0.10;
            characterFrequency[25].c = 'z'; characterFrequency[25].f = 0.07;

            float score = 0;
            int charactersCount[256];

            for (int i = 0; i < 256; i++)
            {
                charactersCount[i] = 0;
            }

            for (int i = 0; i < messageLength; i++)
            {
                charactersCount[message[i]]++;
            }

            for (int i = 0; i < TESTED_CHARACTERS_NUM; i++)
            {
                int currentCharacterCountRegular = charactersCount[characterFrequency[i].c];
                int currentCharacterCountCapital = charactersCount[characterFrequency[i].c - 32];
                int currentCharacterCount = currentCharacterCountCapital + currentCharacterCountRegular;
                score += abs((float)(currentCharacterCount) / messageLength * 100 - characterFrequency[i].f);
            }
            // we still have to check for spaces (1 space in 6 characters equals 16.67% probability)
            score += abs((float) charactersCount[' '] / messageLength * 100 - 16.67);
            return score;
        }


        static string XorDecrypt(unsigned char* message, unsigned char key, int messageLength)
        {
            string originalMessage;

            for (int j = 0; j < messageLength; j++)
            {
                unsigned char originalHexCharacter = message[j] ^ key;
                originalMessage += originalHexCharacter;
            }

            return originalMessage;
        }



    public:
        static unsigned char FindKey(unsigned char* message, int messageLength)
        {
            float* score = new float[256];
            for (int i = 0; i < 256; i++)
            {
                string possibleOriginalMessage = XorDecrypt(message, (unsigned char)i, messageLength);
                score[i] = CalculateScore(possibleOriginalMessage, messageLength);
            }

            // find index of "score" array with lowest score
            int lowestScoreIndex = 0;
            int lowestScore = score[0];
            for (int i = 1; i < 256; i++)
            {
                if (score[i] < lowestScore)
                {
                    lowestScoreIndex = i;
                    lowestScore = score[i];
                }
            }

            // we have the key now. Key is the ASCII character under lowest score index
            unsigned char key = (unsigned char) lowestScoreIndex;

            return key;
        }
};
