# cse120pa3tests
Testing utilities for PA3. Use it at your own risk!

*IMPORTANT: DON'T clone this repo directly, but manually copy it to the server (i.e. with VS Code). Just in case git would mess things up, unless you're a git master.*

## Installation

Put `pa3tests.c` and `tester.py` under your `pa3` folder.

Then add this in `Makefile`:
```bash
pa3tests:	pa3tests.c pa3d.c aux.h umix.h mycode3.o
	$(CC) $(FLAGS) -o pa3tests pa3tests.c mycode3.o
```

Run `make pa3tests` and it will build `pa3tests`. Then you can run a target test via env variable `N` (from 1 to 13) with:
```bash
N=1 ./pa3tests
```

**PS: You have to comment out** `Main()` **function of your** `pa3d.c` before running `make pa3tests`, else there'll be error as they're conflicting with `Main()` from `pa3tests.c`.

**DON'T FORGET to get it back when you submit, just to be safe.**

## To run all tests
To run all 13 tests automatically:
```bash
python tester.py runtests
```
This will dump all output into `testers/test_outputs.txt` for debugging. 

It also dumps all road traces from output into `testers/test_roadtraces.txt` for comparison. It is meant to be the way to **compare results with another key road traces file** i.e. from your friend. I provided one in this repo too (`tester/key_roadtraces.txt`). Tell me if it is different from yours!

## *To compare your roadtrace files with key file:
To compare your roadtraces file with key file:
```bash
python tester.py compare
```

This will compare `tester/test_roadtraces.txt` and `tester/key_roadtraces.txt` and tell you which test output is different.

NOTE: Some test (i.e. 8) will give different roadtraces for each run so don't stress out.


## To generate key result yourself
You can also generate a roadtrace key from your own output with `--key` option:
```bash
python tester.py runtests --key
```
This will generate two same files, just with different names (`tester/key_outputs.txt` and `tester/key_roadtraces.txt`).


## To add a new test
Currently there are 13 tests to run (`N=1` to `N=13`). 

To add a new one, here are the steps. In `pa3tests.c`:
1. Add a new test , i.e. `void Test14() { ... }`
2. In `Main()` (at the bottom), add your function to the list of test functions `func_ptr`.

Lastly, in `tester.py`, just update `N_tests` to reflect the right number of tests.

As you can see there's no magic here. When you pass env variable `N`, it just runs any function at index `N-1` in `func_ptr` array of test functions. Rename function any way you want.

## Collaboration
Feel free to open PR for new test, or bug. Or just to discuss particular test cases or outputs. NOT A PLACE TO DISCUSS SOLUTION ITSELF, BUT TEST CASE.