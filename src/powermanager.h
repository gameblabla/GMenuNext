#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include <SDL.h>
#include "gmenu2x.h"

class PowerManager {
public:
	PowerManager(GMenu2X *gmenu2x, unsigned int suspendTimeout, unsigned int powerTimeout);
	~PowerManager();
	void setSuspendTimeout(unsigned int suspendTimeout);
	void setPowerTimeout(unsigned int powerTimeout);
	void clearTimer();
	void resetSuspendTimer();
	void resetPowerTimer();
	void doRestart(bool showDialog);
	// void resetScreenTimer();
	// void doPoweroff(bool showDialog);
	// void doSuspend(bool suspend);
	static Uint32 doSuspend(unsigned int interval, void * param);
	static Uint32 doPowerOff(unsigned int interval, void * param);
	bool suspendActive;
	SDL_TimerID powerTimer; // = NULL;



private:
	GMenu2X *gmenu2x;
	unsigned int suspendTimeout, powerTimeout;

	// void addScreenTimer();
	// void removeScreenTimer();
	// void setScreenBlanking(bool state);
	// void enableScreen();
	// void disableScreen();

	static PowerManager *instance;
	// bool screenState;
	// unsigned int screenTimeout;
	// unsigned int timeout_startms;

	// friend 
	// friend 
};

#endif