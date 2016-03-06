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
#include <Framework/UWebsocketConnection_impl.h>
#include <Framework/UWebsocketServer_impl.h>

void UWebsocketServer_impl::Listen(const int32 Port)
{
	if (m_WebsocketServer.is_listening())
		return;
	
	try
	{
		m_WebsocketServer.init_asio();

		m_WebsocketServer.set_open_handler(bind(&UWebsocketServer_impl::OnClientConnected, this, ::_1));
		m_WebsocketServer.set_close_handler(bind(&UWebsocketServer_impl::OnClientDisconnected, this, ::_1));
		m_WebsocketServer.set_message_handler(bind(&UWebsocketServer_impl::OnClientMessageReceived, this, ::_1, ::_2));

		m_WebsocketServer.listen((uint8)Port);
		m_WebsocketServer.start_perpetual();
		m_WebsocketServer.start_accept();
	}
	catch (const std::exception&) { }
}

void UWebsocketServer_impl::Poll(const int32 maxIterations)
{
	if (m_WebsocketServer.is_listening())
	{
		auto msgRead = 0;

		if (maxIterations > 0)
		{
			for (int i = 0; i < maxIterations; i++)
			{
				msgRead = m_WebsocketServer.poll_one();

				if (msgRead == 0)
					break;
			}
		}
		else if (maxIterations < 0)
		{
			do
			{
				msgRead = m_WebsocketServer.poll_one();

			} while (msgRead != 0);
		}
	}
}

void UWebsocketServer_impl::BroadcastMessage(const FString& message, const TArray<UWebsocketppConnection*> exclusions)
{
	if (!message.IsEmpty())
	{	
		for (auto* connection : m_Connections)
		{
			if (exclusions.Num() == 0 || !exclusions.Contains(connection))
				connection->BroadcastMessage(message);
		}
	}
}

void UWebsocketServer_impl::Shutdown()
{
	if (m_WebsocketServer.is_listening())
	{
		m_WebsocketServer.stop_listening();
		m_WebsocketServer.stop_perpetual();
		
		for (auto* connection : m_Connections)
			connection->Close();

		m_WebsocketServer.stop();

		if (m_ListenerThread.joinable())
			m_ListenerThread.join();
	}
}

TArray<UWebsocketppConnection*> UWebsocketServer_impl::GetPendingConnections()
{
	TArray<UWebsocketppConnection*> result;

	if (m_WebsocketServer.is_listening() && m_PendingConnections.Num() > 0)
	{
		for (auto* connection : m_PendingConnections)
		{
			result.Add(connection);
			m_Connections.Add(connection);
		}	

		m_PendingConnections.Empty();
	}

	return result;
}

TArray<UWebsocketppConnection*> UWebsocketServer_impl::GetRecentDisconnections()
{
	TArray<UWebsocketppConnection*> result;

	if (m_WebsocketServer.is_listening() && m_RecentDisconnections.Num() > 0)
	{
		for (auto* connection : m_RecentDisconnections)
		{
			result.Add(connection);
			m_Connections.Remove(connection);
		}			

		m_RecentDisconnections.Empty();
	}

	return result;
}

TArray<UWebsocketppConnection*> UWebsocketServer_impl::GetConnections()
{
	return m_Connections;
}

void UWebsocketServer_impl::OnClientConnected(FWebsocketConnectionHandle connection)
{
	auto connectionPtr = m_WebsocketServer.get_con_from_hdl(connection);
	auto pendingConnection = UWebsocketConnection_impl::CreateConnection(connectionPtr);

	if (pendingConnection != NULL)
	{
		m_ConnectionMapping.insert_or_assign(connectionPtr, pendingConnection);
		m_PendingConnections.Add(pendingConnection);
	}		
}

void UWebsocketServer_impl::OnConnectionFailed(FWebsocketConnectionHandle connection)
{
	// TODO: Implement Error Handling for the System.
	// Sending the error to the log
}

void UWebsocketServer_impl::OnClientDisconnected(FWebsocketConnectionHandle connection)
{
	auto connectionPtr = m_WebsocketServer.get_con_from_hdl(connection);
	auto dConnection = m_ConnectionMapping.find(connectionPtr);

	if (dConnection->second != NULL)
	{
		m_ConnectionMapping.erase(connectionPtr);
		m_RecentDisconnections.Add(dConnection->second);
	}
}

void UWebsocketServer_impl::OnClientMessageReceived(FWebsocketConnectionHandle connection, FWebsocketServerMessage msg)
{
	auto connectionPtr = m_WebsocketServer.get_con_from_hdl(connection);
	auto messageConnection = m_ConnectionMapping.find(connectionPtr);

	if (messageConnection->second != NULL)
		messageConnection->second->p_Impl->AddPendingMessage(msg->get_payload());
}