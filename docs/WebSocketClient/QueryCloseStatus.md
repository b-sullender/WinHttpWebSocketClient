# WebSocketClient.QueryCloseStatus

**QueryCloseStatus(pusStatus, pvReason, dwReasonLength, pdwReasonLengthConsumed)**

Retrieve the close status sent by a server.

***pusStatus***  
A pointer to a **`USHORT`** variable to receive the close status code.

***pvReason***  
A pointer to a buffer that will receive a close reason on return. The reason data is not guaranteed to be human readable, clients MUST NOT show it to end users.

***dwReasonLength***  
The length of the **`pvReason`** buffer, in bytes.

***pdwReasonLengthConsumed***  
The number of bytes consumed. If **`pvReason`** is NULL and **`dwReasonLength`** is 0, **`pdwReasonLengthConsumed`** will contain the size of the buffer that needs to be allocated by the calling application.

**Return Value**  
**`NO_ERROR`** on success, otherwise an error code.

**Remarks**  
Call **`QueryCloseStatus`** only after **`Close`** succeeds or if **`Receive`** returns **`WINHTTP_WEB_SOCKET_CLOSE_BUFFER_TYPE`**.
**`pdwReasonLengthConsumed`** will never be greater than 123, so allocating buffer with at least 123 will guarantee that **`ERROR_INSUFFICIENT_BUFFER`** will never be returned.
