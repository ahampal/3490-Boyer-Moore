//Amit Hampal
//ID: 0964514
//Assignment 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//function strips input of new line and replaces with null
char *removeNewLine(char *file) {
	for(int i = 0; i < strlen(file); i++) {
		if(*(file + i) == '\n') {
			*(file + i) = '\0';
		}
	}
	return file;
}	

//function to swap characters
void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

//function to check if two strings are anagrams
int isAnagram(char *a, char *b) {
	int mapOne[200];
	int mapTwo[200];
	//length check
	if(strlen(a) != strlen(b)) {
		return 0;
	}
	//initialize character map
	for(int i = 0; i < 200; i++) {
		mapOne[i] = 0;
		mapTwo[i] = 0;
	}
	for(int i = 0; i < strlen(a); i++) {
		mapOne[(int)a[i]] += 1;
	}
	for(int i = 0; i < strlen(b); i++) {
		mapTwo[(int)b[i]] += 1;
	}
	//check if character maps are the same
	for(int i = 0; i < 200; i++) {
		if(mapOne[i] != mapTwo[i]) {
			return 0;
		}
	}
	return 1;
}

//main function
int main(int argc, char **argv) {
	char **A = malloc(sizeof(char *) * 30001);
	int n;
	int j;
	char *line = malloc(sizeof(char) * 100);
	char *strToFind = malloc(sizeof(char) * 100);
	char *tok = malloc(sizeof(char) *10);
	char *currStr = malloc(sizeof(char) *100);
	FILE *fp;
	int searchCount = 0;
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
	//read in contents of file to memory
	while(!feof(fp))
	{
		fgets(line, 100, fp);
		line = removeNewLine(line);
		tok = strtok(line, " ");
		while(tok != NULL) {
			A[n] = malloc(sizeof(char) * 100);
			strcpy(A[n], tok);
			n++;
			tok = strtok(NULL, " ");
		}
	}
	//get user input
	printf("Anagram to find: ");
	fgets(strToFind, 100, stdin);
	strToFind = removeNewLine(strToFind);
	//bruteforce algorithm
	clock_t b = clock();
	j = 0;
	for(int i = 0; i < n; i++) {
		strcpy(currStr, A[i]);
		currStr = removeNewLine(currStr);
		if(isAnagram(currStr, strToFind) == 1) {
			printf("%s is an anagram\n", currStr);
			searchCount++;
		}
	}
	clock_t a = clock();
	//report results
	double time = (double)(a-b) / CLOCKS_PER_SEC;
	printf("Number of anagrams: %d\n", searchCount);
	printf("Execution time for bruteforce was %lf seconds\n", time);
	free(line);
	free(strToFind);
	fclose(fp);
	return 0;
}
