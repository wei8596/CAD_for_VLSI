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


    printf("\n����ܹ�1�A�п�J p1.txt \n����ܹ�2�A�п�J p2.txt\n");    
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
    
    if(end==count)   //�פ�� 
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
     printf("\n ��J������k���Ӽ�...");
     scanf("%d",&opmult);
     printf("\n ��J����[�k���Ӽ�...");
     scanf("%d",&opadd);
     
     printf("\n���k���ӼơG%d,�[�k���ӼơG%d\n",opmult,opadd);
     signal=0;
     state=1;
     opstate=1;
     for(i=0;i<Size;i++)                                //alulist ��l�� 
     {
     alulist[i].add=opadd;     
     alulist[i].mult=opmult;
     }    
         

//??
	 for(i = 0; i < end; ++i) {  //�]�wlist1���
	 	list1[i].state = 1;
	 	list1[i].op = sample1[i].op;
		list1[i].num = i;
	 }
	 
	 for(i = 0; i < end; ++i) {
	 	int j;
	 	for(j = i-1; j >= 0; --j) {
	 		//�M��B�⤸�X�{����m
	 		if(sample1[list1[j].num].result==sample1[i].op1 || sample1[list1[j].num].result==sample1[i].op2) {
				 state = list1[j].state + 1;  //�B�⤸�X�{state+1
	 			break;
			}
		}
		
		while(1) {
			//state�O�_���������[�k���B���k��
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
		list1[i].state = state;  //�]�wstate
		//�Hstate�Ȭ��ؼа���sorting�Ѥp��j
		qsort(list1, i, sizeof(struct readylist), compare);
	 }
	 
	 for(i = 0; i < end; ++i) {  //�p��Z���̫�@�ӹB��X�ӶZ��
	 	list1[i].dis = state - list1[i].state;
	 }

	 fprintf(fptr_out, "*********************************\n");
	 fprintf(fptr_out, "*\tResource Constraint\t*\n");
	 fprintf(fptr_out, "*\t\t\t\t*\n");
	 fprintf(fptr_out, "*\tMult Constraint:%d\t*\n", opmult);
	 fprintf(fptr_out, "*\tAdd Constraint:%d\t*\n", opadd);
	 fprintf(fptr_out, "*\t\t\t\t*\n");
	 fprintf(fptr_out, "*********************************\n");
	 //��ܱƵ{���G�A�üg�J�ɮ� 
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
	 
	 printf("��J1�~��A��J2����:");
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
