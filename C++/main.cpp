#include <iostream>
#include <string>
#include <functional>
#include <fstream>
#include <vector>
using namespace std;

void replaceAll(string& str, const string& from, const string& to) {
    if(from.empty())
        return;
    string wsRet;
    wsRet.reserve(str.length());
    size_t start_pos = 0, pos;
    while((pos = str.find(from, start_pos)) != string::npos) {
        wsRet += str.substr(start_pos, pos - start_pos);
        wsRet += to;
        pos += from.length();
        start_pos = pos;
    }
    wsRet += str.substr(start_pos);
    str.swap(wsRet); // faster than str = wsRet;
}

struct token{
    int index = 0;
    string type = "";
    string text = "";
    size_t line{};
    bool content(int indexg, size_t lineg, string typeg, string textg){
        index=indexg;
        type=typeg;
        text=textg;
        line=lineg;
        return true;
    }
};

struct variable{
    string name;
    string value="";
    void content(string namel, string a){
        name = namel;
        value = a;
    }
};

std::string evaluate_var(variable x, std::string text){
    string var_name = "$"+x.name;
    auto value = x.value;
    replaceAll(text,var_name,value);
    return text;
}

void out(string text, string type, int index, vector<variable> env){
    int index2 = type.length()+1;
    text.erase(index,index2);
    text.erase(0,1);
    text.pop_back();
    for(int i=0; i<env.size(); i++){
        text = evaluate_var(env[i], text);
        }
        cout << text;
    }
    

void call(string text, string type, int index, vector<variable> env){
    if(type=="out"){
        out(text,type,index,env);
    }
}

int main(int argc, const char* argv[]){
    vector<variable> env;
    ifstream progfile;
    string prog = argv[1];
    progfile.open(prog);
    string line;
    vector<token> tokens;
    
    vector<string> types;
    types.push_back("out");
    types.push_back("var");
    if(progfile.is_open()){
        int linen = 1;
        while (getline(progfile, line)){
            for(int i=0; i<types.size()-1; i++){    
                int times = 0;
                if(line.find(types[i]) != string::npos){
                    size_t index = i;
                    token a;
                    a.content(0, linen, types[i],line);
                    tokens.push_back(a);
                    linen++;
                } else{
                    char vartypes[] = {"string"};
                        if(line[0]==vartypes[0]){
                            size_t index = i;
                            token a;
                            a.content(0, linen, "var",line);
                            tokens.push_back(a);
                            linen++;
                            
                     }
        
                }
                 
            }
        }
        
        progfile.close();
        for(int i=0; i<tokens.size(); i++){
            string type = tokens[i].type;
            string text = tokens[i].text;
            int index = tokens[i].index;
            try{
                if(type!="var"){
                    call(text,type,index,env);
                } else{
                    char quotes = '"';
                    size_t equ = text.find("=");
                    string var = text.substr(0,equ);
                    var.erase(0,7);
                    var.pop_back();
                    string value = text.substr(equ+2,text.length()); 
                    if(value[0] == quotes){
                        value.erase(0,1);
                    }
                    value.pop_back();
                    variable x;
                    x.content(var,value);
                    env.push_back(x);
                }
            } catch(bad_function_call& e){
                cout << "\nNameError: Variable '" << type << "' Does Not Exist\nLine: " << tokens[i].line << endl;;
                return 0;
            }
        }
    } else{
        cout << "File could not be opened!";
    }
}