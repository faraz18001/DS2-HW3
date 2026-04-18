#include "FileExplorer.hpp"
#include <fstream>

FileExplorer::FileExplorer(const string &t, const string &f) {
    fs = new FileSystem();
    fs->LoadFilesFromCsv(f);
    
    if (t == "BST") {
        NameIndex = new BSTIndex();
        DateIndex = new BSTIndex();
    } else {
        NameIndex = new AVLIndex();
        DateIndex = new AVLIndex();
    }
    
    NameIndex->CreateIndex(fs->entries, "Filename");
    DateIndex->CreateIndex(fs->entries, "modifiedOn");
}

FileExplorer::~FileExplorer() {
    delete NameIndex;
    delete DateIndex;
    delete fs;
}

void dumpToFilesystem(const vector<int>& list, int numVisited, const vector<FileSystemEntry>& info, const string& pathOut) {
    ofstream writer(pathOut);
    writer << "Number of nodes traversed: " << numVisited << "\n";
    
    int sz = (int)list.size();
    for (int i = 0; i < sz; i++) {
        int pos = list[i];
        string entryPath = info[pos].path;
        if (entryPath.length() > 0 && entryPath[0] == '/') {
            entryPath = entryPath.substr(1);
        }
        writer << entryPath << "\n";
    }
}

void FileExplorer::FindByName(const string &name, const string &out) {
    pair<vector<int>, int> results = NameIndex->Search(name);
    dumpToFilesystem(results.first, results.second, fs->entries, out);
}

void FileExplorer::FindByDate(const string &day, const string &out) {
    pair<vector<int>, int> results = DateIndex->Search(day);
    dumpToFilesystem(results.first, results.second, fs->entries, out);
}

void FileExplorer::FindByNameAndDate(const string &name, const string &day, const string &out) {
    pair<vector<int>, int> r1 = NameIndex->Search(name);
    pair<vector<int>, int> r2 = DateIndex->Search(day);
    
    vector<int> both;
    int i = 0, j = 0;
    int size1 = (int)r1.first.size();
    int size2 = (int)r2.first.size();

    while (i < size1 && j < size2) {
        int valA = r1.first[i];
        int valB = r2.first[j];
        if (valA == valB) {
            both.push_back(valA);
            i++; j++;
        } else if (valA < valB) {
            i++;
        } else {
            j++;
        }
    }

    dumpToFilesystem(both, r1.second + r2.second, fs->entries, out);
}

void FileExplorer::FindByNameAndSize(const string &name, const int bytes, const string &out) {
    pair<vector<int>, int> results = NameIndex->Search(name);
    vector<int> refined;
    for (int i = 0; i < (int)results.first.size(); i++) {
        int idx = results.first[i];
        if (fs->entries[idx].Size == bytes) {
            refined.push_back(idx);
        }
    }
    dumpToFilesystem(refined, results.second, fs->entries, out);
}

void FileExplorer::FindFilesCreatedDuring(const string &dStart, const string &dEnd, const string &out) {
    pair<vector<int>, int> output = DateIndex->RangeSearch(dStart, dEnd);
    dumpToFilesystem(output.first, output.second, fs->entries, out);
}