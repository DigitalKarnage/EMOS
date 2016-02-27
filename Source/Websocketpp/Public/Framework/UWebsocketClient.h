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

#include "UWebsocketClient.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebsocketClientEvent, const FString&, Message);

UCLASS(BlueprintType, ClassGroup = ("Websocketpp"), HideCategories = (Sockets, ComponentTick, "Component Tick", ComponentReplication, "Component Replication", Variable, "Components|Sockets", Tags, Activation, "Components|Activation"), META = (DisplayName = "Websocket Client", BlueprintSpawnableComponent) )
class WEBSOCKETPP_API UWebsocketClient : public UActorComponent
{
	GENERATED_BODY()

	public:
		/** An Event to bind to that gets called when there is a new message from the connected server */
		UPROPERTY(BlueprintAssignable, Category = "Events")
		FWebsocketClientEvent EventOnMessageReceived;

	public:
		UWebsocketClient(const FObjectInitializer& objectInitializer = FObjectInitializer::Get());

		virtual void TickComponent(float delta, enum ELevelTick tickType, struct FActorComponentTickFunction* thisTickFunction) override;

		/**
			Attempts to connect to a listenting socket server, with the supplied parameters
			@param RemoteLocation a string value representing the dns host of the websocket server
			@param Port an integer value representing the port on the host to connect to
		*/
		UFUNCTION(BlueprintCallable, Category = "Websocket Functions")
		void Connect(const FString& RemoteLocation = FString("echo.websocket.org"), const int32 Port = 80);

		/** Shuts down and prevents further messages from being sent */
		UFUNCTION(BlueprintCallable, Category = "Websocket Functions")
		void Shutdown();

		/** 
			Sends a message on the websocket connection to the end point
			@param Message a string value representing the message to send to the remote websocket server
		*/
		UFUNCTION(BlueprintCallable, Category = "Websocket Functions", Meta = (DisplayName = "Send Message") )
		void K2_SendMessage(const FString& Message);

	private:
		TSharedPtr<class UWebsocketClient_impl> p_Impl;
};