//PROCESS ////////////////////////

#include<stdio.h>
#include<sys/types.h>

void main()
{
int n1,n2;
char var[200];
printf("Enter the string:");
gets(var);
pid_t pid1;


pid1 = fork();
if(pid1 < 0)
{
printf("Child process creation unsucessfull");
}
else if(pid1>0)
{
n1=getpid();
printf("The Process Id of the parent process is %d \n",n1);
words(var);
}
else
{
n2=getpid();
printf("The Process Id of the child process is %d \n",n2);
vowels(var);
}
 
}

int words(char var[])
{
int count=0, i;
for (i = 0;var[i] != '\0';i++)
    {
        if (var[i] == ' ')
            count++;    
    }
printf("Number of words in given string are: %d \n\n", count + 1);
}

int vowels(char var[])
{

int i ,count=0;
char c;
for(i=0; var[i]!='\0' ; i++)
{
c = toupper(var[i]);
if(c=='A' || c=='E' || c=='I' || c=='O' || c=='U'||c=='a'||c=='e'||c=='i'||c=='o'||c=='u')
count+=1;
}
if(count==0)
printf("No Vowels!!\n");
else
printf("No. of vowels=%d \n\n",count);
}







//This program is producer consumer program
//how to run this program
//gcc -o pc pc.c -lpthread -lrt

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define BUFF_SIZE   15           /* total number of slots */
#define NP          3           /* total number of producers */
#define NC          3           /* total number of consumers */
#define NITERS      4           /* number of items produced/consumed */

typedef struct {
    int buf[BUFF_SIZE];   /* shared var */
    int in;               /* buf[in%BUFF_SIZE] is the first empty slot */
    int out;              /* buf[out%BUFF_SIZE] is the first full slot */
    sem_t full;           /* keep track of the number of full spots */
    sem_t empty;          /* keep track of the number of empty spots */
    sem_t mutex;          /* enforce mutual exclusion to shared data */
} sbuf_t;

sbuf_t shared;

void *Producer(void *arg)
{
    int i=0, item, index;

    index = (int)arg;

	
	for (i=0; i < NITERS; i++) {

       
	printf("\n[P%d]producer is starting..",index);    
        /* Produce item */
        item = i;       

        /* Prepare to write item to buf */
	
        /* If there are no empty slots, wait */
	printf("\n[P%d]waiting for empty slots",index);
        sem_wait(&shared.empty);

        /* If another thread uses the buffer, wait */
	printf("\n[P%d]waiting for turn to enter in critical section",index);
        sem_wait(&shared.mutex);

	
	/* critical section start*/        
	printf("\n[P%d]in critical section",index);	
	shared.buf[shared.in] = item;
        shared.in = (shared.in+1)%BUFF_SIZE;
        printf("\n\t[P%d] Producing %d ...\n", index, item); fflush(stdout);
	/*critical section ends*/

        /* Release the buffer */
        sem_post(&shared.mutex);
	printf("\n[P%d]out of critical section",index);        
	
	/* Increment the number of full slots */
        sem_post(&shared.full);
	printf("\n[P%d]in Remainder section",index);
        
	/* Interleave  producer and consumer execution */
        if (i % 2 == 1) sleep(5);
        sleep(5);
	
	}/*end for*/
    
    return NULL;
}

