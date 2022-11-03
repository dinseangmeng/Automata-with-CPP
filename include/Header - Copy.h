#include <iostream>
#include <queue>
#include <conio.h>
#include <iomanip>
#include <TextTable.h>
using namespace std;
struct newRepresentState{
    string value;
    queue<string> setOfState;
};


struct Transition{
    string presentState;
    char TransitionChar;
    queue <string> nextState;
};
struct FA{
    queue<string> Q;
    string startState;
    queue<string>final_state;
    queue <char> character;
    queue<Transition>transitionSet;
    string discription;
};

bool isEmpty(struct FA FA1){
    int k=FA1.character.empty();
    k*=FA1.final_state.empty();
    k*=FA1.Q.empty();
    k*=FA1.startState=="";
    k*=FA1.transitionSet.empty();
    return k;
}
queue<string> StringSplit(string text,char separator){
    queue <string> tmp;
    string tmpText="";
    for(int i=0;i<text.size();i++){
        if(text[i]==separator ){
            tmp.push(tmpText);
            tmpText="";
            continue;
        }
        if(text[i] == ' '){
            continue;
        }
        if(i==text.size()-1){
            tmpText+=text[i];
            tmp.push(tmpText);
            tmpText="";
            continue;
        }
        tmpText+=text[i];
    }
    return tmp;
};
string getStateByPos(queue <string> q,int pos){
    if(pos>0 && pos<q.size()){
        for(int i=0;i<pos;i++){
            q.pop();
        }
        return q.front();
    }else{
        return q.front();
    }
};
bool isduplicate(string text,char separator){
    queue <string> str=StringSplit(text,separator);
    queue <string> str_1=StringSplit(text,separator);
    for(int i=0;i<str.size();i++){
        for(int j=0;j<str_1.size();j++){
            if(i!=j){
                if(getStateByPos(str,i)==getStateByPos(str_1,j)){
                    return true;
                }
            }
        }
    }

    return false;

}

bool isExist(queue <string> Qset,string text){
    while(!Qset.empty()){
        if(text==Qset.front()){
            return true;
        }
        Qset.pop();
    }
    return false;
};

