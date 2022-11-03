#include <queue>
#include <string>

void display_queue(queue <string> tmp, string spliter){
    int i = 1;
    while (!tmp.empty()){
        if (i == 1){
            cout << tmp.front();
        } else cout << spliter << tmp.front();
        i++;
        tmp.pop();
    }
}

struct pair_state{
    bool disting = false;
    string q1, q2;
};

queue <string> get_access_state(FA fa){
    queue <string> state_access;
    queue <Transition> tmp = fa.transitionSet;
    string state;

    // get accessible state
    state_access.push(fa.startState);
    while(!tmp.empty()){
        state = tmp.front().nextState.front();
        if(state != "" && is_str_exist(state_access, state) == false){
            state_access.push(state);
        }
        tmp.pop();
    }
    return state_access;
}

// return as queue of distinguish
queue <pair_state> all_pair_from_access_state(queue <string> access_state){

    // state1 is need to pop the first ele
    queue <string> state1 = access_state;
    state1.pop();

    // state2 is need to pop the last ele
    queue <string> state2;
    int length = access_state.size();
    for(int i = 1; i <= length; i++){
        if(i != length){
            state2.push(access_state.front());
        }
        access_state.pop();
    }

    // get every pair
    pair_state pair_;
    queue <pair_state> all_pair;
    int k = state2.size(), l = 1;
    queue <string> state;

    while(!state1.empty()){
        state = state2;
        if(l <= k){
            for(int i = 1; i <= l; i++){
                pair_.q1 = state1.front();
                pair_.q2 = state.front();
                all_pair.push(pair_);
                state.pop();
            }
            l++;
        }
        state1.pop();
    }
    return all_pair;
}

void display_pair_of_state(queue <pair_state> tmp){
    pair_state p;
    while(!tmp.empty()){
        p = tmp.front();
        cout << "(" << p.q1 << "," << p.q2 << "," << p.disting << ")    ";
        tmp.pop();
    }
}


// part 2.1 of minimized-DFA
queue <pair_state> get_distinguish_pair(FA fa, queue <pair_state> all_pair){
    queue <pair_state> set_;
    pair_state p;

    while(!all_pair.empty()){
        p = all_pair.front();
        if(is_str_exist(fa.final_state, p.q1) == true && is_str_exist(fa.final_state, p.q2) == false){
            p.disting = true;
        }
        if(is_str_exist(fa.final_state, p.q2) == true && is_str_exist(fa.final_state, p.q1) == false){
            p.disting = true;
        }
        set_.push(p);
        all_pair.pop();
    }
    return set_;
}

// Transition function
queue <string> transition_state(queue <Transition> tran, string q, char character){
    while(!tran.empty()){
        if(tran.front().presentState == q && tran.front().TransitionChar == character){
            return tran.front().nextState;
        }
        tran.pop();
    }
}

// function for checking if the pair is distinguish
bool is_distinguish(queue <pair_state> all_pair, pair_state pair_){
    while(!all_pair.empty()){
        if(all_pair.front().q1 == pair_.q1 && all_pair.front().q2 == pair_.q2){
            if(all_pair.front().disting == true){
                return true;
            }
        }
        if(all_pair.front().q1 == pair_.q2 && all_pair.front().q2 == pair_.q1){
            if(all_pair.front().disting == true){
                return true;
            }
        }
        all_pair.pop();
    }
    return false;
}

queue <pair_state> modify_pair(queue <pair_state> all_pair, pair_state pair_){
    queue <pair_state> tmp;
    pair_state p;
    while(!all_pair.empty()){
        p = all_pair.front();
        if(p.q1 == pair_.q1 && p.q2 == pair_.q2){
            p.disting = true;
        } else if(p.q1 == pair_.q2 && p.q2 == pair_.q1){
            p.disting = true;
        }
        tmp.push(p);
        all_pair.pop();
    }
    return tmp;
}

// part 2.2 of minimization-DFA
queue <pair_state> part2_2(FA fa, queue <pair_state> all_pair){
    queue <Transition> tran = fa.transitionSet;
    queue <char> character;
    queue <pair_state> tmp, for_check = all_pair;
    pair_state p, pt;
    queue <string> next_q;

    while(!all_pair.empty()){
        p = all_pair.front();
        if(p.disting == false){
           character = fa.character;
            while(!character.empty()){
                next_q = transition_state(tran, p.q1,character.front());
                pt.q1 = next_q.front();
                next_q = transition_state(tran, p.q2,character.front());
                pt.q2 = next_q.front();

                if(is_distinguish(for_check, pt) == true){
                    p.disting = true;
                }
               character.pop();
            }
        }
        tmp.push(p);
        all_pair.pop();
    }
    return tmp;
}

