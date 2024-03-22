#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"myfile.h"
#define MAX 10000
char nam[9];
char stunum[11];
char cardnum[8]; 
char time[17];
char act[15];
char m[5];
char date[9];
char hour[9];
float money;
float money_left;
int window;
int wz[100];
int amount1[100][1232];
float amount2[100][1232];
Record record[6*MAX];
Record Win[100][6*MAX];
Record history[99*6*MAX];
int pointer;
int start[100];
int len;


 
void menu(){
	 printf("\t\t\t  ******************************************************\n\n");
	 printf("\t\t\t  *                校园卡管理系统                  * \n\n");
	 printf("\t\t\t  ******************************************************\n\n"); 
	 printf("\t\t\t*********************系统功能菜单*************************\n");
	 printf("\t\t\t     ----------------------   ----------------------  \n");
	 printf("\t\t\t     *********************************************  \n");
	 printf("\t\t\t     * 0.开户    * *  1.销户     *   \n");
	 printf("\t\t\t     *********************************************  \n"); 
	 printf("\t\t\t     * 2.发卡    * *  3.挂失     *   \n");
	 printf("\t\t\t     *********************************************  \n");
	 printf("\t\t\t     * 4.查询    * *  5.补卡     *   \n");
	 printf("\t\t\t     *********************************************  \n");
	 printf("\t\t\t     * 6.充值    * *  7.消费     *   \n");
	 printf("\t\t\t     ********************** **********************  \n");
	 printf("\t\t\t     * 8.显示    * *  9.退出系统 *   \n");
	 printf("\t\t\t     **********************          \n");
	 printf("\t\t\t     ----------------------   ----------------------  \n");
}



void display(LinkList*L) 
{   FILE *fp;
	LinkList*p=L->next;
	printf("请输入操作时间：\n");
	scanf("%s",time);
	 if((fp=fopen("output.txt","w"))==NULL)// 以可写的方式打开当前目录下的.txt  
    {  
        printf("不能打开此文件，请按任意键退出\n");  
        exit(1);  //异常退出
    }  
	if(p==NULL)
	{
		printf("还没有学生信息\n");
	}
	
	while(p!=NULL)
	{  
	    printf("%s\t",p->data.number);
	    printf("%s\t",p->data.num);
		printf("%s\t",p->data.name);
		printf("%d\n",p->data.state);
		
		strcpy(act,"开户成功！");
		fprintf(fp,"操作时间：%s,姓名：%s,学号：%s,操作结果：%s\n",time,p->data.name,p->data.number,act); 
//		fprintf(fp,"%s,%s;\n",p->data.number,p->data.name); 
		p=p->next; 
	}
	 fclose(fp); 
 } 
 
void readStuDentput (LinkList *L) //运行前把文件内容读取到电脑内存  
{  
    FILE *fp;  
    fp=fopen("kh001.txt","r"); //以只读方式打开当前目录下的.txt  
    if(fp==NULL)  
    {  
        printf("文件不存在\n");  
        exit(0);                   //终止程序  
    }  
    
    fscanf(fp, "%*[A-Z]");
    fscanf(fp, "%*[\n]");
    while(!feof(fp))  
    {  
        LinkList *n=(LinkList *)malloc(sizeof(LinkList));
        fscanf(fp,"%[^,]",stunum);
		fscanf(fp, "%*[,]");
		fscanf(fp, "%[^;]", nam);
		fscanf(fp, "%*[;]");
		fscanf(fp, "%*[\n]");
	    strcpy(n->data.number,stunum);
	    strcpy(n->data.name,nam);
	    n->data.state=0;
		n->data.balance=0; 
        ListInsert(L,n);
        n=n->next;
    }  
    fclose(fp);  
 
}  

//单人发卡函数 
void give(LinkList *L)
{  
    int k=312346;
    int key,j;
    
    printf("请输入操作时间：\n");
	scanf("%s",time);
	 printf("发卡成功！\n");
    strcpy(act,"发卡成功！");
    
	LinkList*p=L->next;
	while(p!=NULL){
		key=9-getSum(k)%10;
		j=k*10+key;
		itoa(j,cardnum,10);
		strcpy(p->data.num,cardnum);
		strcpy(nam,p->data.name);
		strcpy(stunum,p->data.number);
		p->data.balance=0;
		
		write_diary(time,nam,stunum,act,cardnum);
		p=p->next;
		k++;
	} 
	
 } 
