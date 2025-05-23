# Configure Buttons

## Pinout
J801 [Ext. Periphery]
```mermaid
block-beta
    block
        columns 8
        a0["5.0V"]
        a1["Led 0"]
        a2["Led 1"]
        a3["Button 0"]
        a4["Button 1"]
        a5["Button 2"]
        a6["Button 3"]
        a7["GND"]
    end

classDef highlighter fill:#8bc8e8,stroke:#6c757d,text:#000000,stroke-width:1.5px;
class a3 highlighter
class a4 highlighter
class a5 highlighter
class a6 highlighter
```

## Connection Type
In oder to connect an external button or switch use one of the button pins on connector J801.
Connect the Button so, that it connects the pin to GND.
> [!Caution]
> the button input is low active.

---

# Pinout F469:

### GPIOs
| Function | Pin | Info |
|----------|-----|------|
| Button 0   | PA7 | Input |
| Button 1   | PA2 | Input |
| Button 2   | PG12 | Input |
| Button 3   | PA1 | Input |

---

# Pinout H755

### GPIOs
| Function | Pin | Info |
|----------|-----|------|
| Button 0   | PD15 | Input |
| Button 1   | PE11 | Input |
| Button 2   | PE14 | Input |
| Button 3   | PE13 | Input |

---
 


