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
        if (c == '=' || c == ';'){
            res.push_back(element);
            element = "";
            continue;
        }
        element += c;
    }
    while (res.size() < 3){
        res.push_back("");
    }
    return res;
}

void processC(string& s,mss& destTable,mss& compTable,mss& jumpTable){
    string res = "111";
    vector <string> component = parser(s);
    res += destTable[component[0]];
    res += destTable[component[1]];
    res += destTable[component[2]];   
    s.clear();
    s = res;
}

void converBin(vector <string>& cmd){
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
        }
    }
}
