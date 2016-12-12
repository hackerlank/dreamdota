#ifndef OVERDATE_H_
#define OVERDATE_H_

#include "time.h" 
#include "stdio.h"
#include "Tools.h"
#include <VMP.h>

#define OVERDATE_Y	2013
#define OVERDATE_M	05
#define OVERDATE_D	01

bool isOverdate(){
	VMProtectBeginVirtualization("overdate");
	struct tm local; 
	time_t t; 
	t =	time(NULL); 
	localtime_s(&local, &t); 
	bool rv = (
		local.tm_year > (OVERDATE_Y - 1900)
		||
		(
			local.tm_year == (OVERDATE_Y - 1900)
		&&	local.tm_mon + 1 > OVERDATE_M
		)
		||
		(
			local.tm_year == (OVERDATE_Y - 1900)
		&&	local.tm_mon+1 == OVERDATE_M
		&&	local.tm_mday > OVERDATE_D
		)
	);
	VMProtectEnd();
	return rv;
} 



#endif