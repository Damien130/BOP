//Mason Dill
//Using libraries time and time alarm

unsigned long c_time;
unsigned long last_c_time;
volatile byte state = HIGH;

unsigned int roundTime;

unsigned int playerScore;
bool gameOver;

enum devices {BUTTONS, STICK, SONIC};
enum color {RED, GREEN, BLUE, YELLOW};

//prototypes
void muxByColor(enum color num, int pin);
void muxByDevice(enum devices d, int pin);
void score();

void setdown();

void setup() {
  interrupts();
  pinMode(2, INPUT); //intterupt pin                PHYSICAL PIN 4
  attachInterrupt(digitalPinToInterrupt(2), score, HIGH);
  
  pinMode(7, OUTPUT); //color mux                   PHYSICAL PIN 13
  pinMode(8, OUTPUT); //AKA secondary Mux           PHYSICAL PIN 14

  pinMode(12, OUTPUT); //device mux                 PHYSICAL PIN 18
  pinMode(13, OUTPUT); //AKA Master mux             PHYSICAL PIN 19

  pinMode(11, OUTPUT); //Notify BCD to increment    PHYSICAL PIN 17
  pinMode(10, OUTPUT); //speaker sound signal       PHYSICAL PIN 16
  
  //randomSeed(analogRead(0)); //generate random seed from noise

  c_time = 0;
  last_c_time = millis();
  roundTime  = 4000;
  playerScore = 0;
  gameOver = false;
}

void score(){
  //check to see if addToScore() was called in the last 250 milliseconds
  if (last_c_time < c_time){
    state = LOW;
    digitalWrite(11, LOW); //this will increment the BCD; adds 1 to score display
    playerScore++;
    last_c_time = millis();
   }
   if(playerScore < 100)
    gameOver = false;
}

void loop() {
  if(gameOver){
    //disconnect interrupt pin from all input devices
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    
    //Game will become stuck in this loop if addToScore is not called at the end of this function 
    return;
  }
  gameOver = true;
  //select a random device
  enum devices curD = (enum devices)random(3);
  
  //select a random color 
  enum color curC = (enum color)random(0, 4);;

  muxByColor(curC, 7);//display color to user, mux by interaction
  muxByDevice(curD, 12);//mux by device
  playSound(curD, 16);
   
   c_time = millis();
   delay(roundTime);

   //minimum round time = 500 ms
   if(roundTime > 500)
      roundTime -= 50;
   digitalWrite(11, HIGH);
}

void playSound(enum devices d, int pin){
  switch(d){
    case BUTTONS: analogWrite(pin, 100);
      break;
    case STICK: analogWrite(pin, 170);
      break;
    case SONIC: analogWrite(pin, 250);
      break;
  }
}

void muxByColor(enum color num, int pin){
  switch(num){
    case RED: 
    digitalWrite(pin, LOW);
    digitalWrite(pin+1, LOW);
    break;
    case GREEN:
    digitalWrite(pin, HIGH);
    digitalWrite(pin+1, LOW);
    break;
    case BLUE:
    digitalWrite(pin, LOW);
    digitalWrite(pin+1, HIGH);
    break;
    case YELLOW:
    digitalWrite(pin, HIGH);
    digitalWrite(pin+1, HIGH);
  }
}

void muxByDevice(enum devices d, int pin){
  if (d == BUTTONS){
      digitalWrite(pin, HIGH);
      digitalWrite(pin+1, LOW);
    } else if (d == STICK){
      digitalWrite(pin, LOW);
      digitalWrite(pin+1, HIGH);
    } else if (d == SONIC){
      digitalWrite(pin, HIGH);
      digitalWrite(pin+1, HIGH);
    }
}
