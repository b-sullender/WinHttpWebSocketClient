
//
// websocket.h
// 
// Author:
//     Brian Sullender
//     SULLE WAREHOUSE LLC
// 
// Description:
//     The header file for the WinHttpWebSocketClient namespace.
//

#include <Windows.h>
#include <winhttp.h>

// Connect flags

#define WEBSOCKET_SECURE_CONNECTION        0x0001

// WebSocket client class

namespace WinHttpWebSocketClient
{
	// Helper functions

	// Print a Windows Error Code
	void PrintLastError(DWORD errorCode, WCHAR* des, size_t desLen, WCHAR* action, bool append = false);

	// Open a certificate from a Windows certificate store
	// - If store is NULL then the function searches "My" and "WebHosting" stores
	PCCERT_CONTEXT OpenCertificateByName(WCHAR* subjectName, WCHAR* store, bool userStores);

	// The main WebSocket client class

	class WebSocketClient {
	private:
		// Application session handle to use with this connection
		HINTERNET hSession;
		// Windows connect handle
		HINTERNET hConnect;
		// The initial HTTP request handle to start the WebSocket handshake
		HINTERNET hRequest;
		// Windows WebSocket handle
		HINTERNET hWebSocket;
		// The client certificate used for the connection
		PCCERT_CONTEXT pCertContext;
	public:
		// Error of the called function
		DWORD ErrorCode;
		// The description of the error code
		WCHAR* ErrorDescription;
		// The number of characters the ErrorDescription buffer can hold
		size_t ErrorBufferLength;
		// Initialize the WebSocket client class
		DWORD Initialize(HINTERNET hSession, PCCERT_CONTEXT pCertContext);
		// Connect to a WebSocket server
		DWORD Connect(WCHAR* host, DWORD flags, WCHAR* protocol = NULL);
		// Receive data from the WebSocket server
		DWORD Receive(void* pBuffer, DWORD dwBufferLength, DWORD* pdwBytesRead, WINHTTP_WEB_SOCKET_BUFFER_TYPE* pBufferType);
		// Send data to the WebSocket server
		DWORD Send(WINHTTP_WEB_SOCKET_BUFFER_TYPE bufferType, void* pBuffer, DWORD dwBufferLength);
		// Close the connection to the server
		DWORD Close(CHAR* reason = NULL);
	};
}
