
#include "include/string.h"

/*Implementaion of string functions
 * */
size_t str_len(const char *str){
	size_t len = 0;
	while(str[len]){
		len++;
	}
	return len;
}


short int str_cmp(const char *str1,const char *str2){
	size_t i=-1;
	//loop until both string contains same character
	do{
	i++;
	}while(str1[i]==str2[i] && str1[i] && str2[i]);
	return str1[i]-str2[i];
}

void str_cpy(const char *str1,char *str2){
	size_t i=0;
	while(str1[i]){
		str2[i]=str1[i];
		i++;
	}
	str2[i]=0;
}

