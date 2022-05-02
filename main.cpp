#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <sstream>

using namespace std;

bool registered(vector<string> username, string user){
    for(int i = 0; i < username.size(); i++){
        if(user == username[i]){
            return true;
        }
    }
    return false;
}

bool login(vector<string> username, vector<string> password, string user, string pass, int &x){
    for(int i = 0; i < username.size(); i++){
        if(user == username[i]){
            if(pass == password[i]){
                x = i;
                return true;
            }else{
                return false;
            }
        }
    }
    return false;
}

int main()
{
    fstream baca,tulis;
    int inp,inp1,inp2,inp3,inp4,inp5;
    vector<vector<vector<string>>> file;
    vector<vector<string>> storage;
    vector<string> note;
    vector<string> username;
    vector<string> password;

    baca.open("user_pass.txt", ios::in);
    if(baca.is_open()){
        int jml;
        string tmp,tmp1;
        getline(baca,tmp);
        if(tmp != ""){
            stringstream (tmp) >> jml;
        }
        for(int i = 0; i < jml; i++){
            getline(baca,tmp);
            getline(baca,tmp1);
            if(tmp != ""){
                username.push_back(tmp);
            }
            if(tmp1 != ""){
                password.push_back(tmp1);
            }
        }
        baca.close();
    }

    baca.open("penyimpanan.txt", ios::in);
    if(baca.is_open()){
        int jml,jml1,jml2;
        string tmp,tmp1,tmp2,tmp3;
        getline(baca,tmp);
        if(tmp != " "){
            stringstream (tmp) >> jml;
        }
        for(int i = 0; i < jml; i++){
            getline(baca,tmp1);
            if(tmp != " "){
                stringstream (tmp1) >> jml1;
            }
            for(int j = 0; j < jml1; j++){
                getline(baca,tmp2);
                if(tmp != " "){
                    stringstream (tmp2) >> jml2;
                }
                for(int k = 0; k < jml2; k++){
                    getline(baca,tmp3);
                    note.push_back(tmp3);
                }
                storage.push_back(note);
                while(note.size() > 0){
                    note.pop_back();
                }
            }
            file.push_back(storage);
            while(storage.size()){
                storage.pop_back();
            }
        }
        baca.close();
    }

    do{
        cout << "--- Notes ---" << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "0. Quit" << endl;
        cout << ">>> "; cin >> inp;

        if(inp == 1){
            string name,pass;
            cout << "Username: ";
            cin.ignore(); getline(cin,name);
            cout << "Password: ";
            cin.ignore(); getline(cin,pass);
            int x;
            if(login(username,password,name,pass,x)){
                if(file.size() > x){
                    storage = file[x];
                }
                do{
                    system("cls");
                    cout << "Hello, " << username[x] << endl;
                    cout << "My Notes" << endl;
                    cout << "1. Add note" << endl;
                    cout << "2. View all notes" << endl;
                    cout << "3. Delete notes with category" << endl;
                    cout << "0. Logout" << endl;
                    cout << ">>> "; cin >> inp1;
                    system("cls");
                    if(inp1 == 1){
                        string sentence,title;
                        cout << "Note title : ";
                        cin.ignore(); getline(cin,title);
                        note.push_back(title);
                        cout << "Category   : " << endl;
                        cout << "1. Important" << endl;
                        cout << "2. Reminder" << endl;
                        cout << "3. Other" << endl;
                        cout << ">> "; cin >> inp2;
                        if(inp2 == 1){
                            note.push_back("Important");
                        }else if(inp2 == 2){
                            note.push_back("Reminder");
                        }else{
                            note.push_back("Other");
                        }
                        cout << "Content    : ";
                        cin.ignore(); getline(cin,sentence);
                        note.push_back(sentence);
                        note.push_back(" ");
                        note.push_back("0");
                        cout << "Note created!" << endl;
                        storage.push_back(note);
                        while(note.size() > 0){
                            note.pop_back();
                        }
                        system("pause");
                    }else if(inp1 == 2){
                        do{
                            cout << "All notes" << endl;
                            for(int i = 0; i < storage.size(); i++){
                                cout << i+1 << ". " << storage[i][0] << " (" << storage[i][1] << ")" << endl;
                            }
                            cout << "0. Back" << endl;
                            cout << ">> "; cin >> inp3;
                            system("cls");
                            if(inp3-1 <= storage.size()){
                                do{
                                    cout << "=== " << storage[inp3-1][0] << " ===" << endl;
                                    cout << "Category : " << storage[inp3-1][1] << endl;
                                    cout << "Content  : " << storage[inp3-1][2] << endl;
                                    cout << "1. Edit content" << endl;
                                    if(storage[inp3-1][4] == "0"){
                                        cout << "2. Encrypt" << endl;
                                    }else{
                                        cout << "2. Decrypt" << endl;
                                    }
                                    cout << "3. Delete" << endl;
                                    cout << "0. Back" << endl;
                                    cout << ">> "; cin >> inp4;

                                    if(inp4 == 1){
                                        string new_content;
                                        cout << "New content: ";
                                        cin.ignore(); getline(cin,new_content);
                                        storage[inp3-1][2] = new_content;
                                        cout << "Note content edited!" << endl;
                                        system("pause");
                                    }else if(inp4 == 2){
                                        string kalimat = storage[inp3-1][2], passcode;
                                        if(storage[inp3-1][4] == "0"){
                                            cout << "Input new passcode: ";
                                            cin.ignore(); getline(cin, passcode);
                                            storage[inp3-1][3] = passcode;
                                            for(int i = 0; i < kalimat.size(); i++){
                                                kalimat[i] -= 3;
                                            }
                                            cout << "Note ecrypted!" << endl;
                                            storage[inp3-1][4] = "1";
                                        }else{
                                            cout << "Input passcode: ";
                                            cin.ignore(); getline(cin, passcode);
                                            if(passcode == storage[inp3-1][3]){
                                                for(int i = 0; i < kalimat.size(); i++){
                                                    kalimat[i] += 3;
                                                }
                                                cout << "Note decrypted!" << endl;
                                                storage[inp3-1][4] = "0";
                                            }else{
                                                cout << "Wrong passcode! Decrypt cancelled!" << endl;
                                            }
                                        }
                                        storage[inp3-1][2] = kalimat;
                                        system("pause");
                                    }else if(inp4 == 3){
                                        storage.erase(storage.begin() + (inp3-1));
                                        cout << "Note deleted!" << endl;
                                        system("pause");
                                    }
                                    system("cls");
                                }while(inp4 != 0 && inp4 != 3);
                            }
                        }while(inp3 != 0);
                    }else if(inp1 == 3){
                        do{
                            char sure;
                            string category;
                            cout << "Delete notes with category: " << endl;
                            cout << "1. Important" << endl;
                            cout << "2. Reminder" << endl;
                            cout << "3. Other" << endl;
                            cout << "0. Back" << endl;
                            cout << ">>> "; cin >> inp5;
                            if(inp5 == 1){
                                category = "Important";
                            }else if(inp5 == 2){
                                category = "Reminder";
                            }else if(inp5 == 3){
                                category = "Other";
                            }
                            cout << "Are you sure want to delete all " << category << " notes? (Y/N) ";
                            cin >> sure;
                            if(sure == 'Y'){
                                int z = 0;
                                while(z < storage.size()){
                                    if(storage[z][1] == category){
                                        storage.erase(storage.begin() + z);
                                    }else{
                                        z++;
                                    }
                                }
                                cout << "All " << category << " notes deleted!" << endl;
                            }else if(sure == 'N'){
                                cout << "Delete cancelled" << endl;
                            }
                            system("pause");
                        }while(inp5 > 3 && inp5 < 0);
                    }
                }while(inp1 != 0);
                if(file.size() <= x){
                    file.push_back(storage);
                }else{
                    file[x] = storage;
                }
                while(storage.size() != 0){
                    storage.pop_back();
                }
                system("cls");
            }else{
                cout << "Username or Password is wrong" << endl;
                system("pause");
                system("cls");
            }
        }else if(inp == 2){
            string user,pass,confirm;
            cout << "Username: ";
            cin.ignore(); getline(cin,user);
            cout << "Password: ";
            cin.ignore(); getline(cin,pass);
            cout << "Confirm password: ";
            cin.ignore(); getline(cin,confirm);
            if(registered(username,user)){
                cout << "Username has been registered" << endl;
            }else if(pass != confirm){
                cout << "Password and Confirm is not same" << endl;
            }else if(pass == confirm){
                cout << "User registered!" << endl;
                username.push_back(user);
                password.push_back(pass);
            }
            system("pause");
            system("cls");
        }
    }while(inp != 0);

    tulis.open("user_pass.txt", ios::out);
    if(tulis.is_open()){
        tulis << username.size() << endl;
        for(int i = 0; i < username.size(); i++){
            tulis << username[i] << endl;
            tulis << password[i] << endl;
        }
        tulis.close();
    }

    tulis.open("penyimpanan.txt", ios::out);
    if(tulis.is_open()){
        tulis << username.size() << endl;
        for(int i = 0; i < username.size(); i++){
            tulis << file[i].size() << endl;
            for(int j = 0; j < file[i].size(); j++){
                tulis << file[i][j].size() << endl;
                for(int k = 0; k < file[i][j].size(); k++){
                    tulis << file[i][j][k] << endl;
                }
            }
        }
        tulis.close();
    }
    return 0;
}