FA getInput(){
    struct FA FA;

    int k=0;
    string state;
    char separator=' ';
    cout<<"\nInput your State(separate by space):";
    getline(cin,state);
    while(isduplicate(state,separator)){
        cout<<"State has been duplicate:";
        getline(cin,state);
    }
    while(state=="" || state==" "){
        cout<<"State can't be Empty\n\tInput again:";
        cout<<"\n\t\ttry again:";
        getline(cin,state);
    };

    FA.Q=StringSplit(state,separator);
    string strArr[FA.Q.size()];
    queue<string> stringTmp=FA.Q;
    for(int i=0;!stringTmp.empty();i++){
        strArr[i]=stringTmp.front();
        stringTmp.pop();
    }

    cout<<"Which one is your Start state:";
    do{
        cin>>state;
        if(isExist(FA.Q,state)){
            FA.startState=state;
        }else{
            cout<<"Start State not Exist in all state!!\n";
            cout<<"\t\tInput again:";
            cin>>state;
        }
    }while(!isExist(FA.Q,state));
    k=0;
    cout<<"Input your Final state:";
    cin.ignore(1,'\n');
    do{
        getline(cin,state);
        while(isduplicate(state,separator)){
            cout<<"State has been duplicate:";
            cout<<"\n\t\ttry again:";
            getline(cin,state);
        }
        while(state==""||state==" "){
            cout<<"Final state can't be Empty\n\tInput again:";
            getline(cin,state);
        }
        queue<string> tmp=StringSplit(state,separator);
        while(!tmp.empty()){
            k=isExist(FA.Q,tmp.front());
            if(!k){
                break;
            }
            tmp.pop();
        }
        if(k){
            FA.final_state=StringSplit(state,separator);
        }else{
            cout<<"Final State not Exist in all state!!\n";
            cout<<"Input again:";
            cin>>state;
            tmp=StringSplit(state,' ');
            while(!tmp.empty()){
                k=isExist(FA.Q,tmp.front());
                if(!k){
                    break;
                }
                tmp.pop();
            }
        }
    }while(!k);
    cout<<"Input character:";
    char ch;
    while(1){
        cin>>ch;
        FA.character.push(ch);
        if(cin.get()=='\n'){
            break;
        }
    };
    queue <char> ChTmp=FA.character;
    char chArr[ChTmp.size()];
    for(int i=0;!ChTmp.empty();i++){
        chArr[i]=ChTmp.front();
        ChTmp.pop();
    }
    cout<<"Input transition:";
    for(int i=0;i<FA.Q.size();i++){
        for(int j=0;j<FA.character.size();j++){
            cout<<"\n\t{"<<strArr[i]<<","<<chArr[j]<<"}:";
            k=0;
            int y=0;
            do{
                getline(cin,state);
                while(state==""||state==" "){
                    cout<<"\n\t\tNext is gonna be empty!";
                    cout<<"\n\t\tAre you sure?";
                    cout<<"\n\t\tPress any key to continue| Esc to re-input\n";
                    if(_getch()==27){
                        cout<<"\n\t\tTry again:";
                        getline(cin,state);
                    }else{
                        y=1;
                        break;
                    }
                }
                if(y==0){
                    queue<string> tmp=StringSplit(state,' ');
                    while(!tmp.empty()){
                        k=isExist(FA.Q,tmp.front());
                        if(!k){
                            break;
                        }
                        tmp.pop();
                    }
                    if(k){
                        struct Transition tr;
                        tr.presentState=strArr[i];
                        tr.TransitionChar=chArr[j];
                        tr.nextState=StringSplit(state,separator);
                        FA.transitionSet.push(tr);
                    }else{
                        cout<<"Next State not Exist in all state!!\n";
                        cout<<"Input again:";
                        getline(cin,state);
                        queue<string> tmp=StringSplit(state,separator);
                        while(!tmp.empty()){
                            k=isExist(FA.Q,tmp.front());
                                if(!k){
                                    break;
                                }
                                tmp.pop();
                        }
                        if(k){
                            struct Transition tr;
                            tr.presentState=strArr[i];
                            tr.TransitionChar=chArr[j];
                            tr.nextState=StringSplit(state,separator);
                            FA.transitionSet.push(tr);
                        }

                    }
                }else{
                    struct Transition tr;
                    tr.presentState=strArr[i];
                    tr.TransitionChar=chArr[j];
                    tr.nextState.push("");
                    FA.transitionSet.push(tr);
                    y=0;
                    break;
                }
            }while(!k);

        }
        char cha=172;
        cout<<"\n\t{"<<strArr[i]<<","<<"epsilon"<<"}:";
            k=0;
            int y=0;
            do{
                getline(cin,state);
                while(state==""||state==" "){
                    cout<<"\n\t\tNext is gonna be empty!";
                    cout<<"\n\t\tAre you sure?";
                    cout<<"\n\t\tPress any key to continue| Esc to re-input\n";
                    if(_getch()==27){
                        cout<<"\n\t\tTry again:";
                        getline(cin,state);
                    }else{
                        y=1;
                        break;
                    }
                }
                if(y==0){
                    queue<string> tmp=StringSplit(state,separator);
                    while(!tmp.empty()){
                        k=isExist(FA.Q,tmp.front());
                        if(!k){
                            break;
                        }
                        tmp.pop();
                    }
                    if(k){
                        struct Transition tr;
                        tr.presentState=strArr[i];
                        tr.TransitionChar=cha;
                        tr.nextState=StringSplit(state,separator);
                        FA.transitionSet.push(tr);
                    }else{
                        cout<<"Next State not Exist in all state!!\n";
                        cout<<"Input again:";
                        getline(cin,state);
                        queue<string> tmp=StringSplit(state,separator);
                        while(!tmp.empty()){
                            k=isExist(FA.Q,tmp.front());
                                if(!k){
                                    break;
                                }
                                tmp.pop();
                        }
                        if(k){
                            struct Transition tr;
                            tr.presentState=strArr[i];
                            tr.TransitionChar=cha;
                            tr.nextState=StringSplit(state,separator);
                            FA.transitionSet.push(tr);
                        }

                    }
                }else{
                    struct Transition tr;
                    tr.presentState=strArr[i];
                    tr.TransitionChar=cha;
                    tr.nextState.push("");
                    FA.transitionSet.push(tr);
                    y=0;
                    break;
                }
            }while(!k);

    }
    cout<<"\n\tInput your discription: ";
    getline(cin,state);
    while(state==""||state==" "){
        cout<<"\n\t\tDiscription gonna be Empty!";
        cout<<"\n\t\tAre you sure?";
        cout<<"\n\t\tPress any key to continue| Esc to re-input\n";
        if(_getch()==27){
            cout<<"\n\t\tTry again:";
            getline(cin,state);
        }else{
            break;
        }
    };
    FA.discription=state;
    return FA;
};

