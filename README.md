# PHSCO Contest Template

> ⚠️⚠️⚠️ IMPORTANT! Use this repository as a template; obviously, do not push new contest problem files to this repository.

This repository contains the necessary libraries and templates to manage the problem files for a new contest on Polygon/Codeforces.

`bits/stdc++.h` is provided and recommended for usage in C++ code, mainly solution files.

`testlib.h` is an inbuilt header on Polygon and is practically required for writing generator and validator files.

`exports/` and `exports/export.py` is used to translate Polygon-generated contest files into Hackerrank's test case format. If a contest will be hosted on Codeforces, ignore this folder. Translation should ideally occur after all other problem files are written.

Place problem files in `problems/A/`, `problems/B/`, and so on. This should include the problem statement PDF, if applicable.

`template/` contains example generator, solution, and validator files.

## Problem Files

Each problem should contain `validator.cpp`, at least one `solution.cpp`, and preferably at least one `generator.cpp`. (File names can change.)

`validator.cpp` is required and checks whether a test case is valid, to ensure programs are not passed unfamiliar input.

`solution.cpp` and other solution files will be checked against the test cases. At least one solution should be the "main solution" (answer key).

`generator.cpp` automatically generates specific test cases (i.e. those that test constraint limits).

It is recommended to use in-built `wcmp.cpp` as the checker on Codeforces. If the problem needs a special checker (i.e. those with multiple possible solutions), write a custom `checker.cpp`. `template/wcmp_cf.cpp` contains the source code for the `wcmp.cpp` checker on Codeforces. `template/wcmp_hc.cpp` contains source code for Hackerrank's custom checker. When translating a contest from Codeforces to Hackerrank, both checker files should be written and used.

> Note: Problems should be written & tested on Codeforces due to advanced solution stress-testing features, even if Hackerrank will be the main contest platform. (Of course, some testing on Hackerrank should still be done, but the process is much less streamlined - for example, solution files must be tested manually.)