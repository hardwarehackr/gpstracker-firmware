#pragma once

#include <Arduino.h>

struct sleepTimings_t {
	uint8_t speed;
	uint16_t seconds;
};

struct Config {
	char seed[5];
	char version[5];
	char apn[20];
	uint16_t firstEntry;
	uint16_t lastEntry;
};

#define CONFIG_ADDR 0
#define CONFIG_SEED "UIYA"
#define VERSION "1.00"

#define SLEEP_DEFAULT_TIME_SECONDS	1800

#define GPS_DEFAULT_INTERMEDIATE_TIMEOUT_MS	10000
#define GPS_DEFAULT_TOTAL_TIMEOUT_MS		180000

namespace config {

	static const sleepTimings_t defaultSleepTimings[] PROGMEM = {
		{ 5, SLEEP_DEFAULT_TIME_SECONDS },
	{ 10, 1200 },
	{ 20, 600 },
	{ 30, 540 },
	{ 50, 480 },
	{ 80, 240 },
	{ 100, 210 },
	{ 180, 180 },
	};

	namespace main {	
		Config get();
		void set(const Config config);

		void reset();
	}
}