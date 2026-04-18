#pragma once

#include <string>
#include <vector>

using namespace std;

struct FileSystemEntry {
    string Filename;
    int    Size;
    string accessedOn;
    string modifiedOn;
    string Type;
    string path;
};

class FileSystem {
public:

    vector<FileSystemEntry> entries;

    void   LoadFilesFromCsv(const string &csv_file);
    string ParseTimestamp(const string &timestampStr);
    void   PrintFileEntry();
};