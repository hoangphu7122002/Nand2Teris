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
    symbolTable["Screen"] = 16348;
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
            symTable[label] = i + 1;
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
    return symtable;
}
