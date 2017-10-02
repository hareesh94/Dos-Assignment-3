
#include <xinu.h>

typedef struct msg{
topic16 topic;
int *hand[256];
int subsc;
}msg1;

msg1 t[256];
pid32 p[256][2];
int *arr[256];

//subscribe system call

syscall subscribe(
	  topic16 topic,		                /* topic ID	*/
	  void (*handler)(topic16,uint32)		/* pointer to handler function	*/
	)
{
	intmask	mask;
        int i=0;
        int j=0;
        int k=0;
        mask = disable();
               
        for(i=0;i<256;i++){	
 	if(t[i].topic==NULL || t[i].topic==topic){
        if(t[i].topic==NULL)
        t[i].topic=topic;
	for(k=0;k<256;k++)      
	if(t[i].hand[k]==NULL)  
	t[i].hand[k]=handler;
 	t[i].subsc++;
	}
	}	
	for(j=0;j<256;j++){
        if(p[j][0]==NULL)
        {
	p[j][0]=currpid;
	p[j][1]=topic;
	}
	}
	printf("process subscribed  ");
	restore(mask);
	return OK;
}

//Publish system call

syscall publish(topic16 topic, uint32 data)
{
intmask mask;
int i=0;
int j=0;
mask=disable();
for(j=0;j<256;j++){
if(t[j].topic==topic&&t[j].subsc!=0)
        for(i=0;i<256;i++){
if(t[j].hand[i]!=NULL){
arr[i]=t[j].hand[i];     
printf("broker called");
}
}
}

restore(mask);
return OK;
}

//Unsunscribe system call
syscall unsubscribe(topic16 topic)
{
int mask;
int i=0;
int j=0;
pid32 temp[1][1];
mask=disable();
for(i=0;i<256;i++){
if((currpid==p[i][0])&&(p[i][1]==topic))
{
for(j=0;j<256;j++){	
if(t[j].topic==topic){
t[j].subsc--;
}
}
}
}
for(i=0;i<256;i++){
if(currpid==p[i][0])
{
p[i][0]=NULL;
p[i][1]=NULL;
}
}
printf("Process unsubscribed");
restore(mask);
return OK;
}















