/*Latest
 * Version 9 of Sudoku
 * Change Log: 
 * Implemented rule 2
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define psize 10
void createSudoku();
void fillSudoku();					//using input
void printSudoku();					//print values in sudoku (used in start and end)
void printHintRow();				//prints hint row
void fillHintRow();					//1 in hint list means, that number cannot come.
void fillHintRowUsingSudkoRow(int,int,int);
void fillHintRowUsingSudkoColumn(int,int,int);
void fillHintRowUsingSudkoCell();	
void fillNumUsingHintRow();			//Rule 1 ends
void fillOccurencePerRow();			//Rule 2 Begins; Used to fill OccurencePerRow
void fillOccurencePerCol();			//Fills occurences of number in columns
void fillOccurencePerGrid();			//Fills occurences of number in grids
void clearOccurenceRow();
void clearOccurenceCol();
void clearOccurenceGrid();
int i=0,j=0,k=0,len=0,size=0,fill_count=0;
int *a[psize*psize][psize*psize];
int or[psize*psize][(psize*psize)+1];		//All the arrays here and after are used for rule 2. Takes 7ms in creation. 
int pnr[psize*psize][(psize*psize)+1];
int oc[psize*psize][(psize*psize)+1];
int pnc[psize*psize][(psize*psize)+1];
int og[psize*psize][(psize*psize)+1];
int png[psize*psize][(psize*psize)+1];
void print_og(int);
void print_png(int);
void status();
int main(){
	clock_t start = clock();
	createSudoku();			//Create Data Structure.
	fillSudoku();			//Fill input values
	printSudoku();
			//Initial filling of hint row
	fillNumUsingHintRow();	//Rule 1
//	printSudoku();
//	fillOccurencePerRow();
//	fillOccurencePerCol();
	fillOccurencePerGrid();
	printSudoku();
	status();
	clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	printf("Time elapsed in ms:\t\t\t%.2f", elapsed);
	return 0;
}
void createSudoku(){
	int i,j,k;
	scanf("%d",&size);
	getchar();
	len=size*size;

	for(i=0;i<len;i++){
		for(j=0;j<len;j++){
		a[i][j]=(int*)malloc(sizeof(int)*(len+1));
		}
	}
	for(i=0;i<len;i++){
		for(j=0;j<len;j++){
			for(k=0;k<len+1;k++){
				a[i][j][k]=0;
			}
		}
	}
}
void fillSudoku(){
	int i,j,ch,num=0;
	for(i=0;i<len;i++){
		for(j=0;j<len;j++){
			num=0;
			while(1){
				ch=getchar();\
				if(ch==' ' ||  ch=='\t'|| ch=='\n'){
					break;
				}
				else{
					num=num*10+(ch-'0');
				}
			}
			a[i][j][0]=num;									//Very important step; fills value in sudoku.
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
	printf("-------------------------------------------------------------------------------\n");
}
void fillHintRow(){
	int i,j,num=0;
	for(i=0;i<len;i++){									//probe the sudoku cell by cell
		for(j=0;j<len;j++){
			if(a[i][j][0]>0){							//if a number is filled in sudoku
				num=a[i][j][0];							//get that number in num
				fillHintRowUsingSudkoRow(i,j,num);		//fill this num in hint list of all cells corresponding to its row
				fillHintRowUsingSudkoColumn(i,j,num);	//fill this num in hint list of all cells corresponding to its col
			}
		}
	}
	fillHintRowUsingSudkoCell();
}
void printHintRow(){									
	int i,j,k;
		for(i=0;i<len;i++){
			for(j=0;j<len;j++){
				if(a[i][j][0]==0){						//find where a num is not present
					printf("Hint row for %d %d :",i,j);
					for(k=1;k<=len;k++){
							printf(" %d",a[i][j][k]);
					}
					printf("\n");
				}
			}
		}
	printf("\n");
}
void fillHintRowUsingSudkoRow(int i,int j,int num){
	int col;
	for(col=0;col<len;col++){					//for all its column, where there is a blank, update its hint list that num cannot come
		if(a[i][col][0]==0)a[i][col][num]=1;	//1 in hint list means, that number cannot come
	}
	//printHintRow();											
}
void fillHintRowUsingSudkoColumn(int i,int j,int num){
	int row;
	for(row=0;row<len;row++){					//run for all its rows
		if(a[row][j][0]==0)a[row][j][num]=1;	//if there is a blank, update its hint list that num cannot come	
	}											//1 in hint list means, this number cannot come
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
	//printHintRow();
}
void fillNumUsingHintRow(){						//Fills number using hint row only. Rule 1
	fillHintRow();
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
					printf("%d Filled in %d row, %d col\n",num,i+1,j+1);
					fill_count++;
					i=-1;						
					j=-1;
					fillHintRow();
				}
			}
			if(j==-1)break; //Number is filled, run from starting
			j++;
		}
		i++;
	}
}
void fillOccurencePerRow(){
	int i,j,num=0,flag=0;
	for(i=0;i<len;i++){
		for(j=0;j<len;j++){			//Fill occurences per row
			if(a[i][j][0]==0){		//if a number is not filled in sudoku; probe its hint list
					int hint;
					for(hint=1;hint<=len;hint++){
						if(a[i][j][hint]==0){
							if(or[i][hint]==-1){
								continue;
							}
							or[i][hint]++;
							pnr[i][hint]=pnr[i][hint]+j;
						}
						else if(a[i][j][hint]!=0){
							or[i][hint]=-1;
							pnr[i][hint]=-1;
						}
					}
			}
		}
		for(num=1;num<=len;num++){
			if(or[i][num]==1){								//Only 1 occurence of a number;
					printf("%d Filled in %d row, %d col  using occurences of Row\n",num,i+1,pnr[i][num]+1);
					a[i][pnr[i][num]][0]=num;				//fill that number in sudoku
					fill_count++;
					//printSudoku();
					fillNumUsingHintRow();
					flag=1;
					int hint;
					int pos;
					pos=pnr[i][hint];
					for(hint=1;hint<=len;hint++){			//decrement the occurences of other element in its hint list
						if(hint==num){
							or[i][hint]=0;
							pnr[i][hint]=0;
							continue;
						}
						else if(a[i][pnr[i][num]][hint]==0){
							or[i][hint]--;
							pnr[i][hint]=pnr[i][hint]-pos;
						}
					}
			}
		}
	}
	if(flag==1){
		clearOccurenceRow();
		clearOccurenceCol();
		clearOccurenceGrid();
		fillOccurencePerRow();
		fillOccurencePerCol();
		fillOccurencePerGrid();
	}
}
void clearOccurenceRow(){
	int i,j,depth;
	depth=psize*psize;
	for(i=0;i<depth;i++){
		for(j=0;j<(depth+1);j++){			//Fill occurences per row
			or[i][j]=0;
			pnr[i][j]=0;
		}
	}
}
void fillOccurencePerCol(){
	int i,j,num=0,flag=0;						//here i is col; j is row
	for(i=0;i<len;i++){
		for(j=0;j<len;j++){
			if(a[j][i][0]==0){								//if a number is not filled in sudoku; probe its hint list
					int hint;
					for(hint=1;hint<=len;hint++){			//Probing Hint list
						if(a[j][i][hint]==0){				//check if a number can come there
							if(oc[i][hint]==-1){
								continue;
							}
							oc[i][hint]++;
							pnc[i][hint]=pnr[i][hint]+j;	//save row number
						}
						else if(a[j][i][hint]!=0){
							oc[i][hint]=-1;
							pnc[i][hint]=-1;
						}
					}
			}
		}
		for(num=1;num<=len;num++){
			if(oc[i][num]==1){								//Only 1 occurence of a number;
					printf("%d Filled in %d row, %d col using occurences of Col\n",num,pnc[i][num]+1,i+1);
					a[pnc[i][num]][i][0]=num;				//fill that number in sudoku
					fill_count++;
					//printSudoku();
					fillNumUsingHintRow();
					flag=1;
					int hint;
					int pos;
					pos=pnc[i][num];
					for(hint=1;hint<=len;hint++){			//decrement the occurences of other element in its hint list
						if(hint==num){
							oc[i][hint]=0;
							pnc[i][hint]=0;
							continue;
						}
						else if(a[pnc[i][num]][i][hint]==0){
							oc[i][hint]--;
							pnc[i][hint]=pnc[i][hint]-pos;
						}
					}
			}
		}
	}
	if(flag==1){
		clearOccurenceRow();
		clearOccurenceCol();
		clearOccurenceGrid();
		fillOccurencePerRow();
		fillOccurencePerCol();
		fillOccurencePerGrid();
	}
}
void clearOccurenceCol(){
	int i,j,depth;
	depth=psize*psize;
	for(i=0;i<depth;i++){
		for(j=0;j<(depth+1);j++){			//Fill occurences per row
			oc[i][j]=0;
			pnc[i][j]=0;
		}
	}
}
void fillOccurencePerGrid(){
	int i=0,j=0,row=0,col=0,num=0,grid_no=0,flag=0,cell_no;
	for(i=0;i<len;i=i+size){
		for(j=0;j<len;j=j+size){								//A grid starts here. in row and col, a row starts from  i
			cell_no=0;
			grid_no=i+(int)(j/size);
			
			row=0;
			while(row<size){
				col=0;
				while(col<size){
					cell_no=row*size+col;
					int hint;
					if(a[i+row][j+col][0]==0){	//implies no number is filled in sudoku
						for(hint=1;hint<=len;hint++){			//Probing Hint list
							if(a[i+row][j+col][hint]==0){				//check if a number can come there
								if(og[grid_no][hint]<0){
									continue;
								}
								og[grid_no][hint]++;
								png[grid_no][hint]=png[grid_no][hint]+cell_no;	//save row number
							}
						}
					}
					else if(a[i+row][j+col][0]!=0){
						hint=a[i+row][j+col][0];
						og[grid_no][hint]=-1;
						png[grid_no][hint]=-1;
					}
					col++;
				}
				row++;
			}//Occurences saved in og
		//print_og(grid_no);
		//print_png(grid_no);
	
		for(num=1;num<=len;num++){
			if(og[grid_no][num]==1){//where occ is 1,fill that no in sudoku								//Only 1 occurence of a number;
					int r,c;
					cell_no=png[grid_no][num];
					r=grid_no +(int)((cell_no)/size)-(grid_no%size);
					c=((int)(grid_no%size)*size)+(cell_no%size);
					printf("%d Filled in %d row, %d col using occurences of Grid\n",num,r+1,c+1);
					a[r][c][0]=num;				//fill that number in sudoku
					fill_count++;
					//printSudoku();
					fillNumUsingHintRow();
					flag=1;
					int hint;
					int pos;
					pos=png[grid_no][num];
					for(hint=1;hint<=len;hint++){			//decrement the occurences of other element in its hint list
						if(hint==num){
							og[grid_no][hint]=0;
							png[grid_no][hint]=0;
							continue;
						}
						else if(a[r][c][hint]==0){
							og[grid_no][hint]--;
							png[grid_no][hint]=png[grid_no][hint]-pos;
						}
					}
			}
		}
		if(flag==1){
			clearOccurenceRow();
			clearOccurenceCol();
			clearOccurenceGrid();
			fillOccurencePerRow();
			fillOccurencePerCol();
			fillOccurencePerGrid();
		}
		}//Change per grid must be done above this; end of j
	}
}
void clearOccurenceGrid(){
	int i,j,depth;
	depth=psize*psize;
	for(i=0;i<depth;i++){
		for(j=0;j<(depth+1);j++){			//Fill occurences per row
			og[i][j]=0;
			png[i][j]=0;
		}
	}
}
void print_og(int grid_no){
	int i;
	printf("Occurence of numbers in grid %d is : \t",grid_no);
	for(i=1;i<=len;i++){
		printf("%d ",og[grid_no][i]);
	}
	printf("\n");
}
void print_png(int grid_no){
	int i;
	printf("Pos of numbers in grid %d is : \t\t\t",grid_no);
	for(i=1;i<=len;i++){
		printf("%d ",png[grid_no][i]);
	}
	printf("\n");
}
void status(){
	float num=0,total_num=0;
	total_num=len*len;
	for(i=0;i<len;i++){
		for(j=0;j<len;j++){
				if(a[i][j][0]!=0)num++;
		}
	}
	if(total_num==num){
		printf("Success !\n");
	}
		printf("Total Numbers:\t\t\t\t%.0f\n",total_num);
		printf("Numbers Filled:\t\t\t\t%d\n",fill_count);
		printf("Numbers Left:\t\t\t\t%.0f\n",total_num-num);
		printf("Percentage Filled:\t\t\t%.2f\n",(num*100)/total_num);
}
