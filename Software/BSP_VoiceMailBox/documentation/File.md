# File
This class is a simplfied interface for reading and writing files to the SD-Card.
All Basic functions used in the project are implemented here.
The class uses the FATFS filesystem.
You can find a ready to run project [here](../../Demos/F469/F469_MultiExample/README.md).

---
## Content
- [Features](#features)
- [Setup](#setup)
- [Usage](#usage)
    - [Writing to a file](#writing-to-a-file)
    - [Appending to a file](#appending-to-a-file)
    - [Reading from a file](#reading-from-a-file)

---
## Features
- Writing/Appending/Reading files.
- Deleting files at a given path.
- Rename files.
- Check if a given file path exists.
- reading a list of files in a given directory.

---
## Setup    
- Inside CubeMX, enable the FATFS in the **Middleware and Software Packages** section.
- Start the code generation and open the code editor.
- Make sure the C++ application is setup in order to use this class
You can find the instructions on how to do so [here](CppFromC.md).

---
## Usage
Make sure the C++ application is setup, you can find the instructions on how to do so [here](CppFromC.md).


#### Writing to a file
``` C++ 
#include "BSP_VoiceMailBox.hpp" // includes "peripherals/i2c.hpp"
// ...
void simpleWrite()
{
    using namespace VoiceMailBox;

    File file;
    if (file.open("example.txt", File::AccessMode::write))
    {
        file.write("Hello, World!\n");
        file.close();
        println("File written successfully.");
    }
    else
    {
        println("Failed to open file for writing.");
    }
}
```
---

#### Appending to a file
``` C++ 
#include "BSP_VoiceMailBox.hpp" // includes "peripherals/i2c.hpp"
// ...
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
```
---

#### Reading from a file
``` C++ 
#include "BSP_VoiceMailBox.hpp" // includes "peripherals/i2c.hpp"
// ...
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
```
---