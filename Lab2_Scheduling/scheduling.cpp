#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define Size 200
struct cdfg{
       int op;
       int op1;
       int op2;
       int result;
       }sample1[Size];

struct readylist{
       int state;
       int op;
       int num;
       int dis;
       }list1[Size],temp;
       
struct alu{
       int mult;
       int add;
       }alulist[Size];

int readIn()
{
	FILE *fptr_in;

    int step=0,op=0,op1=0,op2=0,result=0,count=0,end;
	char  In_FileName[20]; 
	int i;


    printf("\n欲選擇圖1，請輸入 p1.txt \n欲選擇圖2，請輸入 p2.txt\n");    
    printf("\n Enter Input filename : ");
	scanf("%s",In_FileName);
	
    if( (fptr_in = fopen(In_FileName , "r")) == NULL )
	{
		printf("Error!!can not open file!! \nPress any key to exit. \n");
    	exit(1); 
	}
	
	fscanf(fptr_in,"%d",&end);
	
	
    while( fscanf(fptr_in," %d %d %d %d ",&op,&op1,&op2,&result) ){


                         sample1[count].op=op;
 //                        printf("op=%d",sample1[count].op);

                         sample1[count].op1=op1;
 //                        printf("op1=%d",sample1[count].op1);

                         sample1[count].op2=op2;
 //                        printf("op2=%d",sample1[count].op2);

                         sample1[count].result=result;
 //                        printf("result=%d\n\n",sample1[count].result);

    count++;
    
    if(end==count)   //終止用 
    break;

    }
//                  sample1[count].step=-1;
//                         printf("count=%d step=%d\n",count,sample1[count].step);


    
	fclose(fptr_in);
	return end;
}


int compare(const void *a, const void *b)
{
	return ((*(struct readylist *)a).state - (*(struct readylist *)b).state);
}


void list_Scheduling(int end)
{
	 int opmult;
	 int opadd;
     int signal;
     int state;
     int opstate;
     int i;
     
     FILE *fptr_out;
     fptr_out = fopen( "Scheduling_outcome.txt" , "w");     
     
     do{
     printf("\n 輸入限制的乘法器個數...");
     scanf("%d",&opmult);
     printf("\n 輸入限制的加法器個數...");
     scanf("%d",&opadd);
     
     printf("\n乘法器個數：%d,加法器個數：%d\n",opmult,opadd);
     signal=0;
     state=1;
     opstate=1;
     for(i=0;i<Size;i++)                                //alulist 初始化 
     {
     alulist[i].add=opadd;     
     alulist[i].mult=opmult;
     }    
         

//??
	 for(i = 0; i < end; ++i) {  //設定list1資料
	 	list1[i].state = 1;
	 	list1[i].op = sample1[i].op;
		list1[i].num = i;
	 }
	 
	 for(i = 0; i < end; ++i) {
	 	int j;
	 	for(j = i-1; j >= 0; --j) {
	 		//尋找運算元出現的位置
	 		if(sample1[list1[j].num].result==sample1[i].op1 || sample1[list1[j].num].result==sample1[i].op2) {
				 state = list1[j].state + 1;  //運算元出現state+1
	 			break;
			}
		}
		
		while(1) {
			//state是否有足夠的加法器、乘法器
			if(list1[i].op == 1) {
				if(alulist[state].add > 0) {
					--alulist[state].add;
					break;
				}
				else {
					++state;
				}
			}
			else {
				if(alulist[state].mult > 0) {
					--alulist[state].mult;
					break;
				}
				else {
					++state;
				}
			}
		}
		list1[i].state = state;  //設定state
		//以state值為目標執行sorting由小到大
		qsort(list1, i, sizeof(struct readylist), compare);
	 }
	 
	 for(i = 0; i < end; ++i) {  //計算距離最後一個運算幾個距離
	 	list1[i].dis = state - list1[i].state;
	 }

	 fprintf(fptr_out, "*********************************\n");
	 fprintf(fptr_out, "*\tResource Constraint\t*\n");
	 fprintf(fptr_out, "*\t\t\t\t*\n");
	 fprintf(fptr_out, "*\tMult Constraint:%d\t*\n", opmult);
	 fprintf(fptr_out, "*\tAdd Constraint:%d\t*\n", opadd);
	 fprintf(fptr_out, "*\t\t\t\t*\n");
	 fprintf(fptr_out, "*********************************\n");
	 //顯示排程結果，並寫入檔案 
	 for(i = 0; i < end; ++i) {
	 	int num = list1[i].num;
	 	printf("State: %d\tv%3d = v%3d ", list1[i].state, sample1[num].result, sample1[num].op1);
	 	fprintf(fptr_out, "State: %d\tv%3d = v%3d ", list1[i].state, sample1[num].result, sample1[num].op1);
	 	if(list1[i].op == 1) {
	 		printf("+");
	 		fprintf(fptr_out, "+");
		}
		else {
			printf("*");
	 		fprintf(fptr_out, "*");
		}
		printf(" v%3d\n", sample1[num].op2);
	 	fprintf(fptr_out, " v%3d\n", sample1[num].op2);
	 }
	 
	 printf("輸入1繼續，輸入2結束:");
	 scanf("%d", &signal);
	 if(signal == 1) continue;
	 else if(signal == 2) break;
	 }while(1);
   	fclose(fptr_out);     
          
}//list_Scheduling
     
      


int main()
{

    int end;

    end=readIn();
    

    list_Scheduling(end);



//    system("pause");
	return 0;
}
