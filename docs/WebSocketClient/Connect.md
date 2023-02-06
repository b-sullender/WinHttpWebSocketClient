# WebSocketClient.Connect

**Connect(host, flags)**

Connect to a WebSocket server.

***host***  
The host name (URL address) and port number. You must specify a scheme in the URL. However, because WinHTTP does not support **`"ws"`** or **`"wss"`** schemes in the URL, you can use **`"http"`** or **`"https"`** without issues.

***flags***  
This parameter can be 0 or a combination of the following flags:
- **`WEBSOCKET_SECURE_CONNECTION`**

***protocol***
A string used for the **`Sec-WebSocket-Protocol`** header. This parameter is optional.

**Return Value**  
**`NO_ERROR`** on success, otherwise an error code.
