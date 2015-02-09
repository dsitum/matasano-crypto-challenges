#include <cstring>
#include <iostream>
using namespace std;

class Message
{
    private:
        int OriginalBase;

    public:
        static const int BASE16 = 16;
        static const int BASE64 = 64;
        static const int UNKNOWN_BASE = 0;

        int OriginalLength;
        int ByteLength;
        string OriginalMessage;
        unsigned char* ByteMessage;
        string ByteMessageString;

        //class constructor that is used for converting original message in raw bytes
        //and calculating the properties that are required for further processing
        Message(string message, int base = UNKNOWN_BASE)
        {
            OriginalMessage = message;
            OriginalBase = base;
            OriginalLength = CalculateOriginalLength();
            ByteLength = CalculateByteLength();

            switch (OriginalBase)
            {
                case BASE16:
                    ByteMessage = HexToBin();
                    ByteMessageString = HexToBinString();
                    break;
                case BASE64:
                    ByteMessage = Base64ToBin();
                    ByteMessageString = Base64ToBinString();
                    break;
                case UNKNOWN_BASE:
                    ByteMessage = RawBytes();
                    ByteMessageString = message;
                    break;
            }
        };

        //method for converting raw bytes to hex encoded string
        static string Base16Output(unsigned char* bytesOfData, int length)
        {
            string output;
            unsigned char HexChars[2];
            for (int i=0; i<length; i++)
            {
                HexChars[0] = (bytesOfData[i] & 0xf0) >> 4;
                HexChars[1] = bytesOfData[i] & 0x0f;

                for (int j=0; j<2; j++)
                {
                    switch(HexChars[j])
                    {
                        case 10: output += 'a'; break;
                        case 11: output += 'b'; break;
                        case 12: output += 'c'; break;
                        case 13: output += 'd'; break;
                        case 14: output += 'e'; break;
                        case 15: output += 'f'; break;
                        default: output += HexChars[j]+48;
                    }
                }
            }

            return output;
        }

        string Base16Output()
        {
            return Base16Output(ByteMessage, ByteLength);
        }

        //method for converting raw bytes to base64 encoded string
        static string Base64Output(unsigned char* bytesOfData, int length)
        {
            string output;
            unsigned char Base64Chars[4];
            for (int i=0; i<length / 3; i++)
            {
                Base64Chars[0] = bytesOfData[i * 3] >> 2;
                Base64Chars[1] = (((bytesOfData[i * 3] & 0x03) << 4) | (bytesOfData[i * 3 + 1] >> 4)) & 0x3f;
                Base64Chars[2] = (((bytesOfData[i * 3 + 1] & 0x0f) << 2) | (bytesOfData[i * 3 + 2] >> 6)) & 0x3f;
                Base64Chars[3] = bytesOfData[i * 3 + 2] & 0x3f;

                for (int j=0; j<4; j++)
                {
                    if(Base64Chars[j]>=0 && Base64Chars[j]<=25)
                    {
                        output += Base64Chars[j]+65;
                    }
                    else if(Base64Chars[j]>=26 && Base64Chars[j]<=51)
                    {
                        output += Base64Chars[j]+71;
                    }
                    else if(Base64Chars[j]>=52 && Base64Chars[j]<=61)
                    {
                        output += Base64Chars[j]-4;
                    }
                    else if(Base64Chars[j]==62)  output += '+';
                    else if(Base64Chars[j]==63)  output += '/';
                    else output += '=';
                }
            }
            return output;
        }

        string Base64Output()
        {
            return Base64Output(ByteMessage, ByteLength);
        }



    private:
        int CalculateOriginalLength()
        {
            return OriginalMessage.length();
        }


        int CalculateByteLength()
        {
            if (OriginalBase == BASE16)
            {
                return OriginalMessage.length() / 2;
            }
            else if (OriginalBase == BASE64)
            {
                int length = OriginalMessage.length() * 3 / 4;
                if (OriginalMessage[OriginalMessage.length() - 2] == '=')
                {
                    length -= 2;
                }
                else if (OriginalMessage[OriginalMessage.length() - 1] == '=')
                {
                    length -= 1;
                }

                return length;
            }
            else
            {
                return OriginalMessage.length();
            }
        }


