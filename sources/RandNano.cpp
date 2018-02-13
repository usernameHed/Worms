#include "RandNano.hh"
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

RandNano::RandNano()
{
	this->setRandInNano();
}

RandNano::~RandNano()
{

}

void RandNano::setRandInNano() const
{
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
	struct timespec ts;
	clock_serv_t cclock;
	mach_timespec_t mts;
	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
	clock_get_time(cclock, &mts);
	mach_port_deallocate(mach_task_self(), cclock);
	ts.tv_sec = mts.tv_sec;
	ts.tv_nsec = mts.tv_nsec;
	srand((time_t)ts.tv_nsec);
#elif _WIN32
	SYSTEMTIME st;
	GetSystemTime(&st);
	srand((time_t)st.wMilliseconds);
#else
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	srand((time_t)ts.tv_nsec);
#endif
}
