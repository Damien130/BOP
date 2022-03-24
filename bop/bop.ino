#include <Time.h>

//Mason Dill
//Using libraries time and time alarm
//https://www.arduino.cc/reference/en/libraries/time/
//https://www.pjrc.com/teensy/td_libs_TimeAlarms.html

enum devices {BUTTONS, STICK, SONIC};
enum pitch {lPitch, mPitch, hPitch};
enum color {RED, GREEN, BLUE, YELLOW};

enum devices* deviceOrder; //length of 3
enum color* buttons;
enum color* stickDirections;
enum color* sonicZones;

//prototypes
void shuffle(enum color* c, int sz);

void setup() {
  pinMode(1, INPUT);    //correct device
  pinMode(2, INPUT);    //correct interaction
  
  pinMode(3, OUTPUT);   //pitch mux signals
  pinMode(4, OUTPUT);
  
  pinMode(5, OUTPUT);   //color mux signals
  pinMode(6, OUTPUT);
  
  randomSeed(analogRead(0)); //generate random seed from noise

  //initialize interactions
  buttons = (enum color*)malloc(sizeof(enum color) * 4);
  stickDirections = (enum color*)malloc(sizeof(enum color) * 4);
  sonicZones = (enum color*)malloc(sizeof(enum color) * 4);
  for(int i = 0; i < 4; i++){
      buttons[i] = (enum color)i;
      stickDirections[i] = (enum color)i;
      sonicZones[i] = (enum color)i;
  }
  shuffle(buttons, 4);
  shuffle(stickDirections, 4);
  shuffle(sonicZones, 4);

  //initialize deviceOrder
  deviceOrder = (enum devices*)malloc(sizeof(enum devices) * 3);
  for(int i = 0; i < 3; i++){
      deviceOrder[i] = (enum devices)i;
  }
  shuffle((enum color*)deviceOrder, 3);
  
}
void score(){
   now(); // Returns the current time as seconds
}

void loop() {
  Alarm.timerOnce(10, score);
}


void shuffle(enum color* c, int sz){
  enum color tc;

  int swapDes;
  int swapLoc;
  //randomly swap elements 12 times
  for(int i =0; i < 12; i++){
      swapLoc =  random(sz);
      tc = c[swapLoc];

      *(c+swapLoc) = c[swapDes];
      *(c+swapDes) = tc;
  }
}

void end(){
    free(buttons);
    free(stickDirections);
    free(sonicZones);
}
