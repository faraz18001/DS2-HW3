#include "FileExplorer.hpp"
#include <fstream>



FileExplorer::FileExplorer(const string &type, const string &csv_file) {
    fs = new FileSystem();
    fs->LoadFilesFromCsv(csv_file);
    
    if (type == "BST") {
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

void writeEntries(const vector<int>& indices, int visited, const vector<FileSystemEntry>& data, const string& output_path) {
    ofstream out(output_path);
    out << "Number of nodes traversed: " << visited << "\n";
    for (int idx : indices) {
        string p = data[idx].path;
        if (!p.empty() && p[0] == '/') {
            p = p.substr(1);
        }
        out << p << "\n";
    }
}

void FileExplorer::FindByName(const string &filename, const string &output_path) {
    pair<vector<int>, int> res = NameIndex->Search(filename);
    writeEntries(res.first, res.second, fs->entries, output_path);
}

void FileExplorer::FindByDate(const string &date, const string &output_path) {
    pair<vector<int>, int> res = DateIndex->Search(date);
    writeEntries(res.first, res.second, fs->entries, output_path);
}

void FileExplorer::FindByNameAndDate(const string &filename, const string &date, const string &output_path) {
    pair<vector<int>, int> nameRes = NameIndex->Search(filename);
    pair<vector<int>, int> dateRes = DateIndex->Search(date);
    
    vector<int> overlap;
    for (int nIdx : nameRes.first) {
        for (int dIdx : dateRes.first) {
            if (nIdx == dIdx) {
                overlap.push_back(nIdx);
                break;
            }
        }
    }

    writeEntries(overlap, nameRes.second + dateRes.second, fs->entries, output_path);
}

void FileExplorer::FindByNameAndSize(const string &filename, const int size, const string &output_path) {
    pair<vector<int>, int> nameRes = NameIndex->Search(filename);
    vector<int> filtered;
    for (int idx : nameRes.first) {
        if (fs->entries[idx].Size == size) filtered.push_back(idx);
    }
    writeEntries(filtered, nameRes.second, fs->entries, output_path);
}

void FileExplorer::FindFilesCreatedDuring(const string &date1, const string &date2, const string &output_path) {
    pair<vector<int>, int> res = DateIndex->RangeSearch(date1, date2);
    writeEntries(res.first, res.second, fs->entries, output_path);
}