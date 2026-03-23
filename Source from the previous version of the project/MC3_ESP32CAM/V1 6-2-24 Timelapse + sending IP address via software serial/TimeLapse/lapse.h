
#pragma once

void setInterval(unsigned long delta);
bool startLapse();
bool stopLapse();
bool processLapse(unsigned long dt);


#define wtd 0  //Wtd - want to debug, when 0 only prints the ip address and disconnection messages else prints all the details as it was.