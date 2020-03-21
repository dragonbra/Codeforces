#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 0x3f3f3f3f;
const int mod = 1e9+7;
const double eps = 1e-5;
const int N = 1e5 + 10;
const int M = 1e2 + 10;

void redirect() {
    #ifdef LOCAL
        freopen("1.in","r",stdin);
        freopen("1.out","w",stdout);
    #endif
}

struct node{
    ll num;
    string book;
    double price;
    void out(){
        printf("%lld ",num);
        cout<<book;
        printf(" %.2lf\n",price);
    }
} List[N];

int n,m;

bool cmp(node a,node b){
    return a.price > b.price;
}

void check(string t){
    int cnt = 0;
    for(int i=1;i<=n;i++){
        if(List[i].book==t){
            cnt++;
        }
    }
    if(cnt){
        cout<<cnt<<endl;
        for(int i=1;i<=n;i++){
            if(List[i].book==t) List[i].out();
        }
    } else {
        puts("Sorry，there is no your favourite!");
    }
}

int main() {
    redirect();

    ll num; string book; double price;

    cin>>n;
    for( int i=1;i<=n;i++ ) {
        if( num==0 && book=="0" && price==0 ) break;

        cin>>num>>book>>price;

        List[i].num = num, List[i].book = book, List[i].price = price;
    }

    cin>>m;
    for( int i=1;i<=m;i++ ) {
        int pos;
        cin>>pos;
        if(pos>=1&&pos<=n){
            List[pos].out();
        } else {
            puts("Sorry，the book on the best position doesn't exist!");
        }
    }

    return 0;
}

/*
-----------------
author:dragon_bra
-----------------
*/