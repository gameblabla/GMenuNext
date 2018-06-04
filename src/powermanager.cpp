#include "powermanager.h"
#include "messagebox.h"
#include "debug.h"

PowerManager *PowerManager::instance = NULL;

PowerManager::PowerManager(GMenu2X *gmenu2x, unsigned int suspendTimeout, unsigned int powerTimeout) {
	instance = this;
	this->suspendTimeout = suspendTimeout;
	this->powerTimeout = powerTimeout;
	this->gmenu2x = gmenu2x;
	this->suspendActive = false;

	this->powerTimer = NULL;

	resetSuspendTimeout();
	// resetPowerTimeout(powerTimeout);
}

PowerManager::~PowerManager() {
	clearTimeout();
	instance = NULL;
}

void PowerManager::clearTimeout() {
	ERROR("clearTimeout");
	if (powerTimer != NULL) SDL_RemoveTimer(powerTimer);
	powerTimer = NULL;
};

void PowerManager::resetSuspendTimeout() {
	ERROR("resetSuspendTimeout");
	clearTimeout();
	powerTimer = SDL_AddTimer(this->suspendTimeout * 1e3, doSuspend, NULL);
};

void PowerManager::resetPowerTimeout() {
	clearTimeout();
	powerTimer = SDL_AddTimer(this->powerTimeout * 60e3, doPowerOff, NULL);
};

void PowerManager::doRestart(bool showDialog = false) {
};


Uint32 PowerManager::doSuspend(unsigned int interval, void * param) {
	if (interval > 0) {
		ERROR("POWER MANAGER ENTER SUSPEND");
	
		MessageBox mb(PowerManager::instance->gmenu2x, PowerManager::instance->gmenu2x->tr["Suspend"]);
		mb.setAutoHide(500);
		mb.exec();

		PowerManager::instance->gmenu2x->setBacklight(0);
		PowerManager::instance->gmenu2x->setCPU(PowerManager::instance->gmenu2x->confInt["cpuMin"]);
		INFO("Enter suspend mode.");
	
		PowerManager::instance->resetPowerTimeout();

		PowerManager::instance->suspendActive = true;

		return interval;
	}

	PowerManager::instance->gmenu2x->setCPU(PowerManager::instance->gmenu2x->confInt["cpuMenu"]);
	PowerManager::instance->gmenu2x->setBacklight(max(10, PowerManager::instance->gmenu2x->confInt["backlight"]));
	INFO("Exit from suspend mode. Restore backlight to: %d", PowerManager::instance->gmenu2x->confInt["backlight"]);

	PowerManager::instance->suspendActive = false;

	ERROR("POWER MANAGER EXIT SUSPEND");
	PowerManager::instance->resetSuspendTimeout();
};

Uint32 PowerManager::doPowerOff(unsigned int interval, void * param) {
	if (interval > 0) {
		ERROR("POWER MANAGER DO POWEROFF");
#if !defined(TARGET_PC)
		system("poweroff");
#endif
		return interval;
	}

	MessageBox mb(PowerManager::instance->gmenu2x, PowerManager::instance->gmenu2x->tr["   Poweroff or reboot the device?   "], "skin:icons/exit.png");
	mb.setButton(SECTION_NEXT, PowerManager::instance->gmenu2x->tr["Reboot"]);
	mb.setButton(CONFIRM, PowerManager::instance->gmenu2x->tr["Poweroff"]);
	mb.setButton(CANCEL,  PowerManager::instance->gmenu2x->tr["Cancel"]);
	int response = mb.exec();
	if (response == CONFIRM) {
		MessageBox mb(PowerManager::instance->gmenu2x, PowerManager::instance->gmenu2x->tr["Poweroff"]);
		mb.setAutoHide(500);
		mb.exec();

#if !defined(TARGET_PC)
		PowerManager::instance->gmenu2x->setBacklight(0);
		system("poweroff");
#endif
	}
	else if (response == SECTION_NEXT) {
		MessageBox mb(PowerManager::instance->gmenu2x, PowerManager::instance->gmenu2x->tr["Rebooting"]);
		mb.setAutoHide(500);
		mb.exec();

#if !defined(TARGET_PC)
		PowerManager::instance->gmenu2x->setBacklight(0);
		system("reboot");
#endif
	}
};
