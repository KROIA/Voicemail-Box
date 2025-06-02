# Configure internal / external Potentiometers

## Jumpers and connections J802/J803

Position:  
<img src=../../Hardware/Diagramms/HardwareJumper-J80x.png width="500">

Jumper use Potentiometer on Board:  
<img src=../../Hardware/Diagramms/HardwareJumper-J80x_Board.png width="150">

Jumper use Potentiometer external:  
<img src=../../Hardware/Diagramms/HardwareJumper-J80x_Ext.png width="150">


Select on-board Potentiometer
```mermaid
block-beta
    block:group1
        columns 3
        a[" Jumper for On Board \n Potentiometer "]:2
        c["Ext. Potentiometer"]
        d["VCC 3.3V"]
        e["Ext. Potentiometer"]
        f["GND"]
    end

classDef highlighter fill:#8bc8e8,stroke:#6c757d,color:#000000,stroke-width:1.5px;
class a highlighter
```

Select ext. Potentiometer
```mermaid
block-beta
    block:group1
        columns 3
        a[" On Board Potentiometer "]
        c[" Jumper for Ext. \n Potentiometer "]:2
        d["VCC 3.3V"]
        e["Ext. Potentiometer"]
        f["GND"]
    end

classDef highlighter fill:#8bc8e8,stroke:#6c757d,color:#000000,stroke-width:1.5px;
class c highlighter
```

---

# Pinout F469:

### Analog
| Function | Pin | Info |
|----------|-----|------|
| Potentiometer 0   | PC4 | Input |
| Potentiometer 1   | PC3 | Input |

---

# Pinout H755

### Analog
| Function | Pin | Info |
|----------|-----|------|
| Potentiometer 0   | PB1 | Input |
| Potentiometer 1   | PC3 | Input |

---
