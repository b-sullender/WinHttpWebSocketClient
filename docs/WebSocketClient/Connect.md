# WebSocketClient.Connect

**Connect(host, flags)**

Connect to a WebSocket server.

***host***  
The host name (URL address) and port number. You must specify a scheme in the URL. However, because WinHTTP does not support **`"ws"`** or **`"wss"`** schemes in the URL, you can use **`"http"`** or **`"https"`** without issues.

***flags***  
This parameter is not currently used. You should pass 0 (zero).

**Return Value**  
**`NO_ERROR`** on success, otherwise an error code.
