#include    <iostream>
#include    <queue>
#include    <conio.h>
#include    <iomanip>
#include    <string>
#include    <Header.h>
#include    <NfaToDfa.h>
#include    <Test String.h>
#include    <header.2.h>
#include    <Minimized-DFA.h>
#include    <MySql man.h>
#include    <color.hpp>
#include    <tabulate/table.hpp>
#include    <FileIO.h>
#include    <Design console.h>

using namespace tabulate;
using namespace dye;
using namespace std;

struct  FA FA1=getTmpFA("FAtmp.txt"),
        FA2=getTmpFA("FAConverted.txt"),
        FA3=getTmpFA("FAMinimized.txt");
MYSQL *Connector=connection();

bool CLIENTDASHBOARD(){
    Menu();
    int choice;
    cin>>choice;
    cout<<"\n";
    if(choice==1){
        if(Connector){
            MySqlMenu(Connector,&FA1,&FA2,&FA3);//MySqlSection
        }else{
            cout<<"\n\t\t"<<red("Couldn't Connect to data base");
            cout<<"\n\t\tPress any key to Continue>>";_getch()==27;

        }
    }else if(choice==2){

        cin.ignore();
        GetInputMenu(&FA1,Connector);//InputFASection
        FA2=getTmpFA("FAConverted.txt");
        FA3=getTmpFA("FAMinimized.txt");

    }else if(choice==3){
        if(!isEmpty(FA1)){
            cin.ignore();
            TestStringSection(&FA1);//InputStringSection
        }else{
            cout<<"\n\t\t"<<red("Opp Seem like you not load/input data yet!");
            cout<<"\n\t\tPress any key to Continue>>";_getch();
        }
    }else if(choice==4){
        if(!isEmpty(FA1)){
            ConvertorMenu(&FA1,&FA2);//ConvertFASection

        }else{
            cout<<"\n\t\t"<<red("Opp Seem like you not load/input data yet!");
            cout<<"\n\t\tPress any key to Continue>>";_getch();
        }
    }else if(choice==5){
        if(!isEmpty(FA1)){
            cin.ignore();
            MinimizeMenu(&FA1,&FA3);//MinimizeFASection

        }else{
            cout<<"\n\t\t"<<red("Opp Seem like you not load/input data yet!");
            cout<<"\n\t\tPress any key to Continue>>";_getch();
        }

    }else if(choice==6){
        if(!isEmpty(FA1)){
            cout<<green("\t\t-> Original::");
            display(FA1,0);
            cout<<"\n\n";
        }else{
            cout<<"\n\t\t"<<red("Opp Seem like you not load/input data yet!");
        }
        if(!isEmpty(FA2)){
            cout<<green("\t\t-> Converted::");
            display(FA2,0);
            cout<<"\n\n";
        }
        if(!isEmpty(FA3)){
            cout<<green("\t\t-> Minimized::");
            display(FA3,0);
            cout<<"\n\n";
        }
        cout<<"\n\t\tPress any key to Continue>>";_getch();
        //DisplayFASection
    }else if(choice==7){
        return false;
    }else return true;
    return true;

}

int main()
{

    string ch;
    if(Connector){
        while(CLIENTDASHBOARD());
    }else{
        cout<<"\t\t\tAre you going to use it offline?(y/n):";
        cin>>ch;
        if(ch=="y"||ch=="yes"){
            while(CLIENTDASHBOARD());

        }
    }













}
