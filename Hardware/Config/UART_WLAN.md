# Configure WLAN/BLE to communicate by UART

## J103

Position:
<img src=../../Documentation/Jumper/HardwareJumper-J103.png width="500">

Jumper:  
<img src=../../Documentation/Jumper/HardwareJumper-J103_UART.png width="500">

Jumper J103 set WLAN/BLE using UART
```mermaid
block-beta
    block
        columns 8
        a0["open"]
        a1["open"]
        a2["open"]
        a3["open"]
        a4["n.c."]
        a5["set"]
        a6["set"]
        a7["open"]
    end

classDef highlighter fill:#8bc8e8,stroke:#6c757d,color:#000000,stroke-width:1.5px;
class a5 highlighter
class a6 highlighter
```

---

# Pinout F469:

### UART
| Function | Pin | Info |
|----------|-----|------|
| UART_TX  | PG14 |  |
| UART_RX  | PG9 |  |

---

# Pinout H755:

### UART
| Function | Pin | Info |
|----------|-----|------|
| UART_TX  | PB6 |  |
| UART_RX  | PB7 |  |

---