void *Consumer(void *arg)
{
    int i=0, item, index;

    index = (int)arg;
	
	for (i=0; i < NITERS; i++) {

	printf("\n[C%d]consumer is starting..",index);    
        

        /* Prepare to reade item from buf */
	
        /* If there are no full slots, wait */
	printf("\n[C%d]waiting for full slots",index);
        sem_wait(&shared.full);

        /* If another thread uses the buffer, wait */
	printf("\n[C%d]waiting for turn to enter in critical section",index);
        sem_wait(&shared.mutex);

	
	/* critical section start*/        
	printf("\n[C%d]in critical section",index);	
	shared.out = (shared.out + 1)%BUFF_SIZE;	
	item = shared.buf[shared.out];
        
        printf("\n\t[C%d] Consuming %d ...\n", index, item); fflush(stdout);
	/*critical section ends*/

        /* Release the buffer */
        sem_post(&shared.mutex);
	printf("\n[C%d]out of critical section",index);        
	
	/* Increment the number of full slots */
        sem_post(&shared.empty);
	printf("\n[C%d]in Remainder section",index);
        
	/* Interleave  producer and consumer execution */
        if (i % 2 == 1) sleep(5);
        
	
	}/*end for*/        
	
    
    return NULL;
}

int main()
{
	pthread_t idP[2], idC[2];
    	int index=0,temp=0;
    	shared.in =0;
	shared.out=-1;
	
    	sem_init(&shared.full, 0, 0);
    	sem_init(&shared.empty, 0, BUFF_SIZE);
	sem_init(&shared.mutex, 0, 1);

    	/* Insert code here to initialize mutex*/
    	printf("***********Producer Consumer Problem ************");
	/* Create a new producer */
	for(index=0;index<2;index++){
	        temp = pthread_create(&idP[index], NULL, Producer, (void*)index);

		if(temp < 0){ 
			printf("unable to create thread"); 
			exit(1);
		}
	}					
	/* Create a new Consumer */
	for(index=0;index<2;index++){
	        temp = pthread_create(&idC[index], NULL,Consumer, (void*)index);

		if(temp < 0){ 
			printf("unable to create thread"); 
			exit(1);
		}
	}
 	for(index=0;index<2;index++){
		pthread_join(idP[index], NULL);
        	pthread_join(idC[index], NULL);
	}
	pthread_exit(NULL);     
       
}

OUTPUT:
student@student-HP-Compaq-4000-Pro-SFF-PC:~$ gcc pc.c -lpthread -lrt
student@student-HP-Compaq-4000-Pro-SFF-PC:~$ ./a.out
***********Producer Consumer Problem ************
[P0]producer is starting..
[P0]waiting for empty slots
[P0]waiting for turn to enter in critical section
[P0]in critical section
	[P0] Producing 0 ...






////////////////////SIMPLE PRODUCER///////////////////////////

#include<stdio.h>
#include<stdlib.h>
#define MAX 10

int count=0,b[MAX];
int producer();
void consumer();

void main()
{
	int i,opt;
	for(i=0;i<MAX;i++)
		b[i]=-1;

	do{	
	printf("\n***Main Menu***");
	printf("\n1.Produce");
	printf("\n2.Consume");
	printf("\n3.Exit");
	
	printf("\nEnter your option:");
	scanf("%d",&opt);

	switch(opt)
	{
		case 1:if(count<MAX)
			producer();
			else
			printf("\n Buffer is full!!!");
			break;

		case 2:if(count>0)
			consumer();
			else
			printf("\n Buffer is empty!!!");
			break;

		case 3: exit(0);
		
		default:printf("\nInvalid Option!!!");
	}
	}while(opt!=3);
}

int producer()
{
	int data,i;
	printf("\nEnter data:");
	scanf("%d",&data);
	
	for(i=0;i<MAX;i++)
	{
		if(b[i]==-1)
		{
			b[i]=data;
			printf("\n%d is placed at position %d",data,i+1);
			count++;
			return i;
		}
	}

}

void consumer()
{	
	int pos;
	printf("\nEnter the location from where data is to be retrieved:");
	scanf("%d",&pos);

	if(b[pos]!=-1)
	{
		printf("\nData:%d",b[pos]);
		b[pos]=-1;
		count--;
	}
	else
		printf("\nNo Data Found!!!");
}
		




MEMORY ALLOCATION

