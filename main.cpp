#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>

using namespace std;

bool ANYMATCH = false;
bool ANYERROR = false;
unordered_map<char,bool> FLAGS{
    {'I',false} // -i
};

void printLines(vector<pair<int,string>>& v,string& fileName);
pair<string,vector<string>> parseInput(int argc,char** argv);
string lower(const string& s);

int main(int argc,char **argv){
    pair<string,vector<string>> parsedInput = parseInput(argc,argv);
    string pattern = parsedInput.first;
    vector<string> fileNames = parsedInput.second; 
    if(pattern.empty() && fileNames.empty()){
        cerr<<"Error: Enter the pattern and file name(s)"<<endl;
        return 2;
    }
    else if(fileNames.empty()){
        cerr<<"Error: Enter the file name(s)"<<endl;
        return 2;
    }
    else{
        for(string fileName:fileNames){
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
                if((FLAGS['I'] && lower(line).find(lower(pattern)) != string::npos) || (line.find(pattern) != string::npos))
                    lines.push_back({lineNo,line});
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

pair<string,vector<string>> parseInput(int argc,char** argv){
    string pattern;
    bool pattFound = false;
    vector<string> fileNames;
    for(int i = 1;i<argc;i++){
        string arg = argv[i];
        if(arg == "-i") FLAGS['I'] = true;
        else if(!pattFound){
            pattern = arg;
            pattFound = true;
        }
        else fileNames.push_back(arg);
    }
    return {pattern,fileNames};
}

string lower(const string& s){
    string out="";
    for(char ch:s){
        out += static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    }
    return out;
}