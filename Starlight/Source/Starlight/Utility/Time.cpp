#include "pcch.h"
#include "Time.h"

#include "GLFW/glfw3.h"


void Time::Initialize()
{
	ASSERT(sTimeInstance == nullptr, "UTime already initialized!");
	sTimeInstance = new Time();
	sTimeInstance->TimeLastFrame = (float)glfwGetTime();
}

void Time::Shutdown()
{
	delete sTimeInstance;
	sTimeInstance = nullptr;
}

void Time::StartTimer(TimerType& timer)
{
	timer.StartTime = std::chrono::high_resolution_clock::now();
}

void Time::EndTimer(TimerType& timer)
{
	std::chrono::duration<float, std::milli> duration = std::chrono::high_resolution_clock::now() - timer.StartTime;
	
	if (timer.Duration) 
		*timer.Duration = duration.count();

	LOG("Timed segment took {}ms to complete.", duration.count());
}

float Time::OnUpdate_Int()
{
	float currTime = (float)glfwGetTime();
	DeltaTime = currTime - TimeLastFrame;
	TimeLastFrame = currTime;

	return DeltaTime;
}

TimerType::TimerType()
	:Duration(nullptr)
{
	Time::StartTimer(*this);
}

TimerType::TimerType(float* duration)
	:Duration(duration)
{
	Time::StartTimer(*this);
}

TimerType::~TimerType()
{
	Time::EndTimer(*this);
}
