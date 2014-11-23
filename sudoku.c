/*Latest
 * Version 6 of Sudoku
 * Learnings:breaking into functions
 * 
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define size 3
void createSudoku();
void fillSudoku();
void printSudoku();
void printHintRow();
void fillHintRow();
void fillHintRowUsingSudkoRow();
void fillHintRowUsingSudkoColumn();
void fillHintRowUsingSudkoCell();
void fillNumUsingHintRow();
int i=0,j=0,k=0,len=0;
int *a[size*size][size*size];
int main(){
	clock_t start = clock();
	createSudoku();			//Create Data Structure.
	fillSudoku();			//Fill input values
	printSudoku();
	fillHintRow();
	fillNumUsingHintRow();
	printSudoku();
	clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time elapsed in ms: %f", elapsed);
	return 0;
}
void createSudoku(){
	int i,j;
	len=size*size;
	for(i=0;i<len;i++){
		for(j=0;j<len;j++){
		a[i][j]=(int*)malloc(sizeof(int)*(len+1));
		}
	}
}
void fillSudoku(){
	int i,j;
	for(i=0;i<len;i++){
			for(j=0;j<len;j++){
				scanf("%d",&a[i][j][0]);
			}
			
	}
}
void printSudoku(){
	int i,j;
	for(i=0;i<len;i++){
		for(j=0;j<len;j++){
			printf("%3d ",a[i][j][0]);
			if((j+1)%size==0)
				printf("\t");			//to print tab after every square	
		}
		if((i+1)%size==0)
			printf("\n");
		printf("\n");					//to print nextline after after square
	}
}
void printHintRow(){
	int i,j,k;
		for(i=0;i<len;i++){
			for(j=0;j<len;j++){
				if(a[i][j][0]==0){
					printf("Hint row for %d %d :",i,j);
					for(k=0;k<(len+1);k++){
							printf(" %d",a[i][j][k]);
					}
					printf("\n");
				}
			}
		}
	printf("\n");
}
void fillHintRowUsingSudkoRow(){
	int i,j,col=0,num=0;
	for(i=0;i<len;i++){
		for(j=0;j<len;j++){
			if(a[i][j][0]>0){
				num=a[i][j][0];
				for(col=0;col<len;col++){
					if(a[i][col][0]==0)a[i][col][num]=1;
				}
			}
		}
	}
	//printHintRow();
}	
void fillHintRowUsingSudkoColumn(){
	int i,j,row=0,num=0;
	for(i=0;i<len;i++){
		for(j=0;j<len;j++){
			if(a[i][j][0]>0){
				num=a[i][j][0];
				for(row=0;row<len;row++){
					if(a[row][j][0]==0)a[row][j][num]=1;
				}
			}
		}
	}
	//printHintRow();
}
void fillHintRowUsingSudkoCell(){
	int i=0,j=0,row=0,col=0,row2=0,col2=0,num=0;
	for(i=0;i<len;i=i+size){
		for(j=0;j<len;j=j+size){
			row=0;
			while(row<size){
				col=0;
				while(col<size){
					if(a[i+row][j+col][0]>0){
						num=a[i+row][j+col][0];
						row2=0;
						col2=0;
						while(row2<size){
								while(col2<size){
									if(a[i+row2][j+col2][0]==0){
										a[i+row2][j+col2][num]=1;
									}
									col2++;
								}
							row2++;
						}
					}
					col++;
				}
				row++;
			}
		}
	}
	printHintRow();
}
void fillNumUsingHintRow(){						//Fills number using hint row only. Rule 1
	int sum=0,num=0,i=0;j=0;k=0;
	while(i<len){
		j=0;
		while(j<len){
			if(a[i][j][0]==0){
				sum=0;
				for(k=1;k<=len;k++){
					sum=sum+a[i][j][k];
					if(a[i][j][k]==0)num=k;
				}
				if(sum==(len-1)){
					a[i][j][0]=num;
					printf("%d Number found in %d row, %d col\n",num,i,j);
					i=-1;
					j=-1;
					fillHintRow();
				}
			}
			if(j==-1)break;
			j++;
		}
		i++;
	}
}
void fillHintRow(){
	fillHintRowUsingSudkoRow();
	fillHintRowUsingSudkoColumn();
	fillHintRowUsingSudkoCell();
}
