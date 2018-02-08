#include "a_Robot.h"
#include "a_Controller.h"
#include "a_Drive.h"
#include "a_SecondLift.h"
#include "a_Chainbar.h"
#include "a_MoGo.h"
#include "Autonomous.h"
#include <Wire.h>
#define LightSensorPin A6


Robot robot;

Controller controller(&robot.Usb);
Drive drive(&robot);
SecondLift secondLift(&robot);
Chainbar chainbar(&robot);
MoGo moGo(&robot);

Autonomous autonomous(&robot, &secondLift, &drive, &moGo, &chainbar);

void runRobot();
void MapRobot();

void setup()
{
	Serial.begin(115200);
	
	while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection

	robot.init();
	drive.init();
	secondLift.init();
	moGo.init();
	chainbar.init();
	autonomous.init();
}

unsigned long lastRunTime = millis();

void loop()
{
    if(millis() - lastRunTime >= 20)
    {
        runRobot();
    }

    //Task the USB every loop.
	robot.TaskUSB();
}


void runRobot()
{
	robot.Read();
	MapRobot();

	drive.Task();
	secondLift.Task();
	moGo.Task();
	chainbar.Task();

	controller.Task();

	robot.Write();
	//cv.Task();

	autonomous.Task();
	
	Serial.print(" Light Sensor: ");
	Serial.print(analogRead(LightSensorPin));
	

}

void MapRobot()
{
	drive.LeftControllerSpeedY = controller.LeftJoystickY;
	drive.LeftControllerSpeedX = controller.LeftJoystickX;
	drive.RightControllerSpeedY = controller.RightJoystickY;
	drive.RightControllerSpeedX = controller.RightJoystickX;

	moGo.TriggerAggregate = controller.TriggerAggregate;
	moGo.RL1 = controller.LR2Aggregate;
	
	secondLift.X = controller.XClick;
	secondLift.A = controller.APress;
	secondLift.B = controller.BPress;
	secondLift.XBox = controller.BackClick;
	secondLift.CBState = chainbar.CBState;

	chainbar.DPadLeftRight = controller.DPadLeftRightClick;
	chainbar.HatButton = controller.YClick;

	if (controller.XBoxClick)
	{
		autonomous.StartAutonomous(1, millis());
	}

	if (controller.StartButton)
	{
		drive.DrivePIDEnabled = false;
		secondLift.PIDEnabled = false;
	}


}
