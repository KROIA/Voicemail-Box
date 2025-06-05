# Flash ESP32

If you have soldered ESP32 on Board instead of using Pmod ESP32, you will have to flash the AT-Command Firmware in order to use it accordingly.

precompiled binaries can be found [here](https://github.com/espressif/esp-at/actions), if you want the most up-to-date version. If not, use the binaries in this [folder](../esp32-wroom-at/build/).

to flash it, you can follow the istructions from [espressif](https://docs.espressif.com/projects/esptool/en/latest/esp32/esptool/flashing-firmware.html)

## Connector J303

Position:  
<img src=../../Hardware/Diagramms/HardwareJumper-J303.png width="500">

Jumper to enter Boot-Mode:  
<img src=../../Hardware/Diagramms/HardwareJumper-J303_Boot.png width="500">

# Pinout J303:

| Function | Pin | Info |
|----------|-----|------|
| +3V3     | 1   | |
| Boot     | 2   | |
| Gnd      | 3   | |
| RX0      | 4   | |
| TX0      | 5   | |
| Gnd      | 6   | |

---


