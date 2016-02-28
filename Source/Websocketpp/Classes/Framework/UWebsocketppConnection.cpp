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
#include <Framework/UWebsocketppConnection.h>

UWebsocketppConnection::UWebsocketppConnection(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	this->SetFlags(RF_RootSet);
	p_Impl = MakeShareable<UWebsocketConnection_impl>(new UWebsocketConnection_impl());
}

void UWebsocketppConnection::Close()
{
	if (p_Impl.IsValid())
		p_Impl->Close();
}

void UWebsocketppConnection::BroadcastMessage(const FString& message)
{
	if (p_Impl.IsValid())
		p_Impl->BroadcastMessage(message);
}

TArray<FString> UWebsocketppConnection::GetPendingMessages()
{
	if (p_Impl.IsValid())
		return p_Impl->GetPendingMessages();

	return TArray<FString>();
}