#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <cerrno>
#include <cstring>

using namespace std;

bool ANYMATCH = false;
bool ANYERROR = false;
unordered_map<char,bool> FLAGS{
    {'I',false} // -i
};
string USAGE = "usage: minigrep [-i] pattern file...\n";

void printLines(vector<pair<int,string>>& v,string& fileName);
pair<string,vector<string>> parseInput(int argc,char** argv);
string lower(const string& s);

int main(int argc,char **argv){
    pair<string,vector<string>> parsedInput = parseInput(argc,argv);
    string pattern = parsedInput.first;
    vector<string> fileNames = parsedInput.second; 
    
    for(string fileName:fileNames){
        errno = 0;
        ifstream file(fileName);
        int err = errno;
        if(!file.is_open()) {
            string reason = (err != 0) ? strerror(err) : "unknown error";
            cerr<<"minigrep: "<<fileName<<": "<<reason<<"\n";
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
    if(argc == 1){
        cerr<<USAGE;
        exit(2);
    }
    for(int i = 1;i<argc;i++){
        string arg = argv[i];
        if(arg == "-i") FLAGS['I'] = true;
        else if(arg[0] == '-'){
            cerr<<"minigrep: unknown option '"<<arg<<"'\n"<<USAGE;
            exit(2);
        }
        else if(!pattFound){
            pattern = arg;
            pattFound = true;
        }
        else fileNames.push_back(arg);
    }
    if(fileNames.empty() || !pattFound){
        cerr<<USAGE;
        exit(2);
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