queue <string> QueueStringAdder(queue <string> str_1,queue<string> str_2){
    queue<string> str_tmp;
    while(!str_1.empty()){
        if(str_1.front()!="" && str_1.front()!=" "){
            str_tmp.push(str_1.front());
        }
        str_1.pop();
    }
    while(!str_2.empty()){
        if(!isExist(str_tmp,str_2.front())){
            if(str_2.front()!="" && str_2.front()!=" "){
                str_tmp.push(str_2.front());
            }

        }
        str_2.pop();
    }
    return str_tmp;
};
queue<string> setOfNextState(queue <Transition> tr,string presentState,char transitionChar){
    queue<string> str;
    if(transitionChar==172){
        str.push(presentState);

    }
    while(!tr.empty()){
        if(tr.front().presentState==presentState &&
            tr.front().TransitionChar==transitionChar){
                str=QueueStringAdder(str,tr.front().nextState);
            break;
           };
        tr.pop();
    }
    return str;
};

bool isEpsilonNfa(struct FA FA1){
    char ch=172;
    for(int i=0;i<FA1.Q.size();i++){
        if(setOfNextState(FA1.transitionSet,getStateByPos(FA1.Q,i),ch).size()>0 &&
           setOfNextState(FA1.transitionSet,getStateByPos(FA1.Q,i),ch).front()!=""&&
           setOfNextState(FA1.transitionSet,getStateByPos(FA1.Q,i),ch).front()!=" "){
            return true;
        };
    }
    return false;
}
bool isNfa(struct FA tmp){
    if(isEpsilonNfa(tmp)){
        return true;
    }
    while(!tmp.transitionSet.empty()){
        if(tmp.transitionSet.front().nextState.size()>1){
            return true;
        }
        tmp.transitionSet.pop();
    }
    return false;
}





void displayString(queue<string> tmp){
    for(int i=0;!tmp.empty();i++){
        if(i==0){
            cout<<"\""<<tmp.front()<<"\"";
        }else{
            cout<<",\""<<tmp.front()<<"\"";
        }
        tmp.pop();
    }
}
queue <Transition> copyTransitionButIgnore(queue<Transition> tr,char ignore){
    queue <Transition> TR_TMP;
    struct Transition tr_tmp;
    while(!tr.empty()){
        if(tr.front().TransitionChar!=ignore){
            tr_tmp.nextState=tr.front().nextState;
            tr_tmp.presentState=tr.front().presentState;
            tr_tmp.TransitionChar=tr.front().TransitionChar;
            TR_TMP.push(tr_tmp);
        }
        tr.pop();
    }
    return TR_TMP;
};
void display(struct FA tmp,int Break=1){
    TextTable t( '-', '|', '+' );
    t.add("");
    if(Break){
        cout<<"\n";
    }
    if(isNfa(tmp)){

        cout<<"\t\tNFA TABLE: ";
    }else{
        cout<<"\t\tDFA TABLE: ";

    }
    cout<<tmp.discription<<"\n";
    int k;
    queue <Transition> tr;
    if(isNfa(tmp)&& isEpsilonNfa(tmp)){
        k=tmp.character.size()+1;
        tr=tmp.transitionSet;
    }else{
        k=tmp.character.size();
        tr=copyTransitionButIgnore(tmp.transitionSet,172);
    }
    string text="";
    cout<<"\t\t";
    while(!tmp.character.empty()){
        text="";
        text+=tmp.character.front();
        t.add("     "+text+"     ");
        tmp.character.pop();
    }
    text="";
    if(isNfa(tmp) && isEpsilonNfa(tmp)){
        t.add("  epsilon  ");

    }
    t.endOfRow();
    cout<<endl;
    while(!tmp.Q.empty()){
            if(isExist(tmp.final_state,tmp.Q.front()) && tmp.Q.front()==tmp.startState){
                t.add("  *->"+tmp.Q.front()+"  ");
            }else if(isExist(tmp.final_state,tmp.Q.front())){
                t.add("    *"+tmp.Q.front()+"  ");
            }else if(tmp.Q.front()==tmp.startState){
                t.add("   ->"+tmp.Q.front()+"  ");
            }
            else{
                t.add("     "+tmp.Q.front()+"  ");
            }


        for(int i=0;i<k;i++){
            text="";
            int y=tr.front().nextState.size();
            if(y==0){
                text="";
            }else if(y==1){
                text=tr.front().nextState.front();
            }else{
                for(int j=0;j<y;j++){
                    if(j==0){
                        text+=tr.front().nextState.front()+",";
                    }else if(j==y-1){
                        text+=tr.front().nextState.front();
                    }else{
                        text+=tr.front().nextState.front()+",";
                    }
                    tr.front().nextState.pop();
                }
            }
            t.add("    "+text+"    ");

            tr.pop();
        }
        t.endOfRow();
        tmp.Q.pop();
    }
    cout << t;

}
bool isEqual(queue<string>SetOfString_1,queue<string> SetOfString_2){
    if(SetOfString_1.size()==SetOfString_2.size()){
        int x=SetOfString_1.size();
        string arr_1[x];
        string arr_2[x];
        int check[x],lastIndex=-2;
        for(int i=0;!SetOfString_1.empty();i++){
            arr_1[i]=SetOfString_1.front();
            arr_2[i]=SetOfString_2.front();
            check[i]=0;
            SetOfString_1.pop();
            SetOfString_2.pop();
        }

        for(int i=0;i<x;i++){
            for(int j=0;j<x;j++){
                if(j!=lastIndex){
                    if(arr_1[i]==arr_2[j]){
                        check[i]=1;
                        lastIndex=j;
                        continue;
                    }
                }
            }
        }
        for(int i=0;i<x;i++){
            if(check[i]==0){
                return false;
            }
        }
        return true;
    }else{
        return false;
    }
};