#include<stdio.h>
#include<conio.h>
void firstfit();
void bestfit();
void worstfit();
int flag[20];
int pr,par,p[20],partition[20];
void main()
{
int i,j,ch;
clrscr();
printf("Enter no of processes\t");
scanf("%d",&pr);
printf("Enter no of partitions\t");
scanf("%d",&par);
 for(i=0;i<pr;i++)
  {
  printf("enter process %d: ",i+1);
  scanf("%d",&p[i]);
  }

 for(i=0;i<par;i++)
  {
  printf("enter partition %d: ",i+1);
  scanf("%d",&partition[i]);
  flag[i]=0;
  }
	printf("\n1.First Fit\n 2.Best Fit \n3.Worst Fit\n");
	scanf("%d",&ch);

       switch(ch)
  {
   case 1:firstfit();
	   break;
   case 2:bestfit();
	   break;
   case 3:worstfit();
       break;
  }

 getch();
 }

 void firstfit()
{
 int i,j;
 int intfrag=0,extfrag=0;
  for(i=0;i<pr;i++)
  {
   for(j=0;j<par;j++)
   {
   if((flag[j]==0) && (p[i]<=partition[j]))
   {
   intfrag=intfrag+partition[j]-p[i];
   flag[j]=1;
   break;
   }
   }
  }
  for(i=0;i<par;i++)
  {
   if(flag[i]==0)
   extfrag=extfrag + partition[i];

  }
  printf("the internal fragmentation is %d\n",intfrag);
  printf("the external  fragmentation is %d\n",extfrag);
}

void bestfit()
{
int i,j,temp;
 int intfrag=0,extfrag=0;
 for(i=0;i<pr;i++)
 {
  for(j=i+1;j<pr;j++)
  {
   if(p[j]<p[i])
   {
   temp=p[i];
   p[i]=p[j];
   p[j]=temp;
   }

  }

 }
 for(i=0;i<par;i++)
 {
  for(j=i+1;j<par;j++)
  {
   if(partition[j]<partition[i])
   {
   temp=partition[i];
   partition[i]=partition[j];
   partition[j]=temp;
   }

  }

 }
  for(i=0;i<pr;i++)
  {
   for(j=0;j<par;j++)
   {
   if((flag[j]==0) && (p[i]<=partition[j]))
   { intfrag=intfrag+partition[j]-p[i];
   flag[j]=1;
   break;
   }
   }
  }
  for(i=0;i<par;i++)
  {
   if(flag[i]==0)
   extfrag=extfrag + partition[i];
  }
  printf("the internal fragmentation is %d\n",intfrag);
 printf("the external  fragmentation is %d\n",extfrag);

}
void worstfit()
{
 int i,j,temp;
 int intfrag=0,extfrag=0;
 for(i=0;i<pr;i++)
 {
  for(j=i+1;j<pr;j++)
  {
   if(p[j]<p[i])
   {
   temp=p[i];
   p[i]=p[j];
   p[j]=temp;
   }

  }

 }
 for(i=0;i<par;i++)
 {
  for(j=i+1;j<par;j++)
  {
   if(partition[j]>partition[i])
   {
   temp=partition[i];
   partition[i]=partition[j];
   partition[j]=temp;
   }

  }

 }
  for(i=0;i<pr;i++)
  {
   for(j=0;j<par;j++)
   {
   if((flag[j]==0) && (p[i]<=partition[j]))
   { intfrag=intfrag+partition[j]-p[i];
   flag[j]=1;
   break;
   }
   }
  }
  for(i=0;i<par;i++)
  {
   if(flag[i]==0)
   extfrag=extfrag + partition[i];
  }
  printf("the internal fragmentation is %d\n",intfrag);
  printf("the external  fragmentation is %d\n",extfrag);
}




//FIFO LRU //////////////////////////////////////////////////////////////////////////////////



