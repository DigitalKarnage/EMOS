/* 
	All rights reserved. Copyright (c) 2015-2016, DigitalKarnage	

	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

	2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in 
	the documentation and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
	THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
	BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
	GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
	LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include <WebsocketppPCH.h>

#if defined(PLATFORM_WINDOWS)
#pragma warning( disable : 4503)
#endif
typedef websocketpp::connection_hdl FWebsocketConnectionHandle;
typedef websocketpp::client<websocketpp::config::asio_client> FWebsocketClient;
typedef websocketpp::config::asio_client::message_type::ptr FWebsocketClientMessagePtr;

class UWebsocketClient_impl
{
	public:
		UWebsocketClient_impl()
		: m_IncomingMessages( TArray<FString>() ),m_OutgoingMessages( TArray<FString>() ) { }

		void Connect(const FString& RemoteLocation = FString("echo.websocket.org"), const int32 Port = 80);
		void Poll(const int32 maxIterations = -1);
		void Shutdown();
		void SendMessageEx(const FString& Message);

		TArray<FString> GetMessages();

	private:
		void OnWebsocketConnected(FWebsocketConnectionHandle connectionHandle);
		void OnWebsocketConnectionClosed(FWebsocketConnectionHandle connectionHandle);
		void OnMessageReceived(FWebsocketConnectionHandle connectionHandle, FWebsocketClientMessagePtr msg);
		bool OnPingRecieved(FWebsocketConnectionHandle connectionHandle, std::string msg);

	private:
		bool bIsConnected = false;
		bool bIsConnecting = false;
		FWebsocketClient m_WebsocketClient;
		FWebsocketConnectionHandle m_ConnectionHandle;

		TArray<FString> m_IncomingMessages;
		TArray<FString> m_OutgoingMessages;

		std::mutex m_IncomingMutex;
		std::mutex m_OutgoingMutex;
};
