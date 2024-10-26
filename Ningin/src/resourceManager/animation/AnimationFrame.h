#pragma once

namespace Ningin
{
	struct AnimationFrame {
		public:
			AnimationFrame(size_t sheetFrameIndex, float frameTime);

		private:
			size_t _sheetFrameIndex;
			float _frameTime;
	};
}