queue <string> get_new_fa(queue <pair_state> all_pair){
    queue <string> str;
    pair_state p;
    while(!all_pair.empty()){
        p = all_pair.front();
        if(p.disting == false){

        }
        all_pair.pop();
    }
    return str;
}

// This function is used for counting the number of distinguish pair
int get_size_disting_pair(queue <pair_state> tmp){
    int k = 0;
    while(!tmp.empty()){
        if(tmp.front().disting == true){
            k++;
        }
        tmp.pop();
    }
    return k;
}

// Compare 2 pair state
bool is_same_Pair(pair_state p1,pair_state p2){
    if(p1.q1!=p2.q1){
        return false;
    }
    if(p1.q2!=p2.q2){
        return false;
    }
    if(p1.disting!=p2.disting){
        return false;
    }
    return true;
}


bool is_the_same(queue <pair_state> p1, queue <pair_state> p2){
    int k = 0, j = p1.size();

    if(p1.size() == p2.size()){

        for(int i = 1; i <= j; i++){
            if(!is_same_Pair(p1.front(),p2.front())){
                return false;
            }
            p1.pop();
            p2.pop();
        }

    } else return false;
    return true;
}

// grouping
queue <string> get_grouping_state(queue <pair_state> all_pair, queue <string> accs){
    queue <string> new_state;
    pair_state p;
    string tmp = "";
    while(!all_pair.empty()){
        p = all_pair.front();
        if(p.disting == false){
            tmp = p.q1 + ", " + p.q2;
        }
        if(tmp != "" && is_str_exist(new_state, tmp) == false){
            new_state.push(tmp);
        }
        all_pair.pop();
    }
    //cout << "\n\n";
    //display_queue(new_state, "**");

    // split all element in new_state to insert into str_tmp
    queue <string> str_tmp, str1;
    queue <string> cmp = new_state;
    string cmp1;
    while(!cmp.empty()){
        cmp1 = cmp.front();
        str1 = split_string(cmp1, ',');
        while(!str1.empty()){
            cmp1 = str1.front();
            str_tmp.push(cmp1);
            str1.pop();
        }
        cmp.pop();
    }
//    cout << "\n--> Test: ";
//    display_queue(str_tmp, ", ");
//    cout << "\n--> Front: " << str_tmp.front();
//    cout << "\n--> End: " << str_tmp.back();

    // add another state that not group into the new_state
    while(!accs.empty()){
        cmp1 = accs.front();
        if(is_str_exist(str_tmp, cmp1) == false){
            new_state.push(cmp1);
        }
        accs.pop();
    }
//    cout << "\n--> New State: ";
//    display_queue(new_state, " -- ");

    // pair new state with old state
    return new_state;
}

// struct grouping
// M state stand for Minimized state
struct M_state{
    queue <string> value;
    queue <string> group;
};


// Noted
M_state get_M_state(FA fa, queue <string> tmp1){
    M_state st;
    st.group = tmp1;

    int length = tmp1.size();
    string q = "q";

    for(int i = 0; i < length; i++){
        q = q + to_string(i) + "'";
        st.value.push(q);
        q = "q";
    }
//    cout << "\n --> Value: ";
//    display_queue(st.value, " | ");
//    cout << "\n --> Set: ";
//    display_queue(st.group, " | ");

// To do next...

//    // reset new st.group
//    queue <string> gr = st.group, tmp, new_;
//    M_state m_tmp = st;
//    string s1;
//
//    int i = 0;
//    while(!gr.empty()){
//        s1 = gr.front();
//        tmp = split_string(s1, ',');
//        while(!tmp.empty()){
//            if(tmp.front() == fa.startState){
//                i = 1;
//                new_.push(tmp.front());
//                break;
//            }
//            tmp.pop();
//        }
//        if(i == 1){
//            break;
//        }
//        gr.pop();
//    }
//
//    gr = st.group;
//    while(!gr.empty()){
//        if(gr.front() != "" && is_str_exist(new_, gr.front()) == false){
//            new_.push(gr.front());
//        }
//        gr.pop();
//    }
//
//    st.group = new_;
//    cout << "\n--> New group: ";
//    display_queue(st.group, " | ");

    return st;
}

string q_in_group_to_q(M_state m, string q){
    queue <string> tmp;
    while(!m.group.empty()){
        tmp = split_string(m.group.front(), ',');
        if(is_str_exist(tmp, q) == true){
            return m.value.front();
        }
        m.group.pop();
        m.value.pop();
    }
}

