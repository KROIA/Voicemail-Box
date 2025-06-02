# ATCommandClient
This class is used to communicate with a device that uses [AT-Commands](https://docs.espressif.com/projects/esp-at/en/latest/esp32/AT_Command_Set/Basic_AT_Commands.html).
In this project, the class is used to communicate with the ESP32  using the UART interface.
You can find a ready to run project [here](../../Demos/F469/F469_MultiExample/README.md).



---
## Content
- [Features](#features)
- [Setup](#setup)
- [Usage](#usage)
  - [Connecting to WiFi](#connecting-to-wifi)
  - [Upload file to server](#upload-file-to-server)
  - [Download file from server](#download-file-from-server)
- [How it works behind the scenes](#how-it-works-behind-the-scenes)
  - [Uploading a file](#uploading-a-file)
  - [Downloading a file](#downloading-a-file)

---
## Features
* Function to connect to a WiFi
* Function to send a file to a server
* Function to download a file from a server
* Function to send custom AT-Commands

---
## Setup
* In the IOC, setup the [UART](../../Demos/F469/F469_HelloAudio/README.md/#wifi-esp32) on which, in this case the ESP32, is connected to.
* Setup the [test server](TestServer.md) in order to be able to upload/download files.
  
---
## Usage
---
### Connecting to WiFi
Inside your applications C++ code, this code snippet can be used. 
``` C++
using namespace VoiceMailBox;
ATCommandClient& pmodESP = getPmodESP();
if(pmodESP.connectToWifi("WIFI_SSID", "WIFI_PASSWORD"))
{
    println("Connected to WIFI");
}
else
{
    println("Failed to connect to WIFI");
}
```

---
### Upload file to server
Inside your applications C++ code, this code snippet can be used. 
Make sure that the ATCommandClient object is already connected to a WiFi. 
``` C++
using namespace VoiceMailBox;
ATCommandClient& pmodESP = getPmodESP();
if (pmodESP.sendFileToServer("test.txt", "devicesbackend/upload/", "192.168.137.1", 8000))
    println("File sent successfully");
else
    println("Failed to send file");
```

---
### Download file from server
Inside your applications C++ code, this code snippet can be used. 
Make sure that the ATCommandClient object is already connected to a WiFi. 
``` C++
using namespace VoiceMailBox;
ATCommandClient& pmodESP = getPmodESP();
if (pmodESP.downloadFileFromServer("test.txt", "media/test.txt", "192.168.137.1", 8000))
    println("File downloaded successfully");
else
    println("Failed to download file");
```

---
## How it works behind the scenes
### Uploading a file
Below are all the commands used to upload a file in chronological order.
Thats what happens when the `pmodESP.sendFileToServer("test.txt", "devicesbackend/upload/", "192.168.137.1", 8000)` is called.


1) Open a TCP connection to the server 
   `AT+CIPSTART="TCP","192.168.137.1",8000\r\n`

2) Wait for the responce from the ESP32:
   `CONNECT\r\n` && `\r\nOK\r\n`

3) Specify how many bytes we send to the ESP32
   After receiving that many bytes, the ESP32 will automatically send a packet to the server.
   That must not nessesary be the whole HTTP header and file content. More about that later.
   `AT+CIPSEND=238\r\n`
   
4) Wait for the response from the ESP32:
   `\r\nOK\r\n\r\n>`
   It is important that the `>` is at the end, indicating that the ESP now waits for packet data.

5) Sending the HTTP POST request as the first package
   ```
   POST /devicesbackend/upload/ HTTP/1.1\r\n
   Host: 192.168.137.1:8000\r\n
   Content-Type: multipart/form-data; boundary=ESP\r\n
   Content-Length: 147\r\n
   \r\n
   --ESP\r\n
   Content-Disposition: form-data; name="test"; filename="test.txt"\r\n
   Content-Type: text/plain\r\n
   \r\n
   ```

> [!NOTE] 
> The `Content-Length` must be specified in order for the server to know how many bytes are usable data.
> This size is not the sice of the whole packet it self, it is the size of the following part:
> ```
> \r\n
> --ESP\r\n
> Content-Disposition: form-data; name="test"; filename="test.txt"\r\n
> Content-Type: text/plain\r\n
> \r\n
> This is a test file for upload.\r\n
> \r\n
> --ESP--\r\n
> ```
>
> 



1) The ESP32 has now received 238 bytes and will respond with:
   `\r\nRecv 238 bytes\r\n`
   and shortly after with:
   `\r\nSEND OK\r\n`
   The first package was sent successfully.

2) Starting a new package since the file data is not sent yet.
   Again define how many bytes the ESP32 will receive for the second package.
   `AT+CIPSEND=33\r\n`

3) Wait for the response from the ESP32:
   `\r\nOK\r\n\r\n>`
   It is important that the `>` is at the end, indicating that the ESP now waits for packet data.

4) Now the file content starts
   `This is a test file for upload.\r\n`

5)  The ESP32 has now received 238 bytes and will respond with:
   `\r\nRecv 33 bytes\r\n`
   and shortly after with:
   `\r\nSEND OK\r\n`
   The first package was sent successfully.

> [!NOTE] 
> If the file is large, it gets split in to chunks of **1024** bytes each.
> In that case the steps 7, 8, 9 and 10 are repeated until all bytes of the file have been sent.

11) Now the file has been sent completle but the communication is not done.
    The end of the content must be signalized. For that, a new packet gets created.
    `AT+CIPSEND=11\r\n`

