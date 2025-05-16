# Configure Leds

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
class a1 highlighter
class a2 highlighter
```

## Connection Type
In oder to connect an external led use one of the led pins on connector J801 to connect the leds cathode.
Connect the annode of the led to the pos Voltage of Choice (+5V is available on the Connector).
> [!Caution]
> the led output is low active.
> do not connect a positive Voltage greater than 30V.