#ifndef Autonomous_h
#define Autonomous_h

#include <Arduino.h>
#include "a_Robot.h"
#include "a_SecondLift.h"
#include "a_Drive.h"
#include "a_MoGo.h"
#include "a_Chainbar.h"
class Autonomous
{

public:

	Autonomous(Robot *p, SecondLift *l, Drive *d, MoGo *m, Chainbar *c);

	void StartAutonomous(int Autonomous, int32_t StartMillis);
	void init();
	void Task();
	void Deploy(int32_t StartMillis);

	bool Deploying = false;

private:

	Robot *robot;
	SecondLift *lift;
	Drive *drive;
	MoGo *mogo;
	Chainbar *chainbar;

	//0 = none, 1 = Match
	int AutonomousType = 0;
	int32_t StartMillis1;
	int32_t StartMillis2;

	void RunAutonomous1(int32_t StartMillis);

};

#endif

