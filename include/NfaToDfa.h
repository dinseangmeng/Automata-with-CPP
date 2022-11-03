#include <iostream>
#include <queue>
#include <conio.h>
#include <iomanip>
#include <string>
using namespace std;

bool isTransitionFired(struct FA FAtmp,string state){//work only on dfa
    char arr[FAtmp.character.size()];
    int j=FAtmp.character.size();
    for(int i=0;!FAtmp.character.empty();i++){
        arr[i]=FAtmp.character.front();
            FAtmp.character.pop();
    }
    int x=0,k=0;

    for(int i=0;!FAtmp.transitionSet.empty();i++){
        if(FAtmp.transitionSet.front().presentState==state &&
           FAtmp.transitionSet.front().TransitionChar==arr[x]){
                k=1;
                x++;
           }
        if(k==1 && x==j){
            return true;
        }
        FAtmp.transitionSet.pop();
    }
    return false;
};




bool isExistInRepresentSet(queue <string> StrTmp,queue <newRepresentState> RTmp){
    while(!RTmp.empty()){
        if(isEqual(StrTmp,RTmp.front().setOfState)){
            return true;
        }
        RTmp.pop();
    }
    return false;
};
struct newRepresentState StringRepresent(queue <string> StrTmp,queue <newRepresentState> RTmp){
    while(!RTmp.empty()){
        if(isEqual(StrTmp,RTmp.front().setOfState)){
            return RTmp.front();
        }
        RTmp.pop();
    }
};



bool isExist_Specail(queue<string>str,string text){
    queue <string>str_1=StringSplit(text,',');
    for(int i=0;!str.empty();i++){
        if(isEqual(str_1,StringSplit(str.front(),','))){
            return true;
        }
        str.pop();
    }
    return false;
}



queue <string> setOfNextStateOfMultiplePre_state(queue <Transition> tr,queue<string> presentState,char transitionChar)
{
    queue <string> str_tmp;
    while(!presentState.empty()){
        str_tmp=QueueStringAdder(str_tmp,setOfNextState(tr,presentState.front(),transitionChar));
        presentState.pop();
    }
    return str_tmp;
};

struct newRepresentState StringRepresentByvalue(string StrTmp,queue <newRepresentState> RTmp){
    while(!RTmp.empty()){
        if(RTmp.front().value==StrTmp){
            return RTmp.front();
        }
        RTmp.pop();
    }
};




void clearQueueString(queue <string>*tmp){
    for(int i=0;!(*tmp).empty();i++){
        (*tmp).pop();
    }
}
queue <string> ECLOSURE(string presentState,queue<Transition>tr){
    char ch=172;
    int k;
    queue<string>str_tmp,str;
    string text;
    str=QueueStringAdder(str,StringSplit(presentState,','));
    str_tmp=setOfNextState(tr,presentState,ch);
    str=QueueStringAdder(str,str_tmp);
    k=QueueStringTOString(setOfNextState(tr,QueueStringTOString(str_tmp,','),ch),',')!="";
    k*=QueueStringTOString(setOfNextState(tr,QueueStringTOString(str_tmp,','),ch),',')!=" ";
    while(k){
        str_tmp=setOfNextState(tr,QueueStringTOString(str_tmp,','),ch);
        str=QueueStringAdder(str,str_tmp);
        k=QueueStringTOString(setOfNextState(tr,QueueStringTOString(str_tmp,','),ch),',')!="";
        k*=QueueStringTOString(setOfNextState(tr,QueueStringTOString(str_tmp,','),ch),',')!=" ";
    }
    return str;
}

queue <string> ECLOSURESet(queue<string> presentState,queue<Transition>tr){
    queue<string>str;
    while(!presentState.empty()){
        str=QueueStringAdder(str,ECLOSURE(presentState.front(),tr));
        presentState.pop();
    }
    return str;
}

