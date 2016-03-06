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
#include <Framework/UWebsocketppClient.h>

UWebsocketppClient::UWebsocketppClient(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	bReplicates = false;
	this->PrimaryComponentTick.bCanEverTick = true;
	this->PrimaryComponentTick.bRunOnAnyThread = false;
	this->PrimaryComponentTick.bTickEvenWhenPaused = true;
	this->PrimaryComponentTick.bStartWithTickEnabled = true;

	this->p_Impl = MakeShareable<UWebsocketClient_impl>(new UWebsocketClient_impl());
}

void UWebsocketppClient::TickComponent(float delta, enum ELevelTick tickType, struct FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(delta, tickType, thisTickFunction);

	p_Impl->Poll();

	auto messages = p_Impl->GetMessages();

	if (EventOnMessageReceived.IsBound())
	{
		for (auto& message : messages)
			EventOnMessageReceived.Broadcast(message);
	}
}

void UWebsocketppClient::Connect(const FString& RemoteLocation, const int32 Port)
{
	if (p_Impl.IsValid())
		p_Impl->Connect(RemoteLocation, Port);
}

void UWebsocketppClient::Shutdown()
{
	if (p_Impl.IsValid())
		p_Impl->Shutdown();
}

void UWebsocketppClient::K2_SendMessage(const FString& Message)
{
	if (p_Impl.IsValid())
		p_Impl->SendMessageEx(Message);
}