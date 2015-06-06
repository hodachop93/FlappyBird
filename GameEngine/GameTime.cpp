#include "GameTime.h"
#include <windows.h>

namespace gamerize
{

	float GameTime::frameTime = 0.0f;
	float GameTime::gameTime = 0.0f;
	long GameTime::lastTime = 0L;

	// get the frame time
	float GameTime::GetFrameTime()
	{
		return frameTime > 1.0f ? 0.1f : frameTime;
	}

	// get game time
	float GameTime::GetGameTime()
	{
		return gameTime;
	}

	// tick tox
	void GameTime::Tick(float time)
	{
		frameTime = time;
		gameTime += time;
	}

	void GameTime::Update()
	{
		long newTime = GetTickCount();
		GameTime::Tick((newTime - lastTime) * 0.001f);
		lastTime = newTime;
	}
};