#include<stdio.h>
int n,pg[30],fr[10];
void fifo();
void optimal();
void lru();
void main()
{
int i,ch;
printf("\nEnter total number of pages:");
scanf("%d",&n);
printf("\nEnter sequence:");
for(i=0;i<n;i++)
scanf("%d",&pg[i]);
do
{
printf("\n MENU");
printf("\n 1.FIFO 2.LRU 3.Optimal 4.Exit");
scanf("%d",&ch);
switch(ch)
{
 case 1: fifo(); break;
 case 2: lru(); break;
 case 3: optimal(); break;
 default:exit(0);
}
}while(ch!=4);
getchar();
}

void fifo()
{
int i,f,r,s,count,flag,num,psize;
f=0; r=0; s=0;
flag=0; count=0;
printf("\nEnter size of page frame:");
scanf("%d",&psize);
for(i=0;i<psize;i++)
{
fr[i]=-1;
}
while(s<n)
{
flag=0;
num=pg[s];
for(i=0;i<psize;i++)
{
if(num==fr[i])
{
s++;
flag=1;
break;
}
}
if(flag==0)
{
if(r<psize)
{
fr[r]=pg[s];
r++;
s++;
count++;
}
else
{
if(f<psize)
{
fr[f]=pg[s];
s++;
f++;
count++;
}
else
f=0;
}
}
printf("\n");
for(i=0;i<psize;i++)
{
printf("%d\t",fr[i]);
}
}
printf("\nTotal Pages=%d",n);
printf("\nPage Faults=%d",count);
printf("\nPage Hits=%d",(n-count));
getchar();
}
void optimal()
{
int count[10],i,j,k,fault,f,flag,temp,current,c,dist,max,m,cnt,p,x;
fault=0;
dist=0;
k=0;
printf("\nEnter frame size:");
scanf("%d",&f);
for(i=0;i<f;i++)
{
count[i]=0;
fr[i]=-1;
}
for(i=0;i<n;i++)
{
flag=0;
temp=pg[i];
for(j=0;j<f;j++)
{
if(temp==fr[j])
{
flag=1;
break;
}
}
if((flag==0)&&(k<f))
{
fault++;
fr[k]=temp;
k++;
}
else if((flag==0)&&(k==f))
{
fault++;
for(cnt=0;cnt<f;cnt++)
{
current=fr[cnt];
for(c=i;c<n;c++)
{
if(current!=pg[c])
count[cnt]++;
else
break;
}
}
max=0;
for(m=0;m<f;m++)
{
if(count[m]>max)
{
max=count[m];
p=m;
}
}
fr[p]=temp;
}
printf("\n");
for(x=0;x<f;x++)
{
printf("%d\t",fr[x]);
}
}
printf("\nTotal number of pages=%d",n);
printf("\nTotal number of faults=%d",fault);
printf("\nTotal number of hits=%d",(n-fault));
getchar();
}

void lru()
{
int count[10],i,j,k,fault,f,flag,temp,current,c,dist,max,m,cnt,p,x;
fault=0;
dist=0;
k=0;
printf("\nEnter frame size:");
scanf("%d",&f);
for(i=0;i<f;i++)
{
count[i]=0;
fr[i]=-1;
}
for(i=0;i<n;i++)
{
flag=0;
temp=pg[i];
for(j=0;j<f;j++)
{
if(temp==fr[j])
{
flag=1;
break;
}
}
if((flag==0)&&(k<f))
{
fault++;
fr[k]=temp;
k++;
}
else if((flag==0)&&(k==f))
{
fault++;
for(cnt=0;cnt<f;cnt++)
{
current=fr[cnt];
for(c=i;c>0;c--)
{
if(current!=pg[c])
count[cnt]++;
else
break;
}
}
max=0;
for(m=0;m<f;m++)
{
if(count[m]>max)
{
max=count[m];
p=m;
}
}
fr[p]=temp;
}
printf("\n");
for(x=0;x<f;x++)
{
printf("%d\t",fr[x]);
}
}
printf("\nTotal number ofpages=%d",n);
printf("\nTotal number of faults=%d",fault);
printf("\nTotal number of hits=%d",(n-fault));
getchar();
}




