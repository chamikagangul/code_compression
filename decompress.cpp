#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

// int main()
// {
//     string compressedInstructions;
//     ifstream MyReadFile("files/compressed.txt");
//     string line;
//     while (getline(MyReadFile, line))
//     {
//         if (line == "xxxx")
//         {
//             break;
//         }
//         compressedInstructions = compressedInstructions + line;
//     }
//     vector<string> dictList;
//     while (getline(MyReadFile, line))
//     {
//         dictList.push_back(line);
//     }
//     MyReadFile.close();

//     string decompressed = decompress(compressedInstructions, dictList);

//     ofstream myfile;
//     myfile.open("dout.txt");
//     myfile << decompressed;
//     myfile.close();
// }