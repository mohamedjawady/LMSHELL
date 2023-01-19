#ifndef LM_PARSER
#define LM_PARSER

// splits string using a separator of type char
void string_split(char * string, char sep, char *** r_array_string, int * r_size);

// splits string using a separator of type char*
void split_string_subs(char* str, char* delimiter, char **subs);

// trims strings leading and terminating whitespace
void lm_trim(char *string);
#endif
