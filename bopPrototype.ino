//Mason Dill
//Using libraries time and time alarm

unsigned long c_time;
unsigned long last_c_time;
volatile byte state = LOW;

unsigned int roundTime;

unsigned int score;

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

void setdown();

void setup() {
  interrupts();
  
  pinMode(2, INPUT); //button interrupt
  pinMode(3, INPUT); //joystick interrupt
  
  pinMode(10, INPUT); //analog stick intterupt

  attachInterrupt(digitalPinToInterrupt(2), addToScore, HIGH);
  //attachInterrupt(digitalPinToInterrupt(3), addToScore, LOW);
  interrupts();
  pinMode(7, OUTPUT); //which color to display at round begin
  pinMode(8, OUTPUT);

  pinMode(12, OUTPUT); //color select
  pinMode(13, OUTPUT);

  pinMode(11, OUTPUT); //notify success
  
  randomSeed(analogRead(0)); //generate random seed from noise

  c_time = 0;
  last_c_time = millis();
  roundTime  = 4000;
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
  //shuffle(buttons, 4);
  shuffle(stickDirections, 4);
  shuffle(sonicZones, 4);

  //initialize deviceOrder
  deviceOrder = (enum devices*)malloc(sizeof(enum devices) * 3);
  for(int i = 0; i < 3; i++){
      deviceOrder[i] = (enum devices)i;
  }
  shuffle((enum color*)deviceOrder, 3);

  //display current setup
  /*int displayColorPin = 3, interactionPin = 1, displayPin = 0;
  digitalWrite(displayPin, HIGH);
  
  for(int i = 0; i < 3; i++){
    //play pitch i where deviceOrder = i
    for(int j = 0; j < 4; j++){
      numToMux(j, interactionPin); //select interaction
      muxByColor(buttons[j], (enum devices)i, displayColorPin);
    }
    delay(2000); //wait for 2 s
  }
  digitalWrite(displayPin, LOW);
  */
}

void addToScore(){
  //check to see if addToScore() was called in the last 250 milliseconds
  if (last_c_time < c_time){
    state = LOW;
    digitalWrite(11, HIGH);
    score++;
    //write score to hex
    last_c_time = millis();
   }
}

void loop() {
  //select a random device
  //enum devices curD = (enum devices)random(3);
  enum devices curD = BUTTONS; //for testing
  //select a random color 
  enum color curC = (enum color)random(0, 4);;

  numToMux((int)curC, 7);//display color to user
  muxByColor(curC, curD, 12); //mux button assigned to color
  //playSound

  //delay(2000);

   //set up interupt dynamically
   
   switch(curD){
    case BUTTONS: attachInterrupt(digitalPinToInterrupt(2), addToScore, HIGH);
    break;
    case STICK: attachInterrupt(digitalPinToInterrupt(2), addToScore, HIGH);
    break;
    case SONIC: ;
   }
   
   c_time = millis();
   delay(roundTime);
   //roundTime -= 50;
   
   //tear down interupt
    detachInterrupt(digitalPinToInterrupt(2));
    //detachInterrupt(digitalPinToInterrupt(10));
    //detachInterrupt(digitalPinToInterrupt(9));
    
    digitalWrite(11, LOW);
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
    digitalWrite(pin+1, LOW);
    break;
    case 1:
    digitalWrite(pin, HIGH);
    digitalWrite(pin+1, LOW);
    break;
    case 2:
    digitalWrite(pin, LOW);
    digitalWrite(pin+1, HIGH);
    break;
    case 3:
    digitalWrite(pin, HIGH);
    digitalWrite(pin+1, HIGH);
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
