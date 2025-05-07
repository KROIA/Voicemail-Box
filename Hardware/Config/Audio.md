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



## Pinout:
- peripheries needed:
	- 1x I2S full duplex
	- 1x I2C

- H755
	- 
	- 
	- 

- F469:
	- 
	- 
	- 