#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	FILE *imageIN,*imageOUT_Y,*imageOUT_U,*imageOUT_V,*out_Y,*out_U,*out_V,*out_done;
	int i=1;
	unsigned int Y,U,V,DONE;//用來放置檔案讀出的十進制值 
	unsigned char head[54];//HEADER
	
	
	imageIN = fopen("mountain256.bmp","rb");//使用mountain256的HEADER給Y U V 使用 以及作為程式的start 
	out_Y = fopen("outportY.out","r");//FPGA_OUTPUT_Y 
	out_U = fopen("outportU.out","r");//FPGA_OUTPUT_U 
	out_V = fopen("outportV.out","r");//FPGA_OUTPUT_V 
	out_done = fopen("done.out","r");//FPGA_OUTPUT_done 
	
	if(imageIN && out_Y && out_U && out_V && out_done){	

	imageOUT_Y = fopen("mountain256_Y.bmp","wb");//OUTPUT_FILE_Y
	imageOUT_U = fopen("mountain256_U.bmp","wb");//OUTPUT_FILE_U
	imageOUT_V = fopen("mountain256_V.bmp","wb");//OUTPUT_FILE_V	

	
		fread(&head,54,sizeof(unsigned char),imageIN);//讀mountain256的HEADER
		fwrite(&head,54,sizeof(unsigned char),imageOUT_Y);//寫入mountain256的HEADER
		fwrite(&head,54,sizeof(unsigned char),imageOUT_U);//寫入mountain256的HEADER
		fwrite(&head,54,sizeof(unsigned char),imageOUT_V);//寫入mountain256的HEADER
		
		while(1)
		{
		
			fscanf(out_Y,"%d",&Y);//掃描每個clock的訊號 
			fscanf(out_U,"%d",&U);//掃描每個clock的訊號 
			fscanf(out_V,"%d",&V);//掃描每個clock的訊號 
			fscanf(out_done,"%d",&DONE);//掃描每個clock的訊號 
			if(DONE) //當done為1時寫入值(8-bit) 
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
		
		
			if(i>65536) //做完256*256次以後中斷 
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
