#include "S33KeyFrame.h"

namespace Soshiant33
{
	S33KeyFrame::S33KeyFrame(int subsetIndex)
	{
		this->subsetIndex = subsetIndex;
		this->hasAction = false;
	}
	void S33KeyFrame::serialize(SPArchive& archive)
	{
		archive & this->subsetIndex;
		archive & this->hasAction;
		archive & this->actionFuncName;
	}
}