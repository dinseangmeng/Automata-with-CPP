#include <iostream>
#include <queue>
#include <conio.h>
#include <iomanip>
#include <mysql.h>
using namespace std;



MYSQL* connection(){
    MYSQL *connector;
    connector=mysql_init(0);
    connector=mysql_real_connect(connector,"localhost","root","","FiniteAutoMata",3306,NULL,0);
    if(!connector){
        cout<<"\n Fail to Connect data base!\n";

    }
    return connector;
}

string TransitionToString(queue<Transition> tr){
    string text="";
    char ch=172;
    int k=tr.size(),x;
    for(int i=0;i<k;i++){
        text+=tr.front().presentState+","+
        tr.front().TransitionChar+":";
        if(tr.front().nextState.size()==1
           && tr.front().nextState.front()==""
           || tr.front().nextState.front()==" "){
            text+=ch;
        }else{
            text+=QueueStringTOString(tr.front().nextState,',');

        }
        if(i<k-1){
            text+="#";
        }
        tr.pop();
    }

    return text;
}

queue <Transition> StringToTransition(string text){
    queue<Transition>TR_TMP;
    struct Transition tr;
    char ch=172;
    queue<string>str,str_1,input,output;
    str=StringSplit(text,'#');
    for(int i=0;i<str.size();i++){
        str_1=StringSplit(getStateByPos(str,i),':');
        input=StringSplit(getStateByPos(str_1,0),',');
        output=StringSplit(getStateByPos(str_1,1),',');
        int x=output.front()[0]==ch;

        if(x){
            tr.presentState=getStateByPos(input,0);
            tr.TransitionChar=getStateByPos(input,1)[0];
            clearQueueString(&tr.nextState);
            tr.nextState.push("");
            TR_TMP.push(tr);
        }else{
            tr.presentState=getStateByPos(input,0);
            tr.TransitionChar=getStateByPos(input,1)[0];
            tr.nextState=output;
            TR_TMP.push(tr);
        }
    }
    return TR_TMP;

}


void DisplayDataInSql(MYSQL *connector){
    MYSQL_ROW row;
    MYSQL_RES *res;
    if(connector){
        int state=mysql_query(connector,"SELECT ID,LABEL,Q,StartState,FinalState,Charactor FROM FA");
        if(!state){
            res=mysql_store_result(connector);
            int n=mysql_num_fields(res);
            cout<<"\n\t\t";
            cout<<setw(10)<<left<<"ID"<<setw(30)<<left<<"LABEL";
            cout<<setw(50)<<left<<"Q"<<setw(10)<<left<<"START";
            cout<<setw(20)<<left<<"FINAL"<<setw(10)<<left<<"CHARACTOR";
            cout<<"\n";
            while(row=mysql_fetch_row(res)){
                cout<<"\t\t";
                cout<<setw(10)<<left<<row[0]<<setw(30)<<left<<row[1];
                cout<<setw(50)<<left<<row[2]<<setw(10)<<left<<row[3];
                cout<<setw(20)<<left<<row[4]<<setw(10)<<left<<row[5];
                cout<<"\n";
            }
        }
    }
}

struct FA GetFAInSql(MYSQL *connector,string id){
    MYSQL_ROW row;
    MYSQL_RES *res;
    struct FA FA_tmp;
    string text="SELECT Q,StartState,FinalState,Charactor,Transition FROM fa WHERE id="+id+";";
    if(connector){
        int state=mysql_query(connector,text.c_str());
        if(!state){
            res=mysql_store_result(connector);
            int n=mysql_num_fields(res);
            while(row=mysql_fetch_row(res)){
                FA_tmp.Q=StringSplit(row[0],',');
                FA_tmp.startState=row[1];
                FA_tmp.final_state=StringSplit(row[2],',');
                for(int i=0;i<string(row[3]).size();i++){
                    FA_tmp.character.push(string(row[3])[i]);
                }
                FA_tmp.transitionSet=StringToTransition(row[4]);
            }
            return FA_tmp;
        }
    }
}


void insertToDataBase(struct FA FA1,MYSQL* connecter,string label){
    string text="INSERT INTO FA VALUES (NULL,";
    text+="\""+label+"\",";
    text+="\""+QueueStringTOString(FA1.Q,',')+"\",";
    text+="\""+FA1.startState+"\",";
    text+="\""+QueueStringTOString(FA1.final_state,',')+"\",";
    text+="\"";
    for(int i=0;i<FA1.character.size();i++){
        text+=GetCharWithPos(FA1.character,i);
    }
    text+="\",";
    text+="\""+TransitionToString(FA1.transitionSet)+"\")";
    //cout<<text;
    int State=mysql_query(connecter,text.c_str());
    if(!State){
        cout<<"\n\tInsert Success";
    }else{
        cout<<"\n\tFailed to save";
    }
}


bool isExistInData(struct FA FA1,MYSQL *connector){
    MYSQL_ROW row;
    MYSQL_RES *res;
    string text="";
    for(int i=0;i<FA1.character.size();i++){
        text+=GetCharWithPos(FA1.character,i);
    }
    int k=0;
    if(connector){
        int state=mysql_query(connector,"SELECT Q,StartState,FinalState,Charactor,Transition FROM FA");
        if(!state){
            res=mysql_store_result(connector);
            int n=mysql_num_fields(res);
            while(row=mysql_fetch_row(res)){
                if(row[0]==QueueStringTOString(FA1.Q,',')&&
                   row[1]==FA1.startState&&
                   row[2]==QueueStringTOString(FA1.final_state,',')&&
                   row[3]==text&&
                   row[4]==TransitionToString(FA1.transitionSet)
                   ){
                    k=1;
                }
            }
            if(k){
                return true;
            }else return false;
        }
    }

}

bool isduplicateName(string label,MYSQL*connector){
    MYSQL_ROW row;
    MYSQL_RES *res;
    string text="SELECT label FROM fa";
    if(connector){
        int state=mysql_query(connector,text.c_str());
        if(!state){
            res=mysql_store_result(connector);
            int n=mysql_num_fields(res);
            while(row=mysql_fetch_row(res)){
                if(row[0]==label){
                    return true;
                }
            }
            return false;
        }
    }
}
