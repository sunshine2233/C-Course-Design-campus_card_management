#include "myfile.h"
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
//初始化链表结点函数 
void InitList(LinkList**L)
{
	*L=(LinkList*)malloc(sizeof(LinkList));
	(*L)->next=NULL; 
}
//插入链表节点函数 
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
//写入操作日志函数 
void write_diary(char*time,char*nam,char*stunum,char*act,char*cardnum)
{
	    FILE *fp;
        fp=fopen("logbook.txt","a+");
        
        
        	fprintf(fp,"操作时间：%s,姓名：%s,学号：%s,操作结果：%s 卡号：%s;\n",time,nam,stunum,act,cardnum);
        	
        fclose(fp); 
}
void write_diary2(FILE*fp,char*time,char*nam,char*stunum,char*act,char*cardnum,float money,float money_left,int window)
{
        	fprintf(fp,"操作时间：%s,姓名：%s,学号：%s,操作结果：%s 卡号：%s,交易额: %.2f,余额:%.2f,窗口号:%d;\n",time,nam,stunum,act,cardnum,money,money_left,window);
}
//开户操作信息写入logbook.txt操作日志 
void displays(LinkList*L)
{
	FILE *fp;
	LinkList*p=L->next;
	strcpy(act,"开户成功！");
	strcpy(time,"20210901");
	
	 if((fp=fopen("logbook.txt","w"))==NULL)// 以可写的方式打开当前目录下的.txt  
    {  
//        printf("不能打开此文件，请按任意键退出\n");  
        exit(1);  //异常退出
    }  
	
	
	while(p!=NULL)
	{  
		fprintf(fp,"操作时间：%s,姓名：%s,学号：%s,操作结果：%s\n",time,p->data.name,p->data.number,act); 
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
//给L链表上所有结点发卡 
void gives(LinkList *L)
{  
    int k=312346;
    int key,j;
    
    strcpy(act,"发卡成功！");
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
// 批量销户函数，并且写入到操作日志 
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
                 strcpy(act,"销户成功！");
                 strcpy(nam,p->data.name);
                 strcpy(cardnum,p->data.num);
                
                 pre->next =p->next;  
                 free(p);
                 
                 write_diary(time,nam,stunum,act,cardnum);
//                 操作日志 
				   
                 break;  
         }  
         pre=p;  
         p=p->next;  
    }  
    if(judge==0)  
    {
	 
       strcpy(act,"学号不存在！");
       FILE *fp;
       fp=fopen("logbook.txt","a+");
       fprintf(fp,"%s,%s,%s\n",time,stunum,act);
       fclose(fp); 
    } 
       
}
//批量挂失和解挂操作，并且写入到操作日志 
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
		    strcpy(act,"挂失成功！");
		    strcpy(nam,q->data.name);
		    strcpy(cardnum,q->data.num);
		    
		    write_diary(time,nam,stunum,act,cardnum);
