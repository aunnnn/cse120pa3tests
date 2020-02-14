#include <stdlib.h>
#include "pa3d.c"

void InitRoad(void);
void driveRoad(int from, int mph);

void Test1()
{
    DPrintf("TEST: Car 1 from west\n");

    DPrintf("\n>> 1 arrives from WEST\n\n");
    driveRoad(WEST, 40);
}

void Test2()
{
    DPrintf("TEST: Car 1 from east\n");
    DPrintf("\n>> 1 arrives from EAST\n\n");
    driveRoad(EAST, 40);
}

void Test3()
{
    DPrintf("TEST: Car 1 and 2 (faster) from west, should be able to go both without crashing\n");

    if (Fork() == 0) {
        DPrintf("\n>> 2 arrives from WEST\n\n");
        driveRoad(WEST, 60);
        Exit();
    }
    DPrintf("\n>> 1 arrives from WEST\n\n");
    driveRoad(WEST, 40);
}

void Test4()
{
    DPrintf("TEST: Car 1 from west and 2 from east, 1 should go first then 2\n");

    if (Fork() == 0) {
        DPrintf("\n>> 2 arrives from EAST\n\n");
        driveRoad(EAST, 60);
        Exit();
    }
    DPrintf("\n>> 1 arrives from WEST\n\n");
    driveRoad(WEST, 40);
}

void Test5()
{
    DPrintf("TEST: Car 1 from west and then with some delay 2 from east (while 1 is still on the road), 1 go first then 2\n");

    if (Fork() == 0) {
        Delay(500);
        DPrintf("\n>> 2 arrives from EAST\n\n");
        driveRoad(EAST, 60);
        Exit();
    }
    DPrintf("\n>> 1 arrives from WEST\n\n");
    driveRoad(WEST, 40);
}

void Test6()
{
    DPrintf("TEST: Car 1 from west, out of road, then car 2 arrives east, 1 go first then 2\n");

    if (Fork() == 0) {
        Delay(1000);
        DPrintf("\n>> 2 arrives from EAST\n\n");
        driveRoad(EAST, 60);
        Exit();
    }
    DPrintf("\n>> 1 arrives from WEST\n\n");
    driveRoad(WEST, 40);

    
}

void Test7()
{
    DPrintf("TEST: Car 1 from west, car 2 arrives while 1 on road, car 3 arrives while 2 is on road and 1 is already out, should be able to go\n");

    if (Fork() == 0) {
        Delay(200);
        DPrintf("\n>> 2 arrives from EAST\n\n");
        driveRoad(EAST, 40);
        Exit();
    }

    if (Fork() == 0) {
        Delay(1000);
        DPrintf("\n>> 3 arrives from EAST\n\n");
        driveRoad(EAST, 60);
        Exit();
    }

    DPrintf("\n>> 1 arrives from WEST\n\n");
    driveRoad(WEST, 40);
}

// Same as pa3d original test. 
// NOTE: Result can be different between each run
void Test8()
{
	DPrintf("TEST: 1 from east, 3 and 4 arrive east and west same time, then 2 arrives west\nNOTE: Result can be DIFFERENT between each run\n");
	if (Fork() == 0) {
		Delay(1200);			// car 2
		DPrintf("\n>> 2 arrives from WEST\n\n");
		driveRoad(WEST, 60);
		Exit();
	}

	if (Fork() == 0) {
		Delay(900);			// car 3
		DPrintf("\n>> 3 arrives from EAST\n\n");
		driveRoad(EAST, 50);
		Exit();
	}

	if (Fork() == 0) {
		Delay(900);			// car 4
		DPrintf("\n>> 4 arrives from WEST\n\n");
		driveRoad(WEST, 30);
		Exit();
	}

	DPrintf("\n>> 1 arrives from EAST\n\n");
	driveRoad(EAST, 40);			// car 1
}

void Test9()
{
    DPrintf("TEST: 1 from west, then A LOT OF CARS arrive east.\n");
    
    if (Fork() == 0) {
        Delay(400);
        DPrintf("\n>> 2 arrives from EAST\n\n");
        driveRoad(EAST, 100);
        Exit();
    }

    if (Fork() == 0) {
        Delay(500);
        DPrintf("\n>> 3 arrives from EAST\n\n");
        driveRoad(EAST, 50);
        Exit();
    }

    if (Fork() == 0) {
        Delay(600);
        DPrintf("\n>> 4 arrives from EAST\n\n");
        driveRoad(EAST, 50);
        Exit();
    }

    if (Fork() == 0) {
        Delay(600);
        DPrintf("\n>> 5 arrives from EAST\n\n");
        driveRoad(EAST, 100);
        Exit();
    }

    if (Fork() == 0) {
        Delay(700);
        DPrintf("\n>> 6 arrives from EAST\n\n");
        driveRoad(EAST, 150);
        Exit();
    }

    if (Fork() == 0) {
        Delay(720);
        DPrintf("\n>> 7 arrives from EAST\n\n");
        driveRoad(EAST, 100);
        Exit();
    }

    if (Fork() == 0) {
        Delay(730);
        DPrintf("\n>> 8 arrives from EAST\n\n");
        driveRoad(EAST, 100);
        Exit();
    }

    if (Fork() == 0) {
        Delay(740);
        DPrintf("\n>> 9 arrives from EAST\n\n");
        driveRoad(EAST, 70);
        Exit();
    }

    DPrintf("\n>> 1 arrives from WEST\n\n");
    driveRoad(WEST, 40);
}

