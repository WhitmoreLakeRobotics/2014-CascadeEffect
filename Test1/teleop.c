#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     RightDriveMotor, tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     LeftDriveMotor, tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     RollerMotor1,   tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     ArmMotor1,     tmotorTetrix, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "motor.h"


float motorXAxis;
float leftMotor;
float rightMotor;
float halfMXAxis;
//const int roller = 2;
const short ArmMin = 0;
const short ArmMax = 2000;
//const int hookDown = 1;
//const int hookUp = 3;
short ArmVal;
int EncoderVal;

void initializeRobot()
{
	//wait1Msec(500);
	//disableDiagnosticsDisplay();
	//nMotorEncoder[ArmMotor1] = ArmMin;
	//servo[servo1] = 0;
	return;
}

//task hook (){
//	while (true){
//		if(joy1Btn(hookUp) == 1){
//			servoTarget[servo2] = 255;
//		}
//	 //nxtDisplayCenteredTextLine(2, "S1 = %d", ServoValue[servo1]);
//		if(joy1Btn(hookDown) == 1){
//			servo[servo2] = 0;
//		}
//	}
//}

//task ArmThings (){

//}

task drive (){
	while (true)
	{
		motorXAxis = convert_joystick_to_motor (joystick.joy1_y2);
		halfMXAxis = motorXAxis / 2;
		rightMotor = convert_joystick_to_motor (joystick.joy1_x2);
		rightMotor = rightMotor - halfMXAxis;
		leftMotor = convert_joystick_to_motor (joystick.joy1_x2);
		leftMotor = leftMotor + halfMXAxis;
		motor[LeftDriveMotor] = -leftMotor;
		motor[RightDriveMotor] = -rightMotor;
	}
}

task main()
{
	initializeRobot();

	waitForStart();   // wait for start of tele-op phase
	//StartTask(ArmThings);
	//StartTask(hook);
	StartTask(drive);
	while(true){

		//ArmVal = convert_joystick_to_motor (joystick.joy2_y1);
		ArmVal = joystick.joy2_y1;
		EncoderVal = nMotorEncoder[ArmMotor1];

		nxtDisplayTextLine(2, "Encoder %d",EncoderVal);
		nxtDisplayTextLine(3, "Arm %d",ArmVal);

		if((EncoderVal > ArmMax && ArmVal < 0) || (EncoderVal < ArmMin && ArmVal > 0) || (EncoderVal <= ArmMax && EncoderVal >= ArmMin)){
			motor[ArmMotor1] = ArmVal;
		}
		else {
			motor[ArmMotor1] = 0;
		}


		//if(joy2Btn(roller) == 1){
		//	motor[RollerMotor] = 100;
		//	wait1Msec(500);
		//}
		//else {
		//	motor[RollerMotor] = 0;
		//}
	}
	//wait1Msec(300000);
}
