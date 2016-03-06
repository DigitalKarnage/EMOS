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

#include <EMOSDBPCH.h>

#include <Framework/UMongoDatabase_impl.h>
#include <Framework/UMongoClient_impl.h>

UMongoDatabase* UMongoClient_impl::GetDatabase() { return pMongoDatabase; }

UMongoDatabase* UMongoClient_impl::Connect(const FString& uriLocation, const int32 port, const FString& dbName)
{
	static FMongoInstance instance;
	
	// internally constructs a 'new' instance, if current is empty;
	instance.current();

	if (pMongoDatabase == NULL || !pMongoDatabase->p_Impl.IsValid())
	{
		auto mdbLocation = FString(uriLocation + ":" + FString::FromInt(port));

		mClient = FMongoClient(FMongoUrl(TCHAR_TO_UTF8(*mdbLocation)));
		pMongoDatabase = UMongoDatabase_impl::CreateDatabase(mClient[TCHAR_TO_UTF8(*dbName)]);
	}
	else
	{
		// Write to log
	}

	return GetDatabase();
}


/*************************************************************************************************/


UMongoClient::UMongoClient(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	// Define the private implementation
	this->p_Impl = MakeShareable<UMongoClient_impl>(new UMongoClient_impl());
}

UMongoDatabase* UMongoClient::GetDatabase()
{
	if (p_Impl.IsValid())
		return p_Impl->GetDatabase();

	return NULL;
}

UMongoDatabase* UMongoClient::Connect(const FString& uriLocation, const int32 port, const FString& dbName)
{
	if (p_Impl.IsValid())
		return p_Impl->Connect(uriLocation, port, dbName);

	return NULL;
}

