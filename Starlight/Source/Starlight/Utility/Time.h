#pragma once

#include "Starlight/Base.h"


class Time;

struct TimerType
{
	typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimeType;
	friend Time;
public:
	TimerType();
	TimerType(float* duration);
	~TimerType();

private:
	TimeType StartTime;
	float* Duration;
};

class Time
{
public:
	static void Initialize();
	static void Shutdown();

	inline static void OnUpdate(float& outDeltaTime) { outDeltaTime = sTimeInstance->OnUpdate_Int(); };
	inline static float GetDeltaTime() { return sTimeInstance->DeltaTime; }

	static void StartTimer(TimerType& timer);
	static void EndTimer(TimerType& timer);

private:
	float OnUpdate_Int();

	inline static Time* sTimeInstance = nullptr;

	float DeltaTime;
	float TimeLastFrame;
};

#define START_TIMED_SEGMENT() { std::unique_ptr<TimerType> __timer##__LINE__ = std::make_unique<TimerType>(nullptr);
#define START_TIMED_SEGMENT(duration) { std::unique_ptr<TimerType> __timer##__LINE__ = std::make_unique<TimerType>(duration);
#define END_TIMED_SEGMENT() }