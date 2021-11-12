#include <stdio.h>
#include <string.h>
#include "uthash.h"

typedef struct digitList {
	int value;
	struct digitList *next;
} digitList;

digitList *headNum1 = NULL;
digitList *headNum2 = NULL;

void digitNumCreate(unsigned long number, digitList **head)
{
	*head = (digitList *)malloc(sizeof(digitList));
	(*head)->value = 0;
	(*head)->next = NULL;

	digitList *digitNode = NULL;
	digitList *tail = *head;

	if (number == 0)
	{
		digitNode = (digitList *)malloc(sizeof(digitList));
		
		digitNode->value = 0;
		digitNode->next = NULL;
		
		tail->next = digitNode;
		tail = digitNode;
		
		((*head)->value)++;
		
		return;
	}

	while (number)
	{
		digitNode = (digitList *)malloc(sizeof(digitList));
		
		digitNode->value = number % 10L;
		digitNode->next = NULL;
		
		tail->next = digitNode;
		tail = digitNode;
		
		((*head)->value)++;
		number /= 10;
	}
}

void printNumber(digitList *number)
{
	if (number == NULL)
	{
		return;
	}

	if (number->next)
	{
		printNumber(number->next);
	}

	printf("%d", number->value);
}

void addTwoNumber(unsigned long num1, unsigned long num2)
{
	digitNumCreate(num1, &headNum1);
	digitNumCreate(num2, &headNum2);
	
	digitList *longNum = NULL;
	digitList *shortNum = NULL;
	digitList *longPrevTail = NULL;
	
	int numToPrint = 0;
	
	if (headNum1->value >= headNum2->value)
	{
		longNum = headNum1->next;
		shortNum = headNum2->next;
		numToPrint = 1;
	}
	else
	{
		longNum = headNum2->next;
		shortNum = headNum1->next;
		numToPrint = 2;
	}
	
	int digitSum = 0;
	int carry = 0;
	while (longNum && shortNum)
	{
		digitSum = longNum->value + shortNum->value + carry;
		if (digitSum >= 10)
		{
			longNum->value = digitSum % 10;
			carry = 1;
		}
		else
		{
			longNum->value = digitSum;
			carry = 0;
		}
		
		longPrevTail = longNum;
		longNum = longNum->next;
		shortNum = shortNum->next;
	}
	
	while (longNum && carry)
	{
		digitSum = longNum->value + carry;
		
		if (digitSum >= 10)
		{
			longNum->value = digitSum % 10;
			carry = 1;
		}
		else
		{
			longNum->value = digitSum;
			carry = 0;
		}
		
		longPrevTail = longNum;
		longNum = longNum->next;
	}
	
	if (carry)
	{
		longPrevTail->next = (digitList *)malloc(sizeof(digitList));
		longNum = longPrevTail->next;
		
		longNum->value = carry;
		longNum->next = NULL;
	}
	
	printf("sum of %ld and %ld: ", num1, num2);
	if (numToPrint == 1)
	{
		printNumber(headNum1->next);
	}
	else
	{
		printNumber(headNum2->next);
	}
	printf("\n");
}

void addTwoNumber_test()
{
	addTwoNumber(12, 10);
	addTwoNumber(12000, 100000);
	addTwoNumber(1200034, 100000453);
	addTwoNumber(12023400, 100234000);
	addTwoNumber(12234000, 100342000);
}
