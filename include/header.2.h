
bool is_str_exist(queue <string> q, string str){
    while(!q.empty()){
        if(q.front() == str){
            return true;
        }
        q.pop();
    }
    return false;
}

bool has_the_same_ele(queue <string> q){
    string str;
    while (!q.empty()){
        str = q.front();
        q.pop();
        if(is_str_exist(q, str) == true){
            return true;
        }
    }
    return false;
}

bool is_subset_of_q(queue <string> q, queue <string> subset){
    while(!subset.empty()){
        if(is_str_exist(q,subset.front()) == false){
            return false;
        }
        subset.pop();
    }
    return true;
}

queue <string> split_string(string text, char spliter){
    queue <string> set_;
    string str = "";
    for (int i = 0; i < text.size(); i++){
        if (text[i] == spliter && str == ""){
            continue;
        } else if(text[i] == spliter){
            set_.push(str);
            str = "";
            continue;
        }
        if (text[i] == ' '){
            continue;
        }
        if (i == text.size() - 1){
            str = str + text[i];
            set_.push(str);
            continue;
        }
        str = str + text[i];
    }
    return set_;
}

string queue_to_str(queue <string> tmp, string spliter, string open, string close){
    string str = open;
    int i = 1;
    while(!tmp.empty()){
        if(i != 1){
            str += spliter;
        }
        str += tmp.front();
        i++;
        tmp.pop();
    }
    str += close;
    return str;
}



