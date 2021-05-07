/*
    SerialControl.cpp - Library for implementing basic robot Moves using Serial Comands
    Created by Dmitry Tarakanovsky, May 3, 2021
    Relised into the public domain
    Methods description:
    ShowInfo  - return about message to serial
    ReadCommand - implements simple read and parse the comand from serial
*/

#include <SerialControl.h>
int gSpeed = 0;
int leftFwdPin = 2;
int leftBkPin = 3;
int rightFwdPin = 4;
int rightBkPin = 5;

Moves* MV = new Moves(leftFwdPin,leftBkPin,rightFwdPin,rightBkPin);
MovesPWM* MVPW = new MovesPWM(leftFwdPin,leftBkPin,rightFwdPin,rightBkPin);

void SerialSwitch(int speed)
{
    if(speed == 300||
            speed == 1200 ||
            speed == 2400 ||
            speed == 4800 ||
            speed == 9600 ||
            speed == 14400 ||
            speed == 19200 ||
            speed == 28800 ||
            speed == 38400 ||
            speed == 57600 ||
            speed == 115200)
            {
                gSpeed = speed;
                Serial.begin(gSpeed);
                Serial.write("Power On\n");

            }  
            
        else return;  
}

SerialControl::SerialControl(int speed)
{
    SerialSwitch(speed);
}

void SerialControl::SetSpeed(int speed)
{
    SerialSwitch(speed);
}

void SerialControl::ShowInfo()
{
    Serial.println("__Commands Line__");
    Serial.println("{serial}");
    Serial.println("BatLVL - return battery charge status");
    Serial.println("CPI pin1,pin2,pin3,pin4; - set motor pins");
    Serial.println("Info; - show info about commands");
    Serial.println("{none pwn}");
    Serial.println("FR; - send robot to go forward");
    Serial.println("GB; - send robot to go forward");
    Serial.println("TLI; - send robot to turn left using independent system");
    Serial.println("TLS; - send robot to turn left using steering system");
    Serial.println("TRI; - send robot to turn right using independent system");
    Serial.println("TRS; - send robot to turn right using steering system");
    Serial.println("STP; - send robot to stop");
    Serial.println("{uses pwm}");
    Serial.println("TRBF,int; - send robot to go forward");
    Serial.println("TLBF,int; - send robot to go forward");
    Serial.println("FRP; - send robot to go forward");
    Serial.println("GBP; - send robot to go back");
    Serial.println("TLIP; - send robot to turn left using independent system");
    Serial.println("TLSP; - send robot to turn left using steering system");
    Serial.println("TRIP; - send robot to turn right using independent system");
    Serial.println("TRSP; - send robot to turn right using steering system");
    Serial.println("STP; - send robot to stop");
    Serial.println("SF,int; - set PWM Freq in range 0 - 250");
    Serial.println("GF; - return PWM freq value; :");
}

void SerialControl::ReadCommand()
{
    String rawCommand;

    if (Serial.available()){
        rawCommand = Serial.readStringUntil(';');
        if(rawCommand.length() < 2)
            return;

        int values[4] = { 0,0,0,0 };
        String command = "";
        String valueBuffer = "0";
        int i = 0;
        bool commandEnd = false;
        int valueIndex = 0;
        while(i != rawCommand.length())
        {
            if(rawCommand[i] == ',')
            {
                if(commandEnd)
                {
                    values[valueIndex] = valueBuffer.toInt();
                    if(valueIndex == 3)
                        break;
                    valueIndex++;
                }
                else
                    commandEnd = true;
                valueBuffer = "";
                i++;
                continue;
            }
            if(!commandEnd)
                command += rawCommand[i];
            else
                valueBuffer += rawCommand[i]; 
            i++;
        }
        values[valueIndex] = valueBuffer.toInt();
        /*
        Serial.print("Command name:\t");
        Serial.println(command);
        Serial.println(values[0]);
        for(int j=0;j<4;j++)
        {
            Serial.print(values[j]);
            if(j == 3)
                Serial.println("\t");
            else
                Serial.print("\t");
        }
        */

        if(command == "Info")
               ShowInfo();
		else if (command == "BatLVL")
		{		
                int val = analogRead(A0);
				int lvl = map(val,0,1024,0,100);
                String level = String(lvl);
				Serial.println("Battery Level is "+level+" :");			
		}
        else
        {
            MovesUnPWM(command,values);
            MovesPulseWideMod(command, values);
        }
    }
}

void SerialControl::MovesUnPWM(String command, int values[])
{
    if (command == "CPI")
    {
        delete MV;
        MV = new Moves(values[0],values[1],values[2],values[3]);
    }
    else if(command == "FR")
        MV->GoForward();
    else if(command == "GB")
        MV->GoBack();
    else if(command == "TLI")
        MV->TurnLeftIndependent();
    else if(command == "TLS")
        MV->TurnLeftSteering();
    else if(command == "TRI")
        MV->TurnLeftIndependent();        
    else if(command == "TRS")
        MV->TurnRightSteering();
    else if(command ==  "ST")
        MV->Stop();
}

void SerialControl::MovesPulseWideMod(String command, int values[])
{
    if (command.equals("CPI"))
    {
        delete MVPW;
        MVPW = new MovesPWM(values[0],values[1],values[2],values[3]);
    }
    else if(command.equals("FRP"))
    {
        Serial.print("FRP Check");
        MVPW->GoForward();
    }
    else if(command.equals("GBP")){ MVPW->GoBack();}
    else if(command.equals("TLIP")){ MVPW->TurnLeftIndependent();} 
    else if(command.equals("TLSP")){ MVPW->TurnLeftSteering();}
    else if(command.equals("TRIP")){MVPW->TurnRightIndependent();}
    else if(command.equals("TRSP")){MVPW->TurnRightSteering();}
    else if(command.equals("STP")){MVPW->Stop();}
    else if(command.equals("GF"))
    {
        String frq = String(MVPW->GetFreq());
        Serial.println("Freq is " + frq +" :");
    }
    else if(command.equals("FRSTP")){MVPW->ForceStop();}
    else if(command.equals("TRBF"))
    {
        if(values[0]>=0&&values[0]<=250)
            MVPW->TurnRightByFreq(values[0]);
    }
    else if(command.equals("TLBF"))
    {
        if(values[0]>=0&&values[0]<=250)
            MVPW->TurnLeftByFreq(values[0]);
    }

    else if(command.equals("SF"))
    {
        if(values[0]>0&&values[0]<250) 
            MVPW->SetFreq(values[0]);
    }
   // else
   // {
  //      Serial.println("404 Unknown command");
   // }

        
}
