#include "myfile.h"
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
//��ʼ�������㺯�� 
void InitList(LinkList**L)
{
	*L=(LinkList*)malloc(sizeof(LinkList));
	(*L)->next=NULL; 
}
//��������ڵ㺯�� 
void ListInsert(LinkList*L,LinkList*p)
{
	LinkList*q=L;
	while(q->next!=NULL)
	{
		q=q->next; 
		
	 } 
	 q->next=p;
		p->next=NULL;
	
}
//д�������־���� 
void write_diary(char*time,char*nam,char*stunum,char*act,char*cardnum)
{
	    FILE *fp;
        fp=fopen("logbook.txt","a+");
        
        
        	fprintf(fp,"����ʱ�䣺%s,������%s,ѧ�ţ�%s,���������%s ���ţ�%s;\n",time,nam,stunum,act,cardnum);
        	
        fclose(fp); 
}
void write_diary2(FILE*fp,char*time,char*nam,char*stunum,char*act,char*cardnum,float money,float money_left,int window)
{
        	fprintf(fp,"����ʱ�䣺%s,������%s,ѧ�ţ�%s,���������%s ���ţ�%s,���׶�: %.2f,���:%.2f,���ں�:%d;\n",time,nam,stunum,act,cardnum,money,money_left,window);
}
//����������Ϣд��logbook.txt������־ 
void displays(LinkList*L)
{
	FILE *fp;
	LinkList*p=L->next;
	strcpy(act,"�����ɹ���");
	strcpy(time,"20210901");
	
	 if((fp=fopen("logbook.txt","w"))==NULL)// �Կ�д�ķ�ʽ�򿪵�ǰĿ¼�µ�.txt  
    {  
//        printf("���ܴ򿪴��ļ����밴������˳�\n");  
        exit(1);  //�쳣�˳�
    }  
	
	
	while(p!=NULL)
	{  
		fprintf(fp,"����ʱ�䣺%s,������%s,ѧ�ţ�%s,���������%s\n",time,p->data.name,p->data.number,act); 
		p=p->next; 
	}
	 fclose(fp); 
}
int getSum(int num)
{
	int sum=0;
	while(num>0)
	{
		int i=num%10;
		sum=sum+i;
		num=num/10;
	}
	return sum;
}
//��L���������н�㷢�� 
void gives(LinkList *L)
{  
    int k=312346;
    int key,j;
    
    strcpy(act,"�����ɹ���");
    strcpy(time,"20210903");
    
	LinkList*p=L->next;
	while(p!=NULL){
		key=9-getSum(k)%10;
		j=k*10+key;
		itoa(j,cardnum,10);
		strcpy(p->data.num,cardnum);
		strcpy(nam,p->data.name);
		strcpy(stunum,p->data.number);
		
		write_diary(time,nam,stunum,act,cardnum);
		p=p->next;
		k++;
		
	} 
	
 } 