//BANKERS /////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<conio.h>
void main()
{
int k=0,output[10],d=0,t=0,ins[5],i,avail[5],allocated[10][5],need[10][5],MAX[10][5],pno,P[10],j,rz, count=0;
clrscr();
printf("\n Enter the number of resources : ");
scanf("%d", &rz);
printf("\n enter the max instances of each resources\n");
for(i=0;i<rz;i++)
{  avail[i]=0;
printf("%c= ",(i+97));
scanf("%d",&ins[i]);
}
printf("\n Enter the number of processes : ");
scanf("%d", &pno);
printf("\n Enter the allocation matrix \n     ");
 
for(i=0;i<rz;i++)
printf(" %c",(i+97));
printf("\n");
for(i=0;i <pno;i++)
{           P[i]=i;
printf("P[%d]  ",P[i]);
for(j=0;j<rz;j++)
{
scanf("%d",&allocated[i][j]);
avail[j]+=allocated[i][j];
}
}
 
printf("\nEnter the MAX matrix \n     ");
for(i=0;i<rz;i++)
{          printf(" %c",(i+97));
avail[i]=ins[i]-avail[i];
}
printf("\n");
for(i=0;i <pno;i++)
{
printf("P[%d]  ",i);
 for(j=0;j<rz;j++)
 scanf("%d", &MAX[i][j]);
}
 
printf("\n");
A: d=-1;
for(i=0;i <pno;i++)
{ count=0; t=P[i];
 for(j=0;j<rz;j++)
 {
 need[t][j] = MAX[t][j]-allocated[t][j];
 if(need[t][j]<=avail[j])
 count++;
 }
  printf("\nneed matrix is:");
  for(j=0;j<rz;j++)
 {
  printf("%d",need[t][j]);
 }
 printf("\n");
if(count==rz)
{
output[k++]=P[i];
 for(j=0;j<rz;j++)
avail[j]+=allocated[t][j];
}
else
 P[++d]=P[i];
}
 
if(d!=-1)
{ pno=d+1;
goto A;
}
printf("\n safe sequence is:");
printf("\t <");
for(i=0;i<k;i++)
printf(" P[%d] ",output[i]);
printf(">");
getch();
}



////////////////////////BASH @2/////////////////////////////////

#!/bin/bash

echo "Cases:"
echo "1.Greater of three numbers."
echo "2.reverse of a number."
echo "3.Sum of digits."
echo "4.Display a word n times."

echo "Choose any option:"
read c

case "$c" in
"1")
	sh ./greater.sh 1 2 3
	;;
"2")
	sh ./rev.sh 123
	;;
"3")
	sh ./sum.sh 123
	;;
"4")
	sh ./name.sh 5 gaurav
	;;
esac

SUM:
#!/bin/bash 

if [ $1 -gt $2 ] && [ $1 -gt $3 ] 
then 
echo $1 " is the greatest." 
elif  [ $2 -gt $1 ] && [ $2 -gt $3 ] 
then 
echo $2 " is the greatest." 
else 
echo $3 " is the greatest." 
fi 

REVERSE:
#!/bin/bash 

num=$1

sd=0
rev=0

while [ $num -gt 0 ]
do 
sd=$(( $num% 10 )) 
rev=$(( $rev* 10 +$sd )) 
num=$(( $num/ 10 )) 
done 
echo "Reverse of the number is :" $rev 

SUM:
#!/bin/bash 

sd=0 
sum=0 

num=$1
while [ $num -gt 0 ] 
do 
    sd=$(( $num% 10 )) # get Remainder 
    num=$(( $num/ 10 ))  # get next digit 
    sum=$(( $sum+ $sd )) # calculate sum of digit 
done 
echo  "Sum of all digit  is $sum" 

WORDS:
#!/bin/bash 

echo "The name is :" 
for i in $(seq 1 $1) 
do 
echo $2
done