//		    操作日志 
	      }
	       if(b==2)
          {
	    	q->data.state=0;
	    	strcpy(act,"解挂成功！");
		    strcpy(nam,q->data.name);
		    strcpy(cardnum,q->data.num);
	    	write_diary(time,nam,stunum,act,cardnum);
//		    操作日志   
	      }
		}
 	   else{
 	   	strcpy(act,"学号不存在！");
        FILE *fp;
        fp=fopen("logbook.txt","a+");
        fprintf(fp,"%s,%s,%s\n",time,stunum,act);
        fclose(fp);
// 	   	操作日志 
		}
   
	
}
//批量补卡操作函数 
void renews(LinkList*L,char*time,char*stunum)
{
//	新建一个节点，但是学号相同
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
 		strcpy(act,"该学号存在未挂失的卡！");
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
	     
	    strcpy(act,"补卡成功！");
		strcpy(nam,p->data.name);
		strcpy(cardnum,p->data.num);
	    write_diary(time,nam,stunum,act,cardnum);
	    
   }
	 
}
//批量读取分时间段的5个充值和消费文件并且执行操作 
void readStuAct(LinkList*L)
{
	int i;
	FILE *fp,*FP,*fp_h;  
    fp=fopen("cz002.txt","r"); //以只读方式打开当前目录下的.txt  
    FP=fopen("logbook2.txt","a+");
    fp_h=fopen("history.txt","a+");
    if(fp==NULL)  
    {   
        exit(0);                   //终止程序  
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
		
	    
	if(strcmp(act,"销户")==0) 
	{
		deletecards(L,time,stunum);
	}
	else if(strcmp(act,"挂失")==0)
	{
		loses(L,time,stunum,1);
	}
	else if(strcmp(act,"解挂")==0)
	{
		loses(L,time,stunum,2);
	}
	else if(strcmp(act,"补卡")==0)
	{
		renews(L,time,stunum);
		
	}
	else if(strcmp(act,"充值")==0) 
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
//读取xf004.txt文件并且分成5个时间段的txt文件 
void ReadConsumptionFile()
{
	FILE*fp3,*fp01,*fp02,*fp03,*fp04,*fp05;
	char date[18],hour[9],m[8];
	if((fp3=fopen("xf014.txt","r"))==NULL)
	{
		printf("不能打开文件xf014！\n");
		return;
	}
	if((fp01=fopen("xf1.txt","rw+"))==NULL)
	{
		printf("不能打开文件xf1！\n");
		return;
	}
	if((fp02=fopen("xf2.txt","rw+"))==NULL)
	{
		printf("不能打开文件xf2！\n");
		return;
	}
	if((fp03=fopen("xf3.txt","rw+"))==NULL)
	{
		printf("不能打开文件！\n");
		return;
	}
	if((fp04=fopen("xf4.txt","rw+"))==NULL)
	{
		printf("不能打开文件！\n");
		return;
	}
	if((fp05=fopen("xf5.txt","rw+"))==NULL)
	{
		printf("不能打开文件！\n");
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
//读取充值文件并且分成五个时间段的文件 
void ReadRechargeFile(char*time,char*act,char*stunum,char*m)
{
	FILE*fp01,*fp02,*fp03,*fp04,*fp05;
	
	if((fp01=fopen("cz1.txt","a+"))==NULL)
	{
		printf("不能打开文件！\n");
		return;
	}
	if((fp02=fopen("cz2.txt","a+"))==NULL)
	{
		printf("不能打开文件！\n");
		return;
	}
	if((fp03=fopen("cz3.txt","a+"))==NULL)
	{
		printf("不能打开文件！\n");
		return;
	}
	if((fp04=fopen("cz4.txt","a+"))==NULL)
	{
		printf("不能打开文件！\n");
		return;
	}
	if((fp05=fopen("cz5.txt","a+"))==NULL)
	{
		printf("不能打开文件！\n");
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
    fp=fopen(file,"r"); //以只读方式打开当前目录下的.txt  
    
    if(fp==NULL)  
    {   
        exit(0);                   //终止程序  
    }  
 
    while(!feof(fp))  
    {  
//    扫描一行执行一次 
        fscanf(fp, "%[^,]",time);
		fscanf(fp, "%*[,]");
		fscanf(fp, "%[^,]", act);
		fscanf(fp, "%*[,]");
		fscanf(fp, "%10s", stunum);
		fscanf(fp, "%*[,]");
		fscanf(fp,"%f",&money);
		fscanf(fp, "%*[;]");
		fscanf(fp, "%*[\n]");
		
//		执行
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
		  		strcpy(act,"挂失不能充值！");
		  		money_left=q->data.balance;
		  		write_diary2(FP,time,nam,stunum,act,cardnum,money,money_left,0);
		  		//		  		写操作日志函数
			}
			else
			{
				if(q->data.balance>1000) 
				{
					fprintf(FP,"充值失败余额超值\n");
				}
				else {
					q->data.balance=q->data.balance+money;
				    strcpy(nam,q->data.name); 
				    strcpy(stunum,q->data.number); 
				    strcpy(cardnum,q->data.num) ;
				    strcpy(act,"充值成功！");
				    money_left=q->data.balance;
//				写操作日志函数 
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
	    	fprintf(FP,"没有找到该卡号；\n");
	    	//		  		写操作日志函数
		}	
		
		
    }
    
    fclose(fp);
	
}
void OperateXf(char*file,LinkList*L,FILE*FP,FILE*fp_h)
{
	FILE *fp;  
    fp=fopen(file,"r"); //以只读方式打开当前目录下的.txt  
    if(fp==NULL)  
    {   
        exit(0);                   //终止程序  
    }  
 
    while(fgets(cardnum,8,fp)!=NULL)
	{
		
//		扫描一行执行一次 
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
//            执行
   	    LinkList*q=L->next;
	    int flag=0;
	    while(q)
 		{
		  if(0==strcmp(q->data.num,cardnum))
		  {
		  	if(q->data.state==1)
		  	{
			     
		  		fprintf(FP,"没有找到该卡号；\n");
//		  		写操作日志函数 
			  }
			  else if(q->data.balance<0)
			  {
			  	strcpy(nam,q->data.name); 
				strcpy(stunum,q->data.number); 
				strcpy(act,"余额不足！");
				money=0; 
				money_left=q->data.balance;
			  	
			  	write_diary2(FP,time,nam,stunum,act,cardnum,money,money_left,window);
//		  		写操作日志函数
			   } 
			else
			{
				q->data.balance=q->data.balance-money;
				strcpy(nam,q->data.name); 
				strcpy(stunum,q->data.number); 
				strcpy(act,"消费成功！");
				money_left=q->data.balance;
//				写操作日志函数 
				write_diary2(FP,time,nam,stunum,act,cardnum,money,money_left,window);

//              写消费记录数组
                if(wz[window]>=6*MAX)
                {
                	wz[window]=0;
                }
					pointer=wz[window];
                Record_consumption(window,time,cardnum,money,pointer,nam,stunum);
                wz[window]+=1;

//				写消费记录txt
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
	            fprintf(FP,"没有找到该卡号；\n");
//	    	写操作日志函数 
		} 
		
    
    }
    
    fclose(fp);
	    
}
//读取位置文件 
void ReadwzFile()
{
	FILE *fp;  
	int i;
	char str[4];
    fp=fopen("wz003.txt","r"); //以只读方式打开当前目录下的.txt  
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
//写消费数组 
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
//写消费记录文件 
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
    fprintf(fp_h,"窗口序号：%s,日期：%s,时间：%s,消费卡号：%s 支付金额：%.2f;\n",w,date,hour,cardnum,money);
}
//归并排序 
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
//		flag数组用于记录该窗口是否全部读完 
	}

//    int length[100];
    start[24]=wz[24]+1;
	for(i=1;i<=57;i++)
	{

//	求出来每一行的长度，即每一个窗口的消费记录数量 
//		length[i]=sizeof(Win[i])/sizeof(Record);
//    	if(length[i]==6*MAX+1)
//    	start[i]=wz[i]+1;
//	初始化first_data数组
		current[i]=start[i];
		strcpy(first_data[i],Win[i][current[i]].time);
	}

//循环
 //初始化min_data；
		strcpy(min_data,"9999999999999990");
		
	while(strcmp(min_data,"9999999999999999")<0)
	{	   
	//选出最小的 
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
        //记录数据 最小的存入history数组 
        strcpy(history[m].time,min_data);
        strcpy(history[m].name,Win[j][current[j]].name);
        strcpy(history[m].w,Win[j][current[j]].w);
        strcpy(history[m].stuID,Win[j][current[j]].stuID);
        strcpy(history[m].cardID,Win[j][current[j]].cardID);
        history[m].pay=Win[j][current[j]].pay;
		//输入新的数据，叶子结点 
        current[j]++;m++;
		if(current[j]>=6*MAX)     
			current[j]=0;
//			如果到了回绕的地方则重新扫描位置为0的数据 
        if(current[j]==wz[j]+1) 
		{
			flag[j]=1;
			strcpy(first_data[j],"9999999999999999");
//			将该窗口比较的数据作为最大则该窗口不会再进行比较 
			strcpy(min_data,"9999999999999999");
		}  
		else
		{
			strcpy(first_data[j],Win[j][current[j]].time);
//			选出最小值的窗口后一个数据存入比较数组first_data 
			strcpy(min_data,Win[j][current[j]].time);
		}
	} 
    len=m;
}
//快速排序 
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
	
//	建立history数组

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
//对中文模糊查询的函数 
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
//模糊查询函数 
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
//模糊查询 
void search_mohu() 
{
	char start_time[17],end_time[17];
	float start_money,end_money;
	int choice,choice1,choice2,i;
	printf("通过学号或者姓名查询：1/2 \n");
	scanf("%d",&choice);
	if(choice==2){
		 printf("请输入模糊查询的姓名:\n");
	     scanf("%s",nam);
		 
	     printf("是否通过时间段查询：1/0\n");
	     scanf("%d",&choice1);
	     if(choice1) {
	     	printf("请输入起止时间：\n");
		 scanf("%s%s",start_time,end_time);
	    }
	     printf("是否通过金额范围查询：1/0 \n");
	    
	     scanf("%d",&choice2);
	     if(choice2) {
	     printf("请输入金额范围：\n");
		 scanf("%f,%f",&start_money,&end_money);
    	}
	     if(choice1&&choice2){
//	     	有问题 
		for(i=0;i<len;i++)
		{
			if(_m(history[i].name,nam)&&strcmp(history[i].time,start_time)>0&&strcmp(history[i].time,end_time)<0&&history[i].pay>=start_money&&history[i].pay<=end_money) 
			printf("时间：%s,姓名：%s,卡号：%s,学号：%s,交易金额：%.2f\n",history[i].time,history[i].name,history[i].cardID,history[i].stuID,history[i].pay); 
		
		}
	    } 
	    else if(choice1){
	    	for(i=0;i<len;i++)
		{
			if(_m(history[i].name,nam)&&strcmp(history[i].time,start_time)>0&&strcmp(history[i].time,end_time)<0) 
			printf("时间：%s,姓名：%s,卡号：%s,学号：%s,交易金额：%.2f\n",history[i].time,history[i].name,history[i].cardID,history[i].stuID,history[i].pay); 
		
		}
		} 
		else if(choice2){
			
			for(i=0;i<len;i++)
		{
			if(_m(history[i].name,nam)&&history[i].pay>=start_money&&history[i].pay<=end_money) 
			printf("时间：%s,姓名：%s,卡号：%s,学号：%s,交易金额：%.2f\n",history[i].time,history[i].name,history[i].cardID,history[i].stuID,history[i].pay); 
		
		}
		}
		else{
			for(i=0;i<len;i++)
		{
			if(_m(history[i].name,nam)) 
			printf("时间：%s,姓名：%s,卡号：%s,学号：%s,交易金额：%.2f\n",history[i].time,history[i].name,history[i].cardID,history[i].stuID,history[i].pay); 
		}
      }
	} 
	else{
		printf("请输入模糊查询的学号:\n");
	    scanf("%s",stunum);
	    
	    printf("是否通过时间段查询：1/0\n");
	     scanf("%d",&choice1);
	     if(choice1) {
	     printf("请输入起止时间：\n");
		 scanf("%s%s",start_time,end_time);
	    }
	     printf("是否通过金额范围查询：1/0 \n");
	     scanf("%d",&choice2);
	     if(choice2) {
	     printf("请输入金额范围：\n");
		 scanf("%f,%f",&start_money,&end_money);
    	}
    	
    	
	     if(choice1&&choice2){
		for(i=0;i<len;i++)
		{
			if(_ms(history[i].stuID,stunum)&&strcmp(history[i].time,start_time)>0&&strcmp(history[i].time,end_time)<0&&history[i].pay>=start_money&&history[i].pay<=end_money) 
			printf("时间：%s,姓名：%s,卡号：%s,学号：%s,交易金额：%.2f\n",history[i].time,history[i].stuID,history[i].cardID,history[i].stuID,history[i].pay); 
		}
	    } 
	    else if(choice1){
	    	for(i=0;i<len;i++)
		{
			if(_ms(history[i].stuID,stunum)&&strcmp(history[i].time,start_time)>0&&strcmp(history[i].time,end_time)<0) 
			printf("时间：%s,姓名：%s,卡号：%s,学号：%s,交易金额：%.2f\n",history[i].time,history[i].name,history[i].cardID,history[i].stuID,history[i].pay); 
		
		}
		} 
	    else if(choice2){
			
			for(i=0;i<len;i++)
		{
			if(_ms(history[i].stuID,stunum)&&history[i].pay>=start_money&&history[i].pay<=end_money) 
			printf("时间：%s,姓名：%s,卡号：%s,学号：%s,交易金额：%.2f\n",history[i].time,history[i].name,history[i].cardID,history[i].stuID,history[i].pay); 
		
		}
		}
		else{
			for(i=0;i<len;i++)
		{
			if(_ms(history[i].stuID,stunum)) 
			printf("时间：%s,姓名：%s,卡号：%s,学号：%s,交易金额：%.2f\n",history[i].time,history[i].name,history[i].cardID,history[i].stuID,history[i].pay); 
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
//统计指定时间的累计消费金额函数 
void statistics(){
	int i;
	char start_time[17],end_time[17];
	printf("请输入查询的学号：\n");
	scanf("%s",stunum);
	printf("请输入时间段：\n");
	scanf("%s%s",start_time,end_time);
	float counter=0;
	for(i=0;i<len;i++){
		if(strcmp(history[i].stuID,stunum)==0&&strcmp(history[i].time,start_time)>0&&strcmp(history[i].time,end_time)<0){
			counter=counter+history[i].pay;
		}
	}
	printf("累计消费金额是：%.2f\n",counter);
}
//打印两种排序之后的结果文件sort.txt 
void print_sort(){
	int i;
	
	FILE *fp;
    fp=fopen("sort.txt","rw+");
	printf("%d\n",len);
	
	for(i=0;i<len;i++){
		
		fprintf(fp,"窗口序号：%s,日期：%s,姓名：%s,学号：%s,消费卡号：%s 支付金额：%.2f;\n",history[i].w,history[i].time,history[i].name,history[i].stuID,history[i].cardID,history[i].pay);
	}
	fclose(fp);
	
}




