
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
	WCHAR* buffer = NULL;

	// WebSocket message buffer
	CHAR* pMessageBuffer = NULL;

	// Allocate error buffer
	buffer = (WCHAR*)malloc(sizeof(WCHAR) * bufferLength);
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
		PrintLastError(webSocket.ErrorCode, buffer, bufferLength, L"WebSocket.Initialize()");
		wprintf(L"%ls\n", buffer);
		goto exit;
	}

	// Attempt to connect to the WebSocket server
	// NOTE: WinHTTP does not support "ws" or "wss" schemes in the URL, we can use "http" or "https" without issues
	if (webSocket.Connect(L"https://sullewarehouse.com/echo", WEBSOCKET_SECURE_CONNECTION) != NO_ERROR)
	{
		wprintf(L"%ls\n", webSocket.ErrorDescription);
		if (webSocket.ErrorCode == 0x2F9A) {
			wprintf(L"%ls\n", L"Check if you have admin privileges");
		}
		goto exit;
	}

	wprintf(L"%ls", L"Connection was a success!\n");

	// Allocate message buffer
	pMessageBuffer = (CHAR*)malloc(0x1000);
	if (pMessageBuffer == NULL) {
		wprintf(L"%ls", L"Failed to allocate message buffer!\n");
		webSocket.Close(WINHTTP_WEB_SOCKET_CLOSE_STATUS::WINHTTP_WEB_SOCKET_SUCCESS_CLOSE_STATUS);
		goto exit;
	}

	while (true)
	{
		// Prompt user
		printf("%s", "Enter your message:\n");

		// Get user input
		fgets(pMessageBuffer, 0x1000, stdin);

		// Remove the line break character
		CHAR* pChar = pMessageBuffer;
		while (*pChar != NULL)
		{
			if (*pChar == '\n')
			{
				*pChar = NULL;
				break;
			}
			pChar++;
		}

		// Check for user `exit` command
		if (_stricmp(pMessageBuffer, "exit") == 0) {
			break;
		}

		// Send the message
		if (webSocket.Send(::WINHTTP_WEB_SOCKET_UTF8_MESSAGE_BUFFER_TYPE, pMessageBuffer, (DWORD)strlen(pMessageBuffer)) != NO_ERROR)
		{
			PrintLastError(webSocket.ErrorCode, buffer, bufferLength, L"Sending message");
			wprintf(L"%ls\n", buffer);
			webSocket.Close(WINHTTP_WEB_SOCKET_CLOSE_STATUS::WINHTTP_WEB_SOCKET_SUCCESS_CLOSE_STATUS);
			goto exit;
		}
		printf("%s %s\n", "Sent:", pMessageBuffer);

		// Define or read variables
		DWORD dwBytesReceived;
		DWORD dwTotalBytesReceived;
		WINHTTP_WEB_SOCKET_BUFFER_TYPE bufferType;

		// Reset dwTotalBytesReceived
		dwTotalBytesReceived = 0;

		// Get data from the server
		do
		{
			if (webSocket.Receive(pMessageBuffer, 0x1000 - dwTotalBytesReceived, &dwBytesReceived, &bufferType) != NO_ERROR)
			{
				PrintLastError(webSocket.ErrorCode, buffer, bufferLength, L"Receive message");
				wprintf(L"%ls\n", buffer);
				webSocket.Close(WINHTTP_WEB_SOCKET_CLOSE_STATUS::WINHTTP_WEB_SOCKET_SUCCESS_CLOSE_STATUS);
				goto exit;
			}

			dwTotalBytesReceived += dwBytesReceived;

		} while ((bufferType == WINHTTP_WEB_SOCKET_BUFFER_TYPE::WINHTTP_WEB_SOCKET_UTF8_FRAGMENT_BUFFER_TYPE) || (bufferType == WINHTTP_WEB_SOCKET_BUFFER_TYPE::WINHTTP_WEB_SOCKET_BINARY_FRAGMENT_BUFFER_TYPE));

		if (bufferType == WINHTTP_WEB_SOCKET_BUFFER_TYPE::WINHTTP_WEB_SOCKET_CLOSE_BUFFER_TYPE)
		{
			// Server wants to close the connection

			USHORT statusCode;
			DWORD dwReasonLengthNeeded;
			CHAR* pCloseReason;
			DWORD dwReasonLength;

			statusCode = 0;
			pCloseReason = NULL;
			dwReasonLength = 0;

			// Get the length of the close reason
			webSocket.QueryCloseStatus(&statusCode, 0, 0, &dwReasonLengthNeeded);
			if (dwReasonLengthNeeded != 0)
			{
				dwReasonLength = dwReasonLengthNeeded;
				pCloseReason = (CHAR*)malloc(dwReasonLength);
				webSocket.QueryCloseStatus(&statusCode, pCloseReason, dwReasonLength, &dwReasonLengthNeeded);
			}

			// NOTE: Close reason is not guaranteed to be human readable
			printf("%s%d%s", "Received: (CLOSE) - Status Code: ", statusCode, ", Reason: ");
			if (pCloseReason == NULL) {
				printf("%s", "NULL\n");
			}
			else {
				for (ULONG i = 0; i < dwReasonLength; i++) {
					printf("%c", pCloseReason[i]);
				}
				printf("%s", "\n");
			}

			// Gracefully close the connection
			webSocket.Close((WINHTTP_WEB_SOCKET_CLOSE_STATUS)statusCode, pCloseReason);

			// Free close reason resources
			if (pCloseReason) {
				free(pCloseReason);
			}

			goto exit;
		}
		else if (bufferType == WINHTTP_WEB_SOCKET_UTF8_MESSAGE_BUFFER_TYPE)
		{
			// We got a UTF8 message
			// NOTE: The WebSocket does not set a terminating NULL character for a string

			// Set terminating NULL character
			pMessageBuffer[dwBytesReceived] = NULL;

			// Print the server echo message
			printf("%s %s\n", "Received:", pMessageBuffer);
		}
	}

	//
	// **** We have encountered an error or finished all operations ****
	//

	wprintf(L"%ls", L"Closing connection\n");

	// Close the WebSocket connection
	if (webSocket.Close(WINHTTP_WEB_SOCKET_CLOSE_STATUS::WINHTTP_WEB_SOCKET_SUCCESS_CLOSE_STATUS) != NO_ERROR)
	{
		PrintLastError(webSocket.ErrorCode, buffer, bufferLength, L"WebSocket.Close()");
		wprintf(L"%ls\n", buffer);
	}

exit:

	// Free message resources
	if (pMessageBuffer) {
		free(pMessageBuffer);
	}

	// Free WebSocket resources
	webSocket.Free();

	// Free certificate resources
	if (pClientCertificate) {
		CertFreeCertificateContext(pClientCertificate);
	}

	// Notify user that we are done
	wprintf(L"%ls", L"Program Exited!\n");

	// Exit
	return 0;
}
