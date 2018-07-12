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

//struct definition
typedef struct arrElem {
	char *origString;
	char *sortString;
}arrElem;

//compare function for strings
int cmpFunc(const void *a, const void *b) {
	return strcmp((char *)a, (char *)b);
}

//compare function for array of structs
int compFunc(const void *a, const void *b) {
	return strcmp( ((arrElem *)a)->sortString, ((arrElem *)b)->sortString );
}

//recursive binary search function
int binarySearch(arrElem *arr, int l, int r, char *x)
{
   if (r >= l)
   {
        int mid = l + (r - l)/2;
        if (strcmp(arr[mid].sortString, x) == 0) {  
            return mid;
		}
        if (strcmp(arr[mid].sortString, x) > 0) {
            return binarySearch(arr, l, mid-1, x);
		}
        return binarySearch(arr, mid+1, r, x);
   }
   return -1;
}

//main function
int main(int argc, char **argv) {
	arrElem A[30000];
	int n;
	int j;
	char *line = malloc(sizeof(char) * 100);
	char *strToFind = malloc(sizeof(char) * 100);
	char *tok = malloc(sizeof(char) *10);
	char *currStr = malloc(sizeof(char) *100);
	FILE *fp;
	char *sortedPattern = malloc(sizeof(char) * 100);
	int searchCount = 0;
	int index;
	int i;
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
	//read contents of file into memory, sort strings using qsort
	while(!feof(fp))
	{
		fgets(line, 100, fp);
		line = removeNewLine(line);
		tok = strtok(line, " ");
		while(tok != NULL) {
			A[n].origString = malloc(sizeof(char) * 100);
			A[n].sortString = malloc(sizeof(char) * 100);
			strcpy(A[n].origString, tok);
			strcpy(A[n].sortString, tok);
			qsort(A[n].sortString, strlen(A[n].sortString), sizeof(char), cmpFunc);
			n++;
			tok = strtok(NULL, " ");
		}
	}
	//sort array using qsort and then get user input
	qsort(A, 30000, sizeof(arrElem), compFunc);
	printf("Anagram to find: ");
	fgets(strToFind, 100, stdin);
	strToFind = removeNewLine(strToFind);
	strcpy(sortedPattern, strToFind);
	qsort(sortedPattern, strlen(strToFind), sizeof(char), cmpFunc);
	clock_t b = clock();
	index = binarySearch(A, 0, 30000, sortedPattern);
	i = index;
	//check elements before returned index to see if they are also anagrams
	if(index != -1) {
		while(strcmp(A[i].sortString, sortedPattern) == 0) {
			printf("%s is an anagram\n", A[i].origString);
			i++;
			searchCount++;
		}
		//check elements after returned index to see if they are also anagrams
		i = index - 1;
		while(strcmp(A[i].sortString, sortedPattern) == 0) {
			printf("%s is an anagram\n", A[i].origString);
			i--;
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
