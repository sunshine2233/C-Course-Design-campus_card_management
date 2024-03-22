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
	 printf("\t\t\t  *                У԰������ϵͳ                  * \n\n");
	 printf("\t\t\t  ******************************************************\n\n"); 
	 printf("\t\t\t*********************ϵͳ���ܲ˵�*************************\n");
	 printf("\t\t\t     ----------------------   ----------------------  \n");
	 printf("\t\t\t     *********************************************  \n");
	 printf("\t\t\t     * 0.����    * *  1.����     *   \n");
	 printf("\t\t\t     *********************************************  \n"); 
	 printf("\t\t\t     * 2.����    * *  3.��ʧ     *   \n");
	 printf("\t\t\t     *********************************************  \n");
	 printf("\t\t\t     * 4.��ѯ    * *  5.����     *   \n");
	 printf("\t\t\t     *********************************************  \n");
	 printf("\t\t\t     * 6.��ֵ    * *  7.����     *   \n");
	 printf("\t\t\t     ********************** **********************  \n");
	 printf("\t\t\t     * 8.��ʾ    * *  9.�˳�ϵͳ *   \n");
	 printf("\t\t\t     **********************          \n");
	 printf("\t\t\t     ----------------------   ----------------------  \n");
}



void display(LinkList*L) 
{   FILE *fp;
	LinkList*p=L->next;
	printf("���������ʱ�䣺\n");
	scanf("%s",time);
	 if((fp=fopen("output.txt","w"))==NULL)// �Կ�д�ķ�ʽ�򿪵�ǰĿ¼�µ�.txt  
    {  
        printf("���ܴ򿪴��ļ����밴������˳�\n");  
        exit(1);  //�쳣�˳�
    }  
	if(p==NULL)
	{
		printf("��û��ѧ����Ϣ\n");
	}
	
	while(p!=NULL)
	{  
	    printf("%s\t",p->data.number);
	    printf("%s\t",p->data.num);
		printf("%s\t",p->data.name);
		printf("%d\n",p->data.state);
		
		strcpy(act,"�����ɹ���");
		fprintf(fp,"����ʱ�䣺%s,������%s,ѧ�ţ�%s,���������%s\n",time,p->data.name,p->data.number,act); 
//		fprintf(fp,"%s,%s;\n",p->data.number,p->data.name); 
		p=p->next; 
	}
	 fclose(fp); 
 } 
 
