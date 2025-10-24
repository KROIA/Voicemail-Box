#ifndef VMB_TIMER_HPP
#define VMB_TIMER_HPP
/**
 * @author Alex Krieg
 */



#include "HAL_abstraction.hpp"
#include "utilities/Updatable.hpp"
#include <functional>



namespace VoiceMailBox
{
	/**
	 * @brief
	 * The Timer class can be used to create simple tasks that should be executed after a certain time period.
	 * Or to just run some code periodically with a certain time interval.
	 * @note
	 * This timer class is not suted for executing functions which require strict timings.
	 * This class uses no interrupts and is dependant on the runtime of the whole application.
	 * The execution of a callback can be delayed by any amount of time in cases where other code uses to much time.
	 * No interrupt will pause long and time wasting functions to execute this timers callback.
	 * For applications where a strict timer interval is needed, use a Hardware Timer.
	 * To hold the execution delay to a minimum, follow these rules in your application:
	 *  - Do not use "while loops" or "for loops" that could block or last for a long time. (long time means a time that is in the scale of your timers update interval)
	 *    For example, if you have a while loop that takes 1ms and you use a timer that updates every 100ms, the worst case that can happen is that
	 *    the callback function gets called with a delay of 1ms after it should have. Because there was a while loop that blocked the updating of the timer instance by 1ms.
	 *  - Do not use delays, since they block any update which would lead in an possible timer update delay of the same time used in the delay call
	 *
	 */
	class Timer : public Updatable
	{
	public:
		/**
		 * @brief Constructor
		 */
		Timer();

		/**
		 * @brief Constructor
		 * @param callback function that will be called when the timer expires.
		 */
		Timer(std::function<void()> callback);

		Timer(const Timer& other) = delete; // Disable copy constructor
		Timer& operator=(const Timer& other) = delete; // Disable copy assignment operator
		Timer(Timer&& other) noexcept = delete; // Disable move constructor
		Timer& operator=(Timer&& other) noexcept = delete; // Disable move assignment operator
		~Timer();

		/**
		 * @brief Start the timer with its last duration time value.
		 * @return true if the timer was started successfully, false if the timer is already running or if an overflow occurred.
		 */
		bool start();

		/**
		 * @brief Start the timer with a specific duration.
		 * @param ms Duration in milliseconds.
		 * @return true if the timer was started successfully, false if the timer is already running or if an overflow occurred.
		 */
		bool start(uint64_t ms);

		/**
		 * @brief Stop the timer.
		 * @return true if the timer was stopped successfully, false if the timer is not running.
		 */
		bool stop();

		/**
		 * @brief Enable or disable auto-restart of the timer.
		 * If enabled, the timer will automatically restart when it expires.
		 * @param enabled true to enable auto-restart, false to disable it.
		 * 
		 * @note If auto-restart is enabled, the hasFinished() flag will always be false.
		 */
		void enableAutoRestart(bool enabled) {
			m_autoRestart = enabled;
		}

		/**
		 * @brief Check if the timer is currently running.
		 * @return true if the timer is running, false otherwise.
		 */
		bool isRunning() const
		{
			return m_isRunning;
		}

		/**
		 * @brief Gets the current elapsed time in milliseconds since the timer started.
		 * @return the elapsed time in milliseconds, or 0 if the timer is not running.
		 */
		uint64_t getElapsedMillis() const
		{
			if (!m_isRunning)
				return 0;
			return getCurrentMillis() - m_startTimeMS;
		}

		/**
		 * @brief Changes or sets the duration of the timer.
		 * @param ms time in milliseconds to set the duration of the timer.
		 * @return true if the change was successful, false if an overflow occurred.
		 */
		bool setDuration(uint64_t ms)
		{
			m_durationMS = ms;
			if (m_isRunning)
			{
				m_endTimeMS = m_startTimeMS + ms;
				if (m_endTimeMS < m_startTimeMS)
				{
					// Overflow occurred, can't set duration
					m_isRunning = false;
					return false;
				}
			}
			return true;
		}

		/**
		 * @brief Gets the duration of the timer in milliseconds.
		 * @return the duration in milliseconds.
		 */
		uint64_t getDuration() const
		{
			return m_durationMS;
		}

		/**
		 * @brief Sets the callback function to be called when the timer expires.
		 * @param callback function to be called when the timer expires.
		 */
		void onFinish(std::function<void()> callback)
		{
			m_callback = std::move(callback);
		}

		/**
		 * @brief Checks if the timer has finished.
		 * @return true if the timer has finished, false otherwise.
		 * @note This will always return false if auto-restart is enabled.
		 */
		bool hasFinished() const
		{
			return m_hasFinished;
		}

		/**
		 * @brief Checks if the timer has a callback function set.
		 * @return true if a callback function is set, false otherwise.
		 */
		bool hasCallback() const
		{
			return m_callback != nullptr;
		}

		/**
		 * @brief Wrapper function to get the current time in milliseconds.
		 * @return current time in milliseconds.
		 */
		static inline uint64_t getCurrentMillis()
		{
			return VMB_HAL_GetTickCountInMs();
		}

		/**
		 * @brief Wrapper function to get the current time in micro seconds.
		 * @return current time in micro seconds.
		 */
		static inline uint64_t getCurrentUs()
		{
			return VMB_HAL_UpdateTick();
		}
	protected:

		
		/**
		 * @brief Called by the Updatable class and checks if the timer has expired.
		 */
		void update() override;

		

	private:
		bool m_isRunning;
		bool m_hasFinished;
		bool m_autoRestart;
		uint64_t m_durationMS;	// Duration in milliseconds
		uint64_t m_endTimeMS;
		uint64_t m_startTimeMS;
		std::function<void()> m_callback;	// Callback function to be called when the timer expires
	};
}
#endif
