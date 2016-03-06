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

#include <EMOSWS.h>
#include <Runtime/Engine/Classes/Components/ActorComponent.h>

#include <Framework/UWebsocketppConnection.h>

#include "UWebsocketppServer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWebsocketServerEvent, const UWebsocketppConnection*, connection, const FString&, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWebsocketConnectionEvent, const UWebsocketppConnection*, connection, const bool, isConnecting);

UCLASS(BlueprintType, ClassGroup = "Websocketpp", HideCategories = (Sockets, ComponentTick, "Component Tick", ComponentReplication, "Component Replication", Variable, "Components|Sockets", Tags, Activation, "Components|Activation"), META = (DisplayName = "Websocket Server", BlueprintSpawnableComponent) )
class EMOSWS_API UWebsocketppServer : public UActorComponent
{
	GENERATED_BODY()

	public:
		UPROPERTY(BlueprintAssignable, Category = "Events", META = (DisplayName = "Event On Message Received") )
		FWebsocketServerEvent EventOnMessageRecieved;

		UPROPERTY(BlueprintAssignable, Category = "Events", META = (DisplayName = "Event On Client Connection Changed") )
		FWebsocketConnectionEvent EventOnClientConnectionChanged;

	public:
		UWebsocketppServer(const FObjectInitializer& objectInitializer = FObjectInitializer::Get());

		virtual void TickComponent(float delta, enum ELevelTick tickType, struct FActorComponentTickFunction* thisTickFunction) override;
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
		
		/** 
			Start listening for websocket connections and communications on the supplied port
			@para Port a value indicating the port to start listening on
		*/
		UFUNCTION(BlueprintCallable, Category = "Functions", META = (DisplayName = "Listen", ClampMin = 1, ClampMax = 65535, UIMin = 1, UIMax = 65535) )
		void Listen(const int32 Port = 80);

		/** 
			Broadcasts a message to all connected clients, excluding all the connections in the 'exclusions' collection
			@param message a string message to broadcast to all connections
			@param exclusions a collection of connections to exclude from the broadcast
		*/
		UFUNCTION(BlueprintCallable, Category = "Functions", META = (DisplayName = "Broadcast Message") )
		void BroadcastMessage(const FString& message, const TArray<UWebsocketppConnection*> exclusions);

		/**  Returns a collection of websocket connection's connected to this server */
		UFUNCTION(BlueprintCallable, Category = "Functions", META = (DisplayName = "Get Connections") )
		TArray<UWebsocketppConnection*> GetConnections();

	private:
		TSharedPtr<class UWebsocketServer_impl> p_Impl;
};