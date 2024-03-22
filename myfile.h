#include <stdio.h>
#define MAX 10000
typedef struct card{
	char name[9];
	char number[11];
	char num[8];
	int state;
	float balance;
}card;
typedef struct LNode
{
	card data;
	struct LNode *next;
 }LinkList; // 单个卡片信息结构体 
typedef struct Record{
	char time[17];
	char cardID[8];
	char name[9];
	char stuID[11];
	char w[3];
	float pay;
}Record;//消费记录结构体 

extern Record record[6*MAX];
extern Record history[99*6*MAX];//用于存储所有消费记录的结构数组 
extern char nam[9];
extern char stunum[11];
extern char cardnum[8]; 
extern char time[17];
extern char act[15];
extern char m[5];
extern char date[9];
extern char hour[9];
extern float money;
extern int window;
extern float money_left;
extern int wz[100];
extern int start[100];
extern int amount1[100][1232];
extern float amount2[100][1232];
extern Record Win[100][6*MAX];
extern int pointer;
extern int len;

void InitList(LinkList**L); 
void ListInsert(LinkList*L,LinkList*p);
void displays(LinkList*L);
void find(LinkList*L);

void write_diary(char*time,char*nam,char*stunum,char*act,char*cardnum);
void write_diary2(FILE*fp,char*time,char*nam,char*stunum,char*act,char*cardnum,float money,float money_left,int window);
void gives(LinkList *L);
int getSum(int num);
void loses(LinkList*L,char*time,char*stunum,int b);
void renews(LinkList*L,char*time,char*stunum);
void deletecards(LinkList*L,char*time,char*stunum);
void readStuAct(LinkList*L);
void ReadConsumptionFile();
void ReadRechargeFile(char*time,char*act,char*stunum,char*m);
void OperateCz(char*file,LinkList*L,FILE*FP);
void OperateXf(char*file,LinkList*L,FILE*FP,FILE*fp_h);

void Record_consumption(int window,char*time,char*cardnum,float money,int pointer,char*nam,char*stunum);
void write_history(FILE*fp_h,int window,char*date,char*hour,char*cardnum,float money);
void ReadwzFile();
void merge_sort();
void quick_sort();
void search_mohu() ;
void statistics(); 
void print_sort();

char *my_strstr(const char * str1,const char * str2, int len);
int _m(char * str1,char * str2);
int _ms(char * str1,char * str2);
int cmp(const void *a, const void *b);
