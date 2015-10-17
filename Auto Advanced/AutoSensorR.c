#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     light,          sensorLightActive)
#pragma config(Motor,  mtr_S1_C1_1,     LeftDriveMotor, tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     RightDriveMotor, tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     RollerMotor,   tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     ArmMotor,      tmotorTetrix, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    HookLeft,             tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    HookRight,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
const float wheelDi = 2.930;
float wheelCir;
float ticksPerInch;
const float rampLength = 10;
float rampLengthTicks;
float ArmTarget = 4000;
//int lightTemp;
const int fast = 40;
const int slow = 25;
int WallThres;
int NoWall;

void initializeRobot()
{
	wheelCir=wheelDi * 3.1415926;
	ticksPerInch = 1440 / wheelCir;
	rampLengthTicks = rampLength * ticksPerInch;
	nMotorEncoder[RightDriveMotor] = 0;
	nMotorEncoder[LeftDriveMotor] = 0;
	return;
}

void DriveStop (){
	motor[LeftDriveMotor] = 0;
	motor[RightDriveMotor] = 0;
	wait1Msec(200);
}

void TurnWall() {
	int DriveSpeed = 25;

	//Back Up!
	motor[LeftDriveMotor] = -DriveSpeed;
	motor[RightDriveMotor] = -DriveSpeed;
	wait1Msec(500);
	DriveStop();
	//Turn
	motor[LeftDriveMotor] = DriveSpeed;
	motor[RightDriveMotor] = -DriveSpeed;
	wait1Msec(250);
	DriveStop();
	//Forward
	motor[LeftDriveMotor] = DriveSpeed;
	motor[RightDriveMotor] = DriveSpeed;
	wait1Msec(2000);
	DriveStop();
}

void FindWall (){
	int attempts = 0;
	int MaxAttempts = 10;
	while(attempts < MaxAttempts){
		if(SensorValue[light] < WallThres){
			TurnWall();
		}
		else {
			attempts = MaxAttempts +1;
		}
		attempts++;
	}
}

void Swing2Wall (){
	motor[LeftDriveMotor] = 0;
	motor[RightDriveMotor] = 30;
	wait1Msec(250);
	DriveStop();
}

task main()
{
	initializeRobot();

	waitForStart(); // Wait for the beginning of autonomous phase.
	WallThres = SensorValue[light]*1.1;
	NoWall = SensorValue[light];

	servo[HookLeft] = 205;
	servo[HookRight] = 20;

	//nMotorEncoderTarget[ArmMotor] = ArmTarget;
	//	motor[ArmMotor] = 50;															Put arm lift back in!!!

	nMotorEncoderTarget[RightDriveMotor] = rampLengthTicks;//
	motor[RightDriveMotor]= 100;												   //drive off
	nMotorEncoderTarget[LeftDriveMotor] = rampLengthTicks; //the ramp
	motor[LeftDriveMotor] = 100;													 //

	while(nMotorRunState[RightDriveMotor] != runStateIdle && nMotorRunState[LeftDriveMotor] != runStateIdle){
	}
	DriveStop();
	motor[ArmMotor] = 0;
	PlayImmediateTone(2500,100);
	Swing2Wall();
	FindWall();
	int count = 0;
	if(SensorValue[light] > NoWall){
		while(count<5001){
			if(SensorValue[light] < WallThres){
				//lightTemp = SensorValue[light];
				motor[LeftDriveMotor] = slow;
				motor[RightDriveMotor]  = fast;
			}
			else{
				motor[LeftDriveMotor] = fast;
				motor[RightDriveMotor] = slow;
			}
			count++;
			wait1Msec(1);
		}
		//All Stop
		DriveStop();
		PlayImmediateTone(2500,100);
		wait1Msec(500);
		PlayImmediateTone(2500,100);
		//Lift bucket to dump balls
	}
}