void readStuDentput (LinkList *L) //����ǰ���ļ����ݶ�ȡ�������ڴ�  
{  
    FILE *fp;  
    fp=fopen("kh001.txt","r"); //��ֻ����ʽ�򿪵�ǰĿ¼�µ�.txt  
    if(fp==NULL)  
    {  
        printf("�ļ�������\n");  
        exit(0);                   //��ֹ����  
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

//���˷������� 
void give(LinkList *L)
{  
    int k=312346;
    int key,j;
    
    printf("���������ʱ�䣺\n");
	scanf("%s",time);
	 printf("�����ɹ���\n");
    strcpy(act,"�����ɹ���");
    
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
// ���˿������� 
void create(LinkList *L)
{
	 LinkList *p;
	 InitList(&p);
	 FILE *fp;
     fp=fopen("logbook.txt","a+");
     
	 printf("������ѧ�ź�������\n");
	 scanf("%s%s;",stunum,nam);
	 printf("���������ʱ�䣺\n");
      scanf("%s",time);
      printf("�����ɹ���\n");
	 strcpy(p->data.name,nam);
	 strcpy(act,"�����ɹ���");
	 strcpy(p->data.number,stunum);
	 p->data.state=0;
     fprintf(fp,"����ʱ�䣺%s,������%s,ѧ�ţ�%s,���������%s\n",time,nam,stunum,act);
        	
    
	ListInsert(L,p);
	 fclose(fp); 

} 
//������������ 
void deletecard(LinkList*L)
{
	printf("��������Ҫɾ����ѧ����ѧ��:\n");  
    scanf("%s",stunum);  
    printf("���������ʱ�䣺\n");
    scanf("%s",time);
    //�ж�  
    LinkList *p,*pre;  
    if(L->next==NULL)  
    {  
        printf("��û��ѧ����Ϣ,������ѧ����Ϣ\n");  
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
                
                 strcpy(act,"�����ɹ�!");
                 write_diary(time,p->data.name,p->data.number,act,p->data.num); 
                 
				 free(p);  
                 printf("�����ɹ�\n"); 
				
                 break;  
         }  
         pre=p;  
         p=p->next;  
    }  
    if(judge==0)  {
    	printf("���ѧ��������\n");
    	strcpy(act,"ѧ�Ų����ڣ�");
       FILE *fp;
       fp=fopen("logbook.txt","a+");
       fprintf(fp,"%s,%s,%s\n",time,stunum,act);
       fclose(fp);
	}
         

}
//���˹�ʧ��Ҳ��� 
void lose(LinkList*L)
{
	int b;
    LinkList*q=L->next;
	fflush(stdin);
	int flag=0;
	printf("������ѧ��:\n");
	gets(stunum);
	printf("������˲�����ʱ�䣺\n");
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
	        printf("\n��ѡ���ܣ�1.��ʧ 2.�����ʧ (1 or 2)?\n");
	        scanf("%d",&b);

        	if(b==1)
	      {
		    q->data.state=1;
		    printf("��ʧ�ѳɹ���\n");
		    
		    strcpy(act,"��ʧ�ɹ���");
		    strcpy(nam,q->data.name);
		    strcpy(cardnum,q->data.num);
		    
		    write_diary(time,nam,stunum,act,cardnum);
	      }
	       if(b==2)
          {
	    	q->data.state=0;
		    printf("�����ʧ�ѳɹ���\n");
		    
		    
		    strcpy(act,"��ҳɹ���");
		    strcpy(nam,q->data.name);
		    strcpy(cardnum,q->data.num);
	    	write_diary(time,nam,stunum,act,cardnum);
	      }
		}
 	   else{
 	   	printf("û���ҵ���Ϣ\n");
 	   	strcpy(act,"ѧ�Ų����ڣ�");
        FILE *fp;
        fp=fopen("logbook.txt","a+");
        fprintf(fp,"%s,%s,%s\n",time,stunum,act);
        fclose(fp);
		}
 	   
   
	
}
//���˲������� 
void renew(LinkList*L)
{
//	�½�һ���ڵ㣬����ѧ����ͬ
  LinkList*q=L->next; 
  printf("�������ʧ��ѧ�ţ�\n");
  scanf("%s",stunum);
  printf("���������ʱ�䣺\n");
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
 		printf("����û�й�ʧ�Ŀ�\n"); 
 		
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
	    printf("�����ɹ���\n");
	    
	     
	    strcpy(act,"�����ɹ���");
		strcpy(nam,p->data.name);
		strcpy(cardnum,p->data.num);
	    write_diary(time,nam,stunum,act,cardnum);
   }
	
	
	 
}
//���˳�ֵ���� 
void recharge(LinkList*L)
{
	printf("�������ֵ��ʱ�䣺\n");
	scanf("%s",time);
	printf("�������ֵ�Ŀ��ţ�\n");
	scanf("%s",cardnum);
	printf("�������ֵ�Ľ��: \n");
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
		  		printf("��ʧ���ܳ�ֵ��\n");
		  		
		  		strcpy(nam,q->data.name) ;
		  		strcpy(cardnum,q->data.num) ;
		  		strcpy(stunum,q->data.number); 
		  		strcpy(act,"��ʧ���ܳ�ֵ��");
		  		money_left=q->data.balance;
		  		write_diary2(FP,time,nam,stunum,act,cardnum,money,money_left,0);
		  		//		  		д������־����
			}
			else
			{   if(q->data.balance>1000) 
				  {
				  	printf("��ֵʧ����ֵ\n");
					fprintf(FP,"��ֵʧ����ֵ\n");
				 }
				else{
				q->data.balance=q->data.balance+money;
				strcpy(nam,q->data.name); 
				strcpy(stunum,q->data.number); 
				strcpy(act,"��ֵ�ɹ���");
				money_left=q->data.balance;
//				д������־���� 
               printf("��ֵ�ɹ������Ϊ%.2f\n",money_left);
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
	    	printf("û���ҵ��ÿ��ţ�\n");
	    	fprintf(FP,"û���ҵ��ÿ��ţ�\n");
	    	//		  		д������־����
		}
	    fclose(FP);
}
//�������Ѳ��� 
void  consume(LinkList*L,float counter[4][1232])
{
	printf("���������ѵ����ڣ�\n");
	scanf("%s",date);
	printf("���������ѵ�ʱ�䣺\n");
	scanf("%s",hour);
	printf("���������ѵĿ��ţ�\n");
	scanf("%s",cardnum);
	printf("���������ѵĽ��: \n");
	scanf("%f",&money);
	printf("���������ѵĴ��ں�: \n");
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
		  		printf("��ʧ�������ѣ�\n");
		  		fprintf(FP,"��ʧ�������ѣ�\n");
//		  		д������־���� 
			}
			  else if(q->data.balance-money<0)
			  
			  {  strcat(str,date);
			     strcat(str,hour);
			     
			  	printf("���㣡\n");
			  	strcpy(nam,q->data.name); 
				strcpy(stunum,q->data.number); 
				strcpy(act,"���㣡");
				money=0; 
				money_left=q->data.balance;
			  	
			  	write_diary2(FP,str,nam,stunum,act,cardnum,money,money_left,window);
//		  		д������־����
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
							printf("�������������룺\n");
						    scanf("%d",&password);
						}
						counter[j][day]=0;
					}
					 
						q->data.balance=q->data.balance-money;
						strcat(str,date);
						strcat(str,hour);
				        strcpy(nam,q->data.name); 
				        strcpy(stunum,q->data.number); 
				        strcpy(act,"���ѳɹ���");
				        money_left=q->data.balance;
				        
				        write_diary2(FP,str,nam,stunum,act,cardnum,money,money_left,window);
