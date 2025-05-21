# Configure internal / external Potentiometers

## Jumpers and connections J802/J803

Select on-board Potentiometer
```mermaid
Header 
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
s
### Pinout:
- peripheries needed:
	- 2x Analog In

- H755
	- Potentiometer 0 | PB1
	- Potentiometer 1 | PC3

- F469:
	- Potentiometer 0 | PC4
	- Potentiometer 1 | PC3