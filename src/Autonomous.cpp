#include "Autonomous.h"

Autonomous::Autonomous(Robot *p, SecondLift *l, Drive *d, MoGo *m, Chainbar *c)
{
	robot = p;
	lift = l;
	drive = d;
	mogo = m;
	chainbar = c;
}

void Autonomous::init()
{

}

void Autonomous::Task()
{
	if (AutonomousType == 1)
	{
		RunAutonomous1(StartMillis1);
	}

//	if (Deploying)
	//{
	//	Deploy(StartMillis2);
	//}

}

void Autonomous::Deploy(int32_t StartMillis)
{
	int32_t time = millis() - StartMillis;

	if (time < 1000)
	{
		mogo->Move(255);
		//move 2lift
	}
	else if (time > 3500 && time < 4500)
	{
		lift->Lift(255);
	}
	else if (time > 4500 && time < 5000)
	{
		chainbar->CBState = 5;
		chainbar->Swing(chainbar->ChainbarStandby);
		chainbar->Rotate(chainbar->YSide);
	}
}

void Autonomous::StartAutonomous(int Autonomous, int32_t StartMillis)
{
	AutonomousType = Autonomous;
	StartMillis1 = StartMillis;
}

void Autonomous::RunAutonomous1(int32_t StartMillis)
{
	int32_t time = millis() - StartMillis;
	/*
	if (time > 3000 && time < 3500)
	{
		robot->LiftY = 3000;
		lift->YPos = 0;
		lift->PIDEnabled = true;
	}
	else if (time > 3500 && time < 5000)
	{
		lift->LiftSetPoint = lift->LiftMax - 475;
		drive->DrivePIDEnabled = true;
		drive->driveSetPoint = -7500;
	}
	*/
	



//NEWCODE
	/*
	if (time < 5000)
	{
		Deploy(StartMillis);
	}
	else if (time > 5000 && time < 7000)
	{
		chainbar->Rotate(10); //CHANGE
	}
	else if (time > 7000 && time < 7500)
	{
		chainbar->Swing(chainbar->ChainbarRightGrab);
	}
	else if (time > 7500 && time < 8500)
	{
		chainbar->Swing(chainbar->ChainbarCenter);
		chainbar->Rotate(chainbar->YSide);
	}
	else if (time > 8500 && time < 10000)
	{
		drive->DrivePIDEnabled = true;
		drive->driveSetPoint -= 1000; //CHANGE
		lift->YPos = 3;
		lift->PIDEnabled = true;
		lift->LiftSetPoint = lift->liftCurPos;
	}
	else if (time > 10000 && time < 11000)
	{
		chainbar->Swing(chainbar->ChainbarRightStandby);
	}
	else if (time > 11000 && time < 12000)
	{
		robot->OpenHats();
		lift->liftSetPoint = lift->LiftMax - 600; //Change
	}
	else if (time > 12000 && time < 12500)
	{
		lift->liftSetPoint = lift->LiftMax;
	}
	else if (time > 12500 && time < 13000)
	{
		lift->YPos = 1;
	}
	else if (time > 13000 && time < 13200)
	{
		robot->OpenHats();
	}
	else if (time > 13400 && time < 15000)
	{
		chainbar->RightPressed();
		chainbar->RightPressed();
	}
*/

}