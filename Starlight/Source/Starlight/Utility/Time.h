#pragma once


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

#define StartTimedSegment() { std::unique_ptr<TimerType> __timer##__LINE__ = std::make_unique<TimerType>(nullptr);

#define StartTimedSegment(duration) { std::unique_ptr<TimerType> __timer##__LINE__ = std::make_unique<TimerType>(duration);

#define EndTimedSegement() }