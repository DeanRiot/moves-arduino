#pragma once
#include <Arduino.h>

class Moves {
    public:
        Moves(int LeftForwardPin,int LeftBackPin, int RightForwardPin, int RightBackPin);
        void GoForward();
        void GoBack();
        void TurnRightIndependent();
        void TurnRightSteering();
        void TurnLeftIndependent();
        void TurnLeftSteering();
        void Stop();
    private:
        int _LeftForwardPin;
        int _LeftBackPin;
        int _RightForwardPin;
        int _RightBackPin;
};

