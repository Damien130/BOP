//#include <Time.h>

//Mason Dill
//Using libraries time and time alarm
//https://www.arduino.cc/reference/en/libraries/time/
//https://www.pjrc.com/teensy/td_libs_TimeAlarms.html

unsigned long c_time = 0;
unsigned long last_c_time = 0;

unsigned int score = 0;

enum devices {BUTTONS, STICK, SONIC};
enum pitch {lPitch, mPitch, hPitch};
enum color {RED, GREEN, BLUE, YELLOW};

enum devices* deviceOrder; //positions correlate to pitch
enum color* buttons; //positions corelate to color
enum color* stickDirections; //positions corelate to color
enum color* sonicZones; //positions corelate to color

//prototypes
void shuffle(enum color* c, int sz);
void muxByColor(enum color c, enum devices d, int pin);
void muxByDevice(enum devices d, int pin);
void numToMux(int num, int pin);

void addToScore();
void setdown();

void setup() {
  pinMode(0, OUTPUT); //display pin
  
  pinMode(1, OUTPUT); //interaction pins
  pinMode(2, OUTPUT);

  pinMode(3, OUTPUT); //display color pin
  pinMode(4, OUTPUT);

  pinMode(5, INPUT); //button interupt

  pinMode(7, OUTPUT); //device select
  pinMode(8, OUTPUT);

  pinMode(12, OUTPUT); //color select
  pinMode(13, OUTPUT);
  
//we actually may be able to use digital signals here (LOW -> V < 1.0v, HIGH -> V > 3.0v)
  pinMode(A4, INPUT); //x
  pinMode(A5, INPUT); //y

  pinMode(A1, INPUT); //ultrasonic sensor
  
  randomSeed(analogRead(0)); //generate random seed from noise

  score = 0;

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

  //display current setup
  int displayColorPin = 3, interactionPin = 1, displayPin = 0;
  digitalWrite(displayPin, HIGH);
  for(int i = 0; i < 3; i++){
    //play pitch i where deviceOrder = i
    for(int j = 0; j < 4; j++){
      numToMux(j, interactionPin); //select interaction
      muxByColor(buttons[j], (enum devices)i, displayColorPin);
    }
    delay(1000); //wait for 1 s
  }
  digitalWrite(displayPin, LOW);
}

void addToScore(){
  c_time = millis();
  //check to see if addToScore() was called in the last 250 milliseconds
  if (c_time - last_c_time > 250){
    
    //digitalWrite(ledPin, ledToggle);
    last_c_time = c_time;
    }
}

void loop() {
  //select a random device
  //enum devices curD = (enum devices)random(3);
  enum devices curD = BUTTONS; //for testing
  //select a random color
  enum color curC = (enum color)random(4);

  muxByDevice(curD, 7);
  muxByColor(curC, curD, 12);
 
  
  //display to user
      //display LED
      //playSound

      
      //if buttons check pin 1
      //find stickDir
      //if ultrasonic,


   //set up interupt dynamically
   //attachInterrupt(digitalPinToInterrupt(pin), ISR, mode)
   //attachInterrupt(signal, functioncall response, low/high mode)
   //attachInterrupt(stickDir, score, low/high mode)
   //wait(time)
   //detachInterrupt(digitalPinToInterrupt(pin))
}

void shuffle(enum color* c, int sz){
  enum color tc;

  int swapDes;
  int swapLoc;
  //randomly swap elements 12 times
  for(int i =0; i < 12; i++){
      swapLoc =  random(sz);
      swapDes = random(sz);
      tc = c[swapLoc];

      *(c+swapLoc) = c[swapDes];
      *(c+swapDes) = tc;
  }
}

void numToMux(int num, int pin){
  switch(num){
    case 0: 
    digitalWrite(pin, LOW);
    digitalWrite(pin, LOW);
    break;
    case 1:
    digitalWrite(pin, HIGH);
    digitalWrite(pin, LOW);
    break;
    case 2:
    digitalWrite(pin, LOW);
    digitalWrite(pin, HIGH);
    break;
    case 3:
    digitalWrite(pin, HIGH);
    digitalWrite(pin, HIGH);
  }
}

void muxByDevice(enum devices d, int pin){
  if (d == deviceOrder[0]){
      digitalWrite(pin, HIGH);
      digitalWrite(pin+1, LOW);
    } else if (d == deviceOrder[1]){
      digitalWrite(pin, LOW);
      digitalWrite(pin+1, HIGH);
    } else if (d == deviceOrder[2]){
      digitalWrite(pin, HIGH);
      digitalWrite(pin+1, HIGH);
    }
}

void muxByColor(enum color c, enum devices d, int pin){
   switch(d){
    case BUTTONS: 
      if(c == buttons[0]){
        digitalWrite(pin, LOW);
        digitalWrite(pin+1, LOW);
      } else if(c == buttons[1]){
        digitalWrite(pin, HIGH);
        digitalWrite(pin+1, LOW);
      } else if(c == buttons[2]){
        digitalWrite(pin, LOW);
        digitalWrite(pin+1, HIGH);
      } else if(c == buttons[3]){
        digitalWrite(pin, HIGH);
        digitalWrite(pin+1, HIGH);
      }
    break;
    case STICK: 
      if(c == stickDirections[0]){
        digitalWrite(pin, LOW);
        digitalWrite(pin+1, LOW);
      } else if(c == stickDirections[1]){
        digitalWrite(pin, HIGH);
        digitalWrite(pin+1, LOW);
      } else if(c == stickDirections[2]){
        digitalWrite(pin, LOW);
        digitalWrite(pin+1, HIGH);
      } else if(c == stickDirections[3]){
        digitalWrite(pin, HIGH);
        digitalWrite(pin+1, HIGH);
      }
    break;
    case SONIC: 
      if(c == sonicZones[0]){
        digitalWrite(pin, LOW);
        digitalWrite(pin+1, LOW);
      } else if(c == sonicZones[1]){
        digitalWrite(pin, HIGH);
        digitalWrite(pin+1, LOW);
      } else if(c == sonicZones[2]){
        digitalWrite(pin, LOW);
        digitalWrite(pin+1, HIGH);
      } else if(c == sonicZones[3]){
        digitalWrite(pin, HIGH);
        digitalWrite(pin+1, HIGH);
      }
    break;
  }
}

void setdown(){
    free(buttons);
    free(stickDirections);
    free(sonicZones);
}
