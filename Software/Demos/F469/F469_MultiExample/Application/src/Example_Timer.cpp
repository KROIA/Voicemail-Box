#include "Example_Timer.hpp"
#include "BSP_VoiceMailBox.hpp"
#include "main.h"
#include <memory>

namespace Example_Timer
{
	/**
	 * @brief Example on how to use the timer class in the VoiceMailBox library.
	 * @details The example prints a message every second using a cyclic timer.
	 */
	void setup_CyclicPrint();
	void loop_CyclicPrint();


	/**
	 * @brief Example on how to use the timer class in the VoiceMailBox library with callbacks
	 * @details The example prints a message every second using a cyclic timer.
	 */
	void setup_CallbackBased();
	void loop_CallbackBased();


	/**
	 * @brief Example on how to use the timer class in the VoiceMailBox library with callbacks and auto-restart
	 * @details The example prints a message every second using a cyclic timer.
	 */
	void setup_CallbackBasedAutoRestart();
	void loop_CallbackBasedAutoRestart();
	
	


	

// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void setup()
	{
		//setup_CyclicPrint();
		//setup_CallbackBased();
		setup_CallbackBasedAutoRestart();
	}

	void loop()
	{
		//loop_CyclicPrint();
		//loop_CallbackBased();
		loop_CallbackBasedAutoRestart();
	}






// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	VoiceMailBox::Timer* timer_1 = nullptr;
	void setup_CyclicPrint()
	{
		VoiceMailBox::setup();

		timer_1 = new VoiceMailBox::Timer();
		timer_1->start(1000);
	}
	void loop_CyclicPrint()
	{
		using namespace VoiceMailBox;
		VoiceMailBox::update();

		if (timer_1->hasFinished())
		{
			timer_1->start();
			println("Cyclic print after " + std::to_string(getTickCountInMs())+ "ms");
		}
	}





// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	VoiceMailBox::Timer* timer_2 = nullptr;
	void setup_CallbackBased()
	{
		using namespace VoiceMailBox;
		VoiceMailBox::setup();

		timer_2 = new VoiceMailBox::Timer([]() {
				timer_2->start(); // Restart the timer for the next callback
				println("Cyclic print after " + std::to_string(getTickCountInMs()) + "ms");
			});
		timer_2->start(1000);
	}
	void loop_CallbackBased()
	{
		VoiceMailBox::update();
	}




// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	VoiceMailBox::Timer* timer_3 = nullptr;
	void setup_CallbackBasedAutoRestart()
	{
		using namespace VoiceMailBox;
		VoiceMailBox::setup();

		timer_3 = new VoiceMailBox::Timer([]() {
			println("Cyclic print after " + std::to_string(getTickCountInMs()) + "ms");
			});
		timer_3->enableAutoRestart(true); // Enable auto-restart
		timer_3->start(1000);
	}
	void loop_CallbackBasedAutoRestart()
	{
		VoiceMailBox::update();
	}
} 
