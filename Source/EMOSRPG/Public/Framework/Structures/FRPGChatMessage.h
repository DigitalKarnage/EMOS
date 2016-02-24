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
#include <Framework/Enumerations/ERPGChatMessageArea.h>

#include "FRPGChatMessage.generated.h"


USTRUCT(BlueprintType, META = (DisplayName = "RPG Chat Message") )
struct EMOSRPG_API FRPGChatMessage
{
	GENERATED_USTRUCT_BODY()

	public:

		// Used in place of the Sender String for Server to Server communications
		UPROPERTY()
		int32 SenderID;		 

		// Used in place of the Recipient String for Server to Server communications
		UPROPERTY()
		int32 RecieptientID; 

		/** Gets or sets a value indicating the chat area this object should be routed through */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Chat Services", META = (DisplayName = "Chat Area") )
		ERPGChatMessageArea ChatArea = ERPGChatMessageArea::Area;

		/** Gets or sets a value indicating the name of the sender */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Chat Services", META = (DisplayName = "Sender") )
		FString Sender;

		/** Gets or sets a value representing the message to route */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Chat Services", META = (DisplayName = "Message") )
		FString Message;

		/** Gets or sets a value indicating the recipient for 'private' messages */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Chat Services", META = (DisplayName = "Recipient") )
		FString Recipient;
};