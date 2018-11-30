 


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

/* State */
unsigned char car = CAROFF;
unsigned char state = HG;
unsigned char stoFlag = FALSE;
unsigned char stoCount = 0;
unsigned char ltoFlag = FALSE;
unsigned char ltoCount = 0;


/* The signal handler just clears the flag and re-enables itself. */
void catch_alarm (int sig) {
   signal (sig, catch_alarm);
   alarm(TICK);
   if (new_minor_cycle) {
      printf("ERROR missed deadline \n");
      exit(0);
   } else {
      new_minor_cycle = 1;
   }
}

void getCar(void) {
   int num = read(0, buf, 4);
   if (num > 0) {
      if (buf[0] == 'o') {
         car = CARON;
      } else if (buf[0] == 'f') {
         car = CAROFF;
      }
   }
}

void fsm(void) {

   switch(state) {
      case HG:
         if (!((car == CARON) && ltoFlag)) {
            state = HG;
	 } else {
            state = HY;
	    stoCount = 0;
	    ltoCount = 0;
         }
         break;
      case HY:
         if (!stoFlag) {
            state = HY;
	 } else {
            state = FG;
	    stoCount = 0;
	    ltoCount = 0;
         }
         break;
      case FG:
         if (((car == CARON) || !stoFlag) && (!ltoFlag)) {
            state = FG;
	 } else {
            state = FY;
	    stoCount = 0;
	    ltoCount = 0;
         }
         break;
      case FY:
         if (!stoFlag) {
            state = FY;
	 } else {
            state = HG;
	    stoCount = 0;
	    ltoCount = 0;
         }
         break;
   } 
}

void putLights(void) {

   switch(state) {
      case HG:
         printf("Highway Green Farm Road Red \n");
         break;
      case HY:
         printf("Highway Yellow Farm Road Red \n");
         break;
      case FG:
         printf("Highway Red Farm Road Green \n");
         break;
      case FY:
         printf("Highway Red Farm Road Yellow \n");
         break;
   } 
}

void shortTimer(void) {
   if (stoCount < STOMAX) {
      stoCount = stoCount +1;
   }
   if (stoCount == STOMAX) {
      stoFlag = 1;
   } else {
      stoFlag = 0;
   }
}

void longTimer(void) {
   if (ltoCount < LTOMAX) {
      ltoCount = ltoCount +1;
   }
   if (ltoCount == LTOMAX) {
      ltoFlag = 1;
   } else {
      ltoFlag = 0;
   }
}

int main (void) {

  *(unsigned char *)0x00ee = jump; //irq jumptable
  *(void(**)())0x00ef = &getCar;

   /* Set up non blocking read */
   fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

   /* Establish a handler for SIGALRM signals. */
   signal (SIGALRM, catch_alarm);

   /* Set an alarm. */
   alarm (TICK);

   printf("\nCSCI 261 Traffic Light Controller Simulation\n\n");
   printf("type the character 'o' to indicate a car is on the sensor\n");
   printf("type the character 'f' to indicate a car is NOT on the sensor\n\n");
   while (1) {
      getCar();
      shortTimer();
      longTimer();
      fsm();
      putLights();
      new_minor_cycle = 0;
      while (!new_minor_cycle);
   }
     
   return(0);
}
