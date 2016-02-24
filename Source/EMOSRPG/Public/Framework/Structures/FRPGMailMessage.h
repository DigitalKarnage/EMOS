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
#include "FRPGMailMessage.generated.h"


USTRUCT(BlueprintType, META = (DisplayName = "RPG Mail Message"))
struct EMOSRPG_API FRPGMailMessage
{
	GENERATED_USTRUCT_BODY()

	public:

		// Used in place of the Sender String for Server to Server communications
		UPROPERTY()
		int32 SenderID;

		// Used in place of the Recipient String for Server to Server communications
		UPROPERTY()
		int32 RecieptientID;

		/** Gets or sets a value indicating the name of the sender */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "In-game Mail Services", META = (DisplayName = "Sender") )
		FString Sender;

		/** Gets or sets a value representing the subject for the message */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "In-game Mail Services", META = (DisplayName = "Message"))
		FString Subject;

		/** Gets or sets a value representing the message to route */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "In-game Mail Services", META = (DisplayName = "Message") )
		FString Message;

		/** Gets or sets a value indicating the recipient for 'private' messages */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "In-game Mail Services", META = (DisplayName = "Recipient") )
		FString Recipient;

		/** Gets or sets a value indicating the amount of currency to send to the recipient */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "In-game Mail Services", META = (DisplayName = "Attached Currency") )
		int32 AttachedCurrency;

		/** Gets or sets a collection of item(s) attached to the message to be received by the recipient */
		//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "In-game Mail Services", META = (DisplayName = "Attached Items"))
		//TArray< FRPGItemInfo > AttachedItems;

		/** Gets or sets a value indicating the total cost to send this message */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "In-game Mail Services", META = (DisplayName = "Send Cost") )
		int32 SendCost;
		
		/** Gets or sets a value indicating the amount to pay to receive the items attached to this message */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "In-game Mail Services", META = (DisplayName = "Cash On Delivery Price") )
		int32 CODPrice;

		/** Gets or sets a value indicating that there is a price to pay to receive the items attached to this message */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "In-game Mail Services", META = (DisplayName = "Is Cash On Delivery?"))
		bool bIsCOD;
};