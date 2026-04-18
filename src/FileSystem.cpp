#include "FileSystem.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;


int stringToInt(string s) {
    int res = 0;
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            res = res * 10 + (s[i] - '0');
        }
    }
    return res;
}

void FileSystem::LoadFilesFromCsv(const string &csv_file) {
    ifstream file(csv_file);
    string line;

    getline(file, line);
    while (getline(file, line)) {
        if (line.empty()) continue;
        FileSystemEntry entry;
        
        string tokens[6];
        int t = 0;
        string currentToken = "";
        for (int i = 0; i < (int)line.length(); i++) {
            if (line[i] == ',' && t < 5) {
                tokens[t] = currentToken;
                currentToken = "";
                t++;
            } else {
                currentToken += line[i];
            }
        }
        tokens[t] = currentToken;

        if (t < 5) continue;

        entry.Filename = tokens[0];
        entry.Type = tokens[1];
        entry.Size = stringToInt(tokens[2]);
        entry.accessedOn = ParseTimestamp(tokens[3]);
        entry.modifiedOn = ParseTimestamp(tokens[4]);
        entry.path = tokens[5];
        
        entries.push_back(entry);
    }

    file.close();
}

void FileSystem::PrintFileEntry() {
    for (int i = 0; i < (int)entries.size(); i++) {
        const FileSystemEntry &entry = entries[i];
        cout << "Filename: " << entry.Filename << "\n";
        cout << "Type: " << entry.Type << "\n";
        cout << "Size:" << entry.Size << "\n";
        cout << "accessedOn: " << entry.accessedOn << "\n";
        cout << "modifiedOn: " << entry.modifiedOn << "\n";
        cout << "path: " << entry.path << "\n";
        cout << "\n";
    }
}

string FileSystem::ParseTimestamp(const string &timestampStr) {
    if ((int)timestampStr.length() >= 10) {
        return timestampStr.substr(0, 10);
    }
    return "";

}