/*
 * Version 4 of Sudoku
 * Learnings:trying to make dynamic 3 dimension array
 * 
*/
#include<stdio.h>
#include<stdlib.h>
int main(){
	int i=0,j=0,k=0;
	int *a[9][9];
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
		a[i][j]=(int*)malloc(sizeof(int)*9);
		}
	}
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			for(k=0;k<9;k++){
				scanf("%d",&a[i][j][k]);
			}
		}
	}
	for(i=0;i<9;i++){
		printf("For i = %d\n",i);
		for(j=0;j<9;j++){
			for(k=0;k<9;k++){
				printf("%d ",a[i][j][k]);
			}
			printf("\n");
		}
	}
	return 0;
}
