#include "FileExplorer.hpp"
#include <fstream>

FileExplorer::FileExplorer(const string &t, const string &f) {
    fs = new FileSystem();
    fs->LoadFilesFromCsv(f);
    
    if (t.compare("BST") == 0) {
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
    ofstream dest(pathOut);
    dest << "Number of nodes traversed: " << numVisited << "\n";
    
    for (int idx : list) {
        string fPath = info[idx].path;
        if (!fPath.empty() && fPath.front() == '/') {
            fPath.erase(fPath.begin());
        }
        dest << fPath << "\n";
    }
}

void FileExplorer::FindByName(const string &name, const string &out) {
    auto resName = NameIndex->Search(name);
    dumpToFilesystem(resName.first, resName.second, fs->entries, out);
}

void FileExplorer::FindByDate(const string &day, const string &out) {
    auto resDate = DateIndex->Search(day);
    dumpToFilesystem(resDate.first, resDate.second, fs->entries, out);
}

void FileExplorer::FindByNameAndDate(const string &name, const string &day, const string &out) {
    auto resName = NameIndex->Search(name);
    auto resDate = DateIndex->Search(day);
    
    vector<int> intersection;
    auto iterA = resName.first.begin();
    auto iterB = resDate.first.begin();

    while (iterA != resName.first.end() && iterB != resDate.first.end()) {
        if (*iterA == *iterB) {
            intersection.push_back(*iterA);
            ++iterA;
            ++iterB;
        } else if (*iterA < *iterB) {
            ++iterA;
        } else {
            ++iterB;
        }
    }

    dumpToFilesystem(intersection, resName.second + resDate.second, fs->entries, out);
}

void FileExplorer::FindByNameAndSize(const string &name, const int bytes, const string &out) {
    auto searchData = NameIndex->Search(name);
    vector<int> filtered;
    for (int targetIdx : searchData.first) {
        if (fs->entries.at(targetIdx).Size == bytes) {
            filtered.push_back(targetIdx);
        }
    }
    dumpToFilesystem(filtered, searchData.second, fs->entries, out);
}

void FileExplorer::FindFilesCreatedDuring(const string &dStart, const string &dEnd, const string &out) {
    auto output = DateIndex->RangeSearch(dStart, dEnd);
    dumpToFilesystem(output.first, output.second, fs->entries, out);
}