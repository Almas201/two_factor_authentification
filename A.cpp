#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>

#define ll long long
#define lld long double
#define mp make_pair
#define endl "\n"
#define pb push_back
#define mod 1000000007
#define Kazakhstan ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

using namespace std;


/**
@author: Almas Turganbayev
*/

vector<ll> tries(50LL);
vector<string> usernames(50LL);
vector<string> passwords(50LL);
vector<string> questions(50LL);
vector<string> answers(50LL);
vector<string> OTP(50LL);
vector<string> HashedPassword(50LL);
bool ok = 1;
ll curr = 0;

ll check(string s){
    if(s=="1") return 1;
    if(s=="2") return 2;
    return 0;
}

ll search(string user){
    for(int i = 0; i < 50; i++){
        if(usernames[i]==user) return i;
    }
    return -1;
}

string generateOTP(ll sizef){
    string str = "abcdefghijklmnopqrstuvwxyz"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    ll n = str.length();
    string OTP;
    for(int i = 1; i <= sizef; i++){
        OTP.push_back(str[rand()%n]);
    }
    return OTP;
}

string encryptPass(string password, ll shift){
    string res = "";
    for(int i = 0; i < password.size(); i++){
        if(isupper(password[i])){
            res+=char(int(password[i]+shift-65)%26+65);
        }else{
            res+=char(int(password[i]+shift-97)%26+97);
        }
    }
    return res;
}

ll recover(ll user_id){
    printf("Question to recover username: ");
    cout<<questions[user_id]<<endl;
    string answer="";
    printf("Answer: ");
    cin>>answer;
    if(answers[user_id]==answer){
        tries[user_id]=0;
        printf("Username is unblocked! Try to SignIn");
    }else{
        printf("Error! Try it next time!!!");
    }

}

void signup(){
    string username="", password="", question="", answer="";
    printf("Enter username: ");
    cin>>username;
    printf("Enter password: ");
    cin>>password;
    printf("Enter question: ");
    cin>>question;
    printf("Enter answer: ");
    cin>>answer;

    usernames[curr]=username;
    passwords[curr]=password;
    questions[curr]=question;
    answers[curr]=answer;
    curr++;
}

void signin(){
    string username="", password="";
    printf("Enter username: ");
    cin>>username;
    ll user_id=search(username);
    if(user_id!=-1LL){
        if(tries[user_id]>=2){
            printf("The user is blocked!\nDo u recover it? If u wanna enter Y or N: ");
            string s="";
            cin>>s;
            if(s=="y"||s=="Y") recover(user_id);
            if(s=="n"||s=="N") return;
        }else{
            printf("Enter password: ");
            cin>>password;
            if(password==passwords[user_id]){
                string encrpyt = encryptPass(password, 4);
                string enctPass;
                printf("\n");
                cout<<"             ENCRYPTED PASSWORD: "<<"["<<encrpyt<<"]";
                printf("\n");
                HashedPassword[user_id]=encrpyt;
                printf("\nJoin with Encrpyted/Decrypted Password: ");
                cin>>enctPass;
                if(enctPass==HashedPassword[user_id]||enctPass==passwords[user_id]){
                    cout<<"\n\nOK! U've done STEP-1, next complete STEP-2\n\n";
                    srand(time(NULL));
                    string gen = generateOTP(6);
                    OTP[user_id]=gen;
                    cout<<"             GENERATED CODE: "<<gen;
                    string tryied = "";
                    printf("\n");
                    printf("            VERIFY THE CODE: ");
                    cin>>tryied;
                    if(tryied==OTP[user_id]){
                        printf("\n");
                        cout<<"["<<usernames[user_id]<<"]"<<" "<<"You are Joined! Welcome!";
                        printf("\n");
                    }else{
                        printf("\nWrong STEP-2!!!"); tries[user_id]++;
                    }
                }else{
                    printf("\nWrong!!"); tries[user_id]++;
                }
            }
            else{printf("\nWrong STEP-1!!!"); tries[user_id]++;}
        }
    }else{
        printf("\nNo such a user");
    }
}

void menu(){
    printf("            #### AUTHOR -> ALMAS TURGANBAYEV ########\n");
    string choice="";
    while(ok){
        printf("Welcome to MENU!!!\n1. SignIn\n2. SignUp\nIf u wanna to SignIn enter 1 or 2 to SignUp");
        printf("\nUr choice: ");
        cin>>choice;
        int num = check(choice);
        switch(num){
            case 1:
                signin();
                break;
            case 2:
                signup();
                break;
            default:
                printf("Nothing!!!");
                break;
        }
        printf("\nIf u wanna continue enter 1 or 0 to finish: ");
        cin>>ok;
        choice="";
    }
}

int main(){
    ll t = 1;
    //cin >> t;
    while(t--){
        menu();
    }
}
