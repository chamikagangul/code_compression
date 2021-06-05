
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <bitset>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

vector<string> dictList;
string lastDecoded = "";

string COMPRESSED = "";

void print(std::string input)
{
    cout << input << endl;
}

string getXOR(string s1, string s2)
{
    auto result = std::bitset<4>(s1) ^ std::bitset<4>(s2);
    string r = result.to_string();
    return r;
}

string getXORn(string s1, string s2, int n)
{

    if (n == 1)
    {
        auto result = std::bitset<1>(s1) ^ std::bitset<1>(s2);
        string r = result.to_string();

        return r;
    }
    else if (n == 2)
    {

        auto result = std::bitset<2>(s1) ^ std::bitset<2>(s2);
        string r = result.to_string();

        return r;
    }
    else if (n == 4)
    {
        auto result = std::bitset<4>(s1) ^ std::bitset<4>(s2);
        string r = result.to_string();
        return r;
    }
    else if (n == 32)
    {
        auto result = std::bitset<32>(s1) ^ std::bitset<32>(s2);
        string r = result.to_string();
        return r;
    }
    return "false";
}

string bitmaskDecompress(string compressed, vector<string> dict)
{
    string location = compressed.substr(3, 5);
    string bitmask = compressed.substr(8, 4);
    string dictIndex = compressed.substr(12, 4);

    int locationI = stoi(location, 0, 2);
    int dictIndexI = stoi(dictIndex, 0, 2);

    // cout << compressed << endl;
    // cout << location << endl;
    // cout << bitmask << endl;
    // cout << dictIndex << endl;

    string rslt = dict[dictIndexI];
    string r = rslt.substr(0, locationI) + getXOR(rslt.substr(locationI, 4), bitmask) + rslt.substr(locationI + 4);
    return r;
}

string bitMisMatchDecompress(string compressed, vector<string> dict, int n)
{
    string location = compressed.substr(3, 5);
    string dictIndex = compressed.substr(8, 4);

    int locationI = stoi(location, 0, 2);
    int dictIndexI = stoi(dictIndex, 0, 2);

    string rslt = dict[dictIndexI];
    string mask = "";

    for (int i = 0; i < n; i++)
    {
        mask = mask + "1";
    }

    string r = rslt.substr(0, locationI) + getXORn(rslt.substr(locationI, n), mask, n) + rslt.substr(locationI + n);
    return r;
}

string twoBitMisMatchDecompress(string compressed, vector<string> dict)
{

    string location1 = compressed.substr(3, 5);
    string location2 = compressed.substr(8, 5);
    string dictIndex = compressed.substr(13, 4);

    int locationI1 = stoi(location1, 0, 2);
    int locationI2 = stoi(location2, 0, 2);
    int dictIndexI = stoi(dictIndex, 0, 2);

    string rslt = dict[dictIndexI];

    string mask = "";

    for (int i = 0; i < 32; i++)
    {
        if (i == locationI1 or i == locationI2)
        {
            mask = mask + "1";
        }
        else
        {
            mask = mask + "0";
        }
    }

    string r = getXORn(rslt, mask, 32);
    // print(mask + " xor " + rslt + " = " + r);
    return r;
}

string directDecompress(string compressed, vector<string> dict)
{
    string dictIndex = compressed.substr(3, 4);
    int dictIndexI = stoi(dictIndex, 0, 2);
    string rslt = dict[dictIndexI];
    return rslt;
}

string rleDecompress(string compressed, string last)
{
    string times = compressed.substr(3, 3);
    int timesI = stoi(times, 0, 2) + 1;
    string rslt = "";

    for (int i = 0; i < timesI; i++)
    {
        rslt = rslt + last + "\n";
    }

    return rslt;
}

