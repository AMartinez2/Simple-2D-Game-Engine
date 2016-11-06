#pragma once


namespace Engine {
	class FpsLimiter {
	public:
		FpsLimiter();
		void init(float maxFPS);
		void setMaxFPS(float maxFPS);
		void begin();
		//end will return current fps
		float end();

	private:
		void calculateFPS();
		float _maxFPS;
		unsigned int _startTicks;
		float _fps;
		float _frameTime;

	};
}