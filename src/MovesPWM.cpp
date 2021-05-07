/*
    MovesPWM.cpp - Library for implementing basic robot MovesPWM using PWM
    Created by Dmitry Tarakanovsky, May 3, 2021
    Relised into the public domain
    Methods description:
    SetFreq(int freq) - set default PWM Freq
    GoForward - send robot to go forward
    GoBack - send robot to go back 
    TurnRightIndependent - turns robot right by only Right motor
    TurnRightSteering - turns robot right by left and right motor
    TurnLeftIndependent - turns robot left by only Right motor
    TurnLeftSteering - turns robot left by left and right motor
    TurnRightByFreq(int freq) - turn right motor by PWM Freq;
    TurnLeftByFreq(int freq)  - turn left motor by PWM Freq;
*/

#include <MovesPWM.h>


MovesPWM::MovesPWM(int LeftForwardPin,int LeftBackPin, int RightForwardPin, int RightBackPin, int freq=100){
	if (freq>250) {_freq = 250;}
	else if (freq<0) {_freq = 0;}
    else {_freq = freq;}
    pinMode(LeftForwardPin,OUTPUT);
    pinMode(LeftBackPin,OUTPUT);
    pinMode(RightForwardPin,OUTPUT);
    pinMode(RightBackPin,OUTPUT);
    _LeftForwardPin = LeftForwardPin;
    _LeftBackPin = LeftBackPin;
    _RightForwardPin = RightForwardPin;
    _RightBackPin = RightBackPin;
}

void MovesPWM::GoForward()
{
    analogWrite(_LeftBackPin,0);
    analogWrite(_RightBackPin,0);
    analogWrite(_LeftForwardPin,_freq);
    analogWrite(_RightForwardPin,_freq);
}

void MovesPWM::GoBack()
{
    analogWrite(_LeftBackPin,_freq);
    analogWrite(_RightBackPin,_freq);
    analogWrite(_LeftForwardPin,0);
    analogWrite(_RightForwardPin,0);
}

void MovesPWM::TurnRightIndependent()
{
    analogWrite(_LeftBackPin,0);
    analogWrite(_RightBackPin,0);
    analogWrite(_LeftForwardPin,0);
    analogWrite(_RightForwardPin,_freq);  
}

void MovesPWM::TurnRightSteering()
{
    analogWrite(_LeftBackPin,_freq);
    analogWrite(_RightBackPin,0);
    analogWrite(_LeftForwardPin,0);
    analogWrite(_RightForwardPin,_freq);  
}

void MovesPWM::TurnLeftIndependent()
{
    analogWrite(_LeftBackPin,0);
    analogWrite(_RightBackPin,0);
    analogWrite(_LeftForwardPin,_freq);
    analogWrite(_RightForwardPin,0);  
}

void MovesPWM::TurnLeftSteering()
{
    analogWrite(_LeftBackPin,0);
    analogWrite(_RightBackPin,_freq);
    analogWrite(_LeftForwardPin,_freq);
    analogWrite(_RightForwardPin,0);    
}

void MovesPWM::TurnRightByFreq(int freq)
{
    if (!(freq<0||freq>250))
    {
        int Rspeed;
        if (freq>125)
        {  
        analogWrite(_RightBackPin,0);
        analogWrite(_RightForwardPin,map(freq,126,250,0,250)); 
        }
        if (freq<125)
        {
        analogWrite(_RightBackPin,map(freq,0,124,0,250));
        analogWrite(_RightForwardPin,0); 
        }

        if(freq == 125)
        {
            Stop();
        }
    }
}

void MovesPWM::TurnLeftByFreq(int freq)
{
    if (!(freq<0||freq>250))
    {
        if (freq>125)
        {
        analogWrite(_LeftBackPin,0);
        analogWrite(_LeftForwardPin,map(freq,126,250,0,250));
        }
        if (freq<125)
        {
        analogWrite(_LeftBackPin,map(freq,0,124,0,250));
        analogWrite(_LeftForwardPin,0);
        }

        if(freq == 125)
        {
            Stop();
        }
    }
}

void MovesPWM::SetFreq(int freq)
{
    if (freq<0||freq>250)
    {
        Serial.println("Warning! Frequency must be in range 0 - 250");
    }
    else _freq = freq;
}

int MovesPWM::GetFreq()
{
    return _freq;
}

void MovesPWM::Stop()
{
    analogWrite(_LeftBackPin,0);
    analogWrite(_RightBackPin,0);
    analogWrite(_LeftForwardPin,0);
    analogWrite(_RightForwardPin,0);    
}

void MovesPWM::ForceStop()
{
    analogWrite(_LeftBackPin,_freq);
    analogWrite(_RightBackPin,_freq);
    analogWrite(_LeftForwardPin,_freq);
    analogWrite(_RightForwardPin,_freq);    
}