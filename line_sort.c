#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The name of the input file and output file
#define IN_FILE "quotes.txt"
#define OUT_FILE "output.txt"

// Defines how many quotes will be in the OUT_FILE
#define MAX_QUOTES 10
#define RMN(str) str[strcspn(str,"\r\n")]=0
// This function will be used in sorting to swap strings ("pointers").
void swap(char**, char**);

// Selection Sort function here.
void selection_sort(char**, size_t);

// Read quotes from file and add them to array of pointers.
// You also must user selection_sort inside this function!
void read_in(char**);

// Print the quotes using array of pointers.
void print_out(char**);

// Save the sorted quotes in the OUT_FILE file.
void write_out(char**);

// Free memory pointed by pointers in the array of pointers!
void free_memory(char**);


int main() {

    // Create array of pointers. Each pointer should point to heap memory where each quote is kept. 
    // I.e. quotes[0] points to smallest string.
    // We need +1 to insert the new quote at the end of the array and then re-sort.
    char* quotes[MAX_QUOTES+1]={NULL};

    // Read quotes from file and place them into array quotes. 
    // Also, sort as you add them
    // You also need to print how many lines were processed
    read_in(quotes);
   
    // Print MAX_QUOTES shortest quotes
    print_out(quotes);

    // Save MAX_QUOTES shortest quotes in the file OUT_FILE
    write_out(quotes);
    
    // Free memory allocated by array of pointers
    free_memory(quotes);
    
    return (0);
}

// Add all required functions below!
void read_in(char** quotes){
	size_t max_len=0;
	size_t max_lines=0;
	size_t len = 0;
	int line;
	size_t quoteCounter = 0;
	FILE *input;
	if((input = fopen(IN_FILE,"r")) == NULL){
		perror("Count't Open the file\n");
		exit(1);	
	}
	while((line = fgetc(input)) != EOF){
		if(line == '\n'){
			max_len = max_len > len ? max_len : len-1;
			len=0;
			max_lines++;
		}
		len++;
	}
	char* tmp = (char*)calloc(max_len+1,sizeof(char));
	if(tmp == NULL){
		printf("Memory allocation error for tmp");
		fclose(input);
		exit(0);
	}
	rewind(input);
	char** tmpQuotes = (char**) calloc(max_lines+1 , sizeof(char*));
	if(tmpQuotes == NULL){
		printf("Memory Allocation Error");
		fclose(input);
		exit(0);
	}
	while(fgets(tmp,(int)max_len+1,input)){
		RMN(tmp);
		len = strlen(tmp);
		if(len > 0){
			tmpQuotes[quoteCounter] = (char*)calloc(len+1,sizeof(char));
			if(tmpQuotes[quoteCounter] == NULL){
				printf("Memory Allocation Error");
				fclose(input);
				exit(0);
			}
			strcpy(tmpQuotes[quoteCounter++],tmp);
		}
	}
	
	fclose(input);
	selection_sort(tmpQuotes,quoteCounter);
	for(int i=0;i < (quoteCounter > MAX_QUOTES ? MAX_QUOTES : quoteCounter);i++){
		swap(&quotes[i],&tmpQuotes[i]);
	}
	for(int i =0;i < max_lines+1;i++){
		free(tmpQuotes[i]);
	}
	free(tmpQuotes);
	printf("Characters in the Longest quote: %zu\n",max_len);
	printf("Lines Processed in the input file: %zu\n",max_lines+1);	
}
void selection_sort(char** quotes, size_t sizeOfQuotes){
	size_t shorter;
	for(int i=0;i < sizeOfQuotes+1;i++){
		shorter = i;
		for(int j=i+1;j < sizeOfQuotes;j++){
			if(strlen(quotes[j]) < strlen(quotes[shorter])){
				shorter = j;
			}else if(strlen(quotes[j]) == strlen(quotes[shorter])){
				int val = strcoll(quotes[j],quotes[shorter]);
				shorter = val > 0 ? shorter: j;
			}
		}
		swap(&quotes[shorter],&quotes[i]);
	}
}
void free_memory(char** data){
	for(int i= 0;data[i] != NULL;i++){
		free(data[i]);
	}
}

void swap(char** a, char** b){
	char* tmp = *a;
	*a = *b;
	*b = tmp;
}
void write_out(char** data){
	FILE* output;
	if((output = fopen(OUT_FILE,"w"))== NULL){
		fclose(output);
		perror("Couldn't open output file\n");
		exit(1);
	}
	for(int i=0;i<MAX_QUOTES;i++){
		if(data[i] != NULL){
			fprintf(output,"%s\n", data[i]);
		}
	}
	fclose(output);
}
void print_out(char** quotes){
	for(int j=0;quotes[j] != NULL;j++){
		printf("%s\n",quotes[j]);
	}
}
