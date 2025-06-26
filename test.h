//
// Created by Aman Shrestha on 26/06/2025.
//

#ifndef UNTITLED1_TEST_H
#define UNTITLED1_TEST_H

#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include<filesystem>
#include<fstream>


using namespace std;
namespace fs = std::filesystem;



class Repository{
public:
    Repository(){};
    string repository_name;
    void createRepository();


};

class File{
public:
    File(){};


    ifstream fin;
    string file_name;
    int last_hash;
    unordered_map<string, int>file_map;

    void addFile();
    int creaeHashValue();




};

class Commit: public File, Repository{
public:

    Commit(){};
    File F;
    Repository R;
    string newLine;

    int commit_ID;
    string timestamp;
    unordered_map<string,string>snapshot;
    vector<string>modifiedFiles;

    void new_commit();
    void commit_history();
    void particular_commit();




};

class Menu{
public:
    Repository R;
    File F;
    Commit C;

    Menu(){};
    void menu();
    int options;

};

#endif //UNTITLED1_TEST_H
