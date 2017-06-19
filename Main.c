#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "mc9s12c32.h"
//#include "mscan.h"



#define ST_ID_100 0x20000000
#define NO_ERR 0 
#define ERR_BUFFER_FULL 1
#define SET_BITS(port,mask) (port)|=(mask)
#define CLR_BITS(port,mask) ((port)&=((~mask)&0xFF))



unsigned char CANSendFrame(unsigned long id, unsigned char priority, unsigned char length, unsigned char *txdata);
void CANInit(void);
void delay(int milliseconds);

void CANInit(void)
{
  CANCTL0 = 0x01; /* Enter Initialization Mode */
  while (! (CANCTL1&0x01)) {}; /* Wait for Initialization Mode
                                  acknowledge (INITRQ bit = 1) */
  CANCTL1 = 0xC0;    // 
  CANBTR0 = 0x07;
  CANBTR1 = 0x23;
  CANCTL0 = 0x00;
  while(CANCTL1&0x01);
}

void main()
{
  unsigned char errorflag = NO_ERR;
  unsigned char txbuff[] = "ABCABC";
  
  CANInit();
  while(!(CANCTL0&0x10)); 
  
  //SET_BITS(CANRFLG,0xC3);
  //SET_BITS(CANRIER,0x01);
  CANRFLG = 0xC3;                                                                 
  CANRIER = 0x00;
  
  EnableInterrupts;
  

errorflag = CANSendFrame(0x020000000, 0x00, (sizeof(txbuff)-1), txbuff);
    
  for(;;)
  {
     if (CANRFLG & 0x01){
      CANRFLG |=0x01;
     }
  }          
}

unsigned char CANSendFrame(unsigned long id, unsigned char priority, unsigned char length, unsigned char *txdata)
{ 
  unsigned char txbuffer;
  int index = 0;
   
  if (!CANTFLG)
  {
    return ERR_BUFFER_FULL;
  }/* Is Transmit Buffer full?? */
    
  
  CANTBSEL = CANTFLG; /* Select lowest empty buffer */
  txbuffer = CANTBSEL; /* Backup selected buffer */
  
  /* Load Id to IDR Register */
  *((unsigned long *) ((unsigned long)(&CANTXIDR0))) = id;
  
  for (index=0; index<length; index++) {
    *(&CANTXDSR0 + index) = txdata[index]; // Load data to Tx buffer
                                            // Data Segment Registers
  }
  
  CANTXDLR = length; // Set Data Length Code 
  CANTXTBPR = priority; // Set Priority 
  CANTFLG = txbuffer; // Start transmission 
  
  while ( (CANTFLG & txbuffer) != txbuffer); // Wait for Transmission completion
  
  return 0;
}


void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

interrupt 39 void CANRxISR(void)
{
  unsigned char length, index;
  unsigned char rxdata[8];
  
  length = (CANRXDLR&0x0F);
  for (index=0; index<length; index++) 
  {
    rxdata[index] = *(&CANRXDSR0 + index); // Get received data
  }

  SET_BITS(CANRFLG,0x01); // Clear RXF, and check for new messages
  //CANRFLG =0x01;
}
