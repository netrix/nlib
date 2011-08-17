#pragma once
#include "nBase.hpp"

namespace NLib
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
#define NRESULT_CP(res, func) { res = func; if(res != NLib::NRV_SUCCESS) { return res; } };

#define NFAILED(arg)  (arg) != NLib::NRV_SUCCESS
#define NSUCCEED(arg) (arg) == NLib::NRV_SUCCESS