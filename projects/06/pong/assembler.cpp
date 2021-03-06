#include <bits/stdc++.h>

using namespace std;

string fileInput;
string fileOutput;



//----------------------------DetectSymbol------------------------------------------

#define msi map<string,int>
//------------------------------prototype-----------------------------------------
//detectTable
void dectectSymbol(vector <string>& content);
//symbol_table_init
    void symbol_table_init(msi&);    
//detect (xxx) - label 
    //helper function:
    string getInParenthesis(const string& s);
    void detectLabel(vector <string>& line,msi& symTable);
//detect (@d+) - variable
    //helper function:
    bool isNumber(const string& s);
    void detectVariable(vector <string>& line,msi& symTable);
//--------------------------------------------------------------------------------

void symbol_table_init(msi& symbolTable){
    for (int i = 0; i < 16; ++i){
        string name = "R" + to_string(i);
        symbolTable[name] = i;
    }
    symbolTable["SCREEN"] = 16348;
    symbolTable["KBD"] = 24576;
    
    symbolTable["SP"] = 0;
    symbolTable["LCL"] = 1;
    symbolTable["ARG"] = 2;
    symbolTable["THIS"] = 3;
    symbolTable["THAT"] = 4;
}

string getInParenthesis(const string& s){
    string res = "";
    for (auto c : s){
        if (c == '(' || c == ')'){
            continue;
        }
        res += c;
    }
    return res;
}

bool isNumber(const string& s){
    for (auto c : s){
        if (c < '0' || c > '9'){
            return false;
        }
    }
    return true;
}

void detectLabel(vector <string>& line, msi& symTable){
    vector <string> res;
    int check = 0;
    for (int i = 0; i < line.size(); ++i){
        if (line[i][0] == '('){
            string label = getInParenthesis(line[i]);
            symTable[label] = i - check++;
        }
        else {
            res.push_back(line[i]);
        }
    }
    line.clear();
    line = move(res);
}

void detectVariable(vector <string>& line,msi& symTable,int& process_mem){
    for (int i = 0; i < line.size(); ++i){
        if (line[i][0] == '@'){
            string detect = line[i].substr(1);
            if (!isNumber(detect)){
                if (symTable.find(detect) == symTable.end()){
                    symTable[detect] = process_mem++;
                }
                line[i].clear();
                line[i] = '@' + to_string(symTable[detect]);
            }
        }
    }
}


msi SymTable(vector<string>& line){
    msi symtable;
    symbol_table_init(symtable);
    int process_mem = 16;
    detectLabel(line,symtable);
    detectVariable(line,symtable,process_mem);
    return symtable;
}

//-----------------------------------------------------------------------------------

//------------------------preprocessing---------------------------------------------

bool delete_partial(string& cmd){
    if (cmd == ""){
        return true;
    }
    if (cmd[0] == '/'){
        return true;
    }
    string res = "";
    for (auto c : cmd){
        if (c == ' '){
            continue;
        }
        if (c == '/'){
            break;
        }
        res += c;
    }
    cmd.clear();
    cmd = res;
    return false;
}

vector <string> preprocessing(){
    vector <string> res;
    string line;
    while(getline(cin,line)){
        if (delete_partial(line) == true){
            continue;
        }
        res.push_back(line);
    }
    return res;
}

//-----------------------------------------------------------------------------------

//------------------------------convertBin-------------------------------------------

#define mss map<string,string>

//---------------prototype---------------------------------------
//init
void convertBin(vector <string>&);

//make-symbolTable
    void init_table(mss&, mss&, mss&);
//A-instruction
    void processA(string&);

//C-instruction
//helper function:
    //parser
    vector <string> parser(const string&);
    void processC(string&,mss&,mss&,mss&);
//----------------------------------------------------------------