string QueueStringTOString(queue<string>Str,char separator){
    string text="";
    int k=0;
    for(int i=0;!Str.empty();i++){
        if(Str.front()!="" && Str.front()!=" "){
            if(k==0){
                text+=Str.front();
            }else{
                text+=separator+Str.front();
            }
            k++;
        }
        Str.pop();
    }
    return text;

};

void displayRepresent(queue <newRepresentState>Rtmp ){
    while(!Rtmp.empty()){
        cout<<Rtmp.front().value<<"\t";
        cout<<QueueStringTOString(Rtmp.front().setOfState,',');
        cout<<"\n";
        Rtmp.pop();
    }
}

void displayTransition(queue <Transition> tr){
    while(!tr.empty()){
        cout<<"{"<<tr.front().presentState<<","<<tr.front().TransitionChar<<"}:";
        while(!tr.front().nextState.empty()){
            cout<<tr.front().nextState.front()<<" ";
            tr.front().nextState.pop();
        }
        tr.pop();
    }
}

void Zero(int arr[],int Size){
    for(int i=0;i<Size;i++){
        arr[i]=0;
    }
}

bool isTransitionEqual(Transition TR1,Transition TR2){
    if(TR1.presentState==TR2.presentState){
        if(TR1.TransitionChar==TR2.TransitionChar){
            if(isEqual(TR1.nextState,TR2.nextState)){
                return true;
            }
        }
    }
    return false;
}
void displayArray(int arr[],int Size){
    for(int i=0;i<Size;i++){
        cout<<arr[i]<<" ";
    }
}
bool isSetTransitionEqual(queue<Transition>TR1,queue<Transition> TR2){
    if(TR1.size()!=TR2.size()){
        return false;
    }
    Transition TRARR_1[TR2.size()];
    Transition TRARR_2[TR2.size()];
    int x=TR1.size(),arr[x],lastIndex=-2;
    Zero(arr,x);
    for(int i=0;!TR2.empty();i++){
        TRARR_1[i]=TR1.front();
        TRARR_2[i]=TR2.front();
        TR2.pop();
        TR1.pop();
    }

    for(int i=0;i<x;i++){
        for(int j=0;j<x;j++){
            if(j!=lastIndex){
                if(isTransitionEqual(TRARR_1[i],TRARR_2[j])){
                    arr[i]=1;
                    lastIndex=j;
                    continue;
                }
            }
        }
    }
    for(int i=0;i<x;i++){
        if(arr[i]==0){
            return false;
        }
    }
    return true;
}

bool isFAEqual(FA FA1,FA FA2){
    int arr[5];
    Zero(arr,5);
    if(isEqual(FA1.Q,FA2.Q)){
        arr[0]=1;
    }
    if(FA1.startState==FA2.startState){
        arr[1]=1;
    }
    if(isEqual(FA1.final_state,FA2.final_state)){
        arr[2]=1;
    }
    if(FA1.character==FA2.character){
        arr[3]=1;
    }
    if(isSetTransitionEqual(FA1.transitionSet,FA2.transitionSet)){
        arr[4]=1;
    }
    for(int i=0;i<5;i++){
        if(arr[i]==0){
            return false;
        }
    }
    return true;

}
