#include "a_Drive.h"
#include "a_SecondLift.h"
// Constructors ////////////////////////////////////////////////////////////////

Drive::Drive(Robot *p)
{
	robot = p;
}
void Drive::init()
{
	
	DriveRightEnc.init(DriveRightEncInt, DriveRightEncDig);
	
	drivePID.init(&driveCurPos, &drivePIDOut, &driveSetPoint, driveKP, driveKI, driveKD, DIRECT);
	driveCurPos = DriveRightEnc.read();
	drivePID.SetMode(MANUAL);
	drivePIDOut = 0;
	drivePID.SetOutputLimits(-400, 400);
	driveSetPoint = 0;

}

void Drive::DriveLeft(float Speed)
{
	robot->DriveLeftSpeed = Speed;
}

void Drive::DriveRight(float Speed)
{
	robot->DriveRightSpeed = Speed;
}


void Drive::Task()
{

	if (DrivePIDEnabled)
		drivePID.SetMode(AUTOMATIC);
	else
		drivePID.SetMode(MANUAL);

	driveCurPos = DriveRightEnc.read()*-1;

	drivePID.Compute();


	if (LeftControllerSpeedY != 0 || RightControllerSpeedY != 0 || LeftControllerSpeedX != 0 || RightControllerSpeedX != 0)
	{
		DriveRight(RightControllerSpeedY);
		DriveLeft(LeftControllerSpeedY);
	}
	else
	{
		DriveRight(0);
		DriveLeft(0);
	}

	if (DrivePIDEnabled)
	{
		DriveRight(drivePIDOut);
		DriveLeft(drivePIDOut);
	}
		
	Serial.print(" DriveRightEnc: ");
	Serial.print(DriveRightEnc.read());

	Serial.print(" DriveSetPoint: ");
	Serial.print(driveSetPoint);

}