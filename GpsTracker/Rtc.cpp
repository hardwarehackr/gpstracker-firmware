#include "Debug.h"

#include "Rtc.h"
#include "Pins.h"

#include <Wire.h>
#include <uDS3231.h>

#define LOGGER_NAME "Rtc"

using namespace utils;

namespace rtc {
	
	void setup() {
		VERBOSE("setup");
		hardware::i2c::powerOn();
		RTC.control(DS3231_12H, DS3231_OFF); //24 hours clock
		RTC.control(DS3231_A1_INT_ENABLE, DS3231_OFF); //Alarm 1 OFF
		RTC.control(DS3231_INT_ENABLE, DS3231_ON); //INTCN OFF
		hardware::i2c::powerOff();

		//TODO : check wether the osc has been halted (meaning the battery could be dead)
	}

	float getTemperature() {
		hardware::i2c::powerOn();
		float temperature = RTC.readTempRegister();
		hardware::i2c::powerOff();

		return temperature;
	}

	timestamp_t getTime() {
		tmElements_t time;
		getTime(time);
		return time::makeTimestamp(time);
	}

	void getTime(tmElements_t &time) {
		hardware::i2c::powerOn();
		RTC.readTime(time);
		hardware::i2c::powerOff();

		VERBOSE_FORMAT("getTime", "%d/%d/%d %d:%d:%d", tmYearToCalendar(time.Year), time.Month, time.Day, time.Hour, time.Minute, time.Second);
	}

	void setTime(const tmElements_t &time) {
		VERBOSE_FORMAT("setTime", "%d/%d/%d %d:%d:%d", tmYearToCalendar(time.Year), time.Month, time.Day, time.Hour, time.Minute, time.Second);

		hardware::i2c::powerOn();
		RTC.writeTime(time);
		hardware::i2c::powerOff();
	}

	void setAlarm(uint16_t seconds) {
		tmElements_t currentTime;
		tmElements_t alarmTime;

		getTime(currentTime);
		time::breakTime(time::makeTimestamp(currentTime) + seconds, alarmTime);

		setAlarm(alarmTime);
	}

	void setAlarm(const tmElements_t &time) {
		hardware::i2c::powerOn();
		RTC.writeAlarm1(DS3231_ALM_HMS, time);

		RTC.control(DS3231_A1_FLAG, DS3231_OFF); //reset Alarm 1 flag
		RTC.control(DS3231_A1_INT_ENABLE, DS3231_ON); //Alarm 1 ON
		RTC.control(DS3231_INT_ENABLE, DS3231_ON); //INTCN ON

		NOTICE_FORMAT("setAlarm", "Next alarm : %d:%d:%d", time.Hour, time.Minute, time.Second);

		hardware::i2c::powerOff();
	}

}