# Updatable
This class is used as a base class on which other classes can derive from.
When a class derives from the Updatable class, the `update()` must be overwritten.
Each object instance that has a Updatable as its base will automatically be updated by the VoiceMailBox::update() function internaly.

## Content
- [Features](#features)
- [Setup](#setup)
- [Usage](#usage)

---
## Features
- Automatic update from the BSP's update function


---
## Setup    
Make sure the C++ application is setup in order to use this class
You can find the instructions on how to do so [here](CppFromC.md).

---
## Usage
To use the class, a derived class must be created that overwrites the `update()` function.



``` C++ 
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
    VoiceMailBox::update(); // calls the update function on all the Updatabel objects
}
```

The console output looks like this:
```
ObjA::update() called
ObjB::update() called
ObjA::update() called
ObjB::update() called
ObjA::update() called
ObjB::update() called
ObjA::update() called
ObjB::update() called
...
```