string decompressOneLine(string compressed, vector<string> dict, string last)
{
    if (compressed.substr(0, 3) == "010")
    {
        return bitmaskDecompress(compressed, dict);
    }
    else if (compressed.substr(0, 3) == "011")
    {
        return bitMisMatchDecompress(compressed, dict, 1);
    }
    else if (compressed.substr(0, 3) == "100")
    {
        return bitMisMatchDecompress(compressed, dict, 2);
    }
    else if (compressed.substr(0, 3) == "101")
    {
        return bitMisMatchDecompress(compressed, dict, 4);
    }
    else if (compressed.substr(0, 3) == "111")
    {
        return directDecompress(compressed, dict);
    }
    else if (compressed.substr(0, 3) == "000")
    {
        return compressed.substr(3);
    }
    else if (compressed.substr(0, 3) == "110")
    {
        return twoBitMisMatchDecompress(compressed, dict);
    }
    else if (compressed.substr(0, 3) == "001")
    {
        return rleDecompress(compressed, last);
    }
    return "not defined : " + compressed.substr(0, 3);
}

string decompress_(string c, vector<string> d)
{
    // print(c);
    string decompressed;
    string last;
    while (true)
    {

        if (count(c.begin(), c.end(), '1') == 0 and c.length() < 35)
        {
            break;
        }

        print(c.substr(0, 3));
        if (c.substr(0, 3) == "010")
        {
            last = bitmaskDecompress(c.substr(0, 16), d);
            ;
            decompressed = decompressed + last + "\n";
            c = c.substr(16);
        }
        else if (c.substr(0, 3) == "011")
        {
            last = bitMisMatchDecompress(c.substr(0, 12), d, 1);
            decompressed = decompressed + last + "\n";
            c = c.substr(12);
        }
        else if (c.substr(0, 3) == "100")
        {
            last = bitMisMatchDecompress(c.substr(0, 12), d, 2);
            decompressed = decompressed + last + "\n";
            c = c.substr(12);
        }
        else if (c.substr(0, 3) == "101")
        {
            last = bitMisMatchDecompress(c.substr(0, 12), d, 4);
            decompressed = decompressed + last + "\n";
            c = c.substr(12);
        }
        else if (c.substr(0, 3) == "111")
        {
            last = directDecompress(c.substr(0, 7), d);
            decompressed = decompressed + last + "\n";
            c = c.substr(7);
        }
        else if (c.substr(0, 3) == "000")
        {
            last = c.substr(3, 32);
            decompressed = decompressed + last + "\n";
            c = c.substr(3 + 32);
        }
        else if (c.substr(0, 3) == "110")
        {
            last = twoBitMisMatchDecompress(c.substr(0, 17), d);
            decompressed = decompressed + last + "\n";
            c = c.substr(17);
        }
        else if (c.substr(0, 3) == "001")
        {
            decompressed = decompressed + rleDecompress(c.substr(0, 17), last);
            c = c.substr(6);
        }
    }

    return decompressed;
}

vector<int> findOnes(string str)
{
    vector<int> locations;
    int N = str.length();
    for (int i = 0; i < N; i++)
    {
        if (str[i] == '1')
        {
            locations.push_back(i);
        }
    }
    return locations;
}

vector<string> countFreq(vector<string> arr)
{
    multimap<int, string> dict;
    int n = arr.size();
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++)
    {
        if (visited[i] == true)
            continue;
        int count = -1;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                visited[j] = true;
                count--;
            }
        }
        dict.insert(pair<int, string>(count, arr[i]));
    }

    vector<string> d;
    int c = 0;
    for (auto &it : dict)
    {

        if (c < 16)
        {
            d.push_back(it.second);
        }
        else
        {
            break;
        }
        c++;
    }
    //     if (c < 16)
    // {
    //     dict[count] = arr[i];
    //     c++;
    // }else{
    //     return dict;
    // }
    return d;
}

string bitmaskBasedCodeCompression(string instruction, vector<string> dictList)
{

    int n = dictList.size();
    for (int j = 0; j < n; j++)
    {

        int instructionSize = 32;
        int maskSize = 4;
        string d = dictList[j];

        for (int i = 0; i < instructionSize - maskSize; i++)
        {
            if (instruction.substr(0, i) == d.substr(0, i) && instruction.substr(i + maskSize) == d.substr(i + maskSize))
            {
                string output = "010";
                string location = std::bitset<5>(i).to_string();
                string XOR = getXOR(instruction.substr(i, maskSize), d.substr(i, maskSize));
                string dictionayIndex = std::bitset<4>(j).to_string();
                output = output + location + XOR + dictionayIndex;
                return output;
            }
        }
    }
    return "false";
}

