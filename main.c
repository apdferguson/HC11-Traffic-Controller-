       /*============================================-=
       ; Behaviour: 
       ;      Generates a square wave with a 40% duty cycle
       ;      using polling   (see text page 366)
       ;      C demonstration version (with magic numbers)
       ;
       ; Assumptions:
       ;      none
       ; Board:
       ;      CME11-E9-EVBU
       ; Author/Date:
       ;      Peter Walsh Feb 2001
       ;      revised Feb 2002
       ;========================================== */


#define porta *(volatile unsigned char *)(0x1000)
#define tic1 *(volatile short int*)()0x1010)
#define toc3 *(volatile short int*)(0x101A)
#define toc2 *(volatile short int *)(0x1018)
#define tcnt *(volatile short int *)(0x100e)
#define tctl1 *(volatile unsigned char *)(0x1020)
#define tflg1 *(volatile unsigned char *)(0x1023)
#define tmsk1 *(volatile unsigned char *)(0x1022)


#define TICK 1
#define CARON 1
#define CAROFF 0
#define HG 0
#define HY 1
#define FG 2
#define FY 3
#define TRUE  1
#define FALSE  0
#define STOMAX 4
#define LTOMAX 8

#define tenSec 10000
#define threeSec 3000
#define sevSec 7000

#define oc2 0x40
#define toggle 0x40
#define clear 0x40
#define jump 0x7e

unsigned int highwayG = 0;
unsigned char fRd = 0;
unsigned char hCheck = 0;
unsigned char state = HG;

void whereWePretendToDoOtherStuff(void){
  while(1){}
}

void Amber(void){
  if(state == HG){
    state = HY;
  }else if(state == FG){
    state = FY;
  }
}

void tractorComin(void){ //need to add 3 second timed yellow light for all transitions in program
  tflg1 = clear;
  if(fRd == 0){ //check to see if a car is already on the road
    toc2 = tcnt + threeSec;
    fRd = 1;
  }else if(fRd == 1){
    toc2 = tcnt + sevSec;
    fRd = 2;
  }
}

void highwayLighToggle(void){
  if(highwayG == 0){
    highwayG = 1;
  }else if(highwayG == 1){
    highwayG = 0;
  }
}

void highwayLightCheck(void){ //check to see if highway light has been green for 10 sec
  tflg1 = clear;
  if(highwayG == 0){
    return;
  }else if(highwayG == 1){
    *(void(**)())0x00ef = tractorComin(); //change irq jump table
    tractorComin();
  }
}

void setup(void){
  state = HG;
  highwayG = 0;
   *(unsigned char *)0x00ee = jump; //set up irq jump table
   *(void(**)())0x00ef = highwayLightCheck;

   *(unsigned char *)0x00dc = jump; //set up toc2 jump table
   *(void(**)())0x00dd = highwayLighToggle;
   tflg1 = clear; //clear flag

   toc2 = tenSec + tcnt;
   tmsk1 |= oc2;

   whereWePretendToDoOtherStuff();

}



unsigned char _start(void) {

  __asm__("lds #_stack");

   setup();


   return 0;
}
