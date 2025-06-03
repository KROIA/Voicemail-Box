# Configure Audio Codec / Periphery

## Jumper J104 (use to connect On Board Mic to Codec)

Position:  
<img src=../../Hardware/Diagramms/HardwareJumper-J104.png width="500">

Jumper for F469:  
<img src=../../Hardware/Diagramms/HardwareJumper-J104_F469.png width="500">

Jumper for H755:  
<img src=../../Hardware/Diagramms/HardwareJumper-J104_H755.png width="500">

---

## Jumper J604

Position:  
<img src=../../Hardware/Diagramms/HardwareJumper-J604.png width="500">

Jumper for dynamic feedback:  
<img src=../../Hardware/Diagramms/HardwareJumper-J604_Dyn.png width="150">

Jumper for static feedback:  
<img src=../../Hardware/Diagramms/HardwareJumper-J604_Stat.png width="150">

Jumper for no feedback:  
<img src=../../Hardware/Diagramms/HardwareJumper-J604_None.png width="150">

## Jumper J601

Position:  
<img src=../../Hardware/Diagramms/HardwareJumper-J601.png width="500">

enable Microphone for left channel:  
<img src=../../Hardware/Diagramms/HardwareJumper-J601_left.png width="150">

enable Microphone for right channel:  
<img src=../../Hardware/Diagramms/HardwareJumper-J601_right.png width="150">


DIP Switch SW601 (blue for recommended settings)

```mermaid
block-beta
        columns 2
        a0["enable DC Blocking Cap left"]
        b0["Short DC Blocking Cap left"]
        a1["enable DC Blocking Cap right"]
        b1["Short DC Blocking Cap right"]
        a2["Disconnect Diff Minus as neg. Output"]
        b2["Connect Diff Minus as neg. Output"]
        a3["Disconnect GND as neg. Output"]   
        b3["Connect GND as neg. Output"]    
classDef highlighter fill:#8bc8e8,stroke:#6c757d,color:#000000,stroke-width:1.5px;
class a0 highlighter
class a1 highlighter
class b2 highlighter
class a3 highlighter
```


---

# Pinout F469:

### I2S
| Function | Pin | Info |
|----------|-----|------|
| I2S_SDA  | PC1 | |
| I2S_SDAe | PC2 | |
| I2S_MCLK | PC6 | |
| I2S_WCLK | PB12 | |
| I2S_BCLK | PB13 | |

### I2C
| Function | Pin | Info |
|----------|-----|------|
| I2C_SDA  | PB8 | shared |
| I2C_SCL  | PB9 | shared |

### GPIOs
| Function | Pin | Info |
|----------|-----|------|
| nReset   | PG13 | Output |

---

# Pinout H755:

### I2S
| Function | Pin | Info |
|----------|-----|------|
| I2S_SDA  | PB15 | |
| I2S_SDAe | PB4 | |
| I2S_MCLK | PC6 | |
| I2S_WCLK | PC6 | |
| I2S_BCLK | PB13 | Jumper SB8 on H755 needs to be placed |

### I2C
| Function | Pin | Info |
|----------|-----|------|
| I2C_SDA  | PB8 | shared |
| I2C_SCL  | PB9 | shared |

### GPIOs
| Function | Pin | Info |
|----------|-----|------|
| nReset   | PG14 | Output |

---

