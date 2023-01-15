#include "parser.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void string_split(char * orig_string, char sep, char *** r_array_string, int * r_size) {
	char* string = orig_string;
	int i, k, len, size;
	char ** array_string;
	
	// Number of substrings
	size = 1, len = strlen(string);
	for(i = 0; i < len; i++) {
		if(string[i] == sep) {
			size++;
		}
	}
	
	array_string = (char**)malloc(size * sizeof(char*));
	
	i=0, k=0;
	array_string[k++] = string; // Save the first substring pointer
	// Split 'string' into substrings with \0 character
	while(k < size) {
		if(string[i++] == sep) {
			string[i-1] = '\0'; // Set end of substring
			array_string[k++] = (string+i); // Save the next substring pointer
		}
	}
	*r_array_string = array_string;
	*r_size = size;
	return;
}


void split_string_subs(char* str, char* delimiter, char **subs){
	char* token;
	token = strtok(str, delimiter);
	int i=0;
	while(token != NULL, i<2) {
		if(i==0){
			subs[i] = token;
		}else{
			subs[i] = token;
		}
		token = strtok(NULL, delimiter);
		i++;
	}
}
