#pragma once

namespace GameEngine {
	class FpsLimiter {
	public:
		FpsLimiter();

		
		void init(float maxFPS);

		void setMaxFPS(float maxFPS);

		void beginFrame();

		float endFrame();
	private:
		void calculateFPS();

		float _fps;
		float _maxFPS;
		float _frameTime;
		unsigned int _startTicks;
	};

}