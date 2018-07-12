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

//function to create bad match table
void shiftTable(char *strToFind, int *table) {
	for(int p = 0; p < 1000; p++) {
		table[p] = strlen(strToFind);
	}
	for(int i = 0; i < (strlen(strToFind) - 1); i++) {
		table[(int)(strToFind[i] - 32)] = strlen(strToFind) - i - 1;
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
	int *table = malloc(sizeof(int) * 1000);
	int patternShift = 0;
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
	//read file into memory
	printf("Loading data...\n");
	while(!feof(fp))
	{
		fgets(line, 100, fp);
		line = removeNewLine(line);
		strcat(A, line);
		n++;
	}
	//get user input and create shift table
	printf("String to find: ");
	fgets(strToFind, 100, stdin);
	strToFind = removeNewLine(strToFind);
	shiftTable(strToFind, table);
	int i = strlen(strToFind) - 1;
	int k;
	clock_t b = clock();
	int patternLen;
	patternLen = strlen(A);
	while(i <= (patternLen - 1)) {
		k = 0;
		patternShift++;
		while (k <= (strlen(strToFind) - 1) && strToFind[strlen(strToFind) - 1 - k] == A[i - k]) {
			k++;
		}
		//shift by entire length of pattern if found match
		if(k == strlen(strToFind)) {
			searchCount++;
			i = i + strlen(strToFind);
		}
		//otherwise shift in accordance to bad match table
		else {
			i = i + table[abs((int)A[i] - 32)];
		}

	}
	clock_t a = clock();
	//report results
	double time = (double)(a-b) / CLOCKS_PER_SEC;
	printf("Number of Occurances is: %d\n", searchCount);
	printf("Number of patternshifts is: %d\n", patternShift);
	printf("Execution time for horspool was %lf seconds\n", time);
	fclose(fp);
	return 0;
}
