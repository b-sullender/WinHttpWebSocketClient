# WinHttpWebSocketClient
Windows C++ WebSocket Client implemented using the WinHTTP functions.

You do not need to compile anything to use this WebSocket client in your application, just include **`websocket.cpp`** and **`websocket.h`** in your application.
Everything is contained in the WinHttpWebSocketClient namespace.

Check **`example.cpp`** for a detailed example.

## Functions

- [PrintLastError](docs/PrintLastError.md)
- [OpenCertificateByName](docs/OpenCertificateByName.md)

## WebSocketClient Class

**WinHttpWebSocketClient::WebSocketClient**

Members:
- Functions
  - [Initialize](docs/WebSocketClient/Initialize.md)
  - [Connect](docs/WebSocketClient/Connect.md)
  - [Receive](docs/WebSocketClient/Receive.md)
  - [Send](docs/WebSocketClient/Send.md)
  - [Close](docs/WebSocketClient/Close.md)
- Variables
  - [ErrorCode](docs/WebSocketClient/ErrorCode.md)
  - [ErrorDescription](docs/WebSocketClient/ErrorDescription.md)
  - [ErrorBufferLength](docs/WebSocketClient/ErrorBufferLength.md)
