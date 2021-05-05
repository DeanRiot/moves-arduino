/*
    Moves.cpp - Library for implementing basic robot moves
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

#include <Moves.h>


Moves::Moves(int LeftForwardPin,int LeftBackPin, int RightForwardPin, int RightBackPin){
    pinMode(LeftForwardPin,OUTPUT);
    pinMode(LeftBackPin,OUTPUT);
    pinMode(RightForwardPin,OUTPUT);
    pinMode(RightBackPin,OUTPUT);
    _LeftForwardPin = LeftForwardPin;
    _LeftBackPin = LeftBackPin;
    _RightForwardPin = RightForwardPin;
    _RightBackPin = RightBackPin;
}

void Moves::GoForward()
{
    digitalWrite(_LeftBackPin,LOW);
    digitalWrite(_RightBackPin,LOW);
    digitalWrite(_LeftForwardPin,HIGH);
    digitalWrite(_RightForwardPin,HIGH);
}

void Moves::GoBack()
{
    digitalWrite(_LeftBackPin,HIGH);
    digitalWrite(_RightBackPin,HIGH);
    digitalWrite(_LeftForwardPin,LOW);
    digitalWrite(_RightForwardPin,LOW);
}

void Moves::TurnRightIndependent()
{
    digitalWrite(_LeftBackPin,LOW);
    digitalWrite(_RightBackPin,LOW);
    digitalWrite(_LeftForwardPin,LOW);
    digitalWrite(_RightForwardPin,HIGH);  
}

void Moves::TurnRightSteering()
{
    digitalWrite(_LeftBackPin,HIGH);
    digitalWrite(_RightBackPin,LOW);
    digitalWrite(_LeftForwardPin,LOW);
    digitalWrite(_RightForwardPin,HIGH);  
}

void Moves::TurnLeftIndependent()
{
    digitalWrite(_LeftBackPin,LOW);
    digitalWrite(_RightBackPin,LOW);
    digitalWrite(_LeftForwardPin,HIGH);
    digitalWrite(_RightForwardPin,LOW);  
}

void Moves::TurnLeftSteering()
{
    digitalWrite(_LeftBackPin,LOW);
    digitalWrite(_RightBackPin,HIGH);
    digitalWrite(_LeftForwardPin,HIGH);
    digitalWrite(_RightForwardPin,LOW);    
}

void Moves::Stop()
{
    digitalWrite(_LeftBackPin,LOW);
    digitalWrite(_RightBackPin,LOW);
    digitalWrite(_LeftForwardPin,LOW);
    digitalWrite(_RightForwardPin,LOW);    
}