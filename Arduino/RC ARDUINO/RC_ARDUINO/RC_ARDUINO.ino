/*
RC Arduino Robot FR Sky interface

--------------
|Description:|
--------------
This code connects an FRSKY Reciever to 2 DC Motors for controlling a robot.


--------------
|CONNECTIONS:|
--------------

Motor Shield: Cytron SHIELD-MDD10
---------------------------------------
Arduino D3  - Motor Driver PWM 1 Input
Arduino D4  - Motor Driver DIR 1 Input
Arduino D9 - Motor Driver PWM 2 Input
Arduino D10 - Motor Driver DIR 2 Input

RC Interface: FR Sky FS-iA6B
---------------------------------------
Arduino D5  - Steering
Arduino D6  - Throttle
Arduino D7  - Elevator (Unused)


AUTHOR: Ryan McGuire
DATE: 6/4/2020

 */

 #include <Servo.h>     //Servo library
 #include "CytronMotorDriver.h" //Motor Shield Library


//Input Variables
//---------------
int ch1; // Steering
int steer;

int ch2; // Throttle
int throt;

int ch5; // KillSwitch
int kill;

int ch6; // Serial Delay
int pause;


//Output Variables
//----------------
CytronMD motor1(PWM_DIR, 9, 8);   // PWM1 = Pin 9 , DIR1 = Pin 8.
CytronMD motor2(PWM_DIR, 11, 13); // PWM2 = Pin 11, DIR2 = Pin 13.






//Servp Variables TEMPORARY
Servo servo_test;      //initialize a servo object for the connected servo            
int angle = 0;    

void setup() {

  
  pinMode(22, INPUT); // Set our input pins as such
  pinMode(23, INPUT);
  pinMode(41, INPUT); // Set our input pins as such
  pinMode(24, INPUT);


  servo_test.attach(31); 
  
  Serial.begin(19200); // Pour a bowl of Serial

}

void loop() {
  //Read Knob
  ch6 = pulseIn(41, HIGH, 25000); // Read the pulse width of Channel 1
  if(ch6<1000)
    {ch6=1000;}
  pause=map(ch6, 1000,2200,1,5000);
  
  //Read KillSwitch
  ch5 = pulseIn(24, HIGH, 25000); // Read the pulse width of Channel 1
  
  if (ch5>1800) //Check for killswitch and failsafe.
    { Serial.println("Failsafe");
    }else{
      //Read Steering
      ch1 = pulseIn(22, HIGH, 25000); // Read the pulse width of Channel 1
      //Add Steering Deadband
      if (ch1<1550 && ch1>1450)
        {ch1=1500;}
      steer=map(ch1, 1000,2000,-500,500);
      
      //Read Throttle
      ch2 = pulseIn(23, HIGH, 25000);// Read the pulse width of Channel 2
      if (ch2<1550 && ch2>1450)
        {ch2=1500;}
      throt=map(ch2, 1000,2000,-500,500);
    
    
    
    
      Serial.print("Ch1  : ");
      Serial.println(ch1);
      
      Serial.print("Steer: ");
      Serial.println(steer);
      
      Serial.print("Ch2  : ");
      Serial.println(ch2);
      
      Serial.print("Throt: ");
      Serial.println(throt);
      
      Serial.print("Ch5  : ");
      Serial.println(ch5);

      Serial.print("Ch6  : ");
      Serial.println(ch6);

      
    
      //Throttle Control
      motor1.setSpeed(map(throt,0,100,0,128));
      motor2.setSpeed(map(throt,0,100,0,128));
    
      angle = map(steer, -500, 500, 0, 179);     // scaling the potentiometer value to angle value for servo between 0 and 180) 
      servo_test.write(angle);                   //command to rotate the servo to the specified angle 
      Serial.print("Ang  : ");
      Serial.println(angle);
  }
    
  Serial.println(" ");
  delay(pause); // I put this here just to make the terminal 
              // window happier
}

void mixing() {
  
}
