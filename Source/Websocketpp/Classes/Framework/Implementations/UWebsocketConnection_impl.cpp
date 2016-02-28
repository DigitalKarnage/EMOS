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

#include <WebsocketppPCH.h>

#include <Framework/UWebsocketConnection_impl.h>

void UWebsocketConnection_impl::Close()
{
	if (m_Connection.get() != NULL)
		m_Connection->close(websocketpp::close::status::going_away, "Closed connection by the server");
}

void UWebsocketConnection_impl::BroadcastMessage(const FString& message) const
{
	if (m_Connection.get() != NULL)
		m_Connection->send(std::string(TCHAR_TO_UTF8(*message)));
}

void UWebsocketConnection_impl::AddPendingMessage(const std::string& message)
{
	m_PendingMessages.push_back(message);
}

const TArray<FString> UWebsocketConnection_impl::GetPendingMessages() const
{
	TArray<FString> result;

	//if (m_PendingMessages.num() > 0)
	//{
	//	for (auto& message : m_PendingMessages)
	//		result.Add(message);

	//	m_PendingMessages->Empty();
	//}

	if (m_PendingMessages.size() > 0)
	{
		for (auto& message : m_PendingMessages)
			result.Add(UTF8_TO_TCHAR(message.c_str()));

		m_PendingMessages.clear();
	}

	return result;
}

UWebsocketppConnection* UWebsocketConnection_impl::CreateConnection(FWebsocketConnection connection)
{
	auto result = NewObject<UWebsocketppConnection>();
	result->p_Impl->m_Connection = connection;

	return result;
}
