//
// Created by Aman Shrestha on 26/06/2025.
//

#ifndef UNTITLED1_TEST_H
#define UNTITLED1_TEST_H

#include<iostream>
#include<unordered_map>
#include<string>
#include<filesystem>
#include<fstream>
#include<sqlite3.h>
#include<vector>




using namespace std;
namespace fs = std::filesystem;
extern vector<string> file_name_vector;
extern vector<int>hash_value_vector;

class Repository{
public:
    Repository(){};
    string repository_name;
    void createRepository();


};

class File{
public:
    File(){};
    sqlite3 *db;
    char *errMsg=nullptr;

    ifstream fin;
    string file_name;
    string repostiory_name;
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
