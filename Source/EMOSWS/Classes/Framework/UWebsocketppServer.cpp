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

#include <Framework/UWebsocketServer_impl.h>
#include <Framework/UWebsocketppServer.h>

UWebsocketppServer::UWebsocketppServer(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	bReplicates = false;
	this->PrimaryComponentTick.bCanEverTick = true;
	this->PrimaryComponentTick.bRunOnAnyThread = false;
	this->PrimaryComponentTick.bTickEvenWhenPaused = true;
	this->PrimaryComponentTick.bStartWithTickEnabled = true;

	this->p_Impl = MakeShareable<UWebsocketServer_impl>(new UWebsocketServer_impl());
}

void UWebsocketppServer::TickComponent(float delta, enum ELevelTick tickType, struct FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(delta, tickType, thisTickFunction);

	if (p_Impl.IsValid())
	{
		p_Impl->Poll();

		auto pendingConnections = p_Impl->GetPendingConnections();
		auto removedConnections = p_Impl->GetRecentDisconnections();
		auto connections = p_Impl->GetConnections();

		if (EventOnClientConnectionChanged.IsBound())
		{
			if (pendingConnections.Num() > 0)
			{
				for (auto* connection : pendingConnections)
					EventOnClientConnectionChanged.Broadcast(connection, true);
			}

			if (removedConnections.Num() > 0)
			{
				for (auto* connection : removedConnections)
					EventOnClientConnectionChanged.Broadcast(connection, false);
			}
		}	

		for (auto* connection : connections)
		{
			auto pendingMessages = connection->GetPendingMessages();

			if (EventOnMessageRecieved.IsBound())
			{
				for (auto& message : pendingMessages)
					EventOnMessageRecieved.Broadcast(connection, message);
			}
		}
	}
}

void UWebsocketppServer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (p_Impl.IsValid())
		p_Impl->Shutdown();
}

void UWebsocketppServer::Listen(const int32 Port)
{
	if (p_Impl.IsValid())
	{
		auto listenPort = Port;

		if (Port < 1 || Port > 65535)
			listenPort = 80;

		p_Impl->Listen(listenPort);
	}
}

void UWebsocketppServer::BroadcastMessage(const FString& message, const TArray<UWebsocketppConnection*> exclusions)
{
	if (p_Impl.IsValid())
		p_Impl->BroadcastMessage(message, exclusions);
}

TArray<UWebsocketppConnection*> UWebsocketppServer::GetConnections()
{
	if (p_Impl.IsValid())
		return p_Impl->GetConnections();

	return TArray<UWebsocketppConnection*>();
}