// 单人开户函数 
void create(LinkList *L)
{
	 LinkList *p;
	 InitList(&p);
	 FILE *fp;
     fp=fopen("logbook.txt","a+");
     
	 printf("请输入学号和性名：\n");
	 scanf("%s%s;",stunum,nam);
	 printf("请输入操作时间：\n");
      scanf("%s",time);
      printf("开户成功！\n");
	 strcpy(p->data.name,nam);
	 strcpy(act,"开户成功！");
	 strcpy(p->data.number,stunum);
	 p->data.state=0;
     fprintf(fp,"操作时间：%s,姓名：%s,学号：%s,操作结果：%s\n",time,nam,stunum,act);
        	
    
	ListInsert(L,p);
	 fclose(fp); 

} 
//单人销户操作 
void deletecard(LinkList*L)
{
	printf("请输入您要删除的学生的学号:\n");  
    scanf("%s",stunum);  
    printf("请输入操作时间：\n");
    scanf("%s",time);
    //判断  
    LinkList *p,*pre;  
    if(L->next==NULL)  
    {  
        printf("还没有学生信息,请增加学生信息\n");  
        return;  
    }  
    pre=L;  
    p=pre->next;  
    int judge=0;  
    while(p)  
    {  
         if(0==strcmp(p->data.number,stunum))  
         {  
                 judge=1;  
                 pre->next =p->next;  
                
                 strcpy(act,"销户成功!");
                 write_diary(time,p->data.name,p->data.number,act,p->data.num); 
                 
				 free(p);  
                 printf("销户成功\n"); 
				
                 break;  
         }  
         pre=p;  
         p=p->next;  
    }  
    if(judge==0)  {
    	printf("这个学生不存在\n");
    	strcpy(act,"学号不存在！");
       FILE *fp;
       fp=fopen("logbook.txt","a+");
       fprintf(fp,"%s,%s,%s\n",time,stunum,act);
       fclose(fp);
	}
         

}
//单人挂失解挂操作 
void lose(LinkList*L)
{
	int b;
    LinkList*q=L->next;
	fflush(stdin);
	int flag=0;
	printf("请输入学号:\n");
	gets(stunum);
	printf("请输入此操作的时间：\n");
	scanf("%s",time);
	while(q)
 		{
		  if(0==strcmp(q->data.number,stunum))
		  {
		  	flag=1;
			break;
		  }
		  q=q->next; 
	    }
	    if(flag==1)
	    {
	    	
	    	fflush(stdin);
	        printf("\n请选择功能：1.挂失 2.解除挂失 (1 or 2)?\n");
	        scanf("%d",&b);

        	if(b==1)
	      {
		    q->data.state=1;
		    printf("挂失已成功！\n");
		    
		    strcpy(act,"挂失成功！");
		    strcpy(nam,q->data.name);
		    strcpy(cardnum,q->data.num);
		    
		    write_diary(time,nam,stunum,act,cardnum);
	      }
	       if(b==2)
          {
	    	q->data.state=0;
		    printf("解除挂失已成功！\n");
		    
		    
		    strcpy(act,"解挂成功！");
		    strcpy(nam,q->data.name);
		    strcpy(cardnum,q->data.num);
	    	write_diary(time,nam,stunum,act,cardnum);
	      }
		}
 	   else{
 	   	printf("没有找到信息\n");
 	   	strcpy(act,"学号不存在！");
        FILE *fp;
        fp=fopen("logbook.txt","a+");
        fprintf(fp,"%s,%s,%s\n",time,stunum,act);
        fclose(fp);
		}
 	   
   
	
}
//单人补卡操作 
void renew(LinkList*L)
{
//	新建一个节点，但是学号相同
  LinkList*q=L->next; 
  printf("请输入挂失的学号：\n");
  scanf("%s",stunum);
  printf("请输入操作时间：\n");
  scanf("%s",time);
  int flag=0; 
  while(q)
 		{
		  if(0==strcmp(q->data.number,stunum))
		  {
		  	if(q->data.state==0)
		  	{
		  		flag=1;
			  }
			  strcpy(nam,q->data.name);
		  }
		  q=q->next; 
	    }
 	if(flag==1)
 	{
 		printf("存在没有挂失的卡\n"); 
 		
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
	    printf("补卡成功！\n");
	    
	     
	    strcpy(act,"补卡成功！");
		strcpy(nam,p->data.name);
		strcpy(cardnum,p->data.num);
	    write_diary(time,nam,stunum,act,cardnum);
   }
	
	
	 
}
//单人充值操作 
void recharge(LinkList*L)
{
	printf("请输入充值的时间：\n");
	scanf("%s",time);
	printf("请输入充值的卡号：\n");
	scanf("%s",cardnum);
	printf("请输入充值的金额: \n");
	scanf("%f",&money);
	
	LinkList*q=L->next;
	int flag=0;
	FILE*FP;
	FP=fopen("logbook2.txt","a+"); 
	while(q)
 		{
		  if(0==strcmp(q->data.num,cardnum))
		  {
		  	if(q->data.state==1)
		  	{
		  		printf("挂失不能充值！\n");
		  		
		  		strcpy(nam,q->data.name) ;
		  		strcpy(cardnum,q->data.num) ;
		  		strcpy(stunum,q->data.number); 
		  		strcpy(act,"挂失不能充值！");
		  		money_left=q->data.balance;
		  		write_diary2(FP,time,nam,stunum,act,cardnum,money,money_left,0);
		  		//		  		写操作日志函数
			}
			else
			{   if(q->data.balance>1000) 
				  {
				  	printf("充值失败余额超值\n");
					fprintf(FP,"充值失败余额超值\n");
				 }
				else{
				q->data.balance=q->data.balance+money;
				strcpy(nam,q->data.name); 
				strcpy(stunum,q->data.number); 
				strcpy(act,"充值成功！");
				money_left=q->data.balance;
//				写操作日志函数 
               printf("充值成功！余额为%.2f\n",money_left);
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
	    	printf("没有找到该卡号；\n");
	    	fprintf(FP,"没有找到该卡号；\n");
	    	//		  		写操作日志函数
		}
	    fclose(FP);
}
//单人消费操作 
void  consume(LinkList*L,float counter[4][1232])
{
	printf("请输入消费的日期：\n");
	scanf("%s",date);
	printf("请输入消费的时间：\n");
	scanf("%s",hour);
	printf("请输入消费的卡号：\n");
	scanf("%s",cardnum);
	printf("请输入消费的金额: \n");
	scanf("%f",&money);
	printf("请输入消费的窗口号: \n");
	scanf("%d",&window);
	
	LinkList*q=L->next;
	int flag=0,day,password=0,j;
	char str[17]="2021";
	FILE*FP;
	FP=fopen("logbook2.txt","a+"); 
	
	while(q)
 		{
		  if(0==strcmp(q->data.num,cardnum))
		  {
		  	if(q->data.state==1)
		  	{
		  		printf("挂失不能消费！\n");
		  		fprintf(FP,"挂失不能消费；\n");
//		  		写操作日志函数 
			}
			  else if(q->data.balance-money<0)
			  
			  {  strcat(str,date);
			     strcat(str,hour);
			     
			  	printf("余额不足！\n");
			  	strcpy(nam,q->data.name); 
				strcpy(stunum,q->data.number); 
				strcpy(act,"余额不足！");
				money=0; 
				money_left=q->data.balance;
			  	
			  	write_diary2(FP,str,nam,stunum,act,cardnum,money,money_left,window);
//		  		写操作日志函数
			   } 
			else
			{
				
				day=atoi(date);
				if(strcmp(hour,"07000000")>=0&&strcmp(hour,"09000000")<=0)
				{
					counter[1][day]=counter[1][day]+money;
					j=1;
				}
				else if(strcmp(hour,"11000000")>=0&&strcmp(hour,"13000000")<=0)
				{
						counter[2][day]=counter[2][day]+money;
					    j=2;
				}
			
				else {
					counter[3][day]=counter[3][day]+money;
					j=3;
				}
				
				
					if(counter[j][day]>20)
					{
						while(password!=8888){
							printf("请输入消费密码：\n");
						    scanf("%d",&password);
						}
						counter[j][day]=0;
					}
					 
						q->data.balance=q->data.balance-money;
						strcat(str,date);
						strcat(str,hour);
				        strcpy(nam,q->data.name); 
				        strcpy(stunum,q->data.number); 
				        strcpy(act,"消费成功！");
				        money_left=q->data.balance;
				        
				        write_diary2(FP,str,nam,stunum,act,cardnum,money,money_left,window);
//				        write_history(fp_h,window,date,hour,cardnum,money);
				        
				        amount1[window][day]++;
				        amount2[window][day]+=money;
//				    写操作日志函数 
				        printf("消费成功！余额为%.2f\n",money_left);
				        printf("时间为%d,%d号窗口累计消费次数为：%d,累计消费金额为：%.2f\n",day,window,amount1[window][day],amount2[window][day]);
			}
		  	flag=1;
			break;
		  }
		  q=q->next; 
	    }
	    if(flag==0)
	    {
	    	printf("没有找到该卡号；\n");
	    	fprintf(FP,"没有找到该卡号；\n");
//	    	写操作日志函数 
		}
		fclose(FP);
//		fclose(fp_h);
}
//单人学号姓名模糊查询 
void find(LinkList*L){
	LinkList*p=L->next;
	int choice;
	printf("通过学号或者姓名查询：1/2 \n");
	scanf("%d",&choice);
		if(choice==2){
		 printf("请输入模糊查询的姓名:\n");
	     scanf("%s",nam);
	     while(p){
	     	if(_m(p->data.name,nam))
	     	printf("%s,%s,%s,%d,%.2f\n",p->data.number,p->data.name,p->data.num,p->data.state,p->data.balance);
	     	p=p->next;
		 }
	 }
	 else{
	 	printf("请输入模糊查询的学号:\n");
	     scanf("%s",stunum);
	     while(p){
	     	if(_ms(p->data.number,stunum))
	     	printf("%s,%s,%s,%d,%.2f\n",p->data.number,p->data.name,p->data.num,p->data.state,p->data.balance);
	     	p=p->next;
		 }
  }
	 
}
int main()
{
	LinkList*L=NULL;
	InitList(&L);  
	int choose,caozuo,i=0,j=0,day;
//	记录累计消费金额 
	float counter[4][1232];
	for(i=0;i<=3;i++){
		for(j=0;j<=1231;j++){
			counter[i][j]=0;
		}
	}
	for(i=1;i<=99;i++){
		for(day=901;day<=1231;day++){
			amount1[i][day]=0;
		    amount2[i][day]=0;
		}
		
	}
	
	
	
     printf("选择单人或者批量操作：1/2 \n");
     scanf("%d",&caozuo);
     if(caozuo==1)
     {
     	printf("\n");
      
	 
	 while(1)
    {
	 menu(); 
	 printf("请输入您选择的服务：\n");
	 scanf("%d",&choose) ;
//	 单人操作 
	 switch(choose)
	 { 
	    case 0:
	    	create(L);
	    	break;
	    case 1:
	    	deletecard(L);
	    	break;
	    case 2:
	    	give(L);
			break;
		case 3:
		    lose(L);
			break;
		case 4:
		    find(L);
	    	break;
	    case 5:
	    	renew(L);
	    	break;
	    case 6:
	    	recharge(L);
			break; 
	    case 7:
	    	consume(L,counter);
	    	
	    	break;
	    case 8:
	    	display(L);
	    	break;
	    case 9:
	        printf("谢谢使用!");
	    	exit(0);
	    default:
	    	printf("请输入正确的选择\n");
	    	break;
	 }
    
	}
	    	
	 } 
	 
	 else{
	 	int choice;
	 	while(1)
	 	{
		printf("请输入选项：1.批量开户 2.批量操作 3.归并排序4.快速排序5.模糊查询6.累计金额7.退出8.打印排序结果文件\n") ;
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			    readStuDentput (L);   //开户 
			    displays(L);//	写入操作文件 
			    gives(L);//发卡 
			    break;
			case 2:
				ReadwzFile();     //	读取初始位置文件wz003.txt 
				ReadConsumptionFile();   // 读取消费文件xf014.txt 
				readStuAct(L);   // 读取消费文件cz002.txt 
				
				break;
			case 3:
//	    		归并排序 
				merge_sort();
				break;
	    	case 4:
	    		quick_sort();
//	    	快速排序 
				break;
	    	case 5:
//	    		模糊查询 
	    		search_mohu();
	    		break;
	    	case 6:
//	    	对指定的学号统计给定起止日期内的累计消费金额。
	    		statistics();	
	    		break;
	    	case 7:
                printf("谢谢使用!");
	    	    exit(0);
	    		break;
	    	case 8:
//	    		打印排序结果文件 
			    print_sort();
			    break;
	    	default:
	    	    printf("请输入正确的选择\n");
	    	    break;    
				
		}
		     
     }
		
 } 
 return 0;
}






