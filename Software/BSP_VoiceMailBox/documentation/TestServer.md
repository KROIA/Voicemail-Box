# Test Server
This is the Testserver for the Voicemail Box SA in the spring semester 2025.
It offers only basic proof of concept functionalities.


---
## Content
- [Features](#features)
- [Setup](#setup)
  - [Firewall](#firewall)
- [Usage](#usage)
  - [Where to find the uploaded files?](#where-to-find-the-uploaded-files)
  - [Uploading the same file twice](#uploading-the-same-file-twice)
  - [Uploading a file](#uploading-a-file)
    - [Using curl](#using-curl)
    - [Using the STM32](#using-the-stm32)
  - [Downloading a file](#downloading-a-file)
    - [Using curl](#using-curl-1)
    - [Using the STM32](#using-the-stm32-1)

---
## Features
* Files can be uploaded
* Files can be downloaded


---
## Setup
1) Make sure Python is installed on the server machine
2) Unpack the `Testserver_Docker.zip` in the path `Software\Demos`                         
3) Follow the setup instruction from the servers markdown file inside the unpacked folder.

### Firewall
- On the server machine, the port **8000** must be opened for TCP.
- Test the connection from another machine in the same network by uploading a file using the command:
  `curl -F 'test=@test.txt' serverip:8000/devicesbackend/upload/`
 

  If the sender pc can't connect to the server, try to disable the firewall on the server machine complety, but enable it again, after finish working with the server.


---
## Usage
#### Where to find the uploaded files?
The uploaded files can be found in the path `ServerRootFolder/src/media`

#### Uploading the same file twice
When a file gets uploaded with the same name twice, the old file gets overwritten.

---
#### Uploading a file
##### Using curl
1) On the sender PC, open the terminal and type the following command:
2) `curl -F 'test=@test.txt' serverip:8000/devicesbackend/upload/`
   > `serverip` is the IP address of the server machine.
  
   > Execute the command in a directory where the file `test.txt` is avilable or enter the full file path there.

##### Using the STM32
Using the [ATCommandClient](ATCommandClient.md) class, uploading a file is easy.
More informations can be found [here](ATCommandClient.md/#upload-file-to-server)

---
#### Downloading a file
##### Using curl
1) On the sender PC, open the terminal and type the following command:
2) `curl -O serverip:8000/media/test.txt`
   > `serverip` is the IP address of the server machine.

   > `media/` is the servers download path.

   > `test.txt` is the target file to download, it will be downloaded to the location the command was executed from.

##### Using the STM32
Using the [ATCommandClient](ATCommandClient.md) class, downloading a file is easy.
More informations can be found [here](ATCommandClient.md/#download-file-from-server)
