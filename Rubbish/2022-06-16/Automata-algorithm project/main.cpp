#include <iostream>
#include <queue>
#include <conio.h>
#include <iomanip>
#include<string>
#include"Header.h"
#include "NfaToDfa.h"
#include"Test String.h"
#include "Design console.h"
#include"header.2.h"
#include"Minimized-DFA.h"
#include"MySql man.h"

using namespace std;

struct FA FA1,FA2;
MYSQL *Connector=connection();


void CLIENTDASHBOARD(){
    Menu();
    int choice;
    string ch;
    cin>>choice;
    switch (choice){
        case 1:
            if(Connector){
                DisplayDataInSql(Connector);
                cout<<"\n\t\tChoose Your data by id:";
                cin>>ch;
                FA1=GetFAInSql(Connector,ch);
                if(!isEmpty(FA1)){
                    display(FA1);
                }else{
                    cout<<"\n\t\t\tThere no data matched!\n";
                }
            }else cout<<"\n\t\t\tCould not connect with Database!\n";
            cout<<"\nPress any key to continue|Esc to stop>>>";
            if(_getch()!=27){
                system("cls");
                CLIENTDASHBOARD();
            }
            break;
        case 2:
            cin.ignore();
            FA1=getInput();
            display(FA1);
            if(Connector){
                cout<<"you want to save?(y/n):";
                cin>>ch;
                if(ch=="y"||ch=="yes"){
                    if(!isExistInData(FA1,Connector)){
                        cout<<"What's of you FA that you going to save?:";
                        cin.ignore();
                        getline(cin,ch);
                        insertToDataBase(FA1,Connector,ch);
                    }else{
                        cout<<"\n\t\t\tData already Exist!\n";
                        cout<<"\n\t\t\tAre insist to save?(y/n):";
                        cin>>ch;
                        if(ch=="y"||ch=="yes"){
                            cout<<"What's of you FA that you going to save?:";
                            cin.ignore();
                            do{
                                getline(cin,ch);
                                if(isduplicateName(ch,Connector) ||ch==""||ch==" "){
                                    cout<<"\n\t\tIt seem your label already exist!\n";
                                    cout<<"\n\t\t\tTry again:";
                                }

                            }while(isduplicateName(ch,Connector) ||ch==""||ch==" ");
                            insertToDataBase(FA1,Connector,ch);
                        }
                    }
                }

            }

            cout<<"\nPress any key to continue|Esc to stop>>>";
            //cout<<TransitionToString(FA1.transitionSet);
            if(_getch()!=27){
                system("cls");
                CLIENTDASHBOARD();
            }
            break;
        case 3:
            if(!isEmpty(FA1)){
                string text;
                cin.ignore();
                do{
                    cout<<"\n\t\tinput string to test:";

                    getline(cin,text);

                    if(isAccept(NfaToDfa(FA1),text)){
                        cout<<"\t\t\t>>>Accept\n";
                    }else{
                        cout<<"\t\t\t>>>Reject\n";
                    }
                    cout<<"\t\tPress Esc back to menu| Any key to test again:";
                }while(_getch()!=27);
                system("cls");
                CLIENTDASHBOARD();
            }else {
                cout<<"\n\t\tYour not input or load data yet";
                cout<<"\n\t\tPress Esc back to menu| Any key to test again:";
                if(_getch()!=27){
                    system("cls");
                    CLIENTDASHBOARD();
                }
            };
            break;
        case 4:
            if(!isEmpty(FA1)){
                cout<<"\n\t\tAre you going to replace your NFA or Create new(y/n):";
                cin>>ch;
                if(ch=="y"||ch=="yes"){
                    FA2=NfaToDfa(FA1);
                    display(FA1);
                    display(FA2);
                    if(Connector){

                        cout<<"you want to save?(y/n):";
                        cin>>ch;
                        if(ch=="y"||ch=="yes"){
                            if(!isExistInData(FA2,Connector)){
                                cout<<"What's of you FA that you going to save?:";
                                cin.ignore();
                                getline(cin,ch);
                                insertToDataBase(FA2,Connector,ch);
                            }else{
                                cout<<"\n\t\t\tData already Exist!\n";
                                cout<<"\n\t\t\tAre insist to save?(y/n):";
                                cin>>ch;
                                if(ch=="y"||ch=="yes"){
                                    cout<<"What's of you FA that you going to save?:";
                                    cin.ignore();
                                    do{
                                        getline(cin,ch);
                                        if(isduplicateName(ch,Connector) ||ch==""||ch==" "){
                                            cout<<"\n\t\tIt seem your label already exist!\n";
                                            cout<<"\n\t\t\tTry again:";
                                        }

                                    }while(isduplicateName(ch,Connector) ||ch==""||ch==" ");
                                    insertToDataBase(FA1,Connector,ch);
                                }
                            }
                        }
                    }

                }else{
                    FA1=NfaToDfa(FA1);

                    display(FA1);
                    if(Connector){
                        cout<<"you want to save?(y/n):";
                        cin>>ch;
                        if(ch=="y"||ch=="yes"){

                            if(!isExistInData(FA1,Connector)){
                                cout<<"What's of you FA that you going to save?:";
                                cin.ignore();
                                getline(cin,ch);
                                insertToDataBase(FA1,Connector,ch);
                            }else{
                                cout<<"\n\t\t\tData already Exist!\n";
                                cout<<"\n\t\t\tAre insist to save?(y/n):";
                                cin>>ch;
                                if(ch=="y"||ch=="yes"){
                                    cout<<"What's of you FA that you going to save?:";
                                    cin.ignore();
                                    do{
                                        getline(cin,ch);
                                        if(isduplicateName(ch,Connector) ||ch==""||ch==" "){
                                            cout<<"\n\t\tIt seem your label already exist!\n";
                                            cout<<"\n\t\t\tTry again:";
                                        }
                                    }while(isduplicateName(ch,Connector) ||ch==""||ch==" ");
                                    insertToDataBase(FA1,Connector,ch);
                                }
                            }
                        }
                    }
                };

            }else cout<<"\n\t\tYour not input or load data yet";
            cout<<"\nPress any key to continue|Esc to stop>>>";
            if(_getch()!=27){
                system("cls");
                CLIENTDASHBOARD();
            }
            break;
        case 5:
            if(!isEmpty(FA1)){
                cout<<"\n\t\tAre you going to replace your NFA or Create new(y/n):";
                cin>>ch;
                if(ch=="y"||ch=="yes"){
                    if(!isNfa(FA1)){
                        FA2=TestDistinguish(TestDistinguish(FA1));
                    }else{
                        FA2=TestDistinguish(TestDistinguish(NfaToDfa(FA1)));
                    };

                    display(FA1);
                    cout<<"\nAfter Minimize:";
                    display(FA2);
                    if(Connector){
                        cout<<"you want to save?(y/n):";
                        cin>>ch;
                        if(ch=="y"||ch=="yes"){
                            if(!isExistInData(FA2,Connector)){
                                cout<<"What's of you FA that you going to save?:";
                                cin.ignore();
                                getline(cin,ch);
                                insertToDataBase(FA2,Connector,ch);
                            }else{
                                cout<<"\n\t\t\tData already Exist!\n";
                                cout<<"\n\t\t\tAre insist to save?(y/n):";
                                cin>>ch;
                                if(ch=="y"||ch=="yes"){
                                    cout<<"What's of you FA that you going to save?:";
                                    cin.ignore();
                                    do{
                                        getline(cin,ch);
                                        if(isduplicateName(ch,Connector) ||ch==""||ch==" "){
                                            cout<<"\n\t\tIt seem your label already exist!\n";
                                            cout<<"\n\t\t\tTry again:";
                                        }

                                    }while(isduplicateName(ch,Connector) ||ch==""||ch==" ");
                                    insertToDataBase(FA1,Connector,ch);
                                }
                            }
                        }
                    }

                }else{
                    if(!isNfa(FA1)){
                        FA1=TestDistinguish(TestDistinguish(FA1));
                    }else{
                        FA1=TestDistinguish(TestDistinguish(NfaToDfa(FA1)));
                    };
                    cout<<"\nAfter Minimize:";
                    display(FA1);
                    if(Connector){
                        cout<<"you want to save?(y/n):";
                        cin>>ch;
                        if(ch=="y"||ch=="yes"){

                            if(!isExistInData(FA1,Connector)){
                                cout<<"What's of you FA that you going to save?:";
                                cin.ignore();
                                getline(cin,ch);
                                insertToDataBase(FA1,Connector,ch);
                            }else{
                                cout<<"\n\t\t\tData already Exist!\n";
                                cout<<"\n\t\t\tAre insist to save?(y/n):";
                                cin>>ch;
                                if(ch=="y"||ch=="yes"){
                                    cout<<"What's of you FA that you going to save?:";
                                    cin.ignore();
                                    do{
                                        getline(cin,ch);
                                        if(isduplicateName(ch,Connector) ||ch==""||ch==" "){
                                            cout<<"\n\t\tIt seem your label already exist!\n";
                                            cout<<"\n\t\t\tTry again:";
                                        }
                                    }while(isduplicateName(ch,Connector) ||ch==""||ch==" ");
                                    insertToDataBase(FA1,Connector,ch);
                                }
                            }
                        }
                    }
                };

            }else cout<<"\n\t\tYour not input or load data yet";
            cout<<"\nPress any key to continue|Esc to stop>>>";
            if(_getch()!=27){
                system("cls");
                CLIENTDASHBOARD();
            }
            break;

        case 6 :
            if(!isEmpty(FA1)){
                display(FA1);
            }
            if(!isEmpty(FA2)){
                display(FA2);
            }
            cout<<"\nPress any key to continue|Esc to stop>>>";
            if(_getch()!=27){
                system("cls");
                CLIENTDASHBOARD();
            };
            break;
        default:
            cout<<"\nPress any key to continue|Esc to stop>>>";
            if(_getch()!=27){
                system("cls");
                CLIENTDASHBOARD();
            };
            break;


    }
}

int main()
{

    string ch;
    if(Connector){
        CLIENTDASHBOARD();
    }else{
        cout<<"\t\t\tAre you going to use it offline?(y/n):";
        cin>>ch;
        if(ch=="y"||ch=="yes"){
            CLIENTDASHBOARD();
        }
    }













}
