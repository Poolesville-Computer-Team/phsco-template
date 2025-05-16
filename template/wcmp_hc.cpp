/* IMPORTANT! */
/* HEAD cannot be modified. */
/* All custom checker logic should go in BODY. */

// Start of HEAD
#include <map>
#include <cmath>
#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
/* This is throwing an error in VSCode so I'm commenting it out.
In the actual Hackerrank platform, this part of the file can't be changed.
#ifdef __APPLE__
    #include <json/json.h>
#else
    #include <json/json.h>
#endif
using namespace Json;
*/

using namespace std;

class TestStruct {
public:
    size_t testcase_id;
    string testcase_input_path;
    string testcase_output_path;
    string testcase_expected_output_path;
    string testcase_error_path;
    vector<string> metadata_file_paths;
    string submission_code_path;
    string submission_language;
    bool testcase_result;
    size_t testcase_signal;
    float testcase_time;
    size_t testcase_memory;
    string data;
};

class ResultStruct {
public:
    bool   result;
    float  score;
    string message;
};
// End of HEAD

// Start of BODY
#include <string>
#include <cstddef>
using namespace std;

// Helper to get English ordinal suffix for n (1st, 2nd, 3rd, 4th, …)
static string englishEnding(size_t n) {
    size_t m = n % 100;
    if (m >= 11 && m <= 13) return "th";
    switch (n % 10) {
        case 1:  return "st";
        case 2:  return "nd";
        case 3:  return "rd";
        default: return "th";
    }
}

// Keep this false for a challenge where test case details should be hidden.
const bool DETAILED_FEEDBACK = false;

void run_custom_checker(const TestStruct t_obj, ResultStruct &r_obj) {
    ifstream expected(t_obj.testcase_expected_output_path);
    ifstream output  (t_obj.testcase_output_path);

    if (!expected.is_open() || !output.is_open()) {
        r_obj.result = false;
        r_obj.score = 0.0f;
        r_obj.message = "Cannot open expected/output file";
        return;
    }

    string exp_tok, out_tok;
    size_t count = 0;

    // Compare token by token
    while ( (expected >> exp_tok) && (output >> out_tok) ) {
        ++count;
        if (exp_tok != out_tok) {
            r_obj.result = false;
            r_obj.score = 0.0f;
            r_obj.message = "Wrong Answer";
            if (!DETAILED_FEEDBACK) return;

            r_obj.message = 
                to_string(count) + englishEnding(count) + 
                " word differs - expected: '" + exp_tok + 
                "', found: '" + out_tok + "'";
            return;
        }
    }

    // Both EOF: perfect match
    if (expected.eof() && output.eof()) {
        r_obj.result = true;
        r_obj.score  = 1.0f;
        if (count == 1) {
            // last token still in exp_tok/out_tok
            r_obj.message = "Passed";
            if (!DETAILED_FEEDBACK) return;

            r_obj.message = "'" + exp_tok + "'";
        } else {
            r_obj.message = "Passed";
            if (!DETAILED_FEEDBACK) return;

            r_obj.message = to_string(count) + " tokens";
        }
    }
    // Participant has extra tokens
    else if (expected.eof()) {
        r_obj.result  = false;
        r_obj.score   = 0.0f;
        r_obj.message = "Wrong Answer";
        if (!DETAILED_FEEDBACK) return;
        
        r_obj.message = "Participant output contains extra tokens";
    }
    // Participant truncated early
    else {
        r_obj.result  = false;
        r_obj.score   = 0.0f;
        r_obj.message = "Wrong Answer";
        if (!DETAILED_FEEDBACK) return;

        r_obj.message = "Unexpected EOF in the participant's output";
    }
}
// End of BODY