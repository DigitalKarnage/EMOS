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

#include <Websocketpp.h>
#include <Runtime/Engine/Classes/Components/ActorComponent.h>

#include <Framework/UWebsocketppConnection.h>

#include "UWebsocketppServer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWebsocketServerEvent, const UWebsocketppConnection*, connection, const FString&, Message);

UCLASS(BlueprintType, ClassGroup = "Websocketpp", HideCategories = (Sockets, ComponentTick, "Component Tick", ComponentReplication, "Component Replication", Variable, "Components|Sockets", Tags, Activation, "Components|Activation"), META = (DisplayName = "Websocket Server") )
class WEBSOCKETPP_API UWebsocketppServer : public UActorComponent
{
	GENERATED_BODY()

	public:
		UPROPERTY(BlueprintAssignable, Category = "Events")
		FWebsocketServerEvent EventOnMessageRecieved;

	public:
		UWebsocketppServer(const FObjectInitializer objectInitializer = FObjectInitializer::Get());


};