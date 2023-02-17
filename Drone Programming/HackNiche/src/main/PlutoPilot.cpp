// Do not remove the include below
#include "PlutoPilot.h"
#include "Peripheral.h"
#include "Utils.h"
#include "Math.h"
#include "User.h"
#include "Sensor.h"
#include "Control.h"
#include "Estimate.h"

//The setup function is called once at PlutoX's hardware startup
void plutoInit()
{
	//Add your hardware initialization code here
	Monitor.println("plutoInit ");
	setUserLoopFrequency(50);
}




//The function is called once before plutoLoop() when you activate developer mode
void onLoopStart()
{
	//Do your one time stuff here
	LED.flightStatus(DEACTIVATE);
	GPIO.init(Pin8, INPUT);
	Monitor.println("onLoopStart ");
}



//The loop function is called in an endless loop
void plutoLoop()
{
	Monitor.println(" ",GPIO.read(Pin8));
	//Add your repeated code here

	if(GPIO.read(Pin8) == 0){

	//	Command.arm();
		LED.set(RED, ON);
		LED.set(GREEN, OFF);
	//	LED.set(BLUE, OFF);
	}
	else{
	//	Command.arm();
		LED.set(RED, OFF);
		LED.set(GREEN, ON);
	//	LED.set(BLUE, OFF);
	}

}



//The function is called once after plutoLoop() when you deactivate developer mode
void onLoopFinish()
{
//Do your cleanup stuff here


}




