#include <iostream>
#include <queue>
#include <conio.h>
#include <iomanip>
#include <mysql.h>
#include <color.hpp>
using namespace std;

string toupperStr(string text){
    string data=text;
    for (int i=0;i<data.length();i++){
        data[i]=toupper(data[i]);
    }
    return data;

}

bool isEmptyString(string str){
    for(int i=0;i<str.size();i++){
        if(str[i]!=' '){
            return false;
        }
    }
    return true;
}

void MySqlMenu(MYSQL *Connector,FA *FA1,FA *FA2,FA *FA3){
    FA FA_tmp;
    while(1){

        system("cls");
        printf("\t\t");
        for(int i=0;i<70;i++){
            printf("=");
        }
        printf("\n");
        printf("\t\t||\t%-60s||\n"
               "\t\t||\t%-60s||\n"
               "\t\t||\t%-60s||\n"
               "\t\t||\t%-60s||\n"
               "\t\t||\t%-60s||\n",
               "1.Load Data",
               "2.Delete Data",
               "3.Save",
               "4.All Data",
               "5.Back to Menu");
        printf("\t\t");
        for(int i=0;i<70;i++){
            printf("=");
        }
        cout<<"\n\t\tInput your option: ";
        int choice;
        cin>>choice;
        if(choice==1){
            string id;
            DisplayDataInSql(Connector);
            cout<<"\n\t\tInput you FA ID: ";
            cin>>id;

            *FA1=GetFAInSql(Connector,id);
            SaveTmp("FAtmp.txt",*FA1);
            SaveTmp("FAMinimized.txt");
            SaveTmp("FAConverted.txt");
            *FA2=getTmpFA("FAConverted.txt"),
            *FA3=getTmpFA("FAMinimized.txt");
             if(!isEmpty(*FA1)){
                display(*FA1);
             }else{
                SubHeader("THERE NO DATA MATCH",5,50,7,'r');
             }
            cout<<"\n\t\tPress any key to Continue | ESC back to menu";
            if(_getch()==27){
                break;
            }
        }else if(choice==2){
            string id,choice;
            DisplayDataInSql(Connector);
            cout<<"\n\t\tInput you FA ID: ";
            cin>>id;
            FA_tmp=GetFAInSql(Connector,id);
            if(!isEmpty(FA_tmp)){
                cout<<"\t\tFA that you Going to delete";
                display(FA_tmp);
                cout<<"\t\t\tAre you sure?Y/N:";
                cin>>choice;
                if(toupperStr(choice)=="YES"|| toupperStr(choice)=="Y"){
                    deleteFA(Connector,id);
                }
            }else{
                SubHeader("THERE NO DATA MATCH",5,50,7,'r');
            }
            cout<<"\n\t\tPress any key to Continue | ESC back to menu";
            if(_getch()==27){
                break;
            }
        }else if(choice==3){
            if(!isEmpty(*FA1)){
                cout<<"\t\t"<<dye::green("Original:");
                display(*FA1,0);
            }else{
                cout<<"\n\t\t"<<dye::red("Not load data yet");
            }
            if(!isEmpty(*FA2)){
                if(!isEmpty(*FA1)){
                    cout<<"\t\t"<<dye::green("Converted:");
                    display(*FA2,2);
                }
            }
            if(!isEmpty(*FA3)){
                if(!isEmpty(*FA1)){
                    cout<<"\n\t\t"<<dye::green("Minimized:");
                    display(*FA3,0);

                }
            }
            if(!isEmpty(*FA1)){

                string ch;
                cout<<"\n\t\tInput type(O/C/M) of FA:";cin>>ch;
                if(toupperStr(ch)=="O"||ch[0]=='o'||ch[0]=='O'){
                    if(isExistInData(*FA1,Connector)){
                        cout<<"\n\t\t"<<dye::red("You Fa already Exist in  database");
                        cout<<"\n\t\tAre you still want to Save?";
                        cout<<"\n\t\t\t\tY/N;";
                        cin>>ch;
                        if(ch=="y"||ch=="Y"){
                            cout<<"\n\t\tInput name of you FA: ";
                            cin.ignore();
                            getline(cin,ch);
                            while(isEmptyString(ch)){
                                cout<<"\n\t\t"<<dye::red("Name couldn't Empty");
                                cout<<"\n\t\tInput again:";
                                getline(cin,ch);
                            };

                            while(isduplicateName(ch,Connector)){
                                cout<<dye::red("\n\t\t\t \""+ch+"\" Already Exist in DataBase");
                                cout<<"\n\t\tInput again:";
                                getline(cin,ch);
                                while(isEmptyString(ch)){
                                    cout<<"\n\t\t"<<dye::red("Name couldn't Empty");
                                    cout<<"\n\t\tInput again:";
                                    getline(cin,ch);
                                };
                            }
                            insertToDataBase(*FA1,Connector,ch);
                        }
                    }else{
                            cin.ignore();
                            cout<<"\n\t\tInput you FA NAME:";
                            getline(cin,ch);
                                while(isEmptyString(ch)){
                                    cout<<"\n\t\t"<<dye::red("Name couldn't Empty");
                                    cout<<"\n\t\tInput again:";
                                    getline(cin,ch);
                                };

                            while(isduplicateName(ch,Connector)){
                                cout<<dye::red("\n\t\t\t \""+ch+"\" Already Exist in DataBase");
                                cout<<"\n\t\tInput again:";
                                getline(cin,ch);
                                while(isEmptyString(ch)){
                                    cout<<"\n\t\t"<<dye::red("Name couldn't Empty");
                                    cout<<"\n\t\tInput again:";
                                    getline(cin,ch);
                                };

                            }
                            insertToDataBase(*FA1,Connector,ch);

                        }

                }else if(toupperStr(ch)=="C"||ch[0]=='c'||ch[0]=='C'){
                    if(!isEmpty(*FA2)){

                        if(isExistInData(*FA2,Connector)){
                            cout<<"\n\t\t"<<dye::red("You Fa already Exist in  database");
                            cout<<"\n\t\tAre you still want to Save?";
                            cout<<"\n\t\t\t\tY/N;";
                            cin>>ch;
                            if(ch=="y"||ch=="Y"){
                                cout<<"\n\t\tInput name of you FA: ";
                                cin.ignore();
                                getline(cin,ch);
                                while(isEmptyString(ch)){
                                    cout<<"\n\t\t"<<dye::red("Name couldn't Empty");
                                    cout<<"\n\t\tInput again:";
                                    getline(cin,ch);
                                };


                                while(isduplicateName(ch,Connector)){
                                    cout<<dye::red("\n\t\t\t \""+ch+"\" Already Exist in DataBase");
                                    cout<<"\n\t\tInput again:";
                                    getline(cin,ch);
                                    while(isEmptyString(ch)){
                                        cout<<"\n\t\t"<<dye::red("Name couldn't Empty");
                                        cout<<"\n\t\tInput again:";
                                        getline(cin,ch);
                                    };

                                }
                                insertToDataBase(*FA2,Connector,ch);
                            }
                        }else{
                            cout<<"\n\t\tInput you FA NAME:";
                            cin.ignore();
                            getline(cin,ch);
                                while(isEmptyString(ch)){
                                    cout<<"\n\t\t"<<dye::red("Name couldn't Empty");
                                    cout<<"\n\t\tInput again:";
                                    getline(cin,ch);
                                };

                            while(isduplicateName(ch,Connector)){
                                cout<<dye::red("\n\t\t\t \""+ch+"\" Already Exist in DataBase");
                                cout<<"\n\t\tInput again:";
                                getline(cin,ch);
                                while(isEmptyString(ch)){
                                    cout<<"\n\t\t"<<dye::red("Name couldn't Empty");
                                    cout<<"\n\t\tInput again:";
                                    getline(cin,ch);
                                };

                            }
                            insertToDataBase(*FA3,Connector,ch);

                        }
                    }else{
                        SubHeader("YOU NOT CONVERT FA YET",5,50,7,'r');
                    }

                }else if(toupperStr(ch)=="M"||ch[0]=='m'||ch[0]=='M'){
                    if(!isEmpty(*FA2)){

                        if(isExistInData(*FA3,Connector)){
                            cout<<"\n\t\t"<<dye::red("You Fa already Exist in  database");
                            cout<<"\n\t\tAre you still want to Save?";
                            cout<<"\n\t\t\t\tY/N;";
                            cin>>ch;
                            if(ch=="y"||ch=="Y"){
                                cin.ignore();
                                cout<<"\n\t\tInput name of you FA: ";
                                getline(cin,ch);
                                while(isEmptyString(ch)){
                                    cout<<"\n\t\t"<<dye::red("Name couldn't Empty");
                                    cout<<"\n\t\tInput again:";
                                    getline(cin,ch);
                                };


                                while(isduplicateName(ch,Connector)){
                                    cout<<dye::red("\n\t\t\t \""+ch+"\" Already Exist in DataBase");
                                    cout<<"\n\t\tInput again:";
                                    getline(cin,ch);
                                    while(isEmptyString(ch)){
                                        cout<<"\n\t\t"<<dye::red("Name couldn't Empty");
                                        cout<<"\n\t\tInput again:";
                                        getline(cin,ch);
                                    };

                                }
                                insertToDataBase(*FA3,Connector,ch);
                            }
                        }else{
                            cout<<"\n\t\tInput you FA NAME:";
                            cin.ignore();
                            getline(cin,ch);
                                while(isEmptyString(ch)){
                                    cout<<"\n\t\t"<<dye::red("Name couldn't Empty");
                                    cout<<"\n\t\tInput again:";
                                    getline(cin,ch);
                                };

                            while(isduplicateName(ch,Connector)){
                                cout<<dye::red("\n\t\t\t \""+ch+"\" Already Exist in DataBase");
                                cout<<"\n\t\tInput again:";
                                getline(cin,ch);
                                while(isEmptyString(ch)){
                                    cout<<"\n\t\t"<<dye::red("Name couldn't Empty");
                                    cout<<"\n\t\tInput again:";
                                    getline(cin,ch);
                                };

                            }
                            insertToDataBase(*FA3,Connector,ch);

                        }
                    }else{
                        SubHeader("YOU NOT MINIMIZED FA YET",5,50,7,'r');
                    }

                }
            }
            cout<<"\n\t\tPress any key to Continue | ESC back to menu>>";
            if(_getch()==27){
                break;
            }
        }else if(choice==4){
            DisplayDataInSql(Connector);
            cout<<"\n\t\tPress any key to Continue | ESC back to menu";
            if(_getch()==27){
                break;
            }
        }else{
            break;
        }
    }

}



