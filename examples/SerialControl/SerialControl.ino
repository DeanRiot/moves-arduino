#include <SerialControl.h>

SerialControl* con;

void setup() {
  // put your setup code here, to run once:
  con = new SerialControl(9600);
}

void loop() {
 
 (*con).ReadCommand();
}
