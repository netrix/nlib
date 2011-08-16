#pragma once
#include "nBase.hpp"

namespace NIne
{
	enum NLibErrors
	{
		NRV_SUCCESS = 0,
		NRV_OUT_OF_MEMORY,
		NRV_FAILED_TO_OPEN_FILE,
		_NRV_NLIBERRORS_SIZE
	};

	typedef NUint32 NRESULT;
}

// Check and pass result
#define NRESULT_CP(res, func) { res = func; if(res != NIne::NRV_SUCCESS) { return res; } };

#define NFAILED(arg)  (arg) != NIne::NRV_SUCCESS
#define NSUCCEED(arg) (arg) == NIne::NRV_SUCCESS