void GetInputMenu(FA *FA1,MYSQL *Connector){
    *FA1=getInput();
    SaveTmp("FAtmp.txt",*FA1);
    SaveTmp("FAMinimized.txt");
    SaveTmp("FAConverted.txt");
    display(*FA1);
    string choice,ch;
    if(Connector){

        cout<<"\n\t\tDo you want to save?:Y/N:";cin>>choice;
        if(toupperStr(choice)=="Y" || toupperStr(choice)=="YES"){
            if(isExistInData(*FA1,Connector)){
                cout<<"\n\t\tYou Fa already Exist in  database";
                cout<<"\n\t\tAre you still want to Save?";
                cout<<"\n\t\t\t\tY/N;";
                cin>>ch;
                if(ch=="y"||ch=="Y"){
                    cin.ignore();
                    cout<<"\n\t\tInput name of you FA: ";
                    getline(cin,ch);
                    while(isEmptyString(ch)){
                        cout<<"\n\t\tName couldn't Empty";
                        cout<<"\n\t\tInput again:";
                        getline(cin,ch);
                    };

                    while(isduplicateName(ch,Connector)){
                        cout<<dye::red("\n\t\t\t \""+ch+"\" Already Exist in DataBase");
                        cout<<"\n\t\tInput again:";
                        getline(cin,ch);
                        while(isEmptyString(ch)){
                            cout<<"\n\t\tName couldn't Empty";
                            cout<<"\n\t\tInput again:";
                            getline(cin,ch);
                        };
                    }
                    insertToDataBase(*FA1,Connector,ch);
                }
            }else{
                cout<<"\n\t\tInput you FA NAME:";
                cin.ignore();
                getline(cin,ch);
                while(isEmptyString(ch)){
                    cout<<"\n\t\tName couldn't Empty";
                    cout<<"\n\t\tInput again:";
                    getline(cin,ch);
                };
                while(isduplicateName(ch,Connector)){
                    cout<<dye::red("\n\t\t\t \""+ch+"\" Already Exist in DataBase");
                    cout<<"\n\t\tInput again:";
                    getline(cin,ch);
                    while(isEmptyString(ch)){
                        cout<<"\n\t\tName couldn't Empty";
                        cout<<"\n\t\tInput again:";
                        getline(cin,ch);
                    };
                }
                insertToDataBase(*FA1,Connector,ch);

            }
        }
    }
    cout<<"\n\t\tPress any key to Continue>>";
    _getch();
}

