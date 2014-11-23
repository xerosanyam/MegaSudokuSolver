/*
 * Version 2 of Sudoku
 * learnings:trying to make dynamic 1 dimension array
 * 
*/
#include<stdio.h>
#include<stdlib.h>
int main(){
	int i=0;
	int *a;
	a=(int*)malloc(sizeof(int)*5);
	for(i=0;i<5;i++){
		scanf("%d",&a[i]);
	}
	for(i=0;i<5;i++){
		printf("%d",a[i]);
	}
	return 0;
}
