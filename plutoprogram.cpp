#include "PlutoPilot.h"
#include "Peripheral.h"
#include "Utils.h"
#include "Math.h"
#include "User.h"
#include "Sensor.h"
#include "Control.h"
#include "Estimate.h"
uint32_t var=0;
bool detected = false;
uint32_t rollback = 0;
//The setup function is called once at PlutoX's hardware startup
void plutolnit()
{
//Add your hardware initialization code here
setUserLoopFrequency(50);
}
//The function is called once before plutoLoop() when you activate
void onLoopStart()
{
//Do your one time stuff here
Command.arm();
Command.takeOff(200);
var = 0;
GPIO.init(Pin8, INPUT);
LED.flightStatus(DEACTIVATE);
rollback = OQ;
detected = false;
}
//The loop function is called in an endless loop
void plutoLoop()
{
if(detected) {
if(rollback < 750) {
RcCommand.set(RC_ROLL, 1400);
rollback += 50;
}
else if(rollback < 1900) {
RcCommand.set(RC_ROLL, 1540);
rollback += 50;
if(rollback > 2200) {
detected = false;
rollback = OQ;
}
}
if(rollback==1900){
RcCommand.set(RC_ROLL, 1500);
detected=false;
rollback=0;
var=6001;
}
//RcCommand.set(RC_ROLL,1480);
}
else if(GPIO.read(Pin8) == 0 && !detected) {
detected = true;
rollback = O;
}
else{
if(var < 3500){
var=var+50;
RcCommand.set(RC_PITCH,1500);
RcCommand.set(RC_ROLL, 1510);
RcCommand.set(RC_YAW, 1500);
//RcCommand.set(RC_THROTTLE,1520);
}
else if(var < 5000) {
RcCommand.set(RC_PITCH, 1500);
RcCommand.set(RC_ROLL, 1490);
RcCommand.set(RC_YAW, 1500);
//RcCommand.set(RC_THROTTLE,1520);
var=var+50;
}
else if(var < 6000) {
var=var+50;
RcCommand.set(RC_PITCH,1500);
RcCommand.set(RC_ROLL, 1500);
RcCommand.set(RC_YAW, 1500);
//RcCommand.set(RC_THROTTLE,1520);
}
else {
if(DesiredAngle.get(AG_ROLL) >0 ) {
RcCommand.set(RC_PITCH,1500);
RcCommand.set(RC_ROLL, 1490);
RcCommand.set(RC_YAW, 1500);
}
else if(DesiredAngle.get(AG_ROLL) < 0) {
RcCommand.set(RC_PITCH,1500);
RcCommand.set(RC_ROLL, 1510);
RcCommand.set(RC_YAW, 1500);
}
else if(DesiredAngle.get(AG_PITCH) > 0) {
RcCommand.set(RC_PITCH,1500);
RcCommand.set(RC_ROLL, 1490);
RcCommand.set(RC_YAW, 1500);
}
else if(DesiredAngle.get(AG_PITCH) < 0) {
RcCommand.set(RC_PITCH,1500);
RcCommand.set(RC_ROLL, 1510);
RcCommand.set(RC_YAW, 1500);
}
else {
RcCommand.set(RC_PITCH,1500);
RcCommand.set(RC_ROLL, 1500);
RcCommand.set(RC_YAW, 1500);
}
}}
}
//The function is called once after plutoLoop() when you deactivate
void onLoopFinish()
{
//Do your cleanup stuff here
}