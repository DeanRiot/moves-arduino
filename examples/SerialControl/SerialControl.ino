#include <SerialControl.h>

SerialControl* con;

void setup() {
 //use one of standart serial speed
  con = new SerialControl(9600);
}

void loop() {
 (*con).ReadCommand();
}
//enter the "info" command in the port monitor
//to see the list of control commands
