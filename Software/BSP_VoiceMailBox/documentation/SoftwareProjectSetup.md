# Software Project Setup



Include paths:
ProjectProperties->C/C++General->Paths and Symbols:
    Select Configuration: "All Configurations"
    Includes:
        Add: 
            Directory: "${ProjDirPath}/../../BSP_VoiceMailBox/inc"
				[x] Add to all configurations
				[x] Add to all languages

        Add:
            Directory: "Application/inc"
                [x] Add to all configurations
				[x] Add to all languages

    
    Select Configuration "Debug"
        Source Location:
            Link Folder:
                [x] Link to folder in file system
                Variables...
                    New...
                        Name: BSP_VoiceMailBox
                        Location: ${PROJECT_LOC}/../../BSP_VoiceMailBox/src
                        OK
                    Select the new created variable: BSP_VoiceMailBox
                    OK
            OK

    Select Configuration "Release"
        Source Location:
            Add Folder:
                Select folders:
                    "BSP_VoiceMailBox"
                    "Application"


Libraries:
ProjectProperties->C/C++ Build->Settings:
    MCU/MPU G++ Linker->Libraries:
        Libraries 
            -l: "_mp3decoder_cortex_m4_v2.2.0"  depending if it is a M4, see filename of lib!
            -l: "_mp3encoder_cortex_m4_v2.2.0"
        Library search path:
            -L: "${ProjDirPath}/../../BSP_VoiceMailBox/Middlewares/ST/STM32_Audio/Codecs/SpiritDSP_MP3_Dec/lib"
            -L: "${ProjDirPath}/../../BSP_VoiceMailBox/Middlewares/ST/STM32_Audio/Codecs/SpiritDSP_MP3_Enc/lib"