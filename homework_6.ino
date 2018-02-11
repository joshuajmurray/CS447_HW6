//Joshua Murray, Aaron Baker & Brian Hoffman
#include <MsTimer2.h>
#define UNIT 1//change this depending on which unit you are programming
//#define UNIT 2
//#define UNIT 3
#define X_INPUT 0
#define Y_INPUT 1
#define Z_INPUT 2
#define L_INPUT 3
//comms
#define UNK 'A'


char cmd;
bool toggle;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  MsTimer2::set(1000, sendValues);
  MsTimer2::start();
  Serial.begin(57600);
  Serial.setTimeout(10);
  Serial.flush();
}

void sendValues() {
  if(toggle){
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);    
  }
  toggle = !toggle;
  Serial.print("Unit:");Serial.print(UNIT);Serial.print(", TEST:");Serial.println(millis());
}

void loop() {
  if(Serial.available()) {
    cmd = Serial.read();
    switch (cmd) {
      case UNK:
        break;
      default:
          Serial.print("==========");Serial.print(cmd);Serial.println(" is an unkown command==============");
        break;
    }
  }
}
