#include <stdio.h>
#include <string.h>
#include "uthash.h"

#define CACHE_CAPACITY		(5)

typedef struct subString {
	int key;
	int value;
	struct subString *next;
	
	UT_hash_handle hh;
} subString;

subString *subStringList = NULL;
subString *subStringHead = NULL;
subString *subStringTail = NULL;

int subStringLen = 0;
int maxSubStringLen = 0;
int maxSubIndexLow = 0;
int maxSubIndexHigh = 0;

void subStringInit()
{
	subStringHead = (subString *)malloc(sizeof(subString));
	
	subStringHead->next = NULL;
}

subString *findChar(int key)
{
	subString *subChar = NULL;
	
	HASH_FIND_INT(subStringList, &key, subChar);
	
	return subChar;
}

subString *addChar(int key, int value)
{
	subString *subChar = (subString *)malloc(sizeof(subString));
	
	subChar->key = key;
	subChar->value = value;
	subChar->next = NULL;

	HASH_ADD_INT(subStringList, key, subChar);
	
	return subChar;
}

void removeChar(subString *subChar)
{
	HASH_DEL(subStringList, subChar);
	free(subChar);
}

void addToTail(subString *subChar)
{
	if (subStringHead->next == NULL)
	{
		subStringHead->next = subChar;
	}
	else
	{
		subStringTail->next = subChar;
	}
	
	subStringTail = subChar;
}

void charProcess(int key, int value)
{
	subString *subChar = findChar(key);
	if (subChar == NULL)
	{
		subChar = addChar(key, value);
	}
	else
	{
		subString *delChar = subStringHead->next;
		subString *tmpChar = NULL;
		
		while (delChar != subChar)
		{
			tmpChar = delChar->next;
			removeChar(delChar);
			delChar = tmpChar;
			
			subStringLen--;
		}
		
		subStringHead->next = delChar->next;
		subStringLen--;
		
		subChar->value = value;
		subChar->next = NULL;
	}

	addToTail(subChar);
	subStringLen++;
	
	printf("maxSubStringLen: %d, subStringLen: %d\n", maxSubStringLen, subStringLen);
	
	if (maxSubStringLen < subStringLen)
	{
		maxSubStringLen = subStringLen;
		maxSubIndexLow = subStringHead->next->value;
		maxSubIndexHigh = subStringTail->value;
	}
}

void subStringProcess(char *str, int len)
{
	int i = 0;
	for (; i < len; i++)
	{
		charProcess(str[i], i);
	}
}

void subStringPrint(char *str)
{
	printf("Longest sub string %d ~ %d: ", maxSubIndexLow, maxSubIndexHigh);
	int i = 0;
	for (i = maxSubIndexLow; i <= maxSubIndexHigh; i++)
	{
		printf("%c", str[i]);
	}
	printf("\n");

	printf("Current sub string: ");
	subString *subChar = subStringHead->next;
	while (subChar != subStringTail)
	{
		printf("%c", subChar->key);
		subChar = subChar->next;
	}

	if (subStringTail)
	{
		printf("%c\n", subStringTail->key);
	}
}

void longestSubString_test()
{
	char str[] = "abcddlkjaflksdjfklk";

	subStringInit();
	
	subStringProcess(str, strlen(str));
	subStringPrint(str);
}
