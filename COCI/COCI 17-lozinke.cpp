/*
COCI 17-lozinke
Idea:   Hash each password
        Create a new string consisting of all passwords, joined by { (ie pass1{pass2)
        Make a sliding window for every size of string from 1 to 10
        Calculate hash of sliding window. If it matches any of the hashes from the passwords, add the connection to a set that have all connections, in order to avoid duplicates (ie pass1=aaa, pass2=aa, aa fits in aaa 2 times)
        Count answer
        Subtract n from the answer, since each password matches itself

Status  70%
        TLE in 4/20 testcases
        WA in 2/20 testcases

UPDATE: 85%
        Solved WAs by completely removing the MOD in order to avoid collisions

UPDATE2:    80%
            Replaced map with policy based data structures to decrease constant times, but this increased memory usage, so I lose the testcases for RTE
UPDATE3:    100%
            Replaced policy based hash table with unordered_map, AC
            
  ______      _                _____
  |  ____/\   | |        /\    / ____|
  | |__ /  \  | |       /  \  | (___
  |  __/ /\ \ | |      / /\ \  \___ \
  | | / ____ \| |____ / ____ \ ____) |
  |_|/_/    \_\______/_/    \_\_____/



*/
#include<bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>

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

ll modpow(ll x, ll y){
    if(y==0)
        return 1;
    if(y==1)
        return x;

    ll z = modpow(x, y/2);
    z = (z*z);

    if(y%2==1)
        z = z*x;
    return z;
}

int main(){
    ll n;
    cin>>n;
    string a[n];
    string b = "";

    for(ll i=0;i<n;i++){
        cin>>a[i];
        b+=a[i];
        b+="{";
    }
    unordered_map<ll, int> hashes;
    vector<set<ll> > ans;
    ans.assign(n+1, set<ll>());

    ll hash = 0;
    for(ll i=0;i<n;i++){
        hash = 0;
        for(ll j=0;j<a[i].size();j++)
            hash = (hash*29) + (a[i][j] - 'a'+1);
        //cout<<hash<<endl;
        hashes[hash]++;
    }
    for(int siz=1;siz<=10;siz++){
        //cout<<siz<<": -------------\n";
        int strcnt = 0;
        int cnt=0;
        ll currhash = 0;
        while(cnt<siz){
            currhash = currhash * 29 + (b[cnt] - 'a' + 1);
            currhash = currhash;
            if(b[cnt]=='{')
                strcnt++;
            cnt++;
        }
        for(int i=cnt;i<b.size();i++){
            //cout<<strcnt<<" "<<currhash<<endl;
            if(hashes[currhash]){

                ans[strcnt].insert(currhash);
            }
            currhash -= modpow(29, siz - 1)*(b[i-siz] - 'a' + 1);
            currhash*=29;
            currhash += (b[i] - 'a' + 1);
            if(b[i]=='{')
                strcnt++;
        }

        if(hashes[currhash]){
            ans[strcnt].insert(currhash);
        }
    }
    ll anss=0;
    for(ll i=0;i<=n;i++){
        for(set<ll>::iterator it=ans[i].begin();it!=ans[i].end();it++){
            anss += hashes[(*it)];
        }
    }
    cout<<anss-n<<endl;


}

