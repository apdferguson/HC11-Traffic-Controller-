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
    *(void(**)())0x0dd = tractorComin();

  }else if(state == FG){
    state = FY;
  }
}

void tractorComin(void){ //need to add 3 second timed yellow light for all transitions in program
  *(void(**)())0x00ef = tractorComin(); //change irq jump table
  tflg1 = clear;
  if(fRd == 0){ //check to see if a car is already on the road
    toc2 = tcnt + threeSec;
    fRd = 1;
  }else if(fRd == 1){
    toc2 = tcnt + sevSec;
    fRd = 2;
  }
  whereWePretendToDoOtherStuff();
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
    Amber();
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
