#ifndef SecondLift_h
#define SecondLift_h

#include <Arduino.h>
#include "a_Robot.h"
#include "Encoder.h"
#include "PID_v1.h"

class SecondLift
{
public:
	// CONSTRUCTORS
	SecondLift(Robot *p); // Default pin selection.

	void Task();
	void init();

	//Floats
	float LiftSpeed;

	Encoder LiftEncoder;

	int X;
	int A;
	int B;
	int XBox;

	//Bools
	bool HatOpen = false;

	void Rotate(int SetPoint);
	void Lift(float Speed);

	PID liftPID;
	double liftCurPos = 0;
	double liftSetPoint = 0;
	double liftPIDOut = 0;
	double liftCorrSetPoint = 0;

	void Prepare();

	int CBState;

	int LiftSetPoint = 0;

	bool PIDEnabled = false;
	int LiftMax = 0;
	int LiftMinReceiver = 0;
	int LiftMinMoGo = 0;

	int YPos = 0;
private:
	Robot *robot;

	int LiftSetPointReceiver = 10424;
	int LiftSetPointMoGo = 6250;
	int LiftSetPointStat = 6250;

	int LiftEncoderInt = 2;
	int LiftEncoderDig = 44;

	float LiftLimit;


	const int liftPIDTolerence = 10;
	const double liftKP = 0.7;
	const double liftKI = 0;
	const double liftKD = 0;

	

	bool MovedDown = false;
	int32_t MoveDownTimer;

};

#endif

