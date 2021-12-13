/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string.h>
#include <bitset> /* bitset is used to store an array of binary values and seeing as binary values are importent to this algorithm*/
#include <list>
#include <bits/stdc++.h> /*contains a buntch of header files, that would serve as incredbly redundent and would complicate the code*/
#include <iterator>
#include <sstream>

using namespace std;

namespace unsigned_types {
    typedef std::basic_string<unsigned char> string;
}

string toBitString(string message)
{
    string bitstring;

    for(size_t i = 0; i < message.size(); i++)
    {
        bitstring = bitstring + bitset<8>(message.c_str()[i]).to_string(); /* This returns the binary value of each char in the text value in 8 bits */
    }
    return bitstring;
}

string dobinarymath(string num1, string num2, string num3, string num4)
{
    unsigned long bytenum1 = bitset<32>(num1).to_ulong(); /* to_ulong returns an interger that same bits set as the bitset.*/
    unsigned long bytenum2 = bitset<32>(num2).to_ulong();
    unsigned long bytenum3 = bitset<32>(num3).to_ulong();
    unsigned long bytenum4 = bitset<32>(num4).to_ulong(); 

    unsigned long total = bytenum1 + bytenum2 + bytenum3 + bytenum4;

    return bitset<32>(total).to_string();
}

string dobinarymathall(string num1, string num2, string num3, string num4, string num5)
{

    unsigned long bytenum1 = bitset<32>(num1).to_ulong();
    unsigned long bytenum2 = bitset<32>(num2).to_ulong();
    unsigned long bytenum3 = bitset<32>(num3).to_ulong();
    unsigned long bytenum4 = bitset<32>(num4).to_ulong();
    unsigned long bytenum5 = bitset<32>(num5).to_ulong();
   
    unsigned long total = bytenum1 + bytenum2 + bytenum3 + bytenum4 + bytenum5;

    return bitset<32>(total).to_string();
}

string dobinarymath2(string num1, string num2)
{
    unsigned long bytenum1 = bitset<32>(num1).to_ulong();
    unsigned long bytenum2 = bitset<32>(num2).to_ulong();

    unsigned long total = bytenum1 + bytenum2;

    return bitset<32>(total).to_string();
}



string padding(string bitmessage) /* This begins the processing part mentioned in the pseudocode for SHA256 */
{
    int len = bitmessage.size();
    bool roundabout = true;
    int count = 0;
    string newmessage = bitmessage;

    while(roundabout)
    {
        if((len + 1 + count + 64) % 512 == 0) /* text file has multiply parts that are spilt into 512 bits that create a 64-entry message schedule array of 32 bit words */
        {
            string temp = "1";              /* An important note, unlike what is said on wikapedia, this code should only try to decyrypt the message once*/
            for(int i = 0; i < count; i++)
            {
                temp = temp + "0";
            }

            newmessage = newmessage + temp;
            roundabout = false;
        }
        else
        {
            count++;
        }

    }
    string leninbinary = bitset<64>(len).to_string();
    
    newmessage = newmessage + leninbinary;
    return newmessage;
}

string shiftRight(string message, int num) /*Shift a strings postion based on what index number is passed, ex: right, 3 (returns htrig) */

{
    string temp;
    for(int i = 0; i < num; i++)
    {
        temp = temp + '0';
    }

    for(int j = 0; j < (message.size() - num); j++)
    {
        temp = temp + message[j];
    }

    return temp;
}

string leftrotatearound(string message, int num)
{
    reverse(message.begin(), message.begin() + num);
    reverse(message.begin() + num, message.end());
    reverse(message.begin(), message.end());

    return message;
}

string rightrotatearound(string message, int num)
{
    return leftrotatearound(message, message.size() - num);
}

string sigma0(string message) /* pseudocode for (w[i-15] rightrotate  7) xor (w[i-15] rightrotate 18) xor (w[i-15] rightshift  3) */
{
    string rotr7 = rightrotatearound(message, 7);
    string rotr18 = rightrotatearound(message, 18);

    string temp;
    for(int i = 0; i < 32; i++)
    {
        temp = temp + to_string((rotr7[i] ^ rotr18[i]));
    }

    string shift3 = shiftRight(message, 3);

    string temp2;
    for(int j = 0; j < 32; j++)
    {
        temp2 = temp2 + to_string((temp[j] ^ shift3[j]));
    }

    return temp2;
}

string sigma1(string message) /* pseudocode (w[i-2] rightrotate 17) xor (w[i-2] rightrotate 19) xor (w[i-2] rightshift 10) */
{
    string rotr17 = rightrotatearound(message, 17);
    string rotr19 = rightrotatearound(message, 19);

    string temp;
    for(int i = 0; i < 32; i++)
    {
        temp = temp + to_string((rotr17[i] ^ rotr19[i]));
    }

    string shift10 = shiftRight(message, 10);

    string temp2;
    for(int j = 0; j < 32; j++)
    {
        temp2 = temp2 + to_string((temp[j] ^ shift10[j]));
    }

    return temp2;
}

string uppercasesigma(string message)
{
    string rotr6 = rightrotatearound(message, 6);
    string rotr11 = rightrotatearound(message, 11);

    string temp;
    for(int i = 0; i < 32; i++)
    {
        temp = temp + to_string((rotr6[i] ^ rotr11[i]));
    }

    string rotr10 = rightrotatearound(message, 10);

    string temp2;
    for(int j = 0; j < 32; j++)
    {
        temp2 = temp2 + to_string((temp[j] ^ rotr10[j]));
    }

    return temp2;
}