//--------------------------implement-----------------------------
//initSymbolTable
void init_table(mss& destTable, mss& compTable, mss& jumpTable){
    //------------------destTable---------------------------------
    destTable[""]    =  "000";
    destTable["M"]   =  "001";
    destTable["D"]   =  "010";
    destTable["MD"]  =  "011";
    destTable["A"]   =  "100";
    destTable["AM"]  =  "101";
    destTable["AD"]  =  "110";
    destTable["AMD"] =  "111";
    
    //------------------compTable---------------------------------
    compTable["0"]   = "0101010";
    compTable["1"]   = "0111111";
    compTable["-1"]  = "0111010";
    compTable["D"]   = "0001100";
    compTable["A"]   = "0110000";
    compTable["!D"]  = "0001101";
    compTable["!A"]  = "0110001";
    compTable["-D"]  = "0001111";
    compTable["-A"]  = "0110011";
    compTable["D+1"] = "0011111";
    compTable["A+1"] = "0110111";
    compTable["D-1"] = "0001110";
    compTable["A-1"] = "0110010";
    compTable["D+A"] = "0000010";
    compTable["D-A"] = "0010011";
    compTable["A-D"] = "0000111";
    compTable["D&A"] = "0000000";
    compTable["D|A"] = "0010101";
    compTable["M"]   = "1110000";
    compTable["!M"]  = "1110001";
    compTable["-M"]  = "1110011";
    compTable["M+1"] = "1110111";
    compTable["M-1"] = "1110010";
    compTable["D+M"] = "1000010";
    compTable["D-M"] = "1010011";
    compTable["M-D"] = "1000111";
    compTable["D&M"] = "1000000";
    compTable["D|M"] = "1010101";
    
    //------------------jumpTable---------------------------------
    jumpTable[""]    = "000";
    jumpTable["JGT"] = "001";
    jumpTable["JEQ"] = "010";
    jumpTable["JGE"] = "011";
    jumpTable["JLT"] = "100";
    jumpTable["JNE"] = "101";
    jumpTable["JLE"] = "110";
    jumpTable["JMP"] = "111";   
}

int stoi(string& s){
    int number = 0;
    int ten = 1;
    for (int i = s.length() - 1; i >= 0; i--){
        number = number + ten * int(s[i] - '0');
        ten = ten * 10;
    }
    return number;
}

//A-instruction
void processA(string& s){
    bitset <16> bits(stoi(s));
    //1
    if (s == "16348"){
        bits = bitset <16>(0);
        bits.set(14,1);
    }
    s.clear();
    s = bits.to_string();
}

//dest=comp;jump
//vector has 3 element
vector <string> parser(const string& line){
    string element = "";
    vector <string> res;
    for (auto c : line){
        if (c == '='){
            res.push_back(element);
            element = "";
        }
        else if (c == ';') {
            if (res.empty()) res.push_back("");
            res.push_back(element);
            element = "";
        }
        else {
            element += c;
        }
    }
    res.push_back(element);
    while (res.size() < 3){
        res.push_back("");
    }
    return res;
}

void processC(string& s,mss& destTable,mss& compTable,mss& jumpTable){
    string res = "111";
    vector <string> component = parser(s);
    res += compTable[component[1]];
    res += destTable[component[0]];
    res += jumpTable[component[2]];   
    s.clear();
    s = res;
}

void convertBin(vector <string>& cmd){
    mss destTable,compTable,jumpTable;
    init_table(destTable,compTable,jumpTable);
    for (auto& line : cmd){
        //A instruction
        if (line[0] == '@'){
            string save = line;
            save = save.substr(1);
            processA(save);
            line = save;
        }
        else {
            string save = line;
            processC(save,destTable,compTable,jumpTable);
            line = save;
        }
    }
}


//-----------------------------------------------------------------------------------

void IOProcessing(){
    cin >> fileInput;
    freopen(fileInput.c_str(), "r", stdin);
    
    
    fileOutput = fileInput;
    int n = fileOutput.size();
    fileOutput = fileOutput.substr(0,n - 3);
    fileOutput += "hack";
    
    freopen(fileOutput.c_str(), "w", stdout);
}

int main(){
    IOProcessing();
    vector <string> line = preprocessing();
    // for (auto& l : line){
    //     cout << l << endl;
    // }
    msi symTable = SymTable(line);
    convertBin(line);
    
    for (int i = 0; i < line.size(); ++i){
        cout << line[i];
        if (i != line.size() - 1){
            cout << endl;
        }
    }
    return 0;
}