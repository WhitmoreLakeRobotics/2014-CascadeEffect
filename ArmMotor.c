#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Sensor, S2,     TouchSensor,    sensorTouch)
#pragma config(Motor,  motorA,          armMotor,      tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int currentspeed = 30;
task main()
{
	motor[armMotor] = currentspeed;
	wait10Msec(1000);
	/*	while(true){
	if(SensorValue[TouchSensor] == 1){
	wait1Msec(100); //?
	currentspeed = currentspeed + 30;
	if(currentspeed == 120){
	currentspeed = 30;
	}
	motor[armMotor] = currentspeed;
	}
	}*/
}
