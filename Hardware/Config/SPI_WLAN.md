# Configure WLAN/BLE to communicate by SPI


## J103

Position:  
<img src=../../Hardware/Diagramms/HardwareJumper-J103.png width="500">

Jumper:  
<img src=../../Hardware/Diagramms/HardwareJumper-J103_SPI.png width="500">

Jumper J103 set WLAN/BLE using SPI
```mermaid
block-beta
    block
        columns 8
        a0["Set"]
        a1["Set"]
        a2["Set"]
        a3["Set"]
        a4["n.c."]
        a5["open"]
        a6["open"]
        a7["Set"]
    end

classDef highlighter fill:#8bc8e8,stroke:#6c757d,color:#000000,stroke-width:1.5px;
class a0 highlighter
class a1 highlighter
class a2 highlighter
class a3 highlighter
class a7 highlighter
```

---

# Pinout F469:

### SPI
| Function | Pin | Info |
|----------|-----|------|
| SPI_MOSI  | PB15 | |
| SPI_MISO | PB14 | |
| SPI_SCK | PD3 | |
| SPI_NSS | PH6 | |

---

# Pinout H755:

### SPI
| Function | Pin | Info |
|----------|-----|------|
| SPI_MOSI  | PB5 | validate!!! |
| SPI_MISO | PA6 | |
| SPI_SCK | PA5 | |
| SPI_NSS | PD14 | |

---
