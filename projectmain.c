/***************************************************************************************/
/*    CAN-Network Protocal    Arish Ghaderi       Group project 6       Spring - 2017   */
/*                                                                                      */
/***************************************************************************************/


/* Acceptance Code Definitions */
#define ACC_CODE_ID100 0x2000
#define ACC_CODE_ID100_HIGH ((ACC_CODE_ID100&0xFF00)>>8)
#define ACC_CODE_ID100_LOW (ACC_CODE_ID100&0x00FF)

/* Mask Code Definitions */
#define MASK_CODE_ST_ID 0x0007
#define MASK_CODE_ST_ID_HIGH ((MASK_CODE_ST_ID&0xFF00)>>8)
#define MASK_CODE_ST_ID_LOW (MASK_CODE_ST_ID&0xFF)


#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

/******* CANIniti code*****/
void CANInit (){
  

CANCTL0 = 0x01;
CANCTL1 |= 0x40;          /*set CAN to use the Bus clock */                 
while (! (CANCTL1&0x01)) {}    
                                          
          
CANBTR0 = 0xC7;         
CANBTR1 = 0x3A;                
CANIDAC = 0x10;         


CANIDAR0 = ACC_CODE_ID100_HIGH;      
CANIDMR0 = MASK_CODE_ST_ID_HIGH;      
CANIDAR1 = ACC_CODE_ID100_LOW;       
CANIDMR1 = MASK_CODE_ST_ID_LOW;       


CANIDAC  = 0x10;                    
CANIDAR2 = 0x00;                    
CANIDMR2 = MASK_CODE_ST_ID_HIGH;   
CANIDAR3 = 0x00;                   
CANIDMR3 = MASK_CODE_ST_ID_LOW;     

CANIDAR4 = 0x00;                      
CANIDMR4 = MASK_CODE_ST_ID_HIGH;      
CANIDAR5 = 0x00;                      
CANIDMR5 = MASK_CODE_ST_ID_LOW;       

CANIDAR6 = 0x00;                                  
CANIDMR6 = MASK_CODE_ST_ID_HIGH;       
CANIDAR7 = 0x00;                                   
CANIDMR7 = MASK_CODE_ST_ID_LOW;          

CANCTL0 = 0x00; 
while ((CANCTL1&0x00) != 0) {} 

}




/*******CAN ISR *********/
void interrupt CAN0RxISR(void)
{
unsigned char length, index;
unsigned char rxdata[8];
length = (CANRXDLR & 0x0F);
for (index=0; index<length; index++){
  
rxdata[index] = *(&CANRXDSR0 + index); /* Get received data */
CANRFLG = 0x01; 
} 
}






void main (void) {

   CANCTL1 = 0xA0;    /*turn the CAN ON */
   CANInit(); 

  /**********Transmition****************/
 
  unsigned char CANSendFrame; /*unsigned log id;*/
  unsigned char priority;
  unsigned char length;
  unsigned char *txdata;
  unsigned char txbuffer;
  unsigned char index;
  unsigned char errorflag = NO_ERR;
  unsigned char txbuff[] = "ABCDEFGH";
  
  
    if (!CANTFLG){
       CANTBSEL = CANTFLG; 
       txbuffer = CANTBSEL; 
     }
     /* Load Id to IDR Register */
     ((unsigned long *) ((unsigned long)(&CANTXIDR0))) = id;
     
      for (index=0;index<length;index++) {
        (&CANTXDSR0 + index) = txdata[index]; }
     
    
                                                          /*Data Segment Registers*/
                            
      CANTXDLR = length;                                  /* Set Data Length Code */
      CANTXTBPR = priority;                               /* Set Priority */
      CANTFLG = txbuffer;                               /* Start transmission */
      while ((CANTFLG & txbuffer) != txbuffer);        /* Wait for Transmission*/     
      
    
    
  /**********************Reception*****************/ 


while (!(CANCTL0&0x10));
CANRFLG = 0xC3;
CANRIER = 0x01;

Enable Interrupts;
for (;;) {
      errorflag = CAN0SendFrame((ST_ID_100), 0x00, sizeof(txbuff)-1, txbuff);
      Delay();
          } 
}

