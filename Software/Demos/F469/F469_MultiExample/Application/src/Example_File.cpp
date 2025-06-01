#include "Example_File.hpp"
#include "BSP_VoiceMailBox.hpp"
#include "main.h"

namespace Example_File
{
	/**
	 * @brief Example on how to write to a file.
	 */
	void simpleWrite();


	/**
	 * @brief Example on how to append to a file.
	 */
	void simpleAppend();


	/**
	 * @brief Example on how to read from a file.
	 */
	void simpleRead();
	
	




// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void setup()
	{
		VoiceMailBox::setup();


		simpleWrite();
		simpleAppend();
		simpleRead();
	}

	void loop()
	{
		// Nothing to loop for
	}






// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void simpleWrite()
	{
		using namespace VoiceMailBox;

		File file;
		if (file.open("example.txt", File::AccessMode::write))
		{
			file.write("Hello, World!\r\n");
			file.close();
			println("File written successfully.");
		}
		else
		{
			println("Failed to open file for writing.");
		}
	}




// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void simpleAppend()
	{
		using namespace VoiceMailBox;

		File file;
		if (file.open("example.txt", File::AccessMode::append))
		{
			file.write("Appending a new line.\r\n");
			file.close();
			println("File appended successfully.");
		}
		else
		{
			println("Failed to open file for appending.");
		}
	}





// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void simpleRead()
	{
		using namespace VoiceMailBox;

		File file;
		if (file.open("example.txt", File::AccessMode::read))
		{
			char buffer[64] = { 0 }; // Buffer to hold the read data
			while (file.read(buffer, sizeof(buffer)))
			{
				println("Read data: \r\n\"\r\n%s\"", buffer);
			}
			file.close();
			println("File read successfully.");
		}
		else
		{
			println("Failed to open file for reading.");
		}
	}






} 
