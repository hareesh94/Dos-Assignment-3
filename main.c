#include <xinu.h>
pid32 pid1;
pid32 pid2;
pid32 pid3;
pid32 brokerid;
topic16 topic;

void bar(topic16 topic,uint32 data)
{
printf(" bar() handler");
}



int i=0;
int j=0;
int *arr[256];
void (*handler)(topic16,uint32);


process p1(void)
{
 void (*handler)(topic16,uint32)=&bar;
   subscribe(15,&bar);
	return OK;
	
}


process p2(void)
{	
	publish(15,63);
	return OK;
}





process broker()
{
for(i=0;i<256;i++){
arr[i];
printf("handler used id %d",arr[i]);
return OK;
}

}

process p3(void){

unsubscribe(15);
}


process    main(void)
{
    printf("Hello\n");
    recvclr();

    pid1 = create(p1, 4096, 50, "p1", 0);
    pid2 = create(p2, 4096, 50, "p2", 0);
brokerid = create(broker,4096,50,"broker",0);    
pid3 = create(p3, 4096, 50, "p3", 0);
    

    resched_cntl(DEFER_START);
    resume(pid1);
    resume(pid2);
    resume(pid3);
    resume(brokerid); 

    resched_cntl(DEFER_STOP);

    return OK;
}