string bitmisMatchCodeCompression(string instruction, vector<string> dictList, int m)
{

    int n = dictList.size();
    bool found = false;
    string output;
    for (int j = 0; j < n; j++)
    {

        int instructionSize = 32;
        int maskSize = m;
        string d = dictList[j];

        for (int i = 0; i < instructionSize - maskSize; i++)
        {
            // cout << "test eqaulity " << instruction.substr(0, i) << " " << d.substr(0, i) << " " << instruction.substr(i + maskSize)<< " "<< d.substr(i+ maskSize) << " " << endl;

            if (instruction.substr(0, i) == d.substr(0, i) && instruction.substr(i + maskSize) == d.substr(i + maskSize))
            {

                string location = std::bitset<5>(i).to_string();
                string XOR = getXORn(instruction.substr(i, maskSize), d.substr(i, maskSize), maskSize);
                string dictionayIndex = std::bitset<4>(j).to_string();

                // cout << "===============" << XOR << endl;

                if (maskSize == 1 and XOR == "1")
                {
                    output = "011";
                    output = output + location + dictionayIndex;
                    found = true;
                    break;
                }
                else if (maskSize == 2 and XOR == "11")
                {
                    output = "100";
                    output = output + location + dictionayIndex;
                    found = true;
                    break;
                }
                else if (maskSize == 4 and XOR == "1111")
                {
                    output = "101";
                    output = output + location + dictionayIndex;
                    found = true;
                    break;
                }
            }
        }
    }
    if (found)
    {
        return output;
    }
    else
    {
        return "false";
    }
    return "false";
}

string twoBitMismatchCompression(string instruction, vector<string> dictList)
{
    int n = dictList.size();
    string result;
    for (int i = 0; i < n; i++)
    {
        string XOR = getXORn(instruction, dictList[i], 32);
        vector<int> locations = findOnes(XOR);
        if (locations.size() == 2)
        {
            return "110" + std::bitset<5>(locations[0]).to_string() + std::bitset<5>(locations[1]).to_string() + std::bitset<4>(i).to_string();
            break;
        }

        // return "";
    }
    return "false";
}

string directCompression(string instruction, vector<string> dictList)
{
    int n = dictList.size();
    for (int i = 0; i < n; i++)
    {
        if (dictList[i] == instruction)
        {
            return "111" + std::bitset<4>(i).to_string();
        }
    }
    return "false";
}

void writeToFile(string s, vector<string> d)
{
    int n = s.length();
    for (int i = 0; i < 32 - (n % 32); i++)
    {
        s = s + "0";
    }
    n = s.length();
    string toSave = "";

    for (int i = 0; i < n / 32; i++)
    {
        toSave = toSave + s.substr(i * 32, 32) + "\n";
    }

    int m = d.size();
    toSave = toSave + "xxxx" + "\n";
    for (int i = 0; i < m; i++)
    {
        toSave = toSave + d[i] + "\n";
    }
    ofstream myfile;
    myfile.open("cout.txt");
    myfile << toSave;
    myfile.close();

    // for (int i = 0; i < 16; i++)
    // {
    //     print(dictList[i]);
    // }
}

void save(string s)
{
    // print(s);

    COMPRESSED = COMPRESSED + s;

    // lastDecoded = decompress(s, dictList,lastDecoded);
    // cout << lastDecoded  << endl;
}

