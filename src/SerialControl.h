#pragma once
#include <Arduino.h>
#include <Moves.h>
#include <MovesPWM.h>

class SerialControl {
    public:
        SerialControl(int speed);
        void ReadCommand();
        void ShowInfo();
        void SetSpeed(int speed);
        void MovesUnPWM(String command, int value[]);
        void MovesPulseWideMod(String command, int value[]);
    private:
        String info;
};

