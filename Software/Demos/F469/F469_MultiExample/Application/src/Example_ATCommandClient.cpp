#include "Example_ATCommandClient.hpp"
#include "BSP_VoiceMailBox.hpp"
#include "main.h"

namespace Example_ATCommandClient
{
	/**
	 * @details
	 * For this example, the testserver is used. Follow the instructions in the README.md file to set up the server.
	 * The instructions can be found in the "BSP_VoiceMailBox/documentation/TestServer.md" file.
	 * 
	 * This example also needs a WiFi to connect to.
	 * Make sure that the server is in the same network so that it is reachable from the PmodESP.
	 */



	/**
	 * @brief Example on how to connect to a WiFi network.
	 */
	void connectToWifi();


	/**
	 * @brief Example on how to upload a file to a server.
	 */
	void uploadFile();


	/**
	 * @brief Example on how to download a file from the server.
	 */
	void downloadFile();
	
	




// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void setup()
	{
		using namespace VoiceMailBox;
		VoiceMailBox::setup();


		connectToWifi();
		delay(1000);
		uploadFile();
		delay(1000);
		downloadFile();
	}

	void loop()
	{
		VoiceMailBox::update();
	}






// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void connectToWifi()
	{
		using namespace VoiceMailBox;
		println("\r\n================================================================================\r\nConnecting to WiFi...");
		ATCommandClient& pmodESP = getPmodESP();

		// WiFi Settings
		const std::string WIFI_SSID     = "Alex-PC";
		const std::string WIFI_PASSWORD = "87924ikR";


		int counter = 5;
		while (!pmodESP.connectToWifi(WIFI_SSID, WIFI_PASSWORD) && counter > 0)
		{
			delay(1000);
			--counter;
			if (counter > 0)
				println("Try to reconnect to WIFI");
			else
				println("Failed to connect to WIFI");
		}
		println("Connected to WiFi end");
	}




// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void uploadFile()
	{
		using namespace VoiceMailBox;
		println("\r\n================================================================================\r\nUploading file...");

		// Server Settings
		const std::string serverIP = "192.168.137.1";
		const uint16_t serverPort = 8000;
		const std::string uploadURL = "devicesbackend/upload/";

		// File Settings
		const std::string fileName = "file.txt";

		// Create dummy file for upload
		File file;
		if (!file.open(fileName, File::AccessMode::write))
		{
			println("Failed to open file for writing");
			return;
		}
		file.write("This is a test file for upload.\r\n");
		file.close();


		ATCommandClient& pmodESP = getPmodESP();

		// This is a blocking call, it returns after finish or timeout
		if (pmodESP.sendFileToServer(fileName, uploadURL, serverIP, serverPort))
			println("File sent successfully");
		else
			println("Failed to send file");

		println("Upload end");
	}





// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void downloadFile()
	{
		using namespace VoiceMailBox;
		println("\r\n================================================================================\r\nDownloading file...");

		// Server Settings
		const std::string serverIP = "192.168.137.1";
		const uint16_t serverPort = 8000;
		const std::string downloadURL = "media/";

		// File Settings
		const std::string fileName = "file.txt";

		// Delete the file before downloading
		if (File::exists(fileName))
		{
			if (File::remove(fileName))
				println("File removed successfully before download");
			else
				println("Failed to remove file before download");
		}

		ATCommandClient& pmodESP = getPmodESP();

		// This is a blocking call, it returns after finish or timeout
		if (pmodESP.downloadFileFromServer(fileName, downloadURL + fileName, serverIP, serverPort))
			println("File downloaded successfully");
		else
			println("Failed to download file");

		// Read the downloaded file
		File file;
		if (file.open(fileName, File::AccessMode::read))
		{
			println("File content:");
			while (!file.eof())
			{
				std::string line = file.readLine();
				println(line);
			}
			file.close();
		}
		else
		{
			println("Failed to open downloaded file for reading");
		}

		println("Download end\r\n================================================================================");
	}






} 
