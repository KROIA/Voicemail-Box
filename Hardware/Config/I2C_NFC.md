# Configure NFC to communicate by I2C

## Jumpers

Jumper J102 [I2C NFC]
```mermaid
block-beta
    block
        columns 1
        a0["set"]
        a1["set"]
        a2["set"]
    end

classDef highlighter fill:#8bc8e8,stroke:#6c757d,color:#000000,stroke-width:1.5px;
class a0 highlighter
class a1 highlighter
class a2 highlighter
```

---

# Pinout F469:

### I2C
| Function | Pin | Info |
|----------|-----|------|
| I2C_SDA  | PB8 | shared |
| I2C_SDA  | PB9 | shared |

### GPIOs
| Function | Pin | Info |
|----------|-----|------|
| NFC_int   | PB1 | Input |

---

# Pinout H755:

### I2C
| Function | Pin | Info |
|----------|-----|------|
| I2C_SDA  | PB8 | shared |
| I2C_SDA  | PB9 | shared |

### GPIOs
| Function | Pin | Info |
|----------|-----|------|
| NFC_int   | PA3 | Input |

---
