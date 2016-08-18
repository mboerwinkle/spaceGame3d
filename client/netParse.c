#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def.h"
void netParse(char* msg){
	char prefix[4] = {msg[0], msg[1], msg[2], 0};
	if(!strcmp(prefix, "CTL")){
		//overwrite control 
	}else if(!strcmp(prefix, "TXT")){
		printf("%s\n", msg);
	}else if(!strcmp(prefix, "SCN")){
		printf("%s\n", msg);
	}
	
}
