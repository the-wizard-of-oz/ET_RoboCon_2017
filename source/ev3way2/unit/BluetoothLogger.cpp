#include "ev3api.h"
#include "BluetoothLogger.h"
#include <syssvc/serial.h>

namespace unit
{
	BluetoothLogger::BluetoothLogger()
	{
	}
	
	BluetoothLogger::~BluetoothLogger()
	{
	}
	
	void BluetoothLogger::log(char* buf, int length)
	{
		serial_wri_dat(SIO_PORT_BT, buf, length);
	}
}
