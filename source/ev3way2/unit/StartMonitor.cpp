#include <string.h>
#include "StartMonitor.h"
#include <syssvc/serial.h>

namespace unit
{
	static const char* startCommand = "1";

	StartMonitor::StartMonitor(TouchSensorDriver* touchSensorDriver)
	: mTouchSensorDriver(touchSensorDriver),
	  mIsStartSignalReceived(false),
	  mIsBluetoothStartSignalReceived(false)
	{
	}

	StartMonitor::~StartMonitor()
	{
		mTouchSensorDriver = nullptr;
	}
	
	bool StartMonitor::execute()
	{
		mIsStartSignalReceived |= mTouchSensorDriver->IsPressed();
		mIsStartSignalReceived |= mIsBluetoothStartSignalReceived;
		
		return mIsStartSignalReceived;
	}
	
	bool StartMonitor::isStartSignalReceived()
	{
		return mIsStartSignalReceived;
	}
	
	bool StartMonitor::isBluetoothStartSignalReceived()
	{
		return mIsBluetoothStartSignalReceived;
	}
	
	void StartMonitor::updateBluetoothStartSignalStatus()
	{
		char buf[64] = {0};

		serial_rea_dat(SIO_PORT_BT, buf, 1);
		mIsBluetoothStartSignalReceived = (strcmp(buf, startCommand) == 0);
	}
}  // namespace unit
