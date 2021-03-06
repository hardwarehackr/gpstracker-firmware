/**
 * Configure how the system waits for the GPS signal.
 */

#pragma once

#define GPS_INTERMEDIATE_TIMEOUT_MS				10000L	///< Time to sleeps between each GPS signal assessment.
#define GPS_TOTAL_TIMEOUT_MS					80000L	///< Timeout after which to stop trying to get a GPS signal.
#define GPS_MISSED_POSITION_GAP_KM				2		///< Gap between the current and previous position above which to consider
														///< that the tracker has moved. Even if stopped, this will trigger a whole
														///< new "cycle" of positions acquisition, and will avoid missing positions
														///< because while moving, the tracker woke up while stopped at a light traffic for instance.