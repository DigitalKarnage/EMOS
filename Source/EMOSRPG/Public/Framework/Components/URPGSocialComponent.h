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

#include <EMOSRPG.h>
#include <Framework/Structures/FRPGChatMessage.h>
#include <Framework/Structures/FRPGMailMessage.h>

#include "URPGSocialComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRPGMailServiceEvent, const FRPGMailMessage&, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRPGChatServiceEvent, const FRPGChatMessage&, message);

UCLASS(BlueprintType, ClassGroup = ("EMOS RPG"), HideCategories = (Sockets, ComponentTick, "Component Tick", ComponentReplication, "Component Replication", Variable, "Components|Sockets", Tags, Activation, "Components|Activation"), META = (DisplayName = "RPG Social Component", BlueprintSpawnableComponent))
class EMOSRPG_API URPGSocialComponent : public UActorComponent
{
	GENERATED_BODY()

	public:
		UPROPERTY(BlueprintAssignable, Category = "Chat Services", META = (DisplayName = "Event On Chat Message Received"))
		FRPGChatServiceEvent EventOnChatMessageReceived;

		UPROPERTY(BlueprintAssignable, Category = "In-game Mail Services", META = (DisplayName = "Event On Mail Message Received"))
		FRPGMailServiceEvent EventOnMailMessageReceived;

	public:
		URPGSocialComponent(const FObjectInitializer& objectInitializer = FObjectInitializer::Get());

		virtual void InitializeComponent() override;
		virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;		
		virtual void TickComponent(float delta, enum ELevelTick tickType, struct FActorComponentTickFunction* thisTickFunction) override;

		/** Sends a chat message to the server for routing */
		UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation, Category = "Chat Services", META = (DisplayName = "Send Chat Message"))
		void Server_SendChatMessage(const FRPGChatMessage& message);

		/** Sends a mail message to the server for routing */
		UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation, Category = "In-game Mail Services", META = (DisplayName = "Send Mail Message"))
		void Server_SendMailMessage(const FRPGMailMessage& message);

		/** Deletes a message at the specified index */
		UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation, Category = "In-game Mail Service", META = (DisplayName = "Delete Mail Message") )
		void Server_DeleteMailMessage(const int32 messageIndex);
		
		/** Retrives all the messages for the owner of this object */
		UFUNCTION(BlueprintCallable, Category = "In-game Mail Services", META = (DisplayName = "Get Mail Messages"))
		void GetMailMessages(TArray< FRPGMailMessage >& result);

	private:
		// Should be called after InitializeComponent
		UFUNCTION(Server, Reliable, WithValidation)
		void Server_GetAllMailboxMessages(); 

		/** A chat message was recieved */
		UFUNCTION(Client, Reliable)
		void Client_OnChatMessageReceived(const FRPGChatMessage& message);

		/** A mail message was received */
		UFUNCTION(Client, Reliable)
		void Client_OnMailMessageReceived(const FRPGMailMessage& message);

		/** all of the mail messages have been retrieved */
		UFUNCTION(Client, Reliable)
		void Client_OnMailboxMessagesRetrieved(const TArray< FRPGMailMessage >& mailboxMessages);

	private:
		mutable TSharedPtr< TArray<FRPGChatMessage> > p_ChatMessages;
		mutable TSharedPtr< TArray<FRPGMailMessage> > p_MailMessages;
		mutable TSharedPtr< class SocialComponentServices > p_Services;
};