//Amit Hampal
//ID: 0964514
//Assignment 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

//function strips input of new line and replaces with null
char *removeNewLine(char *file) {
	for(int i = 0; i < strlen(file); i++) {
		if(*(file + i) == '\n') {
			*(file + i) = '\0';
		}
	}
	return file;
}	

//function to return max of two integers
int max(int a, int b) {
	if( a > b) {
		return a;
	}
	return b;
}

//function to create bad match table
void badTable(char *strToFind, int *table) {
	for(int p = 0; p < 1000; p++) {
		table[p] = strlen(strToFind);
	}
	for(int i = 0; i < (strlen(strToFind) - 1); i++) {
		table[(int)(strToFind[i] - 32)] = strlen(strToFind) - i - 1;
	}
}

//Standard C library function strstr, but modified to return right most value
char *rstrstr(char *s1, char *s2)
{
	size_t  s1len = strlen(s1);
	size_t  s2len = strlen(s2);
	char *s;

	if (s2len > s1len) {
		return NULL;
	}
	for (s = s1 + s1len - s2len; s >= s1; s--) {
		if (strncmp(s, s2, s2len) == 0) {
			return s;
		}
	}
	return NULL;
}

//function to create good suffix table
void goodTable(char *strToFind, int *table) {
	int len = strlen(strToFind);
	char *suff = malloc(sizeof(char) * len);
	char *pref = malloc(sizeof(char) * len);
	char *potentialPref = malloc(sizeof(char) * len);
	char *index;
	char *indexTwo;
	for(int p = 0; p < 1000; p++) {
		table[p] = 1;
	}
	for(int p = len - 1; p > 0; p--) {
		//stores suffix and prefix into strings
		strcpy(suff, strToFind + p);
		strncpy(pref, strToFind, p);
		pref[p] = '\0';
		index = rstrstr(pref, suff);
		//finds if suffix exists in prefix
		if(index != NULL) {
			table[strlen(suff)] = strlen(strToFind) - strlen(index);
		}
		//case for if it doesn't
		else {
			//attempts to find smaller suffix before setting table value to string length
			for(int l = 1; l < len; l++) {
				strncpy(potentialPref, strToFind, l);
				pref[l] = '\0';
				indexTwo = strstr(suff, pref);
				if(indexTwo != NULL) {
					table[strlen(suff)] = strlen(strToFind) - strlen(suff) - strlen(pref);
				}
				else {
					table[strlen(suff)] = strlen(strToFind);
				}
			}
		}
	}
}

//main function
int main(int argc, char **argv) {
	char A[4405000];
	int n;
	char *line = malloc(sizeof(char) * 100);
	FILE *fp;
	char *strToFind = malloc(sizeof(char) * 100);
	int searchCount = 0;
	int *bTable = malloc(sizeof(int) * 1000);
	int *gTable = malloc(sizeof(int) * 1000);
	int patternShift = 0;
	int patternLen = 0;
	//open file for reading
	printf("File is: %s\n", argv[argc - 1]);
	if(argc > 1)
	{
		fp = fopen( argv[argc - 1], "r" );
	}
	else
	{
		return 0;
	}
	if(fp == NULL) 
	{
		printf("Cannot find file. Ensure your syntax is correct. Exiting program.\n");
		return 0;
	}
	n = 0;
	//load data into memory
	printf("Loading data...\n");
	while(!feof(fp))
	{
		fgets(line, 100, fp);
		line = removeNewLine(line);
		strcat(A, line);
		patternLen += strlen(line);
		n++;
	}
	A[n] = '\0';
	//get user input
	printf("String to find: ");
	fgets(strToFind, 100, stdin);
	strToFind = removeNewLine(strToFind);
	//create tables based off user input
	badTable(strToFind, bTable);
	goodTable(strToFind, gTable);
	int i = strlen(strToFind) - 1;
	int k;
	clock_t b = clock();
	//similar algorithm to horspool, but takes max of two tables instead
	while(i <= (patternLen - 1)) {
		k = 0;
		patternShift++;
		while (k <= (strlen(strToFind) - 1) && strToFind[strlen(strToFind) - 1 - k] == A[i - k]) {
			k++;
		}
		//if match found, shift by entire length of pattern
		if(k == strlen(strToFind)) {
			searchCount++;
			i = i + strlen(strToFind);
		}
		//otherwise shift in accordance with tables
		else {
			i = i + max(bTable[abs((int)A[i] - 32)], gTable[k]);
		}

	}
	clock_t a = clock();
	//report results
	double time = (double)(a-b) / CLOCKS_PER_SEC;
	printf("Number of Occurances is: %d\n", searchCount);
	printf("Number of patternshifts is: %d\n", patternShift);
	printf("Execution time for boyer-moore was %lf seconds\n", time);
	fclose(fp);
	return 0;
}
