#ifndef UNIT_BLUETOOTH_LOGGER_H
#define UNIT_BLUETOOTH_LOGGER_H

namespace unit
{
	class BluetoothLogger
	{
		//
	public:
		BluetoothLogger();
		~BluetoothLogger();

		void log(char* buf, int length);
	};
}

#endif
