
//
// example.cpp
// 
// Author:
//     Brian Sullender
//     SULLE WAREHOUSE LLC
// 
// Description:
//     This example program demonstrates creating a WebSocket connection to a server.
//

#include <iostream>

#include "websocket.h"
using namespace WinHttpWebSocketClient;

int wmain()
{
	// Windows Error Code
	DWORD errorCode;

	// Our certificate variable for secure connections
	PCCERT_CONTEXT pClientCertificate = NULL;

	// Buffer length
	const size_t bufferLength = 0x1000;

	// Error buffer
	WCHAR* buffer = (WCHAR*)malloc(sizeof(WCHAR) * bufferLength);
	if (buffer == NULL)
	{
		wprintf(L"%ls", L"Not enough memory\n");
		goto exit;
	}

	// Use WinHttpOpen to obtain a session handle
	// The session should be opened in synchronous mode
	HINTERNET hSession = WinHttpOpen(L"MyApp", WINHTTP_ACCESS_TYPE_NO_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	if (hSession == NULL)
	{
		errorCode = GetLastError();
		PrintLastError(errorCode, buffer, bufferLength, L"WinHttpOpen()");
		wprintf(L"%ls\n", buffer);
		goto exit;
	}

	// Define our WebSocket
	WebSocketClient webSocket;

	// Open a certificate to secure our connections
	//pClientCertificate = OpenCertificateByName(L"sullewarehouse.com", L"WebHosting", false);
	//if (pClientCertificate == NULL)
	//{
		//wprintf(L"%ls", L"Could not find the desired client certificate!\n");
	//}

	// Initialize our WebSocket
	// NOTE: If you do not provide the server with a certificate, data sent from the server will not be encrypted
	if (webSocket.Initialize(hSession, pClientCertificate) != NO_ERROR)
	{
		//wprintf(L"%ls\n", webSocket.ErrorDescription);
		PrintLastError(webSocket.ErrorCode, buffer, bufferLength, L"WebSocket.Initialize()");
		wprintf(L"%ls\n", buffer);
		goto exit;
	}

	// Attempt to connect to the WebSocket server
	// NOTE: WinHTTP does not support "ws" or "wss" schemes in the URL, we can use "http" or "https" without issues
	if (webSocket.Connect(L"https://sullewarehouse.com:41000", 0) != NO_ERROR)
	{
		wprintf(L"%ls\n", webSocket.ErrorDescription);
		if (webSocket.ErrorCode == 0x2F9A) {
			wprintf(L"%ls\n", L"Check if you have admin privileges");
		}
		goto exit;
	}

	wprintf(L"%ls", L"Connection was a success!\n");

	// Send a message
	CHAR message[] = "This is the WebSocket Client!";
	if (webSocket.Send(::WINHTTP_WEB_SOCKET_UTF8_MESSAGE_BUFFER_TYPE, message, (DWORD)strlen(message)) != NO_ERROR)
	{
		PrintLastError(webSocket.ErrorCode, buffer, bufferLength, L"Sending message");
		wprintf(L"%ls\n", buffer);
		webSocket.Close();
		goto exit;
	}
	printf("%s %s\n", "Sent:", message);

	// Define or read variables
	CHAR msgBuffer[256];
	DWORD dwBytesRead;
	WINHTTP_WEB_SOCKET_BUFFER_TYPE bufferType;

	// Get data from the server
	if (webSocket.Receive(msgBuffer, 256, &dwBytesRead, &bufferType) != NO_ERROR)
	{
		PrintLastError(webSocket.ErrorCode, buffer, bufferLength, L"Receive message");
		wprintf(L"%ls\n", buffer);
		webSocket.Close();
		goto exit;
	}

	// NOTE: The WebSocket does not set a terminating NULL character for a string
	if (bufferType == WINHTTP_WEB_SOCKET_UTF8_MESSAGE_BUFFER_TYPE)
	{
		// Set terminating NULL character
		msgBuffer[dwBytesRead] = NULL;

		// Print the server echo message
		printf("%s %s\n", "Received:", msgBuffer);
	}

	// Close connection
	wprintf(L"%ls", L"Closing connection\n");
	webSocket.Close();

exit:

	// Free resources
	if (pClientCertificate) {
		CertFreeCertificateContext(pClientCertificate);
	}

	// Notify user that we are done
	wprintf(L"%ls", L"Program Exited!\n");

	// Exit
	return 0;
}
