#include "Example_Updatable.hpp"
#include "BSP_VoiceMailBox.hpp"

namespace Example_Updatable
{
	class ObjA : public VoiceMailBox::Updatable
	{
	public:
		void update() override
		{
			VoiceMailBox::Logger::println("ObjA::update() called");
			VoiceMailBox::delay(100); // Prevent console flooding, simulate some work being done
		}
	};

	class ObjB : public VoiceMailBox::Updatable
	{
	public:
		void update() override
		{
			VoiceMailBox::Logger::println("ObjB::update() called");
			VoiceMailBox::delay(100); // Prevent console flooding, simulate some work being done
		}
	};

	ObjA* objA = nullptr;
	ObjB* objB = nullptr;
	void setup()
	{
		VoiceMailBox::setup();
	
		objA = new ObjA();
		objB = new ObjB();
	}

	void loop()
	{
		VoiceMailBox::update();
	}
} 
