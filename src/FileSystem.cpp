#include "FileSystem.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

int convertToNum(string str) {
    int val = 0;
    int len = (int)str.length();
    for (int idx = 0; idx < len; idx++) {
        char ch = str[idx];
        if (ch >= '0' && ch <= '9') {
            val = val * 10 + (ch - '0');
        }
    }
    return val;
}

void FileSystem::LoadFilesFromCsv(const string &loc) {
    ifstream stream(loc);
    string lineText;

    if (getline(stream, lineText)) {
        // heading line
    }

    while (getline(stream, lineText)) {
        if (lineText.length() == 0) continue;
        
        FileSystemEntry item;
        string dataParts[6];
        int cursor = 0;
        int textLen = (int)lineText.length();
        
        int columnCount = 0;
        while (columnCount < 5 && cursor < textLen) {
            string segment = "";
            while (cursor < textLen && lineText[cursor] != ',') {
                segment += lineText[cursor++];
            }
            dataParts[columnCount++] = segment;
            cursor++; // Move past comma
        }
        
        if (cursor < textLen) {
            dataParts[5] = lineText.substr(cursor);
        }

        if (columnCount >= 5) {
            item.Filename = dataParts[0];
            item.Type = dataParts[1];
            item.Size = convertToNum(dataParts[2]);
            item.accessedOn = ParseTimestamp(dataParts[3]);
            item.modifiedOn = ParseTimestamp(dataParts[4]);
            item.path = dataParts[5];
            entries.push_back(item);
        }
    }
    stream.close();
}

void FileSystem::PrintFileEntry() {
    int total = (int)entries.size();
    for (int k = 0; k < total; k++) {
        FileSystemEntry& target = entries[k];
        cout << "Filename: " << target.Filename << "\n";
        cout << "Type: " << target.Type << "\n";
        cout << "Size:" << target.Size << "\n";
        cout << "accessedOn: " << target.accessedOn << "\n";
        cout << "modifiedOn: " << target.modifiedOn << "\n";
        cout << "path: " << target.path << "\n";
        cout << "\n";
    }
}

string FileSystem::ParseTimestamp(const string &raw) {
    if (raw.length() < 10) return "";
    char buf[11];
    for (int m = 0; m < 10; m++) {
        buf[m] = raw[m];
    }
    buf[10] = '\0';
    string result = buf;
    return result;
}