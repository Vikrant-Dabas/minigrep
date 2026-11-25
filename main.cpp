#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int STATUS = 0;

int main(int argc,char **argv){
    if(argc == 1){
        cerr<<"Error: Enter the pattern and file name(s)"<<endl;
        return 1;
    }
    else if(argc == 2){
        cerr<<"Error: Enter the file name(s)"<<endl;
        return 1;
    }
    else{
        int fileNum = argc-2;
        for(int i=0;i<fileNum;i++){
            char* fileName = argv[i+2];
            ifstream file(fileName);
            if(!file.is_open()) {
                cerr<<"Failed to open: "<<fileName<<endl;
                STATUS = 2;
                continue;
            }
            string line;
            cout<<"Now printing: "<<fileName<<endl;
            while(getline(file,line)){
                cout<<line<<endl;
            }
            if(i != fileNum-1)cout<<endl;
        }
    }
    return STATUS;
}