void TestStringSection(FA *FA1){
    string text;
    while(1){
        cout<<"\n\t\tInput you string: ";cin>>text;
        if(isAccept(*FA1,text)){
            cout<<"\t\t\tAccept\n";
        }else{
            cout<<"\n\t\t\tReject\n";
        };
        cout<<"\n\t\tPress any key to Continue | ESC back to menu";
        if(_getch()==27){
            break;
        }
    }
}
void ConvertorMenu(FA *FA1,FA *FA2){
    display(*FA1);
    *FA2=NfaToDfa(*FA1);
    SaveTmp("FAConverted.txt",*FA2);
    display(*FA2);
    cout<<"\n\t\tPress any key to Continue>>";_getch()==27;
}

void MinimizeMenu(FA *FA1,FA *FA3){
    display(*FA1);
    if(isNfa(*FA1)){
        *FA3=Minimized(NfaToDfa(*FA1));
        SaveTmp("FAMinimized.txt",*FA3);
    }else{
        *FA3=Minimized(*FA1);
        SaveTmp("FAMinimized.txt",*FA3);
    }
    display(*FA3);
    cout<<"\n\t\tPress any key to Continue>>";_getch()==27;
}




void Menu(){
    system("cls");
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
           "\t\t||\t%-60s||\n"
           "\t\t||\t%-60s||\n",
           "1.MySql Server",
           "2.Input FA",
           "3.Input String",
           "4.Convert NFA to DFA",
           "5.Minimize",
           "6.What's my FA again?",
           "7.Exit");
    printf("\t\t");
    for(int i=0;i<70;i++){
        printf("=");
    }
    cout<<"\n\t\tInput your option: ";
}
