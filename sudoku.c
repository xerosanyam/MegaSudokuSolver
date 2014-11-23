/*
 * Version 5 of Sudoku
 * Learnings:giving shape like a sudoku
 * 
*/
#include<stdio.h>
#include<stdlib.h>
#define size 3
int main(){
	int i=0,j=0,k=0,len=0;
	len=size*size;
	int *a[len][len];
	for(i=0;i<len;i++){
		for(j=0;j<len;j++){
		a[i][j]=(int*)malloc(sizeof(int)*len);
		}
	}
		for(i=0;i<len;j++){
			for(j=0;j<len;k++){
				scanf("%d",&a[i][j][0]);
			}
		}
		for(i=0;i<len;j++){
			for(j=0;j<len;k++){
					printf("%3d ",a[i][j][0]);
				if((k+1)%size==0)
					printf("\t");		//to print tab after every square	
			}
			if((j+1)%size==0)
				printf("\n");
			printf("\n");				//to print nextline after after square
		}
	return 0;
}