        unsigned char* HexToBin()
        {
            unsigned char* BinBuffer = new unsigned char[OriginalLength];

            for (unsigned int i=0;i<OriginalLength;i++)
            {
                if(OriginalMessage[i]>47 && OriginalMessage[i]<58) BinBuffer[i] = OriginalMessage[i]-48;
                else if (OriginalMessage[i] == 'a') BinBuffer[i] = 10;
                else if (OriginalMessage[i] == 'b') BinBuffer[i] = 11;
                else if (OriginalMessage[i] == 'c') BinBuffer[i] = 12;
                else if (OriginalMessage[i] == 'd') BinBuffer[i] = 13;
                else if (OriginalMessage[i] == 'e') BinBuffer[i] = 14;
                else if (OriginalMessage[i] == 'f') BinBuffer[i] = 15;
                else BinBuffer[i] = 0;
            }

            unsigned char* BytesOfData = new unsigned char[ByteLength];

            for (unsigned int i=0; i<ByteLength; i++)
            {
                BytesOfData[i] = (BinBuffer[i * 2] << 4) | BinBuffer[i * 2 + 1];
            }

            return BytesOfData;
        }


        string HexToBinString()
        {
            string message;

            for (int i=0; i<ByteLength; i++)
            {
                message += ByteMessage[i];
            }

            return message;
        }


        unsigned char* Base64ToBin()
        {
            const unsigned char UNDEFINED = 64;
            unsigned char* BinBuffer = new unsigned char[OriginalLength];

            for(int i=0; i<OriginalLength; i++)
            {
                if(OriginalMessage[i]>64 && OriginalMessage[i]<91)
                {
                        BinBuffer[i] = OriginalMessage[i]-65;
                }
                else if(OriginalMessage[i]>96 && OriginalMessage[i]<123)
                {
                        BinBuffer[i] = OriginalMessage[i]-71;
                }
                else if(OriginalMessage[i]>47 && OriginalMessage[i]<58)
                {
                        BinBuffer[i] = OriginalMessage[i]+4;
                }
                else if(OriginalMessage[i]==47)  BinBuffer[i] = 63;
                else if(OriginalMessage[i]==43)  BinBuffer[i] = 62;
                else BinBuffer[i] = UNDEFINED;
            }

            unsigned char buffer[3];
            unsigned char* byteMessage = new unsigned char[ByteLength];
            int length = 0;

            for(int i=0; i<OriginalLength / 4; i++)
            {
                buffer[0] = (BinBuffer[i * 4] << 2) | (BinBuffer[i * 4 + 1] >> 4);
                int buffersUsed = 1;

                if (BinBuffer[i * 4 + 2] != UNDEFINED)
                {
                    buffer[1] = (BinBuffer[i * 4 + 1] << 4) | (BinBuffer[i * 4 + 2] >> 2);
                    buffersUsed++;
                }

                if (BinBuffer[i * 4 + 3] != UNDEFINED)
                {
                    buffer[2] = (BinBuffer[i* 4 + 2] << 6) | BinBuffer[i * 4 + 3];
                    buffersUsed++;
                }

                for (int j=0; j<buffersUsed; j++)
                {
                    byteMessage[length + j] = buffer[j];
                }
                length += buffersUsed;
            }

            return byteMessage;
        }


        string Base64ToBinString()
        {
            string message;

            for (int i=0; i<ByteLength; i++)
            {
                message += ByteMessage[i];
            }

            return message;
        }

        unsigned char* RawBytes()
        {
            unsigned char* rawBytes = new unsigned char[OriginalLength];

            for (int i=0; i<OriginalLength; i++)
            {
                rawBytes[i] = OriginalMessage[i];
            }

            return rawBytes;
        }
};
