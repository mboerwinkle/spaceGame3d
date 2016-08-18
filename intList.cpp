#include <stdio.h>
#include <stdlib.h>
#include "intList.h"
IntList::IntList(){
}
void IntList::add(int val){
	len++;
	list = (int*)realloc(list, len*sizeof(int));
	list[len-1]=val;
}
void IntList::remove(int idx){
	list[idx] = list[len-1];
	len--;
}
int IntList::search(int val){
	for(int x = 0; x<len; x++){
		if(list[x] == val){
			return x;
		}
	}
	return -1;
}
