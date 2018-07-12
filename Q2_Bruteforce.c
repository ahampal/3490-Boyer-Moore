//Amit Hampal
//ID: 0964514
//Assignment 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//function strips input of new line and replaces with null
char *removeNewLine(char *file) {
	for(int i = 0; i <= strlen(file); i++) {
		if(*(file + i) == '\n') {
			*(file + i) = '\0';
		}
	}	
	return file;
}	

//main function
int main(int argc, char **argv) {
	char A[44050][100];
	int n;
	char *line = malloc(sizeof(char) * 100);
	FILE *fp;
	char *strToFind = malloc(sizeof(char) * 100);
	int searchCount = 0;
	int patternShift = 0;
	int patternLen;
	int lineLen;
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
	printf("Loading data...\n");
	//read data into memory
	while(!feof(fp))
	{
		fgets(line, 100, fp);
		line = removeNewLine(line);
		strcpy(A[n], line);
		n++;
	}
	//get user input
	printf("String to find: ");
	fgets(strToFind, 100, stdin);
	strToFind = removeNewLine(strToFind);
	patternLen = strlen(strToFind);
	clock_t b = clock();
	for(int u = 0; u < n; u++) {
		for(int i = 0; i < strlen(A[u]); i++) {
			int j = 0;
			patternShift++;
			//check if pattern matches text
			while(j < patternLen &&  *(strToFind + j) == A[u][i + j]) {
				j++;
			}
			if (j == patternLen) {
				searchCount++;
			}
		}
	}
	clock_t a = clock();
	double time = (double)(a-b) / CLOCKS_PER_SEC;
	//report results
	printf("Number of occurrances is: %d\n", searchCount);
	printf("Number of pattern shifts: %d\n", patternShift);
	printf("Execution time for bruteforce was %lf seconds\n", time);
	free(line);
	fclose(fp);
	return 0;
}
