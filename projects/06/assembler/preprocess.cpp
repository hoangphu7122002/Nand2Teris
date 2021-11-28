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