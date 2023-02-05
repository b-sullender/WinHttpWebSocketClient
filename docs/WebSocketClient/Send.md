# WebSocketClient.Send

**Send(bufferType, pBuffer, dwBufferLength)**

Sends data to the WebSocket server. This function blocks until data is sent.

***bufferType***  
The type of data being sent. This can be 1 of the following:
- **`WINHTTP_WEB_SOCKET_BINARY_MESSAGE_BUFFER_TYPE`**
- **`WINHTTP_WEB_SOCKET_BINARY_FRAGMENT_BUFFER_TYPE`**
- **`WINHTTP_WEB_SOCKET_UTF8_MESSAGE_BUFFER_TYPE`**
- **`WINHTTP_WEB_SOCKET_UTF8_FRAGMENT_BUFFER_TYPE`**
- **`WINHTTP_WEB_SOCKET_CLOSE_BUFFER_TYPE`**

***pBuffer***  
Pointer to the data to send.

***dwBufferLength***  
The number of bytes to send.

**Return Value**  
NO_ERROR on success, otherwise an error code.