queue <string> purify(queue<string> str){
    queue <string> str_tmp,str_1;
    for(int i=0;i<str.size();i++){
        str_1=StringSplit(getStateByPos(str,i),',');
        for(int j=0;j<str_1.size();j++){
            if(!isExist(str_tmp,getStateByPos(str_1,j))){
                str_tmp.push(getStateByPos(str_1,j));
            }
        }
    }
    return str_tmp;
}

FA NfaToDfa(struct FA FA1){
    if(isNfa(FA1)){
        //displayString(ECLOSURE("q3",FA1.transitionSet));

        struct FA FATmp;
        FATmp.discription=FA1.discription;
        int k=0;
        char ch=172;
        string text;
        queue <newRepresentState> RTmp;
        struct newRepresentState RTmp_1;
        FATmp.character=FA1.character;
        struct Transition TR_tmp;
        queue <string> StrTmp,Str,Str_1;

        Str=ECLOSURE(FA1.startState,FA1.transitionSet);
        FATmp.Q.push(QueueStringTOString(Str,','));
        FATmp.startState=QueueStringTOString(Str,',');

        for(int i=0;i<FATmp.Q.size();i++){
            StrTmp=StringSplit(getStateByPos(FATmp.Q,i),',');
            for(int j=0;j<FATmp.character.size();j++){
                Str=setOfNextStateOfMultiplePre_state(FA1.transitionSet,StrTmp,GetCharWithPos(FATmp.character,j));
                Str=purify(Str);

                Str_1=ECLOSURESet(Str,FA1.transitionSet);

                //displayString(Str);

                text=QueueStringTOString(Str_1,',');
                if(!isExist_Specail(FATmp.Q,text)){
                    FATmp.Q.push(text);
                };
            }

        }

        clearQueueString(&Str);
        for(int i=0;i<FATmp.Q.size();i++){
            text="q";
            StrTmp=StringSplit(getStateByPos(FATmp.Q,i),',');
            text+=to_string(k)+"'";
            k++;

            RTmp_1.value=text;
            RTmp_1.setOfState=StringSplit(getStateByPos(FATmp.Q,i),',');
            RTmp.push(RTmp_1);

        }



        for(int i=0;i<FATmp.Q.size();i++){
            StrTmp=StringSplit(getStateByPos(FATmp.Q,i),',');
            Str.push(StringRepresent(StrTmp,RTmp).value);
        }
        FATmp.Q=Str;

        clearQueueString(&Str);
        for(int i=0;i<FATmp.Q.size();i++){
            clearQueueString(&Str);
            Str=StringRepresentByvalue(getStateByPos(FATmp.Q,i),RTmp).setOfState;
            while(!Str.empty()){
                if(isExist(FA1.final_state,Str.front())){
                    FATmp.final_state.push(getStateByPos(FATmp.Q,i));
                    break;
                }
                Str.pop();
            }

        }

        Str=StringSplit(FATmp.startState,',');
        FATmp.startState=StringRepresent(Str,RTmp).value;




        clearQueueString(&StrTmp);



        for(int i=0;i<FATmp.Q.size();i++){
            text=getStateByPos(FATmp.Q,i);
            StrTmp=StringRepresentByvalue(text,RTmp).setOfState;
            for(int j=0;j<FATmp.character.size();j++){
                Str=setOfNextStateOfMultiplePre_state(FA1.transitionSet,
                                                  StrTmp,GetCharWithPos(FATmp.character,j));
                Str=purify(Str);
                Str_1=ECLOSURESet(Str,FA1.transitionSet);
                Str=StringSplit((StringRepresent(Str_1,RTmp).value),',');
                TR_tmp.nextState=Str;
                TR_tmp.presentState=text;
                TR_tmp.TransitionChar=GetCharWithPos(FATmp.character,j);
                FATmp.transitionSet.push(TR_tmp);
            }

        }


        return FATmp;
    }else{
        return FA1;
    }

};
