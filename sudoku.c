/*
 * Version 3 of Sudoku
 * Learnings:trying to make dynamic 2 dimension array
 * 
*/
#include<stdio.h>
#include<stdlib.h>
int main(){
	int i=0,j=0;
	int *a[3];
//	*a=(int*)malloc(sizeof(int)*5);
	for(i=0;i<3;i++){
		a[i]=(int*)malloc(sizeof(int)*3);
	}
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
