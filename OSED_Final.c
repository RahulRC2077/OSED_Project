#include <rtl.h>
#include <lpc214x.h>
#include <stdio.h>

OS_TID tsk1,tsk2,tsk3;    	//declare task identification number variables

os_mbx_declare (MsgBox, 100);                /* Declare an RTX mailbox  100 msgs with name MsgBox*/
       
_declare_box(mpool,20,32);	 /* Reserve a memory for 32 blocks of 20 bytes  */

void delay(unsigned long int);
void hascii(int *);
unsigned  int adc_value=0,temp_adc=0;
int temp,i;
int var[10];
char val[15]; 

void serial()
{
  PINSEL0 |= 0x00000005; 			
  U0LCR = 0x83; 					
  U0DLL = 0x61; 					
  U0LCR = 0x03; 					
  U0IER = 0x01;						
}

void delay(unsigned  long int r1)
{
  	unsigned  long int r;
  	for(r=0;r<r1;r++);
}

__task void job1 (void); 		//declare function for job1
__task void job2 (void); 		//declare function for job2
__task void job3 (void); 		//declare function for job3

__task void job1 (void)		// job1 function definition
{
   U32 *mptr;
	os_tsk_prio_self (3);		// assign priority to job1 as 2
   tsk2=os_tsk_create (job2, 0);		//create job2 and keep in ready state
	 os_mbx_init (MsgBox, sizeof(MsgBox));
   mptr = _alloc_box (mpool);                /* Allocate a memory for the message */
	 PINSEL1  |= 0X00040000;       //AD0.4 pin is selected(P0.18)	
   while (1)
   {
    //CONTROL register for ADC
		AD0CR = 0x09200010;       				  	//command register for ADC-AD0.4
	  delay(100);
		while((temp_adc = AD0GDR) == 0x80000000);	//to check the interrupt bit
		adc_value = AD0GDR;          				//reading the ADC value
		adc_value >>=6;
		adc_value &= 0x000003ff;
 	  //sprintf(val,"Temperature:%d",adc_value);
		sprintf(val,"%d",adc_value);
		while (val[i] != '\0')
	  {	 
	  	mptr[i] = val[i];
		   i++;
	  }
		i=0;
		os_mbx_send (MsgBox, mptr, 0x00ff);      
	  os_tsk_prio(tsk2,4);          //Change priority of task2 to 4	
   }
}

__task void job2 (void)		// job2 function definition
 {
	U32 *rptr;
  while (1)
   {
		PINSEL1|=0x00000000;
    IODIR0 = 0x00000C00;
    IOCLR0 = 0x00000C00;
		os_mbx_wait(MsgBox, (void*)&rptr, 0xffff);
		while(rptr[i]!='\0')
    {
      while(!(U1LSR & 0x20));
      U0THR = rptr[i];                   /* Display the recieved message from UART0 */
      i++;
    }
		i=0;
		if(adc_value>0x60)
    {
      for(i=0;i<10;i++)
			{
				IOSET0 = 0x00000400;
				IOCLR0 = 0x00000800;
				delay(500000);

				IOSET0 = 0x00000800;
				IOCLR0 = 0x00000400;
				delay(500000);
			}
		}
  }
}

int main (void) 
{
serial();
os_sys_init(job1);		//initialize job1 
while (1);
}

