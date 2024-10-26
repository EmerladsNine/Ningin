#include "AnimationFrame.h"
#include "../../math/Math.h"
#include "../../Ningin.h"

namespace Ningin
{
	AnimationFrame::AnimationFrame(size_t sheetFrameIndex, float frameTime) : _sheetFrameIndex(sheetFrameIndex),
		_frameTime(RangeBoundValue(AnimationTimeRange, frameTime)) {}
}