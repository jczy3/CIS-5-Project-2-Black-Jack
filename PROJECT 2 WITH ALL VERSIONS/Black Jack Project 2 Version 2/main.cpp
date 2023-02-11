/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/*
 * File:   main.cpp
 * Author: Joseph Caraan
 *
 * Created on February 11, 2023, 10:10 AM
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
void shuffle (string face[],string suit[]);
int value (string face[], string suit[], int &n); //Version 2, creating a value function to determine the value of the cards.
//bool win function                               //I will deal with the ace in a later version.

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
    shuffle(face,suit);
    cout<<value(face,suit, n);
    /*const int one = 1;
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
        srand(time(NULL)); //Need for random numbers to generate, also ctime used
        minRand = 1;
        maxRand = 11;
        for (int i=0;i<12;i++){ //Dealer's face up card
            randNum1 = rand()%(maxRand-minRand+1)+minRand; //cstdlib use
        }
        dlrval = randNum1; //setting the dealer's value to the the random number generated
        cout<<"The dealer is shuffling the cards..."<<endl<<endl;
        if (dlrval == 11 || dlrval == 1){
            cout<<"The dealer's face up card is an ace."<<endl;
        }
        else{
            cout<<"The dealer's face up card is "<<dlrval<<"."<<endl;
        }
        if (dlrval == 1){ //setting ace equal to 11 if it is the face up card
            dlrval = 11;
        }
        minRand = 2;
        maxRand = 21;
        for (int i=0;i<22;i++){ //Player's random number from 2-21
            plrval = rand()%(maxRand-minRand+1)+minRand;
        }
        cout<<"You drew "<<plrval<<" in total."<<endl;
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
                    minRand = 1; //reinitializing minimum value to increment to the player's card value
                    maxRand = 11; //reinitializing maximum value to increment to the player's card value
                    for (int i=0;i<12;i++){ //randomizing number to add to player's card value
                        randNum1 = rand()%(maxRand-minRand+1)+minRand;
                    }
                    if (randNum1 == 1 || randNum1 == 11){ //letting the player know if they drew an ace
                        cout<<"You drew an ace."<<endl;
                        if (plrval+randNum1 > 21){ //if ace+plrval is more than 21, the ace is set to 1
                            randNum1 = 1; 
                        }
                        if (randNum1 == 1 && 11+plrval < 21){ //if ace+plrval is less than 21, the ace is set to 11
                            randNum1 = 11;
                        }
                        else if (plrval == 10 && (randNum1 == 1 || randNum1 == 11)){ //Edge case for when ace needs to be 11 to get blackjack.
                            plrval = 21;
                            randNum1 = 0;
                        }
                        plrval+=randNum1;
                        cout<<"You now have "<<plrval<<"."<<endl;
                    }
                    else{ //add any other type of card to player's value
                        cout<<"You drew a "<<randNum1<<"."<<endl;
                        plrval+=randNum1;
                        cout<<"You now have "<<plrval<<"."<<endl;
                    }
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
                cout<<"The dealer flips his second card."<<endl;
                minRand = 1; //reinitializing minimum value to increment the dealer's card value
                maxRand = 11; //reinitializing maximum value to increment to the dealer's card value
                for (int i=0;i<12;i++){
                    randNum1 = rand()%(maxRand-minRand+1)+minRand;
                }
                if (randNum1 == 11 || randNum1 == 1){ //If dealer gets an ace
                    cout<<"The dealer's second card is an ace."<<endl;
                    if (dlrval+randNum1 < 21){ 
                        dlrval+=randNum1;
                        cout<<"The dealer now has "<<dlrval<<"."<<endl;
                    }
                    if (dlrval+randNum1 > 21){ //if dealer's 2nd card is an ace and dlrval + ace is greater than 21, ace turns into 1 instead of 11
                        randNum1 = 1;
                        dlrval+=randNum1;
                        cout<<"The dealer now has "<<dlrval<<"."<<endl;
                    }
                    if (randNum1 == 1 && 11+dlrval < 21){ //if dealer's second card is a 1 (ace) and 11 + dlrval is less than 21, ace turns into 11 instead of 1
                        randNum1 = 11;
                        dlrval+=randNum1;
                        cout<<"The dealer now has "<<dlrval<<"."<<endl;
                    }
                    if (dlrval == 10 && (randNum1 == 1 || randNum1 == 11)){
                        randNum1 = 21;
                        dlrval = 0;
                        dlrval+=randNum1;
                        cout<<"The dealer now has "<<dlrval<<"."<<endl;
                    }
                }
                else{ //Add card value to dealer's total value when second card is not an ace
                    cout<<"The second card is a "<<randNum1<<"."<<endl;
                    dlrval+=randNum1;
                    cout<<"The dealer now has "<<dlrval<<"."<<endl;
                }
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
                        minRand = 1; //reinitializing minimum value to increment the dealer's card value
                        maxRand = 11; //reinitializing maximum value to increment to the dealer's card value
                        for (int i=0;i<12;i++){
                            randNum1 = rand()%(maxRand-minRand+1)+minRand;
                        }
                        if (randNum1 == 1 || randNum1 == 11){ //need nested ifs for cases with ace
                            cout<<"The dealer drew an ace."<<endl;
                            if (randNum1+dlrval<21){ //add ace to dealer's value if ace + dealer's value is less than 21
                                dlrval+=randNum1;
                                cout<<"The dealer now has "<<dlrval<<".";
                                cout<<endl;
                            }
                            else if (randNum1+dlrval>21){ //add ace = 1 to dealer's value if ace + dealer's value is greater than 21
                                randNum1 = 1; 
                                dlrval+=randNum1;
                                cout<<"The dealer now has "<<dlrval<<".";
                                cout<<endl;
                            }
                            else if (randNum1 == 1 && 11+dlrval < 21){ //make ace = 11 if randomNum1 = 1 and 11 + dealer's value is less than 21
                                randNum1 = 11;
                                dlrval+=randNum1;
                                cout<<"The dealer now has "<<dlrval<<".";
                                cout<<endl;
                            }
                            if (dlrval == 10 && (randNum1 == 1 || randNum1 == 11)){ //special case, if dealer's value is 10 and randNum1 is an ace
                                dlrval = 21;
                                randNum1 = 0;
                                dlrval+=randNum1;
                                cout<<"The dealer now has "<<dlrval<<".";
                                cout<<endl;
                            }
                        }
                        else{
                                cout<<"The dealer drew a "<<randNum1<<". "<<endl; //if no ace, add card normally to the dealer's value
                                dlrval+=randNum1;
                                cout<<"The dealer now has "<<dlrval<<".";
                                cout<<endl;
                        }
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
    outFile.close();*/
    return 0;
} 
void shuffle (string face[],string suit []){
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
    string strCard;
    strCard=face[26%numface];
    strCard+=" of ";
    strCard+=suit[26%numsuit];
    cout<<setw(14)<<strCard<<endl;
}
int value (string face[], string suit [], int &n){
    n=0;
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
        }
    }
}