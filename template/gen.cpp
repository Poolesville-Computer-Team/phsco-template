#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    
    // command-line options passed when generating test cases
    // preferable to use these instead of creating another generator file
    int n = opt<int>("n");
    int int_opt = opt<int>("int");
    ll ll_opt = opt<ll>("longlong");
    string str_opt = opt<string>("string");

    cout << n << endl; // cout -> test case file

    for (int i = 0; i < n; i++) {
        /*
        * Please read the documentation for class "random_t" and use "rnd" instance in
        * generators. Probably, these sample calls will be useful for you:
        *              rnd.next(); rnd.next(100); rnd.next(1, 2);
        *              rnd.next(3.14); rnd.next("[a-z]{1,100}").
        * 
        * (testlib.h documentation)
        */
        int rnum = rnd.next(0, int_opt); 
        
        // any other helper functions or logic can be used here
        cout << rnum << endl; // write to test file via cout
    }
    
    return 0;
}