// ������������������д�뵽������־ 
void deletecards(LinkList*L,char*time,char*stunum) 
{
	LinkList *p,*pre;  
    
    pre=L;  
    p=pre->next;  
    int judge=0;  
    while(p)  
    {  
         if(0==strcmp(p->data.number,stunum))  
         {  
                 judge=1;  
                 strcpy(act,"�����ɹ���");
                 strcpy(nam,p->data.name);
                 strcpy(cardnum,p->data.num);
                
                 pre->next =p->next;  
                 free(p);
                 
                 write_diary(time,nam,stunum,act,cardnum);
//                 ������־ 
				   
                 break;  
         }  
         pre=p;  
         p=p->next;  
    }  
    if(judge==0)  
    {
	 
       strcpy(act,"ѧ�Ų����ڣ�");
       FILE *fp;
       fp=fopen("logbook.txt","a+");
       fprintf(fp,"%s,%s,%s\n",time,stunum,act);
       fclose(fp); 
    } 
       
}
//������ʧ�ͽ�Ҳ���������д�뵽������־ 
void loses(LinkList*L,char*time,char*stunum,int b)
{
	int flag=0;
    LinkList*q=L->next;


	while(q)
 		{
		  if(0==strcmp(q->data.number,stunum))
		  {
		  	if(q->data.state==0)
		  	{
		  		flag=1;
			    break;
			  }
		  
		  }
		  q=q->next; 
	    }
	    if(flag==1)
	    {
	    	

        	if(b==1)
	      {
		    q->data.state=1;
		    strcpy(act,"��ʧ�ɹ���");
		    strcpy(nam,q->data.name);
		    strcpy(cardnum,q->data.num);
		    
		    write_diary(time,nam,stunum,act,cardnum);
//		    ������־ 
	      }
	       if(b==2)
          {
	    	q->data.state=0;
	    	strcpy(act,"��ҳɹ���");
		    strcpy(nam,q->data.name);
		    strcpy(cardnum,q->data.num);
	    	write_diary(time,nam,stunum,act,cardnum);
//		    ������־   
	      }
		}
 	   else{
 	   	strcpy(act,"ѧ�Ų����ڣ�");
        FILE *fp;
        fp=fopen("logbook.txt","a+");
        fprintf(fp,"%s,%s,%s\n",time,stunum,act);
        fclose(fp);
// 	   	������־ 
		}
   
	
}
//���������������� 
void renews(LinkList*L,char*time,char*stunum)
{
//	�½�һ���ڵ㣬����ѧ����ͬ
  LinkList*q=L->next; 
  
  int flag=0; 
  while(q)
 		{
		  if(0==strcmp(q->data.number,stunum))
		  {
		  	if(q->data.state==0)
		  	{
		  		flag=1;
		  		break; 
			  }
			  strcpy(nam,q->data.name);
		  }
		  q=q->next; 
	    }
 	if(flag==1)
 	{
 		strcpy(act,"��ѧ�Ŵ���δ��ʧ�Ŀ���");
		strcpy(nam,q->data.name);
		strcpy(cardnum,q->data.num);
		
 		write_diary(time,nam,stunum,act,cardnum);
	 }
   else
   {
   	    LinkList*q=L;
	    int k; 
     	while(q->next!=NULL)
	   {
		q=q->next; 
		
	   } 
	    k=atoi(q->data.num)/10+1;
	    int key,j;
    
	    LinkList*p;
	    InitList(&p);
		key=9-getSum(k)%10;
		j=k*10+key;
		itoa(j,cardnum,10);
		strcpy(p->data.num,cardnum);
		strcpy(p->data.number,stunum);
		strcpy(p->data.name,nam);
	    ListInsert(L,p) ;
	     
	    strcpy(act,"�����ɹ���");
		strcpy(nam,p->data.name);
		strcpy(cardnum,p->data.num);
	    write_diary(time,nam,stunum,act,cardnum);
	    
   }
	 
}
//������ȡ��ʱ��ε�5����ֵ�������ļ�����ִ�в��� 
void readStuAct(LinkList*L)
{
	int i;
	FILE *fp,*FP,*fp_h;  
    fp=fopen("cz002.txt","r"); //��ֻ����ʽ�򿪵�ǰĿ¼�µ�.txt  
    FP=fopen("logbook2.txt","a+");
    fp_h=fopen("history.txt","a+");
    if(fp==NULL)  
    {   
        exit(0);                   //��ֹ����  
    }  
    fscanf(fp, "%*[A-Z]");
    fscanf(fp, "%*[\n]"); 
 
    while(!feof(fp))  
    {  

        
        fscanf(fp, "%[^,]",time);
		fscanf(fp, "%*[,]");
		fscanf(fp, "%[^,]", act);
		fscanf(fp, "%*[,]");
		fscanf(fp, "%10s", stunum);
		fscanf(fp, "%*[,]");
		fscanf(fp,"%[^;]",m);
		fscanf(fp, "%*[;]");
		fscanf(fp, "%*[\n]");
		
	    
	if(strcmp(act,"����")==0) 
	{
		deletecards(L,time,stunum);
	}
	else if(strcmp(act,"��ʧ")==0)
	{
		loses(L,time,stunum,1);
	}
	else if(strcmp(act,"���")==0)
	{
		loses(L,time,stunum,2);
	}
	else if(strcmp(act,"����")==0)
	{
		renews(L,time,stunum);
		
	}
	else if(strcmp(act,"��ֵ")==0) 
	{
//		ReadRechargeFile(time,act,stunum,m);
		
	}

	
        
    }  
    fclose(fp);

    OperateCz("cz1.txt",L,FP);
    OperateXf("xf1.txt",L,FP,fp_h);
    OperateCz("cz2.txt",L,FP);
    OperateXf("xf2.txt",L,FP,fp_h);
    OperateCz("cz3.txt",L,FP);
    OperateXf("xf3.txt",L,FP,fp_h);
    OperateCz("cz4.txt",L,FP);
    OperateXf("xf4.txt",L,FP,fp_h);
    OperateCz("cz5.txt",L,FP);
    OperateXf("xf5.txt",L,FP,fp_h);
    
    for(i=1;i<=57;i++){
    	wz[i]--;
	}
    fclose(FP);
    fclose(fp_h);
}
//��ȡxf004.txt�ļ����ҷֳ�5��ʱ��ε�txt�ļ� 
void ReadConsumptionFile()
{
	FILE*fp3,*fp01,*fp02,*fp03,*fp04,*fp05;
	char date[18],hour[9],m[8];
	if((fp3=fopen("xf014.txt","r"))==NULL)
	{
		printf("���ܴ��ļ�xf014��\n");
		return;
	}
	if((fp01=fopen("xf1.txt","rw+"))==NULL)
	{
		printf("���ܴ��ļ�xf1��\n");
		return;
	}
	if((fp02=fopen("xf2.txt","rw+"))==NULL)
	{
		printf("���ܴ��ļ�xf2��\n");
		return;
	}
	if((fp03=fopen("xf3.txt","rw+"))==NULL)
	{
		printf("���ܴ��ļ���\n");
		return;
	}
	if((fp04=fopen("xf4.txt","rw+"))==NULL)
	{
		printf("���ܴ��ļ���\n");
		return;
	}
	if((fp05=fopen("xf5.txt","rw+"))==NULL)
	{
		printf("���ܴ��ļ���\n");
		return;
	}
	fscanf(fp3, "%*[A-Z]");
    fscanf(fp3, "%*[\n]"); 
	while(fgets(cardnum,8,fp3)!=NULL)
	{
		if(cardnum[0]=='W')
		{
			fprintf(fp01,"%s",cardnum);
			fprintf(fp02,"%s",cardnum);
			fprintf(fp03,"%s",cardnum);
			fprintf(fp04,"%s",cardnum);
			fprintf(fp05,"%s",cardnum);
		}
		else{
			fgetc(fp3);
			fgets(date,9,fp3);
			fgetc(fp3);
			fgets(hour,9,fp3);
			fgetc(fp3) ;
			fscanf(fp3,"%[^;]",m);
			fscanf(fp3,"%*[;]");
			fscanf(fp3, "%*[\n]");
			strcat(date,hour);
			if(strcmp(date,"2021090423595959")>0&&strcmp(date,"2021101400000000")<0) 
			fprintf(fp01,"%s,%s,%s\n",cardnum,date,m);
			else if(strcmp(date,"2021101406595959")>0&&strcmp(date,"2021110400000000")<0)
			fprintf(fp02,"%s,%s,%s\n",cardnum,date,m);
			else if(strcmp(date,"2021110406595959")>0&&strcmp(date,"2021112500000000")<0)
			fprintf(fp03,"%s,%s,%s\n",cardnum,date,m);
			else if(strcmp(date,"2021112506595959")>0&&strcmp(date,"2021121600000000")<0)
			fprintf(fp04,"%s,%s,%s\n",cardnum,date,m);
			else if(strcmp(date,"2021121606595959")>0&&strcmp(date,"2021123100000000")<0)
			fprintf(fp05,"%s,%s,%s\n",cardnum,date,m);
		}
	}
	fclose(fp3);
	fclose(fp01);
	fclose(fp02);
	fclose(fp03);
	fclose(fp04);
	fclose(fp05);
} 
//��ȡ��ֵ�ļ����ҷֳ����ʱ��ε��ļ� 
void ReadRechargeFile(char*time,char*act,char*stunum,char*m)
{
	FILE*fp01,*fp02,*fp03,*fp04,*fp05;
	
	if((fp01=fopen("cz1.txt","a+"))==NULL)
	{
		printf("���ܴ��ļ���\n");
		return;
	}
	if((fp02=fopen("cz2.txt","a+"))==NULL)
	{
		printf("���ܴ��ļ���\n");
		return;
	}
	if((fp03=fopen("cz3.txt","a+"))==NULL)
	{
		printf("���ܴ��ļ���\n");
		return;
	}
	if((fp04=fopen("cz4.txt","a+"))==NULL)
	{
		printf("���ܴ��ļ���\n");
		return;
	}
	if((fp05=fopen("cz5.txt","a+"))==NULL)
	{
		printf("���ܴ��ļ���\n");
		return;
	}
	
	if(strcmp(time,"2021090400000000")>0&&strcmp(time,"2021090423595959")<0) 
	fprintf(fp01,"%s,%s,%s,%s\n",time,act,stunum,m);
	else if(strcmp(time,"2021101400000000")>0&&strcmp(time,"2021101423595959")<0)
	fprintf(fp02,"%s,%s,%s,%s\n",time,act,stunum,m);
	else if(strcmp(time,"2021110400000000")>0&&strcmp(time,"2021110423595959")<0)
	fprintf(fp03,"%s,%s,%s,%s\n",time,act,stunum,m);
	else if(strcmp(time,"2021112500000000")>0&&strcmp(time,"2021112523595959")<0)
	fprintf(fp04,"%s,%s,%s,%s\n",time,act,stunum,m);
	else if(strcmp(time,"2021121600000000")>0&&strcmp(time,"2021121623595959")<0)
	fprintf(fp05,"%s,%s,%s,%s\n",time,act,stunum,m);
	
	
	fclose(fp01);
	fclose(fp02);
	fclose(fp03);
	fclose(fp04);
	fclose(fp05);
}
void OperateCz(char*file,LinkList*L,FILE*FP)
{
	FILE *fp; 
    fp=fopen(file,"r"); //��ֻ����ʽ�򿪵�ǰĿ¼�µ�.txt  
    
    if(fp==NULL)  
    {   
        exit(0);                   //��ֹ����  
    }  
 
    while(!feof(fp))  
    {  
//    ɨ��һ��ִ��һ�� 
        fscanf(fp, "%[^,]",time);
		fscanf(fp, "%*[,]");
		fscanf(fp, "%[^,]", act);
		fscanf(fp, "%*[,]");
		fscanf(fp, "%10s", stunum);
		fscanf(fp, "%*[,]");
		fscanf(fp,"%f",&money);
		fscanf(fp, "%*[;]");
		fscanf(fp, "%*[\n]");
		
//		ִ��
        LinkList*q=L->next;
	    int flag=0;
	    while(q)
 		{
		  if(0==strcmp(q->data.number,stunum))
		  {
		  	if(q->data.state==1)
		  	{
		  		
		  		strcpy(nam,q->data.name) ;
		  		strcpy(cardnum,q->data.num) ;
		  		strcpy(act,"��ʧ���ܳ�ֵ��");
		  		money_left=q->data.balance;
		  		write_diary2(FP,time,nam,stunum,act,cardnum,money,money_left,0);
		  		//		  		д������־����
			}
			else
			{
				if(q->data.balance>1000) 
				{
					fprintf(FP,"��ֵʧ����ֵ\n");
				}
				else {
					q->data.balance=q->data.balance+money;
				    strcpy(nam,q->data.name); 
				    strcpy(stunum,q->data.number); 
				    strcpy(cardnum,q->data.num) ;
				    strcpy(act,"��ֵ�ɹ���");
				    money_left=q->data.balance;
//				д������־���� 
                    write_diary2(FP,time,nam,stunum,act,cardnum,money,money_left,0);
				}
			}
		  	flag=1;
			break;
		  }
		  
		  
		  
		  q=q->next;
	    }
	    if(flag==0)
	    {
	    	fprintf(FP,"û���ҵ��ÿ��ţ�\n");
	    	//		  		д������־����
		}	
		
		
    }
    
    fclose(fp);
	
}
void OperateXf(char*file,LinkList*L,FILE*FP,FILE*fp_h)
{
	FILE *fp;  
    fp=fopen(file,"r"); //��ֻ����ʽ�򿪵�ǰĿ¼�µ�.txt  
    if(fp==NULL)  
    {   
        exit(0);                   //��ֹ����  
    }  
 
    while(fgets(cardnum,8,fp)!=NULL)
	{
		
//		ɨ��һ��ִ��һ�� 
		if(cardnum[0]=='W')
		{
			strcpy(cardnum,cardnum+1);
			window=atoi(cardnum); 
		}
		else{
			fgetc(fp);
			fscanf(fp,"%[^,]",time);
			fgetc(fp) ;
			fscanf(fp,"%f",&money);
			fscanf(fp,"%*[;]");
			fscanf(fp, "%*[\n]");
            }
//            ִ��
   	    LinkList*q=L->next;
	    int flag=0;
	    while(q)
 		{
		  if(0==strcmp(q->data.num,cardnum))
		  {
		  	if(q->data.state==1)
		  	{
			     
		  		fprintf(FP,"û���ҵ��ÿ��ţ�\n");
//		  		д������־���� 
			  }
			  else if(q->data.balance<0)
			  {
			  	strcpy(nam,q->data.name); 
				strcpy(stunum,q->data.number); 
				strcpy(act,"���㣡");
				money=0; 
				money_left=q->data.balance;
			  	
			  	write_diary2(FP,time,nam,stunum,act,cardnum,money,money_left,window);
//		  		д������־����
			   } 
			else
			{
				q->data.balance=q->data.balance-money;
				strcpy(nam,q->data.name); 
				strcpy(stunum,q->data.number); 
				strcpy(act,"���ѳɹ���");
				money_left=q->data.balance;
//				д������־���� 
				write_diary2(FP,time,nam,stunum,act,cardnum,money,money_left,window);

//              д���Ѽ�¼����
                if(wz[window]>=6*MAX)
                {
                	wz[window]=0;
                }
					pointer=wz[window];
                Record_consumption(window,time,cardnum,money,pointer,nam,stunum);
                wz[window]+=1;

//				д���Ѽ�¼txt
                strncpy(date,time,8);
                strncpy(hour,time+8,8);
                write_history(fp_h,window,date,hour,cardnum,money); 
               
			}
		  	flag=1;
			break;
		  }
		  q=q->next; 
	    }
	    if(flag==0)
	    {
	            fprintf(FP,"û���ҵ��ÿ��ţ�\n");
//	    	д������־���� 
		} 
		
    
    }
    
    fclose(fp);
	    
}
//��ȡλ���ļ� 
void ReadwzFile()
{
	FILE *fp;  
	int i;
	char str[4];
    fp=fopen("wz003.txt","r"); //��ֻ����ʽ�򿪵�ǰĿ¼�µ�.txt  
    fscanf(fp, "%*[A-Z]");
    fscanf(fp, "%*[\n]"); 
    for(i=1;i<=99;i++)
    {
    	fscanf(fp,"%[^,]",str);
    	fscanf(fp,"%*[,]");
    	fscanf(fp,"%d",&wz[i]);
    	fscanf(fp,"%*[;]");
    	fscanf(fp,"%*[\n]");
    	start[i]=wz[i];
	}
	fclose(fp);
}
//д�������� 
void Record_consumption(int window,char*time,char*cardnum,float money,int pointer,char*nam,char*stunum)
{
	char win[3];
	char string[3]; 
	char str[3]="0";
    if(window<10)
    {
    	strcat(str,itoa(window,string,10));
    	strcpy(win,str);
	} 
	else 
	{
	 	strcpy(win,itoa(window,string,10));
	}
	strcpy(Win[window][pointer].time,time);
	strcpy(Win[window][pointer].cardID,cardnum);
	strcpy(Win[window][pointer].name,nam);
	strcpy(Win[window][pointer].stuID,stunum);
	strcpy(Win[window][pointer].w,win);
	Win[window][pointer].pay=money;

}
//д���Ѽ�¼�ļ� 
void write_history(FILE*fp_h,int window,char*date,char*hour,char*cardnum,float money)
{
	
	char w[3];
	char string[3]; 
	char str[3]="0";
    if(window<10)
    {
    	strcat(str,itoa(window,string,10));
    	strcpy(w,str);
	} 
	else 
	{
	 	strcpy(w,itoa(window,string,10));
	}
    fprintf(fp_h,"������ţ�%s,���ڣ�%s,ʱ�䣺%s,���ѿ��ţ�%s ֧����%.2f;\n",w,date,hour,cardnum,money);
}
//�鲢���� 
void merge_sort()
{
	int current[100],i,j=1;
	int m=0;
	char first_data[100][17]; 
	char min_data[17];
	int flag[100];
	int k=0;
	for(k=1;k<58;k++)
	{
		flag[k]=0;
//		flag�������ڼ�¼�ô����Ƿ�ȫ������ 
	}

//    int length[100];
    start[24]=wz[24]+1;
	for(i=1;i<=57;i++)
	{

//	�����ÿһ�еĳ��ȣ���ÿһ�����ڵ����Ѽ�¼���� 
//		length[i]=sizeof(Win[i])/sizeof(Record);
//    	if(length[i]==6*MAX+1)
//    	start[i]=wz[i]+1;
//	��ʼ��first_data����
		current[i]=start[i];
		strcpy(first_data[i],Win[i][current[i]].time);
	}

//ѭ��
 //��ʼ��min_data��
		strcpy(min_data,"9999999999999990");
		
	while(strcmp(min_data,"9999999999999999")<0)
	{	   
	//ѡ����С�� 
       for(i=1;i<58;i++)
       {
    	    if(flag[i]!=1){
    		    if(strcmp(first_data[i],min_data)<0)
                {
        	     strcpy(min_data,first_data[i]);
        	      j=i;
                }
		    }
        }
        //��¼���� ��С�Ĵ���history���� 
        strcpy(history[m].time,min_data);
        strcpy(history[m].name,Win[j][current[j]].name);
        strcpy(history[m].w,Win[j][current[j]].w);
        strcpy(history[m].stuID,Win[j][current[j]].stuID);
        strcpy(history[m].cardID,Win[j][current[j]].cardID);
        history[m].pay=Win[j][current[j]].pay;
		//�����µ����ݣ�Ҷ�ӽ�� 
        current[j]++;m++;
		if(current[j]>=6*MAX)     
			current[j]=0;
//			������˻��Ƶĵط�������ɨ��λ��Ϊ0������ 
        if(current[j]==wz[j]+1) 
		{
			flag[j]=1;
			strcpy(first_data[j],"9999999999999999");
//			���ô��ڱȽϵ�������Ϊ�����ô��ڲ����ٽ��бȽ� 
			strcpy(min_data,"9999999999999999");
		}  
		else
		{
			strcpy(first_data[j],Win[j][current[j]].time);
//			ѡ����Сֵ�Ĵ��ں�һ�����ݴ���Ƚ�����first_data 
			strcpy(min_data,Win[j][current[j]].time);
		}
	} 
    len=m;
}
//�������� 
void quick_sort()
{
	
//	int length[100];
	int i,m=0,j;
	start[24]=wz[24]+1;

	for(i=1;i<=57;i++){
		j=start[i];
		while(1)
		{
			history[m]=Win[i][j];
			m++;j++;
			if(j>=6*MAX)	j=0;
			if(j==wz[i]+1) break;
		}
	}
	
//	����history����

   len=m;

   qsort(history,len,sizeof(Record),cmp);

}

