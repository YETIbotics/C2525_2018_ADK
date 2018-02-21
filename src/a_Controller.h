#ifndef Controller_h
#define Controller_h

#include <Arduino.h>
#include "XBOXRECV.h"


class Controller
{
public:
	// CONSTRUCTORS
	Controller();
	Controller(USB *pUsb); // Default pin selection.

	void Task();


	float LeftJoystickY;
	float LeftJoystickX;
	float RightJoystickY;
	float RightJoystickX;
	float TriggerAggregate;
	int LR2Aggregate;

	int StartButton;

	int DPadLeftRight;
	int DPadLeftRightClick;
	int APress;
	int YPress;
	int BPress;
	int XPress;
	int AClick;
	int BClick;
	int XClick;
	int YClick;
	int BackClick;
	int XBoxClick;


private:

	XBOXRECV Xbox;
	const int joystickMinThresh = 5500;
	USB dummyXboxPointer;

};

#endif