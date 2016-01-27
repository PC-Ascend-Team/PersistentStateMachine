#include <EEPROM.h>

int address = 0;
int stateMachineReset = 12;
int sysLED = 13;
int waitTime = 10000; // in ms
int timer = 0;
int state;
int i;

void setup() {

  Serial.begin(9600);

  pinMode(stateMachineReset, INPUT);
  pinMode(sysLED, OUTPUT);
  
  // reset the state machine if reset button is pressed
  // uncomment when button implimented
  //if(digitalRead(stateMachineReset) == HIGH) {
    //EEPROM[address] = 0;
  //}

  // to test until button available, uncomment the next line within
  // 10s of "Running State 0: Waiting State" gets printed to Serial
  // and re-upload. Then wait for "Running State 1: Processing State"
  // to get printed to Serial and press Arduino reset button.
  // state machine should then run from state 1.
  //EEPROM[address] = 0;

  state = EEPROM[address]; // set state to stored state
  i = 0;

}

void loop() {

  switch(state) {
    
    // waiting state
    case 0:

      Serial.println("Running State 0: Waiting State");

      // blink sysLED on/off every .5s for 10s
      while(timer < waitTime) {
        // turn sysLED on for .5s
        digitalWrite(sysLED, HIGH);
        delay(500);

        // turn sysLED off for .5s
        digitalWrite(sysLED, LOW);
        delay(500);

        timer = timer + 1000; // increment timer 1s
      }

      // transition to state 1
      if(timer >= waitTime) { 
        state = 1;
        EEPROM[address] = state; // save sate
      }
      
      break;
    
    // proccessing state
    case 1:

        // turn sysLED on/off .25s forever
        while(1 > i++) {
          Serial.println("Running State 1: Processing State"); 
        }

        // turn sysLED on for .25s
        digitalWrite(sysLED, HIGH);
        delay(250);

        // turn sysLED off for .25s
        digitalWrite(sysLED, LOW);
        delay(250);
      
      break;
  }

}
