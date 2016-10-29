#include <stdio.h>
#include <stdlib.h>
#include "chebDist.h"
unsigned long int chebDist(point& one, point& two){
	unsigned long dist1, dist2, dist;
	if(one[0]>two[0]){
		dist = one[0]-two[0];
	}else{
		dist = two[0]-one[0];
	}
	if(one[1]>two[1]){
		dist1 = one[1]-two[1];
	}else{
		dist1 = two[1]-one[1];
	}
	if(one[2]>two[2]){
		dist2 = one[2]-two[2];
	}else{
		dist2 = two[2]-one[2];
	}
	if(dist1 > dist){
		dist=dist1;
	}
	if(dist2 > dist){
		dist=dist2;
	}
	return dist;
}
