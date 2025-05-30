# RecordPlayback example
This example uses two buttons on the PCB to start/stop recording a mp3 file and to play/stop the recorded mp3 file.
The application code can be found in `Application/src/Application.cpp`

The whole applications business logic is implemented in the `setup()` function and consists of instantiating:
- The `recorder`, providing the audio codec and a led to work on.
- The `player`, providing the audio codec and a different led to work on.
- Registering the `setOnFallingEdgeCallback` for the buttons, providing the logic for both on what to do when a button gets pressed.

## How to use
Make sure a SD-Card is inserted in to the F469-Discovery board.
Either use the microphone or the audio input jack and also connect the output jack to a speaker box.

### Recording audio
By pressing the Button 0 (SW801) once, the recording starts. that is visualized by the green flashing LED.
To stop the recording, just press the same button again.
The recording will be saved to the SD-Card.

### Playback audio
Make sure that you recorded a audio before or manually placed a mp3 file in to the SD-Card with the correct name.
By pressing the Button 1 (SW802) once, the playback starts. that is visualized by the red flashing LED.
To stop the playback, just press the same button again.



