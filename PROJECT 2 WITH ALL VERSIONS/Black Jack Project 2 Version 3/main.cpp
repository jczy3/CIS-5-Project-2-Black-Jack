/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/*
 * File:   main.cpp
 * Author: Joseph Caraan
 *
 * Created on February 11, 2023, 12:41 PM
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>

using namespace std;
/*
 *
 */
void shuffle (string [],string []);
int value (string [], string [], int &,int &); 
void print (string face[], string suit []); //Version 3, create a print function and clean up code, removing past statements and loops that would draw just numbers and not faces/suits.
bool win();                                 

int main(int argc, char** argv) {
    //Opening file blackjack.TXT using fstream
    srand(static_cast<unsigned>(time(0))); //setting random seed
    //Declaring variables
    const int NCARDS=52;//Number of Cards
    string face[]={"Ace","2","3","4","5",
                    "6","7","8","9",
                    "10","Jack","Queen","King"};   //Face Values of the Cards
    string suit[]={"Spades","Diamonds",
                   "Clubs","Hearts"};//All the suits in a deck
    int n;
    const int one = 1;
    int minRand, //Minimum random number to be selected
    maxRand, //Maximum random number to be selected
    randNum1; //Random number to be selected
    float balance; // Balance of player
    int plrval; //Player's card value
    int dlrval; //Dealer's card value
    int wincnt; //Amount of wins 
    int losecnt; //Amount of losses 
    float absol; //Calculates the amount of money lost or gained playing 
    float gamecnt; //Amount of games
    float prcnt; //Percent of the games won 
    bool win; //decides if player won or not
    float result = (int)balance; //decides whether to add or subtract from the balance
    int swtwage; //switch case for the wager of the player
    float wage; //custom amount input by the user
    char res; //response from the user, whether they want to continue or not
    string DrOrSt; //prime decider on how loops end/continue. "draw or stand"
   
    //Initializing Variables
    wincnt = 0;
    losecnt = 0;
    gamecnt = 0;
    swtwage = 4;
    balance = 10000;
    win = true;
    res = 'y';
    //Beginning output
    cout<<"Welcome to the Blackjack game!"<<endl;
    cout<<"Balance: $"<<fixed<<setprecision(2)<<balance<<endl; //iomanip use
    cout<<"Enter '1' to wager $20, '2' to wager $50, "
            "'3' to wager $100, or '4' to select your own wager: "; //iostream use
   
    do{ //code runs once, then loops until while condition is false
        cin>>swtwage; //inputs the switch case wage
        switch (swtwage){
            case 1:
                wage = 20*one;
                break; //NOTE: USING BREAK FOR THE SWITCH CASE, NOT A LOOP
            case 2:
                wage = 50*one;
                break; //NOTE: USING BREAK FOR THE SWITCH CASE, NOT A LOOP
            case 3:
                wage = pow(10,2); //cmath libary used 
                break; //NOTE: USING BREAK FOR THE SWITCH CASE, NOT A LOOP
            case 4:
                cout<<"Enter a wager greater than $0: $";
                cin>>wage; //Input wage 
                while(wage<0.009 || wage>balance){ //input validation for entering a custom wage
                    cout<<"Error. Please input a wager no greater than your balance"
                            " and one that is at least $0.01: $";
                    cin>>wage;
                }
                break; //NOTE: USING BREAK FOR THE SWITCH CASE, NOT THE LOOP
        }
        cout<<"The dealer is shuffling the cards..."<<endl<<endl;
        cout<<"The dealer's face up card is a/n ";
        dlrval = value(face,suit, plrval, dlrval); //setting the dealer's value to the the random number generated
        print(face,suit);
        cout<<"."<<endl;
        cout<<"You drew a/n ";
        plrval = value(face,suit, plrval, dlrval);
        print(face,suit);
        cout<<" and a/n ";
        plrval += value(face,suit, plrval, dlrval);
        print(face,suit);
        cout<<"."<<endl;
        cout<<"You have a value of "<<plrval<<" in total."<<endl;
        if (plrval == 21){ //Lucky Blackjack straight off
            cout<<"Blackjack! You win!"<<endl;
            win = true;
        }
        else{
            cout<<"Enter draw or stand: ";
            cin>>DrOrSt;
            cout<<endl;
            if (DrOrSt != "draw" || DrOrSt != "stand"){ //Input Validation for draw or stand, also string library used here
                while (DrOrSt != "draw" && DrOrSt != "stand"){
                    cout<<"Error. Please enter draw or stand: ";
                    cin>>DrOrSt;
                    cout<<endl;
                }
            }                                          
            if (DrOrSt == "draw"){
                while (DrOrSt == "draw"){
                    cout<<"You drew a/n ";
                    plrval += value(face,suit, plrval, dlrval);
                    print(face,suit);
                    cout<<"."<<endl;
                    cout<<"You now have "<<plrval<<"."<<endl;
                    if(plrval>21){ //condition for a bust
                        cout<<"You busted!"<<endl;
                        win = false;
                        DrOrSt = "exit";
                    }
                    else if(plrval==21){ //condition for a blackjack
                        cout<<"Blackjack! You win!"<<endl;
                        win = true;
                        DrOrSt = "exit";
                    }
                    else if (plrval<21){ //condition to keep drawing cards or to stand, loops back if response is "draw"
                        cout<<"Enter draw or stand: ";
                        cin>>DrOrSt;
                        cout<<endl;
                    }
                }
            }
            if (DrOrSt == "stand"){ //Goes to this block of code if the response is "stand", block of code is for second card only
                dlrval += value(face,suit, plrval, dlrval);
                cout<<"The dealer flips his second card. It is a ";
                print(face,suit);
                cout<<"."<<endl;
                cout<<"The dealer now has "<<dlrval<<"."<<endl;
                if(dlrval>plrval || dlrval==21){ //Condition for dealer to beat player
                        cout<<"The dealer wins! You lose!"<<endl;
                        win = false;
                        DrOrSt = "exit";
                }
                else if (dlrval>21){ //Condition for dealer to bust
                        cout<<"The dealer busted! You win!";
                        win = true;
                        DrOrSt = "exit";
                }
                else if (dlrval==plrval){ //this is when there is a tie
                    cout<<"The dealer received your value. "
                            "No balance will be added or removed."<<endl;
                }
                else if (dlrval<21 && dlrval<plrval){ //Condition for dealer grab more cards, this is where dealer grabs more cards
                    cout<<"Dealer is now pulling more cards..."<<endl;
                    while (dlrval < plrval){ //loop for dealer to grab more cards until greater than or equal to player
                        dlrval += value(face,suit, plrval, dlrval); //grab another card and put into deck
                        cout<<"The dealer drew a/n ";
                        print(face,suit);
                        cout<<"."<<endl;
                        cout<<"The dealer now has "<<dlrval<<"."<<endl;
                    }
                    if((dlrval>plrval && dlrval<21 ) || (dlrval==21 && plrval != 21)){ //condition for dealer to win, if he/she gets 21 or is greater than player while being less than or equal to 21
                        cout<<"The dealer wins! You lose!"<<endl;
                        win = false;
                        DrOrSt = "exit";
                    }
                    else if (dlrval>21){ //condition for dealer to bust when pulling more cards
                        cout<<"The dealer busted! You win!"<<endl;
                        win = true;
                        DrOrSt = "exit";
                    }
                    if (dlrval==plrval){ //condition for dealer to make a tie
                        cout<<"The dealer received your value. "
                                "No balance will be added or gained."<<endl;
                        DrOrSt = "exit";
                    }
                }
            }
        }
        gamecnt++;
        if(dlrval!=plrval){ //need this if statement so that balance will not be added or subtracted on a tie
            result = (win==true) ? balance+=wage : balance-=wage; //ternary operator deciding whether to add or subtract the wager from balance
            result = (win==true) ? wincnt++ : losecnt++;
            cout<<"New Balance = $"<<fixed<<setprecision(2)<<balance<<endl; //formatting result
        }
        else if (dlrval==plrval){
            cout<<"Balance = $"<<fixed<<setprecision(2)<<balance<<endl; //formatting same balance on a tie
        }
        if (balance > 0){ //runs statement if user has money
            cout<<"Enter 'y' to keep playing and 'n' to quit: ";
            cin>>res;
        }
        if (res == 'y' && balance>0){ //runs if user wants to keep playing and has money
            cout<<endl<<"Enter '1' to wager $20, '2' to wager $50, "
                    "'3' to wager $100, or '4' to select your own wager: ";
        }
        else if (balance==0){ //runs if user is out of money
            cout<<"You're out of money! Go grab some more!";
        } 
    }while (res=='y' && balance>0); 
    //This statistics code runs after the blackjack game
    cout<<endl;
    fstream outFile;
    outFile.open("blackjack.TXT");
    ifstream inFile;
    inFile.open("blackjackinput.TXT");
    string o,p;
    inFile>>o>>p;
    outFile<<o<<" "<<p<<endl;
    outFile<<"You played for "<<setprecision(0)<<gamecnt<<" round/s."<<endl; //amount of games played
    outFile<<"You won "<<wincnt<<" times."<<endl; //amount of wins
    outFile<<"You lost "<<losecnt<<" times."<<endl; //amount of losses
    prcnt = (wincnt/gamecnt)*100;
    outFile<<"You won "<<fixed<<setprecision(2)<<prcnt<<"% of the rounds that you played."<<endl; //percentage of games won
    absol = abs(10000 - balance); //cstdlib use
    outFile<<"You gained/lost $"<<absol<<"."; //amount of money gained/lost
    inFile.close();
    outFile.close();
    return 0;
} 
void shuffle (string face[],string suit []){ //function in which arrays face and suit are passed into, and are later passed into the value function
    static int numface = 13;
    static int numsuit = 4;
    for(int i = 0; i<numsuit; i++){ //randomizing the suit
        int random = rand()%numsuit;
        string temp  = suit[i];
        suit[i] = suit[random];
        suit[random] = temp;
    }
    for(int i = 0; i<numface; i++){ //randomizing the face
        int random = rand()%numface;
        string temp  = face[i];
        face[i] = face[random];
        face[random] = temp;
    }
}
int value (string face[], string suit [], int &plrval, int &dlrval){
    shuffle(face,suit);
    int n=0;
    int length = face[n].length();
    char* chrary = new char [length+1];
    strcpy(chrary,face[n].c_str());
    for(int i=0;i<length;i++){
        if(isdigit(chrary[i])){
            int num = stoi(chrary);
            return num;
        }
        else{
            if (chrary[i]=='K' || chrary[i]=='Q' ||chrary[i]=='J'){
                return 10;
            }
            if (chrary[i]=='A' && plrval+11>21){
                return 1;
            }
            else if (chrary[i]=='A' && plrval+11<21){
                return 11;
            }
            if (chrary[i]=='A' && dlrval+11>21){
                return 1;
            }
            else if (chrary[i]=='A' && dlrval+11<21){
                return 11;
            }
        }
    }
}
void print(string face[], string suit []){
    string strCard;
    strCard=face[26%13];
    strCard+=" of ";
    strCard+=suit[26%4];
    cout<<strCard;
}
bool win(){
    
}