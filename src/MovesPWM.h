#pragma once
#include <Arduino.h>

class MovesPWM {
    public:
        MovesPWM(int LeftForwardPin,int LeftBackPin, int RightForwardPin, int RightBackPin, int freq=250);
        void GoForward();
        void GoBack();
        void TurnRightIndependent();
        void TurnRightSteering();
        void TurnLeftIndependent();
        void TurnLeftSteering();
        void SetFreq(int freq);
        int GetFreq();
        void Stop();
        void ForceStop();
    private:
        int _LeftForwardPin;
        int _LeftBackPin;
        int _RightForwardPin;
        int _RightBackPin;
		int _freq;
};

