/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/*
 * File:   main.cpp
 * Author: Joseph Caraan
 *
 * Created on February 11, 2023, 5:44 PM
 */
#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <stdlib.h> //for exit()

using namespace std;
/*
 *
 */
void aryshuffle (string [],string []); //shuffles face and suit
void wagetrack (vector<float>&, float); //tracks the wages of each round
int value (string [], string [], int &,int &, int); //calls shuffle function, then sets a value to the card pulled
void print (string [], string []);  //prints out which card was drawn
bool win(bool); //boolean which decides whether player won or not
int balance(int, float); //function that tracks balance
float balance(float, int); //overload balance function to ensure float result
bool binSrch(vector<int>&, int, int , int&); //binary search for a blackjack
void selSrt(vector<int>&,int n); //sorts array of values pulled and settled on by player
void bublSrt(vector<int>&,int n); //array that sorts the values of the player

int main(int argc, char** argv) {
    //Opening file blackjack.TXT using fstream
    srand(static_cast<unsigned>(time(0))); //setting random seed
    //Declaring variables
    const int NCARDS=52;//Number of Cards
    const int one = 1;
    const int SIZE = 100;
    string face[]={"Ace","2","3","4","5",
                    "6","7","8","9",
                    "10","Jack","Queen","King"};   //Face Values of the Cards
    string suit[]={"Spades","Diamonds",
                   "Clubs","Hearts"}; //All the suits in a deck
    vector <float> track1(0); //STL Vector, tracks wages
    vector <int> track2(0); //STL Vector, tracks player values
    float blnce; // Balance of player
    int plrval; //Player's card value
    int dlrval; //Dealer's card value
    int wincnt; //Amount of wins 
    int losecnt; //Amount of losses 
    int valcnt; //Amount of wrong inputs created by user
    float absol; //Calculates the amount of money lost or gained playing 
    float gamecnt; //Amount of games
    float prcnt; //Percent of the games won 
    bool decis; //decides if player won or not
    float result = (int)blnce; //decides whether to add or subtract from the balance
    int swtwage; //switch case for the wager of the player
    float wage; //custom amount input by the user
    char res; //response from the user, whether they want to continue or not
    int n; //defaulted argument in value function
    int a; //used for overloading function balance
    int indx; //index used for tracking certain values for certain games
    string DrOrSt; //prime decider on how loops end/continue. "draw or stand"
   
    //Initializing Variables
    indx = 0;
    a = 0;
    n = 0;
    valcnt = 0;
    gamecnt = 0;
    swtwage = 4;
    blnce = 10000;
    decis = true;
    res = 'y';
    //Beginning output
    cout<<"Welcome to the Blackjack game!"<<endl;
    cout<<"Balance: $"<<fixed<<setprecision(2)<<balance(blnce,a)<<endl; //iomanip use
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
                while(wage<0.009 || wage>blnce){ //input validation for entering a custom wage
                    cout<<"Error. Please input a wager no greater than your balance"
                            " and one that is at least $0.01: $";
                    cin>>wage;
                    valcnt++;
                    if(valcnt == 4){
                        cout<<endl<<"WARNING: One more bad input by the user will result in"
                                " the termination of the program."<<endl;
                    }
                    if(valcnt == 5 && wage<0.009 || wage>blnce){
                        exit(0); //utilization of exit from input validation
                    }
                }
                valcnt = 0;
                break; //NOTE: USING BREAK FOR THE SWITCH CASE, NOT THE LOOP
        }
        wagetrack(track1,wage); //track the wage entered by user
        cout<<"The dealer is shuffling the cards..."<<endl<<endl;
        cout<<"The dealer's face up card is a/n ";
        dlrval = value(face,suit, plrval, dlrval,n); //setting the dealer's value to the random card pulled
        print(face,suit); //print out the dealer's face up card
        cout<<"."<<endl;
        cout<<"You drew a/n ";
        plrval = value(face,suit, plrval, dlrval,n); //assign value of card pulled
        print(face,suit);
        cout<<" and a/n ";
        plrval += value(face,suit, plrval, dlrval,n);
        print(face,suit); //print both cards pulled
        cout<<"."<<endl;
        cout<<"You have a value of "<<plrval<<" in total."<<endl; //total player value
        if (plrval == 21){ //Lucky Blackjack straight off
            track2.push_back(plrval); //track the player's value for this game that was played
            cout<<"Blackjack! You win!"<<endl;
            decis = true;
        }
        else{
            cout<<"Enter draw or stand: "; //prompt user to draw or stand
            cin>>DrOrSt;
            cout<<endl;
            if (DrOrSt != "draw" || DrOrSt != "stand"){ //Input Validation for draw or stand, also string library used here
                while (DrOrSt != "draw" && DrOrSt != "stand"){
                    valcnt++; //counting how many times validation is broken
                    cout<<"Error. Please enter draw or stand: ";
                    cin>>DrOrSt;
                    cout<<endl;
                    if(valcnt == 4){ //input validation warning
                        cout<<endl<<"WARNING: Two more bad inputs by the user will result in"
                                " the termination of the program."<<endl;
                    }
                    if(valcnt == 6 && (DrOrSt != "draw" || DrOrSt != "stand")){
                        exit(0); //utilization of exit from input validation
                    }
                }
                valcnt = 0; //reset input validation counter
            }                                          
            if (DrOrSt == "draw"){
                while (DrOrSt == "draw"){
                    cout<<"You drew a/n ";
                    plrval += value(face,suit, plrval, dlrval,n); //add drawn card value to player's value
                    print(face,suit);
                    cout<<"."<<endl;
                    cout<<"You now have "<<plrval<<"."<<endl;
                    if(plrval>21){ //condition for a bust
                        track2.push_back(plrval); //track player value when win/lose
                        cout<<"You busted!"<<endl;
                        decis = false;
                        DrOrSt = "exit";
                    }
                    else if(plrval==21){ //condition for a blackjack
                        track2.push_back(plrval); //track player value when win/lose
                        cout<<"Blackjack! You win!"<<endl;
                        decis = true;
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
                track2.push_back(plrval); //track player value for when player stands
                dlrval += value(face,suit, plrval, dlrval,n); //add face down card value to dealer value
                cout<<"The dealer flips his second card. It is a ";
                print(face,suit);
                cout<<"."<<endl;
                cout<<"The dealer now has "<<dlrval<<"."<<endl;
                if(dlrval>plrval || dlrval==21){ //Condition for dealer to beat player
                        cout<<"The dealer wins! You lose!"<<endl;
                        decis = false;
                        DrOrSt = "exit";
                }
                else if (dlrval>21){ //Condition for dealer to bust
                        cout<<"The dealer busted! You win!";
                        decis = true;
                        DrOrSt = "exit";
                }
                else if (dlrval==plrval){ //this is when there is a tie
                    cout<<"The dealer received your value. "
                            "No balance will be added or removed."<<endl;
                }
                else if (dlrval<21 && dlrval<plrval){ //Condition for dealer grab more cards, this is where dealer grabs more cards
                    cout<<"Dealer is now pulling more cards..."<<endl;
                    while (dlrval < plrval){ //loop for dealer to grab more cards until greater than or equal to player
                        dlrval += value(face,suit, plrval, dlrval,n); //grab another card and put into deck
                        cout<<"The dealer drew a/n ";
                        print(face,suit); //prints dealers pulled card
                        cout<<"."<<endl;
                        cout<<"The dealer now has "<<dlrval<<"."<<endl;
                    }
                    if((dlrval>plrval && dlrval<21 ) || (dlrval==21 && plrval != 21)){ //condition for dealer to win, if he/she gets 21 or is greater than player while being less than or equal to 21
                        cout<<"The dealer wins! You lose!"<<endl;
                        decis = false;
                        DrOrSt = "exit";
                    }
                    else if (dlrval>21){ //condition for dealer to bust when pulling more cards
                        cout<<"The dealer busted! You win!"<<endl;
                        decis = true;
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
            result = (win(decis)==true) ? blnce+=wage : blnce-=wage; //ternary operator deciding whether to add or subtract the wager from balance
            result = (win(decis)==true) ? wincnt++ : losecnt++; //counting amount of games won or lost
            cout<<"New Balance = $"<<fixed<<setprecision(2)<<blnce<<endl;
        }
        else if (dlrval==plrval){
            cout<<"Balance = $"<<fixed<<setprecision(2)<<blnce<<endl; //formatting same balance on a tie
        }
        if (blnce > 0){ //runs statement if user has money
            cout<<"Enter 'y' to keep playing and 'n' to quit: ";
            cin>>res;
        }
        if (res == 'y' && blnce>0){ //runs if user wants to keep playing and has money
            cout<<endl<<"Enter '1' to wager $20, '2' to wager $50, "
                    "'3' to wager $100, or '4' to select your own wager: ";
        }
        else if (blnce==0){ //runs if user is out of money
            cout<<"You're out of money! Go grab some more!";
        } 
    }while (res=='y' && blnce>0); 
    //This statistics code runs after the blackjack game
    cout<<endl;
    fstream outFile;
    outFile.open("blackjack.TXT"); //opening blackjack.TXT file
    ifstream inFile;
    inFile.open("blackjackinput.TXT"); //opening blackjackinput.TXT file
    string o,p;
    inFile>>o>>p;
    outFile<<o<<" "<<p<<endl;
    outFile<<"You played for "<<fixed<<setprecision(0)<<gamecnt<<" round/s."<<endl; //amount of games played
    int mat [2][2] = {{wincnt,losecnt}}; //2D array
    outFile<<"You won "<<mat[0][0]<<" times."<<endl; //amount of wins
    outFile<<"You lost "<<mat[0][1]<<" times."<<endl; //amount of losses
    prcnt = (wincnt/gamecnt)*100;
    outFile<<"You won "<<fixed<<setprecision(2)<<prcnt<<"% of the rounds that you played."<<endl; //percentage of games won
    absol = abs(10000 - blnce); //cstdlib use
    outFile<<"You gained/lost $"<<absol<<"."<<endl; //amount of money gained/lost
    for(int i = 0; i < gamecnt;i++){
        outFile<<"You bet "<<track1[i]<<" on round "<<i+1<<". "<<endl; //displays the wages of each round
    }
    indx = 0;
    if(binSrch(track2,SIZE,plrval,indx))outFile<<"You got a blackjack on round "<<indx+1<<"."<<endl; //searches for when player gets a blackjack
    indx = 0;
    selSrt(track2,gamecnt); //sorting array of player values using selection sort
    outFile<<"Sorted array of player's values using selection sort:"<<endl; 
    for(int i = 0; i < gamecnt; i++){
        outFile<<track2[i]<<" ";
        if (i%10==9)cout<<endl;
    }
    outFile<<endl; 
    bublSrt(track2, gamecnt); //sorting array of player values using bubble sort
    outFile<<"Sorted array of player's values using bubble sort:"<<endl;
    for(int i = 0; i < gamecnt; i++){
        outFile<<track2[i]<<" ";
        if (i%10==9)cout<<endl;
    }
    inFile.close(); //close blackjackinput.TXT
    outFile.close(); //close blackjack.TXT
    return 0;
} 
void aryshuffle (string face[],string suit []){ //function in which arrays face and suit are passed into, and are later passed from the value function
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
void wagetrack (vector<float> &track1, float wage){ //function in the vector "track" is passed into and later from this wagetrack function
    track1.push_back(wage); //pushback wage from specific round
}
int value (string face[], string suit [], int &plrval, int &dlrval, int n = 0){ //defaulted argument n
    aryshuffle(face,suit);
    int tens[] = {10,10,10}; //parallel array
    int length = face[n].length();
    char* chrary = new char [length+1];
    strcpy(chrary,face[n].c_str());
    for(int i=0;i<length;i++){
        if(isdigit(chrary[i])){ //checking if char array has a digit
            int num = stoi(chrary);
            return num;
        }
        else{
            if (chrary[i]=='K' || chrary[i]=='Q' ||chrary[i]=='J'){ //return 10 from parallel array if card is a King, Queen, or Jack
                return tens[0];
            }
            if (chrary[i]=='A' && plrval+11>=21){ //set ace to 11 condition for player
                return 1;
            }
            else if (chrary[i]=='A' && plrval+11<=21){ //set ace to 11 condition for player
                return 11;
            }
            if (chrary[i]=='A' && dlrval+11>=21){ //set ace to 1 condition for dealer
                return 1;
            }
            else if (chrary[i]=='A' && dlrval+11<=21){ //set ace to 11 condition for dealer
                return 11;
            }
        }
    }
}
void print(string face[], string suit []){ //prints out face and suit of a card pulled
    string strCard;
    strCard=face[26%13];
    strCard+=" of ";
    strCard+=suit[26%4];
    cout<<strCard; 
}
bool win(bool decis){ //decides whether player won or not
    if(decis){
        return true; //return true if the decision is true
    }
    else{
        return false; //else, return false
    }
}
int balance(int blnce, float a){ //add wager to balance if won, overload to make sure balance stays a float
    blnce+=a;
    return blnce;
}
float balance(float blnce, int a){ //overloading balance function
    blnce+=a;
    return blnce;
}
bool binSrch(vector<int> &track2, int n, int plrval, int &indx){ //binary searching for specific value, in this case 21
    int middle = (n/2)-1;
    indx = 0;
    if(track2[middle]==plrval)return middle;
    if(track2[middle]>plrval){ //split in the middle, check left
        for(indx = middle; indx>=0; indx--){
            if(track2[indx]==plrval)return indx;
        }
    }
    if(track2[middle]<plrval){ //split in the middle, check right
        for(indx = middle; indx<n; indx++){
            if(track2[indx]==plrval)return indx;
        }
    }
}
void selSrt(vector<int> &a,int n){ //selection sort utilizing xor 
    for (int j = 0; j<n-1;j++){
        for (int i = j+1; i<n;i++){
            if (a[j]>a[i]){
                a[j]=a[j]^a[i];
                a[i]=a[j]^a[i];
                a[j]=a[j]^a[i];    //similar to swap
            }
        }
    }
}
void bublSrt(vector<int> &a,int n){ //bubble sorting player values at the end of the game
    for(int i = 0; i<n-1 ; i++){    //in blackjack.TXT
        for (int j = 0; j<n-i-1;j++){
            if (a[j]>a[j+1]){
                a[j+1]=a[j+1]^a[j]; //utilizing xor once again
                a[j]=a[j+1]^a[j];
                a[j+1]=a[j+1]^a[j];
            }
        }
    }
}
