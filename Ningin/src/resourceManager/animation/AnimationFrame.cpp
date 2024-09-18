#include "AnimationFrame.h"
#include "../../math/Math.h"
#include "../../Ningin.h"

AnimationFrame::AnimationFrame(size_t sheetFrameIndex, float frameTime): _sheetFrameIndex(sheetFrameIndex),
 _frameTime(RangeBoundValue(AnimationTimeRange, frameTime)) {}
