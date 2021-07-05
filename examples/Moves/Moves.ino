#include <Moves.h>

Moves* moves;

void setup() {
  //Use the pins to which the h-bridge
  //is connected(pwm) in scopes
  moves = new Moves(3,4,5,6);
}

//notice:
/*all movement functions (except Stop) must be terminated 
 * before the next one is executed. 
 * Use the Stop function for this purpose.
 */
void loop() {
        //stop motors
        moves->Stop();
        //set motors state to go foward
        moves->GoForward();
        //set motors state to go back
        moves->GoBack();
        //set left motor state to go foward
        moves->TurnLeftIndependent();
        //set left motor state to go foward
        //and right motor state to go back
        moves->TurnLeftSteering();
        //set right motor state to go foward
        moves->TurnRightIndependent();
        //set right motor state to go foward
        //and left motor state to go back        
        moves->TurnRightSteering();
}