//				        write_history(fp_h,window,date,hour,cardnum,money);
				        
				        amount1[window][day]++;
				        amount2[window][day]+=money;
//				    д������־���� 
				        printf("���ѳɹ������Ϊ%.2f\n",money_left);
				        printf("ʱ��Ϊ%d,%d�Ŵ����ۼ����Ѵ���Ϊ��%d,�ۼ����ѽ��Ϊ��%.2f\n",day,window,amount1[window][day],amount2[window][day]);
			}
		  	flag=1;
			break;
		  }
		  q=q->next; 
	    }
	    if(flag==0)
	    {
	    	printf("û���ҵ��ÿ��ţ�\n");
	    	fprintf(FP,"û���ҵ��ÿ��ţ�\n");
//	    	д������־���� 
		}
		fclose(FP);
//		fclose(fp_h);
}
//����ѧ������ģ����ѯ 
void find(LinkList*L){
	LinkList*p=L->next;
	int choice;
	printf("ͨ��ѧ�Ż���������ѯ��1/2 \n");
	scanf("%d",&choice);
		if(choice==2){
		 printf("������ģ����ѯ������:\n");
	     scanf("%s",nam);
	     while(p){
	     	if(_m(p->data.name,nam))
	     	printf("%s,%s,%s,%d,%.2f\n",p->data.number,p->data.name,p->data.num,p->data.state,p->data.balance);
	     	p=p->next;
		 }
	 }
	 else{
	 	printf("������ģ����ѯ��ѧ��:\n");
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
//	��¼�ۼ����ѽ�� 
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
	
	
	
     printf("ѡ���˻�������������1/2 \n");
     scanf("%d",&caozuo);
     if(caozuo==1)
     {
     	printf("\n");
      
	 
	 while(1)
    {
	 menu(); 
	 printf("��������ѡ��ķ���\n");
	 scanf("%d",&choose) ;
//	 ���˲��� 
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
	        printf("ллʹ��!");
	    	exit(0);
	    default:
	    	printf("��������ȷ��ѡ��\n");
	    	break;
	 }
    
	}
	    	
	 } 
	 
	 else{
	 	int choice;
	 	while(1)
	 	{
		printf("������ѡ�1.�������� 2.�������� 3.�鲢����4.��������5.ģ����ѯ6.�ۼƽ��7.�˳�8.��ӡ�������ļ�\n") ;
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			    readStuDentput (L);   //���� 
			    displays(L);//	д������ļ� 
			    gives(L);//���� 
			    break;
			case 2:
				ReadwzFile();     //	��ȡ��ʼλ���ļ�wz003.txt 
				ReadConsumptionFile();   // ��ȡ�����ļ�xf014.txt 
				readStuAct(L);   // ��ȡ�����ļ�cz002.txt 
				
				break;
			case 3:
//	    		�鲢���� 
				merge_sort();
				break;
	    	case 4:
	    		quick_sort();
//	    	�������� 
				break;
	    	case 5:
//	    		ģ����ѯ 
	    		search_mohu();
	    		break;
	    	case 6:
//	    	��ָ����ѧ��ͳ�Ƹ�����ֹ�����ڵ��ۼ����ѽ�
	    		statistics();	
	    		break;
	    	case 7:
                printf("ллʹ��!");
	    	    exit(0);
	    		break;
	    	case 8:
//	    		��ӡ�������ļ� 
			    print_sort();
			    break;
	    	default:
	    	    printf("��������ȷ��ѡ��\n");
	    	    break;    
				
		}
		     
     }
		
 } 
 return 0;
}






