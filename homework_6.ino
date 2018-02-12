//Joshua Murray, Aaron Baker & Brian Hoffman
#include <MsTimer2.h>
#include <EEPROM.h>
#define UNIT_MEMORY_LOCATION 0
#define X_INPUT 0
//comms
#define START 'R'
#define SYNC 'S'
#define STOP 'T'

int unit;
char cmd;
bool toggle;
unsigned long timeVal;

void setup() {
  unit = EEPROM.read(UNIT_MEMORY_LOCATION);//EEPROM is programmed seperately with UNIT IDs
  timeVal = 0;//timestamp
  toggle = false;
  pinMode(13, OUTPUT);//LED for visual sync
  pinMode(1, INPUT);//Sensor input
  digitalWrite(13, LOW);//LED for visual sync
  MsTimer2::set(100, sendValues);//10hz
  Serial.begin(57600);
  Serial.flush();
}

void sendValues() {//ISR
  if(toggle){//toggle LED for visual sync
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);    
  }
  toggle = !toggle;
  Serial.print("ID:");Serial.print(unit);Serial.print(", ");Serial.print(timeVal);Serial.print(", ");Serial.println(analogRead(1));
  timeVal++;//increment timer
}

void loop() {
  if(Serial.available()) {
    cmd = Serial.read();
    switch (cmd) {
      case START:
        MsTimer2::start();
        break;
      case SYNC:
        MsTimer2::stop();
        timeVal = 0;
        MsTimer2::start();
        break;
      case STOP:
        MsTimer2::stop();
        break;
      default:
          Serial.print("==========");Serial.print(cmd);Serial.println(" is an unkown command==============");
        break;
    }
  }
}
