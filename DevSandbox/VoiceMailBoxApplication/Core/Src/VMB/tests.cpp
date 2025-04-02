#include "tests.hpp"
#include "main.h"


namespace VMB
{
    bool testFat32File()
    {
        FAT32File file;

        // Open a file for writing
        if (file.open("test.txt", FA_WRITE | FA_CREATE_ALWAYS)) {
            printf("File opened for writing\n\r");
            file.write("Hello, FATFS!");
            file.flush();
            file.close();
        }
        else {
            printf("Failed to open file for writing\n\r");
        }

        // Open the same file for reading
        if (file.open("test.txt", FA_READ)) {
            char buffer[20] = { 0 };
            file.read(buffer, sizeof(buffer) - 1);
            printf("Read from file: %s\n\r", buffer);
            file.close();
        }
        else {
            printf("Failed to open file for reading\n\r");
            return false;
        }

        // Check if file exists
        if (FAT32File::exists("test.txt")) {
            printf("File exists!\n\r");
        }
        else {
            printf("File does not exist\n\r");
            return false;
        }

        // Rename the file
        if (FAT32File::rename("test.txt", "renamed.txt")) {
            printf("File renamed successfully\n\r");
        }
        else {
            printf("Failed to rename file\n\r");
            return false;
        }

        // Delete the file
        if (FAT32File::remove("renamed.txt")) {
            printf("File deleted successfully\n\r");
        }
        else {
            printf("Failed to delete file\n\r");
            return false;
        }

        // List files in root directory
        printf("Listing root directory:\n\r");
        std::vector<std::string> files = FAT32File::listDirectory("/");
        for (const auto& name : files) {
            printf(" - %s\n\r", name.c_str());
        }
        return true;
    }

    bool testWIFI()
    {
    	VMB::WiFiServerClient client(*getHuart6());

    	return true;
    }
}
