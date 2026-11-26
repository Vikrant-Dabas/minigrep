#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool ANYMATCH = false;
bool ANYERROR = false;

void printLines(vector<pair<int,string>>& v,string& fileName);

int main(int argc,char **argv){
    if(argc == 1){
        cerr<<"Error: Enter the pattern and file name(s)"<<endl;
        return 2;
    }
    else if(argc == 2){
        cerr<<"Error: Enter the file name(s)"<<endl;
        return 2;
    }
    else{
        int fileNum = argc-2;
        string pattern = argv[1];
        for(int i=0;i<fileNum;i++){
            string fileName = argv[i+2];
            ifstream file(fileName);
            if(!file.is_open()) {
                cerr<<"Failed to open: "<<fileName<<endl;
                ANYERROR = true;
                continue;
            }
            string line;
            vector<pair<int,string>> lines;
            int lineNo = 1;
            while(getline(file,line)){
                if(line.find(pattern) != string::npos){
                    lines.push_back({lineNo,line});
                }
                lineNo++;
            }
            printLines(lines,fileName);
            if(!lines.empty()) ANYMATCH = true;
        }
    }
    if (ANYERROR) return 2;
    else if (!ANYMATCH) return 1;
    else return 0;
}

void printLines(vector<pair<int,string>>& v,string& fileName){
    if(!v.empty()){
        for(auto p:v){
            cout<<fileName<<":"<<p.first<<":"<<p.second<<"\n";
        }
    }
}