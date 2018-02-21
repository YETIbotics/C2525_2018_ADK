#ifndef Chainbar_h
#define Chainbar_h

#include <Arduino.h>
#include "a_Robot.h"

class Chainbar
{
public:
	// CONSTRUCTORS
	Chainbar(Robot *p); // Default pin selection.

	void Task();
	void init();
	
	int DPadLeftRight;

	//Bools
	bool HatOpen = false;

	int HatButton;

	void Rotate(float SetPoint);
	void Swing(float SetPoint);
	void HatRelease();

	int CBState = 5;


	//Set Points

	int ChainbarLeftStandby = 3800;
	int ChainbarLeftGrab = 2500;
	int ChainbarRightStandby = 8250;
	int ChainbarRightGrab = 9000;
	int ChainbarCenter = 6000;
	int ChainbarStandby = 4470;

	void RightPressed();
	void LeftPressed();
	void UpPressed();
	void DownPressed();

	int YForward = 700 * 4;
	int YSide = 1340 * 4;



private:
	Robot *robot;




	int32_t CBTimerGrab = 0;
	int32_t CBTimerRelease = 0;

	bool CBMove = false;



};

#endif

