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

#include <EMOSRPG.h>
#include <Framework/Components/SocialComponentServices.h>
#include <Framework/Components/URPGSocialComponent.h>

URPGSocialComponent::URPGSocialComponent(const FObjectInitializer& objectInitializer)
{
	this->bReplicates = true;
	this->bNetAddressable = true;
	this->bAutoActivate = false;
	this->bEditableWhenInherited = true;
	this->CreationMethod = EComponentCreationMethod::Native;

	this->bWantsInitializeComponent = true;

	this->PrimaryComponentTick.bCanEverTick = true;
	this->PrimaryComponentTick.bRunOnAnyThread = false;
	this->PrimaryComponentTick.bTickEvenWhenPaused = true;
	this->PrimaryComponentTick.bStartWithTickEnabled = true;
	this->PrimaryComponentTick.bAllowTickOnDedicatedServer = true;

	this->p_ChatMessages = MakeShareable< TArray<FRPGChatMessage> >(new TArray<FRPGChatMessage>());
	this->p_MailMessages = MakeShareable< TArray<FRPGMailMessage> >(new TArray<FRPGMailMessage>());
	this->p_Services = MakeShareable<SocialComponentServices>(new SocialComponentServices());
}

void URPGSocialComponent::InitializeComponent()
{
	Super::InitializeComponent();
	

}

void URPGSocialComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void URPGSocialComponent::TickComponent(float delta, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction)
{
	Super::TickComponent(delta, tickType, thisTickFunction);

}

bool URPGSocialComponent::Server_SendChatMessage_Validate(const FRPGChatMessage& message)
{

	return true;
}

void URPGSocialComponent::Server_SendChatMessage_Implementation(const FRPGChatMessage& message)
{

}

bool URPGSocialComponent::Server_SendMailMessage_Validate(const FRPGMailMessage& message)
{

	return true;
}

void URPGSocialComponent::Server_SendMailMessage_Implementation(const FRPGMailMessage& message)
{

}

bool URPGSocialComponent::Server_DeleteMailMessage_Validate(const int32 messageIndex)
{

	return true;
}

void URPGSocialComponent::Server_DeleteMailMessage_Implementation(const int32 messageIndex)
{

}

void URPGSocialComponent::GetMailMessages(TArray< FRPGMailMessage >& result)
{

}

bool URPGSocialComponent::Server_GetAllMailboxMessages_Validate()
{

	return true;
}

void URPGSocialComponent::Server_GetAllMailboxMessages_Implementation()
{

}

void URPGSocialComponent::Client_OnChatMessageReceived_Implementation(const FRPGChatMessage& message)
{

}

void URPGSocialComponent::Client_OnMailMessageReceived_Implementation(const FRPGMailMessage& message)
{

}

void URPGSocialComponent::Client_OnMailboxMessagesRetrieved_Implementation(const TArray< FRPGMailMessage >& mailboxMessages)
{

}

