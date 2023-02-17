/*Do not remove the include below*/
#include "PlutoPilot.h"
#include "Sensor.h"
#include "User.h"
#include "Utils.h"

/*The setup function is called once at Pluto's hardware startup*/

void plutoInit ()
{
	/*Add your hardware initialization code here*/
}

/*The function is called once before plutoLoop when you activate Developer
Mode*/
void onLoopStart ()
{
	/*do your one time tasks here*/
	LED.flightStatus(DEACTIVATE); /*Disable default Led behavior*/
}

/*The loop function is called in an endless loop*/
void plutoLoop ()
{
	/*Add your repeated code here*/
	if (Acceleration.getNetAcc()< 2 &&(!FlightStatus.check(FS_CRASHED)))
	/*Condition for free fall*/
	{
		Command.arm(); /*Arm the drone*/
		LED. set (RED, ON);
		LED. set (GREEN, ON);
	}
}

/*The function is called once after plutoLoop when you deactivate Developer
Mode*/
void onLoopFinish ()
{
	/*do your cleanup tasks here*/
	LED.flightStatus(ACTIVATE); /*Enable the default LED behavior*/
}