# Configure Power Supply Unit

## PSU Setup
There is two ways to Supply the Eval Board:
- Supply using the Connector for ST-Link on the Eval-Boards
	- Set the Supply Jumper on H755 or F469 to STLINK
	- only connect the micro-usb to the H755 / F469
	- use only when you are certain, that your power draw is low (meaning mostly "no External Speakers")

- Supply using the USB Type-C Connector on the VMBB
	- Set the Supply Jumper on H755 or F469 to E5V
	- connect USB-C to supply on VMBB and MIcro-USB on H755 or F469 to connect programmer/debugger
	- use for permanent setup (when you are finished with the coding)
	- use when you have a more power demanding setup