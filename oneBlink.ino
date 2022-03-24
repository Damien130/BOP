//Shreya Khanal
int LED1 = 8;
int SW = 9;
bool SW_state = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(SW, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:

  // Read from the switch
  SW_state = digitalRead(SW);

  if (SW_state == true) {
    // Turn LED1 on
    digitalWrite(LED1, HIGH);
    delay(500); 
     
    // Turn LED1 off           
    digitalWrite(LED1, LOW);
    delay(500); 
  }
}
