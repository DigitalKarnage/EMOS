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

#include <EMOSWSPCH.h>
#include <Framework/UWebsocketClient_impl.h>

void UWebsocketClient_impl::Connect(const FString& RemoteLocation, const int32 Port)
{
	if (bIsConnected || bIsConnecting)
		return;
	
	bIsConnecting = true;

	if (Port > 0 && !RemoteLocation.IsEmpty())
	{
		auto ip = RemoteLocation.Replace(UTF8_TO_TCHAR("ws://"), UTF8_TO_TCHAR(""));
		auto url = std::string(TCHAR_TO_UTF8( *FString("ws://" + ip + ":" + FString::FromInt(Port)) ));

		try
		{
			m_WebsocketClient.init_asio();

			websocketpp::lib::error_code errorCode;
			m_WebsocketClient.clear_access_channels(websocketpp::log::alevel::all);
			m_WebsocketClient.clear_error_channels(websocketpp::log::elevel::all);

			m_WebsocketClient.set_open_handler(bind(&UWebsocketClient_impl::OnWebsocketConnected, this, ::_1));
			m_WebsocketClient.set_close_handler(bind(&UWebsocketClient_impl::OnWebsocketConnectionClosed, this, ::_1));
			m_WebsocketClient.set_message_handler(bind(&UWebsocketClient_impl::OnMessageReceived, this, ::_1, ::_2));
			
			auto connection = m_WebsocketClient.get_connection(url, errorCode);
			m_Connection = m_WebsocketClient.get_con_from_hdl(connection);

			m_WebsocketClient.connect(connection);
		}
		catch (std::exception&) {} // just swallow the errors for now 
	}
}

void UWebsocketClient_impl::Poll(const int32 maxIterations)
{
	if (!bIsConnecting && !bIsConnected)
		return;

	auto msgRead = 0;

	if (maxIterations > 0)
	{
		for (int i = 0; i < maxIterations; i++)
		{
			msgRead = m_WebsocketClient.poll_one();

			if (msgRead == 0)
				break;
		}
	}
	else if (maxIterations < 0)
	{
		do
		{
			msgRead = m_WebsocketClient.poll_one();

		} while (msgRead != 0);
	}
}

void UWebsocketClient_impl::Shutdown()
{
	if (bIsConnected)
		m_Connection->close(websocketpp::close::status::going_away, "");
}

void UWebsocketClient_impl::SendMessageEx(const FString& Message)
{
	if (!Message.IsEmpty())
	{
		// out state changed once we gained access to the thread
		if (bIsConnected)
			m_Connection->send(std::string(TCHAR_TO_UTF8(*Message)));

		else m_OutgoingMessages.Add(Message);
	}
}

TArray<FString> UWebsocketClient_impl::GetMessages()
{
	TArray<FString> result;
	
	if (m_IncomingMessages.Num() > 0)
	{
		for (auto& message : m_IncomingMessages)
			result.Add(message);

		m_IncomingMessages.Empty();
	}
	
	return result;
}

void UWebsocketClient_impl::OnWebsocketConnected(FWebsocketConnectionHandle connectionHandle)
{
	bIsConnected = true;
	bIsConnecting = false;

	for (auto& message : m_OutgoingMessages)
		m_Connection->send(std::string(TCHAR_TO_UTF8(*message)));

	m_OutgoingMessages.Empty();
}

void UWebsocketClient_impl::OnWebsocketConnectionClosed(FWebsocketConnectionHandle connectionHandle)
{
	bIsConnected = false;
	bIsConnecting = false;

	m_OutgoingMessages.Empty();
}

void UWebsocketClient_impl::OnMessageReceived(FWebsocketConnectionHandle connectionHandle, FWebsocketClientMessagePtr msg)
{
	if (msg->get_payload().size() > 0)
	{
		auto msgStr = msg->get_payload().c_str();
		m_IncomingMessages.Add( FString(UTF8_TO_TCHAR(msg->get_payload().c_str())) );
	}
}