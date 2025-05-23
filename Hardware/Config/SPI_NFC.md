# Configure NFC to communicate by SPI

## Jumpers

Jumper J102 [I2C NFC]
```mermaid
block-beta
    block
        columns 1
        a0["open"]
        a1["open"]
        a2["open"]
    end

classDef highlighter fill:#8bc8e8,stroke:#6c757d,color:#000000,stroke-width:1.5px;
```

---

# Pinout F469:

### SPI ?
| Function | Pin | Info |
|----------|-----|------|
| SPI_MOSI  | PA5 | |
| SPI_MISO | PA8 | |
| SPI_SCK | PB4 | |
| SPI_NSS | PA15 | |

### GPIOs
| Function | Pin | Info |
|----------|-----|------|
| NFC_int   | PB1 | Input |

---

# Pinout H755:

### SPI ?
| Function | Pin | Info |
|----------|-----|------|
| SPI_MOSI  | PB5 | |
| SPI_MISO | PG9 | |
| SPI_SCK | PB3 | |
| SPI_NSS | PA4 | |

### GPIOs
| Function | Pin | Info |
|----------|-----|------|
| NFC_int   | PA3 | Input |

---