queue <Transition> get_new_transition_DFA(FA fa, M_state M){

    queue <Transition> old_t = fa.transitionSet, new_t;
    queue <char> X;
    Transition t_tmp;
    M_state m = M;
    queue <string> str, str1;
    string next_q;

    while(!m.group.empty()){
        str = split_string(m.group.front(), ',');
        X = fa.character;
        while(!X.empty()){
            str1 = transition_state(old_t, str.front(), X.front());
            t_tmp.presentState = m.value.front();
            t_tmp.TransitionChar = X.front();

            next_q = q_in_group_to_q(M, str1.front());
            //cout << next_q << endl;
            t_tmp.nextState.push(next_q);

            new_t.push(t_tmp);
            // need to pop t_tmp.nextState cuz if we don't pop we will get more state
            t_tmp.nextState.pop();
            X.pop();
        }
        m.value.pop();
        m.group.pop();
    }

    queue <Transition> transi = new_t;
//    cout << endl;
//    while(!transi.empty()){
//        cout << "\t(" << transi.front().presentState << "," << transi.front().TransitionChar << "): ";
//        display_queue(transi.front().nextState, ", ") ;
//        cout << endl;
//        transi.pop();
//    }

    return new_t;

}

FA get_first_final_new_DFA_state(FA fa, M_state M){
    string str, sq = fa.startState;
    FA new_fa;
    queue <string> fq, tmp1, tmp = M.group;

    while(!tmp.empty()){
        tmp1 = split_string(tmp.front(), ',');
        while(!tmp1.empty()){
            if(tmp1.front() == sq){
                str = q_in_group_to_q(M, tmp1.front());
                new_fa.startState = str;
            }
            if(is_str_exist(fa.final_state, tmp1.front()) == true){
                str = q_in_group_to_q(M, tmp1.front());
                if(is_str_exist(fq, str) == false){
                    fq.push(str);
                }
            }
            tmp1.pop();
        }
        tmp.pop();
    }
    new_fa.final_state = fq;
//    cout << "\n--> Start q: " << new_fa.startState;
//    cout << "\n--> Final q: ";
//    display_queue(new_fa.final_state, ", ");

    return new_fa;
}

bool is_all_pair_distinguish(queue <pair_state> all_pair){
    while(!all_pair.empty()){
        if(all_pair.front().disting == false){
            return false;
        }
        all_pair.pop();
    }
    return true;
}

// Main minimized funciton
FA Minimized(FA FA1){
    FA fa1 = FA1;

//    display(FA1);

    queue <string> access_state;
    access_state = get_access_state(FA1);
//    cout << "> Access state: ";
//    display_queue(access_state, ",");

    // all pair
    queue <pair_state> all_pair;
    queue <pair_state> pre_all_pair;

    all_pair = all_pair_from_access_state(access_state);
//    cout << "\n\n--> All pair: " << all_pair.size();
//    cout << endl << "> All pair...\n";
//    display_pair_of_state(all_pair);

    // all distinguish pair
    all_pair = get_distinguish_pair(FA1, all_pair);
//    cout << "\n\n--> Number of all pair: " << get_size_disting_pair(all_pair);
//    cout << endl << "\n> All distinguish pair... \n";
//    display_pair_of_state(all_pair);

    int i = 2;
    do{
        pre_all_pair = all_pair;
//        cout<<pre_all_pair.size()<<" : "<<all_pair.size();
        all_pair = part2_2(FA1, all_pair);
//        cout << "\n\n--> Number of all pair: " << get_size_disting_pair(all_pair);
//        cout << endl << "\n> part 2." << i << " ...\n";
//        display_pair_of_state(all_pair);
        i++;
    } while(!is_the_same(all_pair, pre_all_pair) );


    if (is_all_pair_distinguish(all_pair) == true){
        if (isEqual(FA1.Q, access_state) == true){
            return fa1;
        }
    };

    queue <string> tmp;
    queue <Transition> t;

    tmp = get_grouping_state(all_pair, access_state);

    M_state m;
    m = get_M_state(FA1, tmp);
    t = get_new_transition_DFA(FA1, m);

    // fa has final and start
    FA fa;

    fa = get_first_final_new_DFA_state(FA1, m);
    fa.transitionSet = t;
    fa.character = FA1.character;
    fa.Q = m.value;
    fa.discription=FA1.discription;
    if(!isFAEqual(fa,Minimized(fa))){
            fa=Minimized(fa);
    }
    return fa;
}
