#include <MovesPWM.h>

MovesPWM* moves;

void setup() {
  //Use the pins to which the h-bridge
  //is connected(pwm) in scopes
  //and frequency in the range from 0 to 250 as the 5th argument.
  //If the 5th argument is not specified, the default value is 100.
  moves = new MovesPWM(3, 4, 5, 6, 250);
}

//notice:
/*all basic movement functions (except Stop) must be terminated
   before the next one is executed.
   Use the Stop function for this purpose.
*/
void loop() {
  //________basic moveset___________
  //set motors state to go foward
  moves->GoForward();
  delay(500);

  //stop motors
  moves->Stop();

  //set motors state to go back
  moves->GoBack();
  delay(500);
  moves->Stop();

  //set left motor state to go foward
  moves->TurnLeftIndependent();
  delay(500);
  moves->Stop();

  //set left motor state to go foward
  //and right motor state to go back
  moves->TurnLeftSteering();
  delay(500);
  moves->Stop();

  //set right motor state to go foward
  moves->TurnRightIndependent();
  delay(500);
  moves->Stop();

  //set right motor state to go foward
  //and left motor state to go back
  moves->TurnRightSteering();
  delay(500);
  moves->Stop();

  //________work with frequency___________

  //to get used Frequency value use code like
  int freq = moves->GetFreq();

  //to set new Frequency value use code like
  //in arg use values in range 0-250
  moves->SetFreq(125);

  //________independent control of motors with a preset frequency ___________

  //if arg greather then 125 set right motor state to go foward
  //the speed can be set in the range from 126 to 250
  //it will be work like frequency in range 0-250 on forward pin
  moves->TurnRightByFreq(200);
  delay(500);

  //if arg equals 125 set right motor state to stop
  moves->TurnRightByFreq(125);
  delay(500);

  //if arg greather then 125 set right motor state to go back
  //the speed can be set in the range from 124 to 0
  //it will be work like frequency in range 0-250 on back pin
  moves->TurnRightByFreq(62);
  delay(500);

  //if arg greather then 125 set left motor state to go foward
  //the speed can be set in the range from 126 to 250
  //it will be work like frequency in range 0-250 on forward pin
  moves->TurnLeftByFreq(200);
  delay(500);

  //if arg equals 125 set left motor state to stop
  moves->TurnLeftByFreq(125);
  delay(500);

  //if arg greather then 125 set left motor state to go back
  //the speed can be set in the range from 124 to 0
  //it will be work like frequency in range 0-250 on back pin
  moves->TurnLeftByFreq(62);
  delay(500);
}