12) Wait for the response from the ESP32:
   `\r\nOK\r\n\r\n>`
   It is important that the `>` is at the end, indicating that the ESP now waits for packet data.

13) Now the end string gets sent, which was specified in the header at the beginning.
    `\r\n--ESP--\r\n`

14) The ESP32 has now received 238 bytes and will respond with:
   `\r\nRecv 11 bytes\r\n`
   and shortly after with:
   `\r\nSEND OK\r\n`
   The first package was sent successfully.

15) The connection can now be closed.
    `AT+CIPCLOSE\r\n`

16) The ESP32 will respond with
    `CLOSED\r\n\r\nOK\r\n`


The file should appear on the server now.

### Downloading a file
Below are all the commands used to upload a file in chronological order.
Thats what happens when the `pmodESP.downloadFileFromServer("test.txt", "media/test.txt", "192.168.137.1", 8000)` is called.


1) Open a TCP connection to the server 
   `AT+CIPSTART="TCP","192.168.137.1",8000\r\n`

2) Wait for the responce from the ESP32:
   `CONNECT\r\n` && `\r\nOK\r\n`

3) Specify how many bytes we send to the ESP32
   After receiving that many bytes, the ESP32 will automatically send a packet to the server.
   `AT+CIPSEND=96\r\n`

4) Wait for the response from the ESP32:
   `\r\nOK\r\n\r\n>`
   It is important that the `>` is at the end, indicating that the ESP now waits for packet data.

5) Sending the HTTP GET request as the first package   
   ```
   GET /media/file.txt HTTP/1.1\r\n
   Host: 192.168.137.1:8000\r\n
   User-Agent: ESP32\r\n
   Connection: close\r\n
   \r\n
   ```

6) The ESP32 has now received 238 bytes and will respond with:
   `\r\nRecv 96 bytes\r\n`
   and shortly after with:
   `\r\nSEND OK\r\n`
   The first package was sent successfully.

7) After that the ESP32 already starts to send the packet from the server.
   ```
   \r\n
   +IPD,397:HTTP/1.1 200 OK\r\n
   Date: Sun, 01 Jun 2025 09:11:17 GMT\r\n
   Server: WSGIServer/0.2 CPython/3.13.3\r\n
   Content-Type: text/plain\r\nContent-Length: 33\r\n
   Content-Disposition: inline; filename="file.txt"\r\n
   Last-Modified: Sun, 01 Jun 2025 09:11:16 GMT\r\n
   X-Frame-Options: DENY\r\n
   X-Content-Type-Options: nosniff\r\n
   Referrer-Policy: same-origin\r\n
   Cross-Origin-Opener-Policy: same-origin\r\n
   \r\n
   This is a test file for upload.\r\n
   ```

> [!NOTE] 
> The ESP32 will send a text with the syntax: `+IPD,XXX:` 
> The number `XXX` represents the amount of bytes that do follow after.
> The STM32 must receive that many bytes and then process it. 
>
> If the file is large, multiple such chunks will arrive.
> In that case the ESP32 will send its next `+IPD,XXX:` right after the previous bytes have been sent.

8) At the end the ESP32 will send:
   `\r\nCLOSED\r\n`

9) The filename can be extracted out of the first received chunk.
10) The file content statrts after `\r\n\r\n` was found.