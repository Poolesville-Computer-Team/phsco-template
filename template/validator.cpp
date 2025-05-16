#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// add any numerical problem constraints here
const int max_testcases = 1'000;
const ll max_n = 1'000'000'000'000'000;

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);

    int numtests = inf.readInt(1, max_testcases, "num-tests");
    inf.readEoln();
    // unlike in checkers or solution files, whitespace matters here!
    // validator will reject a test case that is missing proper whitespace/eolns

    for (int i = 1; i <= numtests; i++) {
        // parsing test case i
        setTestCase(i);
        
        // refer to InStream from testlib.h
        ll num1 = inf.readLong(1, max_n, "placeholder-name1");
        inf.readSpace(); // !!!
        ll num2 = inf.readLong(1, max_n, "placeholder-name2");
        inf.readEoln();
        
        // ensure that passed boolean condition is true
        // (will reject if false)
        ensuref(num1 < num2, "num1 should be less than num2");
    }

    inf.readEof(); // !!!
    return 0;
}