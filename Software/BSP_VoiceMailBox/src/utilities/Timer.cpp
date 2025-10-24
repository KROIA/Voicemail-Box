#include "utilities/Timer.hpp"

namespace VoiceMailBox
{
	Timer::Timer()
		: m_isRunning(false)
		, m_hasFinished(false)
		, m_autoRestart(false)
		, m_durationMS(0)
		, m_endTimeMS(0)
		, m_startTimeMS(0)
		, m_callback(nullptr)
	{

	}
	Timer::Timer(std::function<void()> callback)
		: m_isRunning(false)
		, m_hasFinished(false)
		, m_autoRestart(false)
		, m_durationMS(0)
		, m_endTimeMS(0)
		, m_startTimeMS(0)
		, m_callback(std::move(callback))
	{

	}
	Timer::~Timer()
	{

	}
	bool Timer::start()
	{
		return start(m_durationMS);
	}
	bool Timer::start(uint64_t ms)
	{
		if (m_isRunning)
			return false; // Timer is already running
		m_startTimeMS = getCurrentMillis();
		m_isRunning = true;
		m_hasFinished = false;
		return setDuration(ms);
	}
	bool Timer::stop()
	{
		if (!m_isRunning)
			return false; // Timer is not running
		m_isRunning = false;
		m_hasFinished = false;
		return true;
	}

	void Timer::update()
	{
		if (!m_isRunning)
			return; // Timer is not running

		uint64_t currentMillis = getCurrentMillis();
		if (currentMillis >= m_endTimeMS)
		{
			m_isRunning = false;
			if (m_callback)
			{
				m_callback(); // Call the finish callback if set
			}
			if (m_autoRestart)
			{
				if (!start())
				{
					// Can't restart time because of overflow
					m_hasFinished = false;
				}
			}
			else
			{
				m_hasFinished = true;
			}
		}
	}
}
