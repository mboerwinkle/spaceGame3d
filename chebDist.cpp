#include <stdio.h>
#include <stdlib.h>
#include "chebDist.h"
unsigned long int chebDist(Ship* one, Ship* two){
	if(one == NULL || two == NULL){
		return 0;
	}
	unsigned long dist1, dist2, dist;
	if(one->pos[0]>two->pos[0]){
		dist = one->pos[0]-two->pos[0];
	}else{
		dist = two->pos[0]-one->pos[0];
	}
	if(one->pos[1]>two->pos[1]){
		dist1 = one->pos[1]-two->pos[1];
	}else{
		dist1 = two->pos[1]-one->pos[1];
	}
	if(one->pos[2]>two->pos[2]){
		dist2 = one->pos[2]-two->pos[2];
	}else{
		dist2 = two->pos[2]-one->pos[2];
	}
	if(dist1 > dist){
		dist=dist1;
	}
	if(dist2 > dist){
		dist=dist2;
	}
	return dist;
}
