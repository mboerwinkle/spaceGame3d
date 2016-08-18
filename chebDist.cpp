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
	if(one->pos[0]>two->pos[0]){
		dist1 = one->pos[0]-two->pos[0];
	}else{
		dist1 = two->pos[0]-one->pos[0];
	}
	if(one->pos[0]>two->pos[0]){
		dist2 = one->pos[0]-two->pos[0];
	}else{
		dist2 = two->pos[0]-one->pos[0];
	}
	if(dist1 > dist){
		dist=dist1;
	}
	if(dist2 > dist){
		dist=dist2;
	}
	return dist;
}
