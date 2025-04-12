#include <iostream>
#include <vector>

using namespace std;

struct folder{
    string name;
    int capacity;
    vector<string> files;
};

bool is_txt(string file){
    if (file.length() < 4) return false;
    if(file.substr(file.length() - 4) == ".txt"){
        return true;
    }
    else{
        return false;
    }
}

string search(vector<folder> folders, string file_name, string path, int index = 0) {
    folder f = folders[index];
    for(int i = 0 ; i < f.capacity ; i++){
        string file = f.files[i];
        if(file == file_name){
            path = path + f.name + file;
            return path;
        }
    }
    for(int i = 0 ; i < f.capacity ; i++){
        string file = f.files[i];
        if(!is_txt(file)){
            int new_ind = 0;
            for(int i = 0; i < folders.size(); i++){
                if(folders[i].name == file){
                    new_ind = i;
                    break;
                }
            }
            string res = search(folders, file_name, path + f.name , new_ind);
            if(!res.empty()){
                return res;
            }
        }
    }
    return "";
}

int main(){
    int total_folder = 0;
    cin >> total_folder;
    vector<folder> folders;
    for(int i = 0 ; i < total_folder ; i++){
        folder f;
        cin >> f.name;
        cin >> f.capacity;
        for(int i = 0 ; i < f.capacity; i++){
            string str;
            cin >> str;
            f.files.push_back(str);
        }
        folders.push_back(f);
    }
    string file_name;
    cin >> file_name;
    string path;
    cout << search(folders , file_name, path);
    return 0;
}