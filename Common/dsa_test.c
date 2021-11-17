#include <stdio.h>
#include <string.h>

typedef void (*func)(void);

typedef struct {
	char testName[64];
	func testFunc;
} testSuit;

extern void LRU_test();
extern void addTwoNumber_test();
extern void longestSubString_test();

testSuit test[] = {
	{ "LRU", 					LRU_test },
	{ "addTwoNum", 				addTwoNumber_test },
	{ "longestSubString", 		longestSubString_test },
};

void testRun(char *testName)
{
	int testCount = sizeof(test) / sizeof(testSuit);
	
	int i = 0;
	for (; i < testCount; i++)
	{
		if (!strncmp(testName, test[i].testName, strlen(testName)))
		{
			printf("Ready to run: %s\n", test[i].testName);
			test[i].testFunc();
			break;
		}
	}
	
	if (i == testCount)
	{
		printf("No test function found!\n");
	}
}