string ch(string x, string y, string z)
{
    bitset<32> bitsX = bitset<32>(x);
    bitset<32> bitsY = bitset<32>(y);
    bitset<32> bitsZ = bitset<32>(z);

    
    bitset<32> andGate = bitsX & bitsY;
    bitset<32> notAndGate = (~bitsX)& bitsZ;
    

    bitset<32> xorGate = andGate ^ notAndGate;

    string temp = xorGate.to_string();

    return temp;

}


string maj(bitset<32> a, bitset<32> b, bitset<32> c) /*psudocode section (a and b) xor (a and c) xor (b and c) */
{
    bitset<32> majority = (a & b) ^ (a & c) ^ ( b & c);

    return majority.to_string();
}


vector<string> parsingPaddedMessage(string paddedbitstring)
{
     vector<string> parsedpassage;

     int count = 0; 

     for(int i = 0; i < 16; i++)
     {
        string temp;

        for(int j = count; j < (count + 32); j++)
        {
            temp = temp + paddedbitstring[j];
        }

        parsedpassage.push_back(temp);
        count += 32;

     }

     for(int j = 16; j < 64; j++)
     {
         string sigmaFirst = sigma1(parsedpassage[j-2]);
         string w7 = parsedpassage[j-7];
         string sigmaZero = sigma0(parsedpassage[j-15]);
         string w16 = parsedpassage[j -16];

        string totalString = dobinarymath(sigmaFirst, w7, sigmaZero, w16);
        parsedpassage.push_back(totalString);

     }

     return parsedpassage;

}


string sha256(string message) /* We start by intializing the hash values after the outputs the Mark.text file*/
{
/* These have to be hard coded constants represent the first 32 bits of the fractional parts of the square roots 2, 3, 5, 7, 11, 13, 17, 19*/
    unsigned int h0 = 0x6a09e667;
    unsigned int h1 = 0xbb67ae85;
    unsigned int h2 = 0x3c6ef372;
    unsigned int h3 = 0xa54ff53a;
    unsigned int h4 = 0x510e527f;
    unsigned int h5 = 0x9b05688c;
    unsigned int h6 = 0x1f83d9ab;
    unsigned int h7 = 0x5be0cd19;

    vector<unsigned int> k = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    
    string bitstring = toBitString(message);
    string paddedString = padding(bitstring);
    bool testit = true;
    int count = 0;
    int remaininglength = 0;
    int y = 0;
    while(paddedString[y])
    {
        remaininglength++;
        y++;
    }

    
    while(testit) /* While amount of the files length doesn't equal 0 keep counting how many chuncks will be needed to break down the textfile contents */
    {
        remaininglength = remaininglength - 512;
        count++;

        if(remaininglength == 0)
        {
            testit = false;
        }
    }
    
    
    
    vector<vector<string>> listOfParsedChunks;

    for(int i = 0; i < count; i++)
    {
        
        string currentString = paddedString.substr((i * 512), ((i + 1) *512));
        vector<string> parsed = parsingPaddedMessage(currentString);
        listOfParsedChunks.push_back(parsed);
/*Extend the first 16 words into the remaining 48 words */

        unsigned int a = 0x6a09e667;
        unsigned int b = 0xbb67ae85;
        unsigned int c = 0x3c6ef372;
        unsigned int d = 0xa54ff53a;
        unsigned int e = 0x510e527f;
        unsigned int f = 0x9b05688c;
        unsigned int g = 0x1f83d9ab;
        unsigned int h = 0x5be0cd19;


        for(int j = 0; j < 63; j++) /* This starts the compression loop which mutates the values  a - h*/
        {
            
            string bigSigma1 = uppercasesigma(bitset<32>(e).to_string());
            string cH = ch(bitset<32>(e).to_string(), bitset<32>(f).to_string(), bitset<32>(g).to_string());
            string temp1 = dobinarymathall(bitset<32>(h).to_string(), bigSigma1, cH, bitset<32>(k[j]).to_string(), parsed[j]);

            string sigmaZero = sigma0(bitset<32>(a).to_string());
            string majority = maj(a, b, c);
            string temp2 = dobinarymath2(sigmaZero, majority);


            h = g;
            g = f;
            e = e;
            e = d + int(bitset<32>(temp1).to_ulong()); 
            d = c;
            c = b;
            b = a;
            a = int(bitset<32>(temp1).to_ulong()) + int(bitset<32>(temp2).to_ulong());
        }

        h0 = h0 + a;
        h1 = h1 + b;
        h2 = h2 + c;
        h3 = h3 + d;
        h4 = h4 + e;
        h5 = h5 + f;
        h6 = h6 + g;
        h7 = h7 + h;


    }

    std::stringstream h0String;
    h0String << std::hex << h0;
    
    /*This translates the binary to hexdemicial values*/

    std::stringstream h1String;
    h1String << std::hex << h1;

    std::stringstream h2String;
    h2String << std::hex << h2;

    std::stringstream h3String;
    h3String << std::hex << h3;

    std::stringstream h4String;
    h4String << std::hex << h4;

    std::stringstream h5String;
    h5String << std::hex << h5;

    std::stringstream h6String;
    h6String << std::hex << h6;

    std::stringstream h7String;
    h7String << std::hex << h7;


    return h0String.str() + h1String.str() + h2String.str() + h3String.str() + h4String.str() + h5String.str() + h6String.str() + h7String.str();
    
    /* This prints the hash value you see at the end of the program after it finshes processing*/
}

string readFile(const string &fileName)
{
    ifstream ifs(fileName.c_str(), ios::in | ios::binary | ios::ate);

    ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, ios::beg);

    vector<char> bytes(fileSize);
    ifs.read(bytes.data(), fileSize);

    return string(bytes.data(), fileSize);
    
    /*Reads Mark.file and outputs files contents */
}

int main()
{
    string message = readFile("Mark.txt");
   cout << message << endl;

   cout << sha256(message) << endl;
   
    return 0;
}
