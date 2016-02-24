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

#include <Engine.h>
#include "ERPGCharacterType.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class ERPGCharacterType : uint8
{
	/** A value which represents nothing */
	None = 0x00,

	/** A value which represents a Monster which has made a name for itself */
	Boss = 0x01,

	/** A value which represents an NPC which utilizes the In-Game Auction House Implementations */
	Consignment = 0x02,

	/** A value which represents a Generic Non Player Character */
	NPC = 0x03,

	/** A value which represents a mailbox used by the In-Game mail system */
	Mailbox = 0x04,

	/** A value which represents an enemy in the world */
	Monster = 0x05,

	/** A value which represnts a companion for a player */
	Pet = 0x06,

	/** A value representing a character played by a real person */
	Player = 0x07,

	/** A value representing a player which has their user store opened */
	UserStore = 0x08
};