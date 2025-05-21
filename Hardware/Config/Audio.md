# Configure Audio Codec / Periphery

## Jumpers and DIP Switches


Jumper J601 (use to connect On Board Mic to Codec)

```mermaid
block-beta
    block:group1:2
        columns 1
        b["Microphone On-Board as left Channel"]
        d["Microphone On-Board as right Channel"]
    end

classDef highlighter fill:#8bc8e8,stroke:#6c757d,color:#000000,stroke-width:1.5px;
class b highlighter
class d highlighter
```

---

Jumper J604

```mermaid
block-beta
        columns 3
        a[" Jumper for dynamic feedback "]:2
        b["-"]
        space:3
        c["-"]
        d[" Jumper for static feedback "]:2    
classDef highlighter fill:#8bc8e8,stroke:#6c757d,color:#000000,stroke-width:1.5px;
class a highlighter
class d highlighter
```
- Top Position = dynamic feedback
- Bottom Position = static feedback
- none = use no feedback

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

## Registers modified in example SW

```mermaid
---
config:
    packet: #with default value
        bitWidth: 64
        bitsPerRow: 8
        showBits: true
---
packet-beta title PLL Register - 0x03
    0-2: "PLL P Value"  
    3-6: "PLL Q Value"
    7: "PLL"
```
```mermaid
---
config:
    packet: #with default value
        bitWidth: 64
        bitsPerRow: 8
        showBits: true
---
packet-beta title LEFT ADC PGA GAIN CONTROL - 0x0F
    0-6: "Gain 0dB - 59.5 dB"  
    7: "Mute"
```

```mermaid
---
config:
    packet: #with default value
        bitWidth: 64
        bitsPerRow: 8
        showBits: true
---
packet-beta title RIGHT ADC PGA GAIN CONTROL - 0x10
    0-6: "Gain 0dB - 59.5 dB"  
    7: "Mute"
```

```mermaid
---
config:
    packet: #with default value
        bitWidth: 64
        bitsPerRow: 8
        showBits: true
---
packet-beta title MIC2 L/R TO LEFT ADC CONTROL - 0x11
    0-3: "Left Gain 0dB - -12dB - 0xFF = Mute"  
    4-7: "Right Gain 0dB - -12dB - 0xFF = Mute"  
```

## Pinout:
- peripheries needed:
	- 1x I2S full duplex
	- 1x I2C

- H755
	- I2S_SDA  | PB15
    - I2S_SDAe | PB4
    - I2S_MCLK | PC6
    - I2S_WCLK | PB12
	- I2S_BCLK | PB13
    (Jumper SB8 on H755 needs to be placed)  
    ---
    - I2C_SDA | PB8
    - I2C_SCL | PB9
    ---
    - nReset  | PG14

- F469:
	- I2S_SDA  | PC1
    - I2S_SDAe | PC2
    - I2S_MCLK | PC6
    - I2S_WCLK | PB12
	- I2S_BCLK | PB13
    ---
    - I2C_SDA PB8
    - I2C_SCL PB9
    ---
    - nReset  | PG13