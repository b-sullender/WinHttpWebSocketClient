# WebSocketClient.Initialize

**Initialize(hSession, pCertContext)**

Initializes the WebSocket class.

***hSession***  
A session handle opened by a call to **WinHttpOpen()** function. The session should be opened in synchronous mode for compatibility with future versions of this class.

***pCertContext***  
A handle to a certificate to be used for making secure communication. If you do not provide the server with a client certificate, data sent from the server will not be encrypted.

**Return Value**  
NO_ERROR on success, otherwise an error code.
