#include <iostream>
#include <queue>
#include <conio.h>
#include <iomanip>
using namespace std;

void Menu(){
    printf("\t\t");
    for(int i=0;i<70;i++){
        printf("=");
    }
    printf("\n");
    printf("\t\t||\t%-60s||\n"
           "\t\t||\t%-60s||\n"
           "\t\t||\t%-60s||\n"
           "\t\t||\t%-60s||\n"
           "\t\t||\t%-60s||\n"
           "\t\t||\t%-60s||\n",
           "1.Load from Sever",
           "2.Input FA",
           "3.Input String",
           "4.Convert NFA to DFA",
           "5.Minimize",
           "6.What's my FA again?");
    printf("\t\t");
    for(int i=0;i<70;i++){
        printf("=");
    }
    cout<<"\n\t\tInput your option | Esc to go back:";
}
