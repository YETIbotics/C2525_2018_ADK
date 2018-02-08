#ifndef Drive_h
#define Drive_h

#include <Arduino.h>
#include "a_Robot.h"
#include "Encoder.h"
#include "PID_v1.h"

class Drive
{
public:
	// CONSTRUCTORS
	Drive(Robot *p); // Default pin selection.

	void Task();
	void init();

	//Floats
	float LeftControllerSpeedY;
	float LeftControllerSpeedX;
	float RightControllerSpeedY;
	float RightControllerSpeedX;

	Encoder DriveRightEnc;

	void DriveLeft(float Speed);
	void DriveRight(float Speed);

	PID drivePID;
	double driveCurPos = 0;
	double driveSetPoint = 0;
	double drivePIDOut = 0;
	double driveCorrSetPoint = 0;

	bool DrivePIDEnabled = false;
private:
	Robot *robot;

	int DriveRightEncInt = 3;
	int DriveRightEncDig = 45;


	int DriveSetPoint = 0;

	bool _drivePIDEnabled = false;
	const int drivePIDTolerence = 10;
	const double driveKP = 0.2;
	const double driveKI = 0;
	const double driveKD = 0;


};

#endif
