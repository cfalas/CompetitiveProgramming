/*
Solution:   Find first character in 2 guesses (first ask for 2 characters(AB) and then one of the 2(A or X))
            Find all of the rest characters except last one by sending s+"A"+s+"BA"+s+"BB"+s+"BY", so that when the next character is A, it will return s.size()+1, if it is B, it will return s.size()+2 and if it is Y it will return s.size(). The same logic is applied according to what the first character was
            Find the last character in the same way as the first (Can't ask like before, as it will never return s.size()+2, because there is no such character)

Status:     0% - Submitted before I found the grader, so I could test, I couldn't even compile it
            0% - Mistyped one of the characters for A instead of B, didn't notice on the tests that I was using
            5% - Didn't test for N=1, it returned a string of 2 characters
            100% - AC

  ______      _                _____ 
  |  ____/\   | |        /\    / ____|
  | |__ /  \  | |       /  \  | (___  
  |  __/ /\ \ | |      / /\ \  \___ \
  | | / ____ \| |____ / ____ \ ____) |
  |_|/_/    \_\______/_/    \_\_____/ 
                                            
                                            

*/
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define INF 1000000
#define MOD 1000000007

typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef pair<ii, ll> iii;
typedef vector<ii> vii;

#define F first
#define S second

#define mp make_pair
#define endl '\n'
#define priority_queue pq

#include "combo.h"

string guess_sequence(int N) {
    // Find first character in 2 moves
    char first;
    if(press("AB")>=1){
        if(press("B"))
            first = 'B';
        else
            first = 'A';
    }
    else{
        if(press("X"))
            first = 'X';
        else
            first = 'Y';
    }
    string s = "";
    s+=first;
    if(N==1)
        return s;
    for(int i=1;i<N-1;i++){
        if(first=='A'){
            int ans = press(s + "X" + s + "BX" + s + "BB" + s + "BY");
            if(ans==s.size())
                s+="Y";
            else if(ans==s.size()+1)
                s+="X";
            else
                s+="B";
        }
        if(first=='B'){
            int ans = press(s + "X" + s + "AX" + s + "AA" + s + "AY");
            if(ans==s.size())
                s+="Y";
            else if(ans==s.size()+1)
                s+="X";
            else
                s+="A";
        }
        if(first=='X'){
            int ans = press(s + "A" + s + "BA" + s + "BB" + s + "BY");
            if(ans==s.size())
                s+="Y";
            else if(ans==s.size()+1)
                s+="A";
            else
                s+="B";
        }
        if(first=='Y'){
            int ans = press(s + "X" + s + "BX" + s + "BB" + s + "BA");
            if(ans==s.size())
                s+="A";
            else if(ans==s.size()+1)
                s+="X";
            else
                s+="B";
        }
    }
    if(first=='A'){
        if(press(s + "B" + s + "X")==s.size()+1){
            if(press(s + "B")==s.size()+1)
                s+="B";
            else
                s+="X";
        }
        else
            s+="Y";
    }
    if(first=='B'){
        if(press(s + "A" + s + "X")==s.size()+1){
            if(press(s + "A")==s.size()+1)
                s+="A";
            else
                s+="X";
        }
        else
            s+="Y";
    }
    if(first=='X'){
        if(press(s + "B" + s + "A")==s.size()+1){
            if(press(s + "B")==s.size()+1)
                s+="B";
            else
                s+="A";
        }
        else
            s+="Y";
    }
    if(first=='Y'){
        if(press(s + "B" + s + "X")==s.size()+1){
            if(press(s + "B")==s.size()+1)
                s+="B";
            else
                s+="X";
        }
        else
            s+="A";
    }
    return s;
}

