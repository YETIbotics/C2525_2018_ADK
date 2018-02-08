
#include "a_Robot.h"
// Constructors ////////////////////////////////////////////////////////////////

#define maestroSerial Serial1

MiniMaestro maestro(maestroSerial);

Robot::Robot()

{
	Usb.Init();
	mc.init();

	prevDriveRightSpeed = 0;
	prevDriveLeftSpeed = 0;

}

void Robot::init() 
{
	
	maestroSerial.begin(9600);


	maestro.setAcceleration(0, 0);
	//maestro.setSpeed(0, 10);

	maestro.setAcceleration(1, 10);
	maestro.setSpeed(1, 10);

	maestro.setAcceleration(2, 20);
	//maestro.setSpeed(2, 10);

	maestro.setTarget(1, ChainbarY);
	maestro.setTarget(0, ChainbarX);
	maestro.setTarget(2, LiftY);


	maestro.setSpeed(0, 0);
	maestro.setSpeed(1, 0);
	maestro.setSpeed(2, 0);

	
}

void Robot::TaskUSB()
{
	Usb.Task();
}

void Robot::OpenHats()
{
	ChainbarHat = servoMax * 3 / 4;
	LiftHats = servoMax * 3 / 4;
	HatTimer = millis();
}

void Robot::Read() 
{
	
}

void Robot::Write() 
{
	//DriveRightSpeed
	if (DriveRightSpeed < -400)
		DriveRightSpeed = -400;
	if (DriveRightSpeed > 400)
		DriveRightSpeed = 400;

	DriveRightSpeed = map(DriveRightSpeed, -400, 400, -255, 255);

	mc.setMotorSpeed(4, DriveRightSpeed);

	//Serial.print(DriveRightSpeed);
	//Serial.print("\t");

	//DriveLeftSpeed
	if (DriveLeftSpeed < -400)
		DriveLeftSpeed = -400;
	if (DriveLeftSpeed > 400)
		DriveLeftSpeed = 400;

	DriveLeftSpeed = map(DriveLeftSpeed, -400, 400, -255, 255);

	mc.setMotorSpeed(5, DriveLeftSpeed);
	//Serial.print(DriveLeftSpeed);
	//Serial.print("\t");

	if (SecondLiftSpeed < -400)
		SecondLiftSpeed = -400;
	if (SecondLiftSpeed > 400)
		SecondLiftSpeed = 400;

	SecondLiftSpeed = map(SecondLiftSpeed, -400, 400, -255, 255);

	mc.setMotorSpeed(2, SecondLiftSpeed);

	if (MoGoSpeed < -400)
		MoGoSpeed = -400;
	if (MoGoSpeed > 400)
		MoGoSpeed = 400;

	MoGoSpeed = map(MoGoSpeed, -400, 400, -255, 255);

	mc.setMotorSpeed(3, MoGoSpeed);


	if (millis() - HatTimer > 250)
	{
		ChainbarHat = servoMin;
		LiftHats = servoMin;
	}
	
	maestro.setTarget(1, ChainbarY);
	maestro.setTarget(0, ChainbarX);
	maestro.setTarget(2, LiftY);

	maestro.setTarget(3, ChainbarHat);
	maestro.setTarget(4, LiftHats);

	maestro.setTarget(5, MoGoLiftSpeed);

	Serial.print(" LiftY: ");
	Serial.print(LiftY);

}