// Car 1 slow from west, 
// 2, 3, 4 closely from east
// Car 5 then enter from west, should go after 2
// 5 |----1>-----| 2,3,4
// Should be 1,2,5,3,4
void Test10()
{
    DPrintf("TEST: 1 slowly from west, 2,3,4 closely arrive east, 5 then enter from west, should go after 2, i.e. 1,2,5,3,4\n");
    if (Fork() == 0) {
        Delay(400);
        DPrintf("\n>> 2 arrives from EAST\n\n");
        driveRoad(EAST, 100);
        Exit();
    }

    if (Fork() == 0) {
        Delay(500);
        DPrintf("\n>> 3 arrives from EAST\n\n");
        driveRoad(EAST, 50);
        Exit();
    }

    if (Fork() == 0) {
        Delay(600);
        DPrintf("\n>> 4 arrives from EAST\n\n");
        driveRoad(EAST, 50);
        Exit();
    }

    if (Fork() == 0) {
        Delay(700);
        DPrintf("\n>> 5 arrives from WEST\n\n");
        driveRoad(WEST, 50);
        Exit();
    }

    DPrintf("\n>> 1 arrives from WEST\n\n");
    driveRoad(WEST, 30);
}

// Car 1 slow from west, 
// 2, 3, 4 closely from east
// Car 5, 6, 7 then enter from west
// Should be 1, 2, 5, 3, 6, 4, 7
// 7,6,5 |----1>-----| 2,3,4
// Road Trace: >|<|>|<|>|<|>|
void Test11()
{
    DPrintf("TEST: 1 slowly from west, 2,3,4 closely from east, 5,6,7 closely from west, should take turn.\n");

    if (Fork() == 0) {
        Delay(400);
        DPrintf("\n>> 2 arrives from EAST\n\n");
        driveRoad(EAST, 100);
        Exit();
    }

    if (Fork() == 0) {
        Delay(500);
        DPrintf("\n>> 3 arrives from EAST\n\n");
        driveRoad(EAST, 50);
        Exit();
    }

    if (Fork() == 0) {
        Delay(600);
        DPrintf("\n>> 4 arrives from EAST\n\n");
        driveRoad(EAST, 50);
        Exit();
    }

    if (Fork() == 0) {
        Delay(700);
        DPrintf("\n>> 5 arrives from WEST\n\n");
        driveRoad(WEST, 50);
        Exit();
    }

    if (Fork() == 0) {
        Delay(780);
        DPrintf("\n>> 6 arrives from WEST\n\n");
        driveRoad(WEST, 70);
        Exit();
    }

    if (Fork() == 0) {
        Delay(1200);
        DPrintf("\n>> 7 arrives from WEST\n\n");
        driveRoad(WEST, 60);
        Exit();
    }

    DPrintf("\n>> 1 arrives from WEST\n\n");
    driveRoad(WEST, 30);
}

// ***Test case 5 from discussion, Expected: 1,3,2
// 1 is VERY slow that 2 CANNOT take off, then 2 arrives
void Test12() {
    DPrintf("TEST: From discussion, 1 arrives west but VERY slow. 2 arrives west too but CANNOT take off. Then 3 arrives east so it can go before 2\n");

    if (Fork() == 0) {
        Delay(100);
        DPrintf("\n>> 2 arrives from WEST\n\n");
        driveRoad(WEST, 100);
        Exit();
    }

    if (Fork() == 0) {
        Delay(120);
        DPrintf("\n>> 3 arrives from EAST\n\n");
        driveRoad(EAST, 100);
        Exit();
    }

    DPrintf("\n>> 1 arrives from WEST\n\n");
    driveRoad(WEST, 10); // Slow A!
}

// 1,2,3 closely arrive at west, but once D arrives before C, C should wait for D to finish.
void Test13() {
    DPrintf("TEST: 1,2,3 closely arrive at west, but then 4 arrives at east, 4 should be able to go\n");

    if (Fork() == 0) {
        Delay(100);
        DPrintf("\n>> 2 arrives from WEST\n\n");
        driveRoad(WEST, 50);
        Exit();
    }

    if (Fork() == 0) {
        Delay(200);
        DPrintf("\n>> 3 arrives from WEST\n\n");
        driveRoad(WEST, 50);
        Exit();
    }

    if (Fork() == 0) {
        Delay(150);
        DPrintf("\n>> 4 arrives from EAST\n\n");
        driveRoad(EAST, 50);
        Exit();
    }

    DPrintf("\n>> 1 arrives from WEST\n\n");
    driveRoad(WEST, 50);
}

void Main()
{
    // InitRoad here, but you can do it again in each test.
	InitRoad();

    // New test(s) should go here. Also update 'N_tests' intester.py to cover new tests
	void (*func_ptr[20])() = {
		Test1, Test2, Test3, Test4, Test5, 
		Test6, Test7, Test8, Test9, Test10, 
		Test11, Test12, Test13
		};

	char *N = getenv("N");
    if (N == NULL) {
        DPrintf("You must provide N.\n");
        Exit();
	}
	int Nint = atoi(N);
	if (Nint <= 0 || Nint > sizeof(func_ptr)/sizeof(func_ptr[0])) {
		DPrintf("Invalid N = %d.\n", Nint);
		Exit();
	}
	DPrintf("N is %d.\n", Nint);
	(*func_ptr[Nint-1])();

	Exit();
}
