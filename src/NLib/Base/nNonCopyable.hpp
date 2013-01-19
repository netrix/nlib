#pragma once

namespace NLib
{
	class NNonCopyable
	{
	protected:
		NNonCopyable() {}
		~NNonCopyable() {}

	private:
		NNonCopyable(const NNonCopyable&) {}
		const NNonCopyable& operator=(const NNonCopyable&) { return *this; }
	};
}