void compress()
{
    multimap<int, string> dict;

    // reading file
    string line;
    vector<string> instructions;
    ifstream MyReadFile("original.txt");

    while (getline(MyReadFile, line))
    {
        instructions.push_back(line);
    }

    MyReadFile.close();
    int instructionsLength = instructions.size();
    // creating dictionary
    dictList = countFreq(instructions);
    // dictList = sortAndGetFirst16(dict);

    //code compression
    int RLEcount = -1;

    for (int i = 0; i < instructionsLength; i++)
    {

        string compressed;
        if (i > 0)
        {

            // cout << i + 1 << endl;
            // if (i == 43)
            // {
            //     break;
            // }
            if (instructions[i - 1] == instructions[i])
            {
                if (RLEcount < 7)
                {
                    RLEcount++;
                    compressed = "same";
                }
                else
                {
                    if (RLEcount > -1)
                    {
                        compressed = "001" + std::bitset<3>(RLEcount).to_string();
                        // print("==== overflow ====");
                        save(compressed);
                    }
                    RLEcount = 0;
                }
            }
            else
            {
                if (RLEcount > -1)
                {
                    compressed = "001" + std::bitset<3>(RLEcount).to_string();
                    save(compressed);
                }
                RLEcount = -1;

                // direct compression
                compressed = directCompression(instructions[i], dictList);
                if (compressed != "false")
                {
                    save(compressed);
                    continue;
                }
                // bit mismatch compression
                compressed = bitmisMatchCodeCompression(instructions[i], dictList, 1);
                if (compressed != "false")
                {
                    // print("------------------------------------------------------");
                    save(compressed);
                    continue;
                }

                compressed = bitmisMatchCodeCompression(instructions[i], dictList, 2);
                if (compressed != "false")
                {
                    // print("------------------------------------------------------");
                    save(compressed);
                    continue;
                }

                compressed = bitmisMatchCodeCompression(instructions[i], dictList, 4);
                if (compressed != "false")
                {
                    // print("------------------------------------------------------");
                    save(compressed);
                    continue;
                }

                //bitmarks compression
                compressed = bitmaskBasedCodeCompression(instructions[i], dictList);
                if (compressed != "false")
                {
                    save(compressed);
                    continue;
                }
                //two bit mismatch
                compressed = twoBitMismatchCompression(instructions[i], dictList);
                if (compressed != "false")
                {
                    // print("------------------------------------------------------");
                    save(compressed);
                    continue;
                }

                //original
                save("000" + instructions[i]);
            }
        }
        else
        {
            // direct compression
            compressed = directCompression(instructions[i], dictList);
            if (compressed != "false")
            {
                save(compressed);
                continue;
            }
            // bit mismatch compression
            compressed = bitmisMatchCodeCompression(instructions[i], dictList, 1);
            if (compressed != "false")
            {
                // print("------------------------------------------------------");
                save(compressed);
                continue;
            }

            compressed = bitmisMatchCodeCompression(instructions[i], dictList, 2);
            if (compressed != "false")
            {
                // print("------------------------------------------------------");
                save(compressed);
                continue;
            }

            compressed = bitmisMatchCodeCompression(instructions[i], dictList, 4);
            if (compressed != "false")
            {
                // print("------------------------------------------------------");
                save(compressed);
                continue;
            }

            //bitmarks compression
            compressed = bitmaskBasedCodeCompression(instructions[i], dictList);
            if (compressed != "false")
            {
                save(compressed);
                continue;
            }
            //two bit mismatch
            compressed = twoBitMismatchCompression(instructions[i], dictList);
            if (compressed != "false")
            {
                save(compressed);
                continue;
            }

            //original
            save("000" + instructions[i]);
        }

        //checking
        // string decompressed = decompress(compressed, dictList);
        // if (decompressed == instructions[i])
        // {
        //     cout << "true" << endl;
        // }
        // else
        // {
        //     cout << compressed << endl;
        // }
    }

    writeToFile(COMPRESSED, dictList);
}

void decompress()
{
    string compressedInstructions;
    ifstream MyReadFile("cout.txt");
    string line;
    while (getline(MyReadFile, line))
    {
        if (line == "xxxx")
        {
            break;
        }
        compressedInstructions = compressedInstructions + line;
    }
    vector<string> dictList;
    while (getline(MyReadFile, line))
    {
        dictList.push_back(line);
    }
    MyReadFile.close();

    string decompressed = decompress_(compressedInstructions, dictList);

    ofstream myfile;
    myfile.open("dout.txt");
    myfile << decompressed;
    myfile.close();
}

int main(int argc, char *argv[])
{
    string mode = argv[1];

    // for (int i = 0; i < argc; i++)
    // {
    //     cout << argv[i]  << " " << i<< " "<< typeid("1").name() << endl;
    // }

    if (mode == "1")
    {
        compress();
    }
    else if (mode == "2")
    {
        decompress();
    }
    else
    {
        print("Input is not valid");
    }

    return 0;
}
