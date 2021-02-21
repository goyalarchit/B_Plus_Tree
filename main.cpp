#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<vector>
#include"BPTree.h"
#include"PrettyPrint.h"

using namespace std;

void error(string message){
    cerr<<"Error : "<<message<<endl;
    exit(-1);
}

int parseQueryFromStr(char * s){
    if(strcmp(s,"INSERT")==0)
        return 0;
    else if(strcmp(s,"FIND")==0)
        return 1;
    else if(strcmp(s,"COUNT")==0)
        return 2;
    else if(strcmp(s,"RANGE")==0)
        return 3;
    else if (strcmp(s,"PRINT")==0)
        return 4;
    else
        return 5;
}

int arg_count[] = {1,1,1,2,0};

int main(int argc,char* argv[]){
    if (argc!=2){
        error("Invalid Format, please use \"./a.out <input_filename>\"");
    }
    BPTreePrinter printer;
    BPTree tree; 
    ifstream iFile;
    vector <int> query;
    iFile.open(argv[1],ios::in);
    string queryStr;
    int tokenCount;
    if(!iFile)
        error("File couldn't be opened");
    while(getline(iFile,queryStr)){
        char * rest = &queryStr[0];
        char * token;
        tokenCount=0;
        while(token = strtok_r(rest," ",&rest)){
            tokenCount++;
            if (tokenCount==1)
                query.push_back(parseQueryFromStr(token));
            else
                query.push_back(atoi(token));
        }
        if (query.size()-1!=arg_count[query[0]])
            error("Invalid Number Of Arguments");
        switch(query[0]){
            case 0  :   tree.insert(query[1]);
                        // cout<<"INSERT Query"<<endl;
                        break;
            case 1  :   tree.search(query[1]);
                        // cout<<"FIND Query"<<endl;
                        break;
            case 2  :   tree.count(query[1]);
                        // cout<<"COUNT Query"<<endl;
                        break;
            case 3  :   tree.range(query[1],query[2]);
                        // cout<<"RANGE Query"<<endl;
                        break;
            case 4  :   cout<<"PRETTY PRINTING B+ TREE "<<endl;
                        printer.print(tree);
                        break;
            default :   cerr<<"INVALID QUERY"<<endl;
        }
        query.clear();
    }
    iFile.close();
    return 0;
}