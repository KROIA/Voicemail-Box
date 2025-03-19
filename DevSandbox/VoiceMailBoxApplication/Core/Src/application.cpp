#include "application.h"
#include "LibVoiceMailBox.hpp"
#include "FAT32File.hpp"

void setup()
{
	//int a = VMB::test();
	VMB::FAT32File file;

	if(file.open("test.txt", VMB::FAT32File::AccessMode::write))
	{
		file.write("Text");
		file.close();
	}


}
void loop()
{

}
