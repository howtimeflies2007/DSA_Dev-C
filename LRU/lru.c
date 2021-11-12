#include <stdio.h>
#include <string.h>
#include "uthash.h"

#define CACHE_CAPACITY		(5)

typedef struct cache {
	int key;
	int value;
	struct cache *prev;
	struct cache *next;
	
	UT_hash_handle hh;
} cache;

cache *cacheTable = NULL;
cache *cacheHead = NULL;
cache *cacheTail = NULL;
int capacity = 0;

void removeNode(cache *cacheNode)
{
	cacheNode->prev->next = cacheNode->next;
	cacheNode->next->prev = cacheNode->prev;
}

cache *removeLastNode()
{
	cache *cacheNode = NULL;
	
	if (cacheTail->prev != cacheHead)
	{
		cacheNode = cacheTail->prev;
	}
	
	removeNode(cacheNode);
	
	return cacheNode;
}

void addToHead(cache *cacheNode)
{
	cacheNode->next = cacheHead->next;
	cacheHead->next = cacheNode;
	cacheNode->prev = cacheHead;
	cacheNode->next->prev = cacheNode;
}

cache *findCache(int key)
{
	cache *cacheNode = NULL;
	
	HASH_FIND_INT(cacheTable, &key, cacheNode);
	
	return cacheNode; 
}

cache *addCache(int key, int value)
{
	cache *cacheNode = (cache *)malloc(sizeof(cache));
	
	cacheNode->key = key;
	cacheNode->value = value;
	cacheNode->prev = NULL;
	cacheNode->next = NULL;
	
	HASH_ADD_INT(cacheTable, key, cacheNode);
	
	return cacheNode;
}

void removeCache(cache *cacheNode)
{
	HASH_DEL(cacheTable, cacheNode);
	free(cacheNode);
}

void printCache()
{
	cache *cacheNode = cacheHead->next;
	
	printf("cache:");
	while (cacheNode != cacheTail)
	{
		printf(" %d", cacheNode->value);
		
		cacheNode = cacheNode->next;
	}
	printf("\n");
}

void cacheInit()
{
	cacheHead = (cache *)malloc(sizeof(cache));
	cacheTail = (cache *)malloc(sizeof(cache));
	
	cacheHead->next = cacheTail;
	cacheTail->prev = cacheHead;
}

int cacheGet(int key)
{
	cache *cacheNode = NULL;
	
	cacheNode = findCache(key);
	if (cacheNode)
	{
		removeNode(cacheNode);
		addToHead(cacheNode);
		
		return cacheNode->value;
	}
	else
	{
		return -1;
	}
}

void cachePut(int key, int value)
{
	cache *cacheNode = NULL;

	cacheNode = findCache(key);
	if (cacheNode)
	{
		cacheNode->value = value;
		
		removeNode(cacheNode);
		addToHead(cacheNode);
	}
	else
	{
		if (capacity >= CACHE_CAPACITY)
		{
			cache *lastNode = removeLastNode();
			removeCache(lastNode);
		}
		else
		{
			capacity++;
		}

		cacheNode = addCache(key, value);
		addToHead(cacheNode);
	}
}

void LRU_test()
{
	cacheInit();
	cachePut(1, 1);
	cachePut(2, 2);
	cachePut(3, 3);
	cachePut(4, 4);
	printCache();
	cachePut(2, 9);
	printCache();
	printf("getCache: %d\n", cacheGet(4));
	printCache();
	cachePut(5, 5);
	cachePut(6, 6);
	printCache();
	printf("getCache: %d\n", cacheGet(1));
	printCache();
	printCache();
	printf("getCache: %d\n", cacheGet(4));
	printCache();
}
