# WebSocketClient.Receive

**Receive(pBuffer, dwBufferLength, pdwBytesRead, pBufferType)**

Reads data from the WebSocket server. This function blocks until data is received.

***pBuffer***
A pointer to the destination buffer.

***dwBufferLength***
The length of the destination buffer in bytes.

***pdwBytesRead***
A pointer to a variable to receive the number of bytes read.

***pBufferType***
Pointer to a varible of type **`WINHTTP_WEB_SOCKET_BUFFER_TYPE`** to receive the type of data received.

**Return Value**
NO_ERROR on success, otherwise an error code.
