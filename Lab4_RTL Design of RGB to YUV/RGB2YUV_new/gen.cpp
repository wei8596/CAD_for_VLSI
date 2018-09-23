#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	FILE *imageIN,*imageOUT_Y,*imageOUT_U,*imageOUT_V,*out_Y,*out_U,*out_V,*out_done;
	int i=1;
	unsigned int Y,U,V,DONE;//�Ψө�m�ɮ�Ū�X���Q�i��� 
	unsigned char head[54];//HEADER
	
	
	imageIN = fopen("mountain256.bmp","rb");//�ϥ�mountain256��HEADER��Y U V �ϥ� �H�Χ@���{����start 
	out_Y = fopen("outportY.out","r");//FPGA_OUTPUT_Y 
	out_U = fopen("outportU.out","r");//FPGA_OUTPUT_U 
	out_V = fopen("outportV.out","r");//FPGA_OUTPUT_V 
	out_done = fopen("done.out","r");//FPGA_OUTPUT_done 
	
	if(imageIN && out_Y && out_U && out_V && out_done){	

	imageOUT_Y = fopen("mountain256_Y.bmp","wb");//OUTPUT_FILE_Y
	imageOUT_U = fopen("mountain256_U.bmp","wb");//OUTPUT_FILE_U
	imageOUT_V = fopen("mountain256_V.bmp","wb");//OUTPUT_FILE_V	

	
		fread(&head,54,sizeof(unsigned char),imageIN);//Ūmountain256��HEADER
		fwrite(&head,54,sizeof(unsigned char),imageOUT_Y);//�g�Jmountain256��HEADER
		fwrite(&head,54,sizeof(unsigned char),imageOUT_U);//�g�Jmountain256��HEADER
		fwrite(&head,54,sizeof(unsigned char),imageOUT_V);//�g�Jmountain256��HEADER
		
		while(1)
		{
		
			fscanf(out_Y,"%d",&Y);//���y�C��clock���T�� 
			fscanf(out_U,"%d",&U);//���y�C��clock���T�� 
			fscanf(out_V,"%d",&V);//���y�C��clock���T�� 
			fscanf(out_done,"%d",&DONE);//���y�C��clock���T�� 
			if(DONE) //��done��1�ɼg�J��(8-bit) 
			{
				
				fwrite(&Y,1,sizeof(unsigned char),imageOUT_Y);
				fwrite(&Y,1,sizeof(unsigned char),imageOUT_Y);
				fwrite(&Y,1,sizeof(unsigned char),imageOUT_Y);
		
				fwrite(&U,1,sizeof(unsigned char),imageOUT_U);
				fwrite(&U,1,sizeof(unsigned char),imageOUT_U);
				fwrite(&U,1,sizeof(unsigned char),imageOUT_U);

				fwrite(&V,1,sizeof(unsigned char),imageOUT_V);
				fwrite(&V,1,sizeof(unsigned char),imageOUT_V);
				fwrite(&V,1,sizeof(unsigned char),imageOUT_V);				
				i++;
				
				
			}
		
		
			if(i>65536) //����256*256���H�ᤤ�_ 
			{
			
			
				printf("DONE\n");
				break;
			
			}
	
		
		}
		

		
	}	
	else{
			printf("Could not read the file\n");
			system("pause");
			return 0 ;	
	}
	
	
	//close file
	fclose(imageIN);
	fclose(imageOUT_Y);
	fclose(imageOUT_U);
	fclose(imageOUT_V);
	fclose(out_Y);
	fclose(out_U);
	fclose(out_V);
	fclose(out_done);
	// close file
	
	system("pause");
	return 0 ;	
	
	
	
	
	
	
	
	
	
	
	
}
