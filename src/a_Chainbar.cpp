#include "a_Chainbar.h"

// Constructors ////////////////////////////////////////////////////////////////

Chainbar::Chainbar(Robot *p)
{
	robot = p;
}
void Chainbar::init()
{

}

void Chainbar::Rotate(float SetPoint)
{
	robot->ChainbarY = SetPoint;
}

void Chainbar::Swing(float SetPoint)
{
	robot->ChainbarX = SetPoint;
}

void Chainbar::HatRelease()
{
	robot->OpenHats();
}

void Chainbar::LeftPressed()
{
	if (!CBMove)
	{
		if (CBState == 0 || CBState == 4 || CBState == 2 || CBState == 5)
		{
			Swing(ChainbarLeftStandby);
			CBState = 1;
		}
		else if (CBState == 3)
		{
			Swing(ChainbarCenter);
			CBState = 0;
			//ChainbarY = ChainbarForward(Something)
		}
		else
		{
			Swing(ChainbarLeftGrab);
			CBTimerGrab = millis();
			CBMove = true;
		}
	}
	
}

void Chainbar::RightPressed()
{

	if (!CBMove)
	{
		if (CBState == 0 || CBState == 4 || CBState == 1 || CBState == 5)
		{
			Swing(ChainbarRightStandby);
			CBState = 2;
		}
		else if (CBState == 3)
		{
			Swing(ChainbarCenter);
			//ChainbarY = ChainbarForward(Something)
		}
		else
		{
			Swing(ChainbarRightGrab);
			CBTimerGrab = millis();
			CBMove = true;
		}
	}
}

void Chainbar::UpPressed()
{
	/*Grab from front*/

}


void Chainbar::DownPressed()
{
	CBState = 5;
	Swing(ChainbarStandby);
}

void Chainbar::Task()
{
	//CBState 0 = Neutral, 1 = LeftStandby, 2 = RightStandby, 3 = FrontStandby, 4 = StandbyStage, 5 = Standby

	if (DPadLeftRight == 1)
		RightPressed();
	if (DPadLeftRight == -1)
		LeftPressed();
	if (DPadLeftRight == 2)
		UpPressed();
	if (DPadLeftRight == -2)
		DownPressed();


	if (millis() - CBTimerGrab > 500 && millis() > 1000)
	{
		CBTimerGrab = 0;
		if (CBMove)
		{
			CBState = 0;
			CBMove = false;
			Swing(ChainbarCenter);
			CBTimerRelease = millis();
		}
	}

	if (millis() - CBTimerRelease > 1000 && millis() - CBTimerRelease < 1200 && millis() > 1300)
	{
		HatRelease();
	}
	else if (millis() - CBTimerRelease > 1200 && millis() - CBTimerRelease < 1500 && millis() > 1600)
	{
		CBState = 4;
		Swing(ChainbarStandby);
	}
	
	
	
	if (HatButton == 1)
		HatRelease();
	/*
	Serial.print("CBState: ");
	Serial.println(CBState);
	Serial.print("Controller: ");
	Serial.println(DPadLeftRight);
	Serial.print("CBTimer: ");
	Serial.println(CBTimer);
	Serial.print("CBMove");
	Serial.println(CBMove);
	*/


}
