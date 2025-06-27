//
// Created by Aman Shrestha on 26/06/2025.
//

#include"test.h"

static int callback(void *data, int argc, char **argv, char **azColName) {
    unordered_map<string, int>* file_map = static_cast<unordered_map<string, int>*>(data);

    if (argc >= 2 && argv[0] && argv[1]) {
        string fileName = argv[0];  // FileName column
        int hashValue = stoi(argv[1]);  // HashValue column
        (*file_map)[fileName] = hashValue;
    }
    return 0;
};


void loadDataFromDatabase(unordered_map<string, int>& file_map) {
    sqlite3* db;
    char* errMsg = 0;

    int rc = sqlite3_open("gitclone.db", &db);

    if (rc) {
        cout << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return;
    }
    const char* select_command = "SELECT FileName, HashValue FROM git_info;";

    rc = sqlite3_exec(db, select_command, callback, &file_map, &errMsg);

    sqlite3_close(db);
};


void Repository::createRepository() {
    cout << "What is the repository name?  " << endl;
    cin.ignore();
    getline(cin,repository_name);

    if(fs::create_directory(repository_name)){
        cout<<"Repoistory Created: "<<repository_name<<endl;
    }
    else{
        cout<<"Failed To Create "<<endl;
    };

};

int File::creaeHashValue() {
    srand(time(0));
    return rand();
}
void File::addFile() {


string repository_name;
    cout<<"What is the repository name? "<<endl;
    cin>>repository_name;

    cout << "What is the file name? "<<endl;
    cin>>file_name;

    last_hash=creaeHashValue();


    fs::path fullPath=repository_name+ "/"+file_name+ "_" +"1"+".txt";
    ofstream fout(fullPath);
    fout<<"New File Creation";
    fout.close();

    ifstream file;
    file.open(fullPath);


    if(file.is_open()){
        cout<<"File Opened Successfully! "<<endl;

        file_map[file_name+ "_" +"1"]=last_hash;
        int rc= sqlite3_open("gitclone.db",&db);


        const char* creation_command="CREATE TABLE IF NOT EXISTS git_info("
                            "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                            "FileName TEXT NOT NULL,"
                            "HashValue INTEGER NOT NULL);";

        rc= sqlite3_exec(db,creation_command,nullptr,0,&errMsg);

        string insert_command="INSERT INTO git_info(FileName, HashValue) VALUES ('" + file_name + "_1','" + to_string(last_hash) + "');";

        rc= sqlite3_exec(db,insert_command.c_str(),nullptr,0,&errMsg);

        sqlite3_close(db);
    }
    else{
        cout<<"File Couldn't Open" <<endl;
    }

    file.close();

};

void Commit::new_commit() {
    int rc= sqlite3_open("gitclone.db",&db);

    cout<<"What is the repository name? "<<endl;
    cin>>repository_name;

    cout << "What is the file name? "<<endl;
    cin>>file_name;

    int version = 1;
    string baseFileName = file_name;
    while (fs::exists(repository_name + "/" + file_name + "_" + to_string(version) + ".txt")) {
        version++;
    }

    fs::path fullPath = repository_name + "/" + baseFileName + "_" + to_string(version) + ".txt";

   cout<<"What new changes you wanna do? "<<endl;
   cin.ignore();
   getline(cin,newLine);

   ofstream fout(fullPath);
   fout<<newLine;
   commit_ID=F.creaeHashValue();
   file_map[file_name + "_" + to_string(version)]=commit_ID;
    string fullFileName = file_name + "_" + to_string(version);
    string insert_command = "INSERT INTO git_info(FileName, HashValue) VALUES ('" + fullFileName + "','" + to_string(commit_ID) + "');";

    rc= sqlite3_exec(db,insert_command.c_str(),nullptr,0,&errMsg);

    sqlite3_close(db);

   fout.close();


    };


    void Commit::commit_history() {
        loadDataFromDatabase(file_map);
        string folder_name ;
        cout<<"What is the repository name? "<<endl;
        cin>>folder_name;

        string line;


        for (const auto& C : file_map) {
            cout << "File Name: " << C.first << endl;
            cout << "Hash ID: " << C.second << endl;

            fs::path fullPath = folder_name + "/" + C.first + ".txt";

            ifstream fin(fullPath);
            if (fin.is_open()) {
                while (getline(fin, line)) {
                    cout << line << endl;
                }
            } else {
                cout << "Could not open file: " << fullPath << endl;
            }

            cout << "______________________" << endl;
        };
    };

void Commit::particular_commit() {
    ifstream fin;
    string line;
    loadDataFromDatabase(file_map);

        string folder_name ;
        cout<<"What is the repository name? "<<endl;
        cin>>folder_name;

      cout<<"What is the last hash ID? "<<endl;
      cin>>commit_ID;


  for(auto C:file_map){
      if(C.second==commit_ID){
          fs::path fullPath = folder_name + "/" + C.first + ".txt";
          fin.open(fullPath);
          while(getline(fin,line)){
              cout<<line<<endl;
          };

      };


  };
  fin.close();
};

void Menu::menu() {

while(options!=6){
    cout<<"What is the option you wanna choose? "<<endl;
    cout<<"1. Add Repository? "<<endl;
    cout<<"2. Create File"<<endl;
    cout<<"3. Commit New Changes? "<<endl;
    cout<<"4. Commit History"<<endl;
    cout<<"5. View File At Particular Commit"<<endl;
    cout<<"6. Break"<<endl;

    cin>>options;

    if(options==1){
    R.createRepository();
    }
    else if(options==2){
       F.addFile();
    }
    else if(options==3){
        C.new_commit();
    }
    else if(options==4){
        C.commit_history();
    }
    else if(options==5){
        C.particular_commit();
    }
    else if(options==6){
        break;
    }
}
}


