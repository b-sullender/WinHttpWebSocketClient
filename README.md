# WinHttpWebSocketClient
Windows C++ WebSocket Client implemented using the WinHTTP functions.

You do not need to compile anything to use this WebSocket client in your application, just include **`websocket.cpp`** and **`websocket.h`** in your application.
Everything is contained in the **`WinHttpWebSocketClient`** namespace.

See **`example.cpp`** for a detailed example.

LICENSE TERMS
=============
```
  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.
  
  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:
  
  (1) If any part of the source code for this software is distributed, then this
      README file must be included, with this copyright and no-warranty notice
      unaltered; and any additions, deletions, or changes to the original files
      must be clearly indicated in accompanying documentation.
  (2) Permission for use of this software is granted only if the user accepts
      full responsibility for any undesirable consequences; the authors accept
      NO LIABILITY for damages of any kind.
```

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
  - [QueryCloseStatus](docs/WebSocketClient/QueryCloseStatus.md)
  - [Free](docs/WebSocketClient/Free.md)
- Variables
  - [ErrorCode](docs/WebSocketClient/ErrorCode.md)
  - [ErrorDescription](docs/WebSocketClient/ErrorDescription.md)
  - [ErrorBufferLength](docs/WebSocketClient/ErrorBufferLength.md)

## WebSocket Resources

- [WebSocket server for Microsoft IIS](https://github.com/sullewarehouse/iiswebsocketserver)
