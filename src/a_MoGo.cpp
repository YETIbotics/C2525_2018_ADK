#include "a_MoGo.h"

// Constructors ////////////////////////////////////////////////////////////////

MoGo::MoGo(Robot *p)
{
	robot = p;
}
void MoGo::init()
{

}

void MoGo::Move(float Speed)
{
	robot->MoGoSpeed = Speed;
}

void MoGo::Lift(float Speed)
{
	MoGoLiftPos += Speed;
	if (MoGoLiftPos < MoGoLiftMin)
		MoGoLiftPos = MoGoLiftMin;
	if (MoGoLiftPos > MoGoLiftMax)
		MoGoLiftPos = MoGoLiftMax;
}

void MoGo::Task()
{
	if (RL1 == -1)
		Move(-400);
	else if (RL1 == 1)
		Move(400);
	else
		Move(0);

	if (TriggerAggregate > 200)
		Lift(1000);
	else if (TriggerAggregate < -200)
		Lift(-1000);
	else
		Lift(0);

	robot->MoGoLiftSpeed = MoGoLiftPos;
	Serial.println(MoGoLiftPos);

}
