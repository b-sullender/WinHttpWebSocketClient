# PrintLastError

**WinHttpWebSocketClient::PrintLastError(errorCode, des, desLen, action, append)**

Print an error code to a string with a description. Some codes are replaced with a C++ definition.

***errorCode***  
The error code to print. For example, the value returned from the **`GetLastError()`** function.

***des***  
The destination of the error string.

***action***  
The function or action that caused the error. This is the start of the error string.

***append***  
If this is **`true`** the error string gets appended to the destination ***des*** string. This parameter is optional, the default is false.

**Return Value**  
N/A
