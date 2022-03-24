int LED1 = 2;
int LED2 = 3;
int LED3 = 4;
int SW = 9;
bool SW_state = false;

//comment by Mason
void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(SW, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Initialize all LEDs to be off
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);  
  digitalWrite(LED3, LOW);
  
  // Read from the switch
  SW_state = digitalRead(SW);

  if (SW_state == true) {
    // Turn LED1 on
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);  
    digitalWrite(LED3, LOW);
    delay(500);
    
    // Turn LED2 on        
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);  
    digitalWrite(LED3, LOW);
    delay(500);
    
    // Turn LED3 on
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);  
    digitalWrite(LED3, HIGH);
    delay(500);
  }
}
