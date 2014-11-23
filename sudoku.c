/*
 * Version 1 of Sudoku
 * learnings: n dimension matrices are allowed in C
 * 
*/
#include<stdio.h>
#include<stdlib.h>
int main(){
	int i;
	int a[5][5][5][5][5][5];
	for(i=0;i<5;i++){
	scanf("%d",&a[i][i][i][i][i][i]);
	}
	for(i=0;i<5;i++){
	printf("%d",a[i][i][i][i][i][i]);
	}
	return 0;
}
