#include "a_SecondLift.h"

// Constructors ////////////////////////////////////////////////////////////////

SecondLift::SecondLift(Robot *p)
{
	robot = p;
}
void SecondLift::init()
{
	LiftLimit = 0.5;
	
	LiftEncoder.init(LiftEncoderInt, LiftEncoderDig);

	liftPID.init(&liftCurPos, &liftPIDOut, &liftSetPoint, liftKP, liftKI, liftKD, DIRECT);
	liftCurPos = LiftEncoder.read();
	liftPID.SetMode(MANUAL);
	liftPIDOut = 0;
	liftPID.SetOutputLimits(-400 * 0.5, 400);
	liftSetPoint = 1000;
}

void SecondLift::Rotate(int SetPoint)
{
	robot->LiftY = SetPoint;
}

void SecondLift::Lift(float Speed)
{
	robot->SecondLiftSpeed = Speed;
}

void SecondLift::Task()
{

	liftCurPos = LiftEncoder.read() * -1;

	if (liftCurPos > LiftMax)
	{
		LiftMax = liftCurPos;
	}

	LiftMinReceiver = LiftMax - 1800;
	LiftMinMoGo = LiftMax - 1400;

	liftPID.Compute();

	Lift(liftPIDOut);

	if (A && !PIDEnabled)
		Lift(-400 * LiftLimit);
	else if (B && !PIDEnabled)
		Lift(400);
	else if (!PIDEnabled)
		Lift(0);

	if (XBox)
	{
		PIDEnabled = !PIDEnabled;
		liftSetPoint = liftCurPos;
	}

	if (A && PIDEnabled)
	{
		if (YPos == 2)
			liftSetPoint = LiftMinReceiver;
		if (YPos == 1)
			liftSetPoint = LiftMinMoGo;
	}

	if (B && PIDEnabled)
	{
		liftSetPoint = LiftMax;
	}

	if (X)
	{
		if (YPos == 0 || YPos == 1)
		{
			YPos = 2;
		}
		else if (YPos == 2)
		{
			YPos = 1;
		}
	}

	if (PIDEnabled)
		liftPID.SetMode(AUTOMATIC);
	else
		liftPID.SetMode(MANUAL);
		

	if (YPos == 1)
		Rotate(LiftSetPointMoGo);
	else if (YPos == 2)
		Rotate(LiftSetPointReceiver);
	else if (YPos == 3)
		Rotate(LiftSetPointStat);

	Serial.print(" LiftEncoder: ");
	Serial.print(LiftEncoder.read());

	
	if (CBState == 0)
	{
		PIDEnabled = true;
		liftSetPoint = LiftMax;
		YPos = 2;
		MovedDown = false;
	}
	else if (CBState == 4 && !MovedDown)
	{
		liftSetPoint = LiftMinReceiver;
		MovedDown = true;
		MoveDownTimer = millis();
	}


	if (millis() - MoveDownTimer > 750 && millis() - MoveDownTimer < 900)
	{
		liftSetPoint = LiftMax;
		liftPID.SetTunings(1.5, 0, 0);
	}

	if (millis() - MoveDownTimer > 1500 && millis() - MoveDownTimer < 1600)
	{
		YPos = 1;
	}

	if (millis() - MoveDownTimer > 2400 && millis() - MoveDownTimer < 2500)
	{
		liftSetPoint = LiftMinMoGo;
		liftPID.SetTunings(0.7, 0, 0);
	}

	if (millis() - MoveDownTimer > 3100 && millis() - MoveDownTimer < 3500)
	{
		robot->OpenHats();
	}

	if (millis() - MoveDownTimer > 3400 && millis() - MoveDownTimer < 4400)
	{
		liftSetPoint = LiftMax;
	}





}

