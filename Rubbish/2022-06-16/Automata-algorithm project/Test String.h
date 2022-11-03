#include <iostream>
#include <queue>
#include <conio.h>
#include <iomanip>
using namespace std;


bool isAccept(struct FA FA1,string text){
    if(!isNfa(FA1)){
        string state=FA1.startState;
        for(int i=0;i<text.size();i++){
            state=QueueStringTOString(setOfNextState(FA1.transitionSet,state,text[i]),',');
        }
        if(isExist(FA1.final_state,state)){
            return true;
        }
        return false;

    }
    return false;
}
