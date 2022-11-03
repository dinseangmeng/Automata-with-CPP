#include<iostream>
#include<fstream>
using namespace std;
FA FAEmpty;
FA getTmpFA(string fileName){
    FA FA1;
    fileName="tmp/"+fileName;
    fstream File;
    File.open(fileName.c_str(),ios::in);
    string QStr="",
    StartStateStr="",
    FinalStateStr="",
    CharactorStr="",
    TransitionStr="",
    DescriptionStr="";
    while(!File.eof()){
        File>>QStr>>StartStateStr>>FinalStateStr>>CharactorStr>>TransitionStr;

        getline(File,DescriptionStr);
        FA1.Q=StringSplit(QStr,',');
        FA1.startState=StartStateStr;
        FA1.final_state=StringSplit(FinalStateStr,',');
        for(int i=0;i<CharactorStr.size();i++){
            FA1.character.push(CharactorStr[i]);
        }
        FA1.transitionSet=StringToTransition(TransitionStr);
        FA1.discription=DescriptionStr;
    }
    File.close();
    return FA1;
}
void SaveTmp(string fileName,FA FA1=FAEmpty){
    fileName="tmp/"+fileName;
    fstream File;
    File.open(fileName.c_str(),ios::out);
    File<<"\n"<<QueueStringTOString(FA1.Q,',')<<" "
        <<FA1.startState<<" "
        <<QueueStringTOString(FA1.final_state,',')<<" ";
    for(int i=0;i<FA1.character.size();i++){
        File<<GetCharWithPos(FA1.character,i);
    }
    File<<" ";
    File<<TransitionToString(FA1.transitionSet)<<" "
        <<FA1.discription;
    File.close();
}
