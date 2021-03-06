#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     leftDriveMotor, tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     rightDriveMotor, tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     armMotor,      tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    HookLeft,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    HookRight,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "motor.h"

const int hook_up = 1;
const int hook_down = 2;
short armVal;
int EncoderVal;
const short ArmMin = 0;
const short ArmMax = 11800;
short leftMotor;
short rightMotor;
short halfMXAxis;
short motorXAxis;
void initializeRobot()

{
	return;
}


task main()
{
	initializeRobot();

	waitForStart();   // wait for start of tele-op phase

	while (true)
	{
		armVal = convert_joystick_to_motor (joystick.joy2_y2);
		EncoderVal = nMotorEncoder[armMotor];
		if((EncoderVal > ArmMax && armVal < 0) || (EncoderVal < ArmMin && armVal > 0) || (EncoderVal <= ArmMax && EncoderVal >= ArmMin)){
			motor[armMotor] = armVal;
		}
		else {
			motor[armMotor] = 0;
		}

		motorXAxis = convert_joystick_to_motor(joystick.joy1_x2);
		halfMXAxis = motorXAxis / 2;
		rightMotor = convert_joystick_to_motor(joystick.joy1_y2);
		leftMotor = convert_joystick_to_motor(joystick.joy1_y2);
		if (leftMotor < 0){
			leftMotor = leftMotor*-leftMotor;
		}
		else{
			leftMotor = leftMotor*leftMotor;
		}
		if (rightMotor < 0) {
			rightMotor = rightMotor*-rightMotor;
		}
		else{
			rightMotor = rightMotor*rightMotor;
		}
		rightMotor = rightMotor + halfMXAxis;
		leftMotor = leftMotor - halfMXAxis;

		motor[leftDriveMotor] = leftMotor;
		motor[rightDriveMotor] = rightMotor;

		if(joy2Btn(hook_up) == 1){
			servo[HookRight] = 20;
			servo[HookLeft] = 205;
		}
		else if(joy2Btn(hook_down) == 1){
			servo[HookRight] = 140;
			servo[HookLeft] = 75;
		}
	}
}
