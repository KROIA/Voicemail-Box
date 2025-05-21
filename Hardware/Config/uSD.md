# Configure micro SD Card Slot

## H755 vs F469

If you want to use F469, use the micro SD Slot on the F469 itself.
Since H755 does not have one by default, use the one on VMBB.

---

# Pinout F469:

### SDIO
| Function | Pin | Info |
|----------|-----|------|
| SD_DAT0  | PC8 | |
| SD_DAT1 | PC9 | |
| SD_DAT2 | PC10 | |
| SD_DAT3 | PC11 | |
| SD_CLK | PD2 | |
| SD_CMD | PC11 | |

### GPIOs
| Function | Pin | Info |
|----------|-----|------|
| SD_DET   | PG2 | Input |

---

# Pinout H755:

### SDMMC
| Function | Pin | Info |
|----------|-----|------|
| SD_DAT0  | PC8 | |
| SD_DAT1 | PC9 | |
| SD_DAT2 | PC10 | |
| SD_DAT3 | PC11 | |
| SD_CLK | PC12 | |
| SD_CMD | PD2 | |

### GPIOs
| Function | Pin | Info |
|----------|-----|------|
| SD_DET   | PG10 | Input |

---


