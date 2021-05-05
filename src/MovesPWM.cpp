/*
    MovesPWM.cpp - Library for implementing basic robot MovesPWM using PWM
    Created by Dmitry Tarakanovsky, May 3, 2021
    Relised into the public domain
    Methods description:
    GoForward - send robot to go forward
    GoBack - send robot to go back 
    TurnRightIndependent - turns robot right by only Right motor
    TurnRightSteering - turns robot right by left and right motor
    TurnLeftIndependent - turns robot left by only Right motor
    TurnLeftSteering - turns robot left by left and right motor
*/

#include <MovesPWM.h>


MovesPWM::MovesPWM(int LeftForwardPin,int LeftBackPin, int RightForwardPin, int RightBackPin, int freq = 250){
	if (freq>250) freq = 250;
	if (freq<0) freq = 0;
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