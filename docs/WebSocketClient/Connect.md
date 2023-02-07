# WebSocketClient.Connect

**Connect(host, flags, protocol)**

Connect to a WebSocket server.

***host***  
The host name (URL address) and port number. You must specify a scheme in the URL. However, because WinHTTP currently does not support **`"ws"`** or **`"wss"`** schemes in the URL, you can use **`"http"`** or **`"https"`** without issues. You can specify a port in the URL, for example: **`https://sullewarehouse.com:41000`** where **`41000`** is the port number. If no port number is in the URL then the function uses HTTP default port number 80 or HTTPS default port number 443 depending on the scheme used. Using HTTPS does not automatically establish a secure connection. You must still specify the **`WEBSOCKET_SECURE_CONNECTION`** flag.

***flags***  
This parameter can be **`0`** or a combination of the following flags:
- **`WEBSOCKET_SECURE_CONNECTION`** Negotiates a secure connection.

***protocol***  
A string used for the **`Sec-WebSocket-Protocol`** header. This parameter is optional.

**Return Value**  
**`NO_ERROR`** on success, otherwise an error code.