char *my_strstr(const char * str1,const char * str2, int len)
{
	char *tmp2,*tmp1 = (char *)malloc(len);
	memcpy(tmp1,str2,len);
	*(tmp1+1)='\0';
	tmp2 = strstr(str1,tmp1);
	free(tmp1);
	return tmp2;
}
//������ģ����ѯ�ĺ��� 
int _m(char * str1,char * str2)
{
	char *pos=str1,*pos1=str2,*pos2=str2;
	char *tmp;
	while(1)
		switch(*pos1)
		{
		case '*':
			pos1++;
			pos2++;
			while(*pos2 != '*' && *pos2 != '?' && *pos2 != '\0')
				pos2+=2;
			if (pos2 != pos1)
			{
				tmp = my_strstr(pos,pos1,pos2-pos1);
				if(tmp != NULL)
				{
					pos = tmp+ (pos2-pos1);
					pos1 = pos2;
				}
				else
					return 0;
			}
			break;
		case '?':
			pos1++;
			pos2++;
			if(*pos!='\0')
				pos+=2;
			else
				return 0;
			break;
		case '\0':
			return 1;
			break;
		default:
			while(*pos2 != '*' && *pos2 != '?' && *pos2 != '\0')
				pos2+=2;
			if(!memcmp(pos,pos1,pos2-pos1))
			{
				pos += pos2-pos1;
				pos1 = pos2;
			}
			else
				return 0;
			break;
		}
	return 0;
}
//ģ����ѯ���� 
int _ms(char * str1,char * str2)
{
	char *pos=str1,*pos1=str2,*pos2=str2;
	char *tmp;
	while(1)
		switch(*pos1)
		{
		case '*':
			pos1++;
			pos2++;
			while(*pos2 != '*' && *pos2 != '?' && *pos2 != '\0')
				pos2++;
			if (pos2 != pos1)
			{
				tmp = my_strstr(pos,pos1,pos2-pos1);
				if(tmp != NULL)
				{
					pos = tmp+ (pos2-pos1);
					pos1 = pos2;
				}
				else
					return 0;
			}
			break;
		case '?':
			pos1++;
			pos2++;
			if(*pos!='\0')
				pos++;
			else
				return 0;
			break;
		case '\0':
			return 1;
			break;
		default:
			while(*pos2 != '*' && *pos2 != '?' && *pos2 != '\0')
				pos2++;
			//tmp = my_strstr(pos,pos1,pos2-pos1);
			//if(tmp != NULL && tmp == pos)
			if(!memcmp(pos,pos1,pos2-pos1))
			{
				pos += pos2-pos1;
				pos1 = pos2;
			}
			else
				return 0;
			break;
		}
	return 0;
}
//ģ����ѯ 
void search_mohu() 
{
	char start_time[17],end_time[17];
	float start_money,end_money;
	int choice,choice1,choice2,i;
	printf("ͨ��ѧ�Ż���������ѯ��1/2 \n");
	scanf("%d",&choice);
	if(choice==2){
		 printf("������ģ����ѯ������:\n");
	     scanf("%s",nam);
		 
	     printf("�Ƿ�ͨ��ʱ��β�ѯ��1/0\n");
	     scanf("%d",&choice1);
	     if(choice1) {
	     	printf("��������ֹʱ�䣺\n");
		 scanf("%s%s",start_time,end_time);
	    }
	     printf("�Ƿ�ͨ����Χ��ѯ��1/0 \n");
	    
	     scanf("%d",&choice2);
	     if(choice2) {
	     printf("�������Χ��\n");
		 scanf("%f,%f",&start_money,&end_money);
    	}
	     if(choice1&&choice2){
//	     	������ 
		for(i=0;i<len;i++)
		{
			if(_m(history[i].name,nam)&&strcmp(history[i].time,start_time)>0&&strcmp(history[i].time,end_time)<0&&history[i].pay>=start_money&&history[i].pay<=end_money) 
			printf("ʱ�䣺%s,������%s,���ţ�%s,ѧ�ţ�%s,���׽�%.2f\n",history[i].time,history[i].name,history[i].cardID,history[i].stuID,history[i].pay); 
		
		}
	    } 
	    else if(choice1){
	    	for(i=0;i<len;i++)
		{
			if(_m(history[i].name,nam)&&strcmp(history[i].time,start_time)>0&&strcmp(history[i].time,end_time)<0) 
			printf("ʱ�䣺%s,������%s,���ţ�%s,ѧ�ţ�%s,���׽�%.2f\n",history[i].time,history[i].name,history[i].cardID,history[i].stuID,history[i].pay); 
		
		}
		} 
		else if(choice2){
			
			for(i=0;i<len;i++)
		{
			if(_m(history[i].name,nam)&&history[i].pay>=start_money&&history[i].pay<=end_money) 
			printf("ʱ�䣺%s,������%s,���ţ�%s,ѧ�ţ�%s,���׽�%.2f\n",history[i].time,history[i].name,history[i].cardID,history[i].stuID,history[i].pay); 
		
		}
		}
		else{
			for(i=0;i<len;i++)
		{
			if(_m(history[i].name,nam)) 
			printf("ʱ�䣺%s,������%s,���ţ�%s,ѧ�ţ�%s,���׽�%.2f\n",history[i].time,history[i].name,history[i].cardID,history[i].stuID,history[i].pay); 
		}
      }
	} 
	else{
		printf("������ģ����ѯ��ѧ��:\n");
	    scanf("%s",stunum);
	    
	    printf("�Ƿ�ͨ��ʱ��β�ѯ��1/0\n");
	     scanf("%d",&choice1);
	     if(choice1) {
	     printf("��������ֹʱ�䣺\n");
		 scanf("%s%s",start_time,end_time);
	    }
	     printf("�Ƿ�ͨ����Χ��ѯ��1/0 \n");
	     scanf("%d",&choice2);
	     if(choice2) {
	     printf("�������Χ��\n");
		 scanf("%f,%f",&start_money,&end_money);
    	}
    	
    	
	     if(choice1&&choice2){
		for(i=0;i<len;i++)
		{
			if(_ms(history[i].stuID,stunum)&&strcmp(history[i].time,start_time)>0&&strcmp(history[i].time,end_time)<0&&history[i].pay>=start_money&&history[i].pay<=end_money) 
			printf("ʱ�䣺%s,������%s,���ţ�%s,ѧ�ţ�%s,���׽�%.2f\n",history[i].time,history[i].stuID,history[i].cardID,history[i].stuID,history[i].pay); 
		}
	    } 
	    else if(choice1){
	    	for(i=0;i<len;i++)
		{
			if(_ms(history[i].stuID,stunum)&&strcmp(history[i].time,start_time)>0&&strcmp(history[i].time,end_time)<0) 
			printf("ʱ�䣺%s,������%s,���ţ�%s,ѧ�ţ�%s,���׽�%.2f\n",history[i].time,history[i].name,history[i].cardID,history[i].stuID,history[i].pay); 
		
		}
		} 
	    else if(choice2){
			
			for(i=0;i<len;i++)
		{
			if(_ms(history[i].stuID,stunum)&&history[i].pay>=start_money&&history[i].pay<=end_money) 
			printf("ʱ�䣺%s,������%s,���ţ�%s,ѧ�ţ�%s,���׽�%.2f\n",history[i].time,history[i].name,history[i].cardID,history[i].stuID,history[i].pay); 
		
		}
		}
		else{
			for(i=0;i<len;i++)
		{
			if(_ms(history[i].stuID,stunum)) 
			printf("ʱ�䣺%s,������%s,���ţ�%s,ѧ�ţ�%s,���׽�%.2f\n",history[i].time,history[i].name,history[i].cardID,history[i].stuID,history[i].pay); 
		}
      }
      
      
	}
}
int cmp(const void *a, const void *b){
	char mark1[17];
	char mark2[17];
	strcpy(mark1,((Record *)a)->time);
	strcpy(mark2,((Record *)b)->time);
    return strcmp(mark1,mark2)>0 ? 1:-1;
}
//ͳ��ָ��ʱ����ۼ����ѽ��� 
void statistics(){
	int i;
	char start_time[17],end_time[17];
	printf("�������ѯ��ѧ�ţ�\n");
	scanf("%s",stunum);
	printf("������ʱ��Σ�\n");
	scanf("%s%s",start_time,end_time);
	float counter=0;
	for(i=0;i<len;i++){
		if(strcmp(history[i].stuID,stunum)==0&&strcmp(history[i].time,start_time)>0&&strcmp(history[i].time,end_time)<0){
			counter=counter+history[i].pay;
		}
	}
	printf("�ۼ����ѽ���ǣ�%.2f\n",counter);
}
//��ӡ��������֮��Ľ���ļ�sort.txt 
void print_sort(){
	int i;
	
	FILE *fp;
    fp=fopen("sort.txt","rw+");
	printf("%d\n",len);
	
	for(i=0;i<len;i++){
		
		fprintf(fp,"������ţ�%s,���ڣ�%s,������%s,ѧ�ţ�%s,���ѿ��ţ�%s ֧����%.2f;\n",history[i].w,history[i].time,history[i].name,history[i].stuID,history[i].cardID,history[i].pay);
	}
	fclose(fp);
	
}




