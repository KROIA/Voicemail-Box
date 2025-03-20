#include "application.h"
#include "LibVoiceMailBox.hpp"
#include "FAT32File.hpp"

void setup()
{
	/*//int a = VMB::test();
	VMB::FAT32File file;

	if(file.open("test.txt", VMB::FAT32File::AccessMode::append))
	{
		file.write("Text");
		file.close();
	}

	*/
	using namespace VMB;
    FAT32File file;

    // Open a file for writing
    if (file.open("test.txt", FA_WRITE | FA_CREATE_ALWAYS)) {
        printf("File opened for writing\n");
        file.write("Hello, FATFS!");
        file.flush();
        file.close();
    }
    else {
        printf("Failed to open file for writing\n");
    }

    // Open the same file for reading
    if (file.open("test.txt", FA_READ)) {
        char buffer[20] = { 0 };
        file.read(buffer, sizeof(buffer) - 1);
        printf("Read from file: %s\n", buffer);
        file.close();
    }
    else {
        printf("Failed to open file for reading\n");
    }

    // Check if file exists
    if (FAT32File::exists("test.txt")) {
        printf("File exists!\n");
    }
    else {
        printf("File does not exist\n");
    }

    // Rename the file
    if (FAT32File::rename("test.txt", "renamed.txt")) {
        printf("File renamed successfully\n");
    }
    else {
        printf("Failed to rename file\n");
    }

    // Delete the file
    if (FAT32File::remove("renamed.txt")) {
        printf("File deleted successfully\n");
    }
    else {
        printf("Failed to delete file\n");
    }

    // List files in root directory
    printf("Listing root directory:\n");
    std::vector<std::string> files = FAT32File::listDirectory("/");
    for (const auto& name : files) {
        printf(" - %s\n", name.c_str());
    }
}
void loop()
{

}
