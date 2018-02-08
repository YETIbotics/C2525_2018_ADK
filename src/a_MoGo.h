#ifndef MoGo_h
#define MoGo_h

#include <Arduino.h>
#include "a_Robot.h"

class MoGo
{
public:
	// CONSTRUCTORS
	MoGo(Robot *p); // Default pin selection.

	void Task();
	void init();

	int TriggerAggregate;
	int RL1;

	void Move(float Speed);
	void Lift(float Speed);

private:
	Robot *robot;

	int MoGoLiftMin = 304 * 4;
	int MoGoLiftMax = 7500;

	int MoGoLiftPos = 300 * 4;

};

#endif

