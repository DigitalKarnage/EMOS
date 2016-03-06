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

#include <Framework/UMongoCollection_impl.h>
#include <Framework/UMongoDatabase_impl.h>

bool UMongoDatabase_impl::RemoveCollection(UMongoCollection* collection)
{
	auto result = mMongoCollections.Remove(collection) != 0;

	if (result)
		collection->p_Impl->mMongoCollection.drop();

	return result;
}

UMongoCollection* UMongoDatabase_impl::CreateCollection(const FString& name)
{
	auto result = GetCollectionByName(name);

	if (result != NULL)
	{
		std::string stdName = TCHAR_TO_UTF8(*name);
		auto collection = mMongoDatabase.create_collection(stdName);

		result = UMongoCollection_impl::CreateCollection(collection);
		mMongoCollections.Add(result);
	}

	return result;
}

UMongoCollection* UMongoDatabase_impl::GetCollectionByName(const FString& name)
{
	UMongoCollection* result = NULL;
	std::string stdName = TCHAR_TO_UTF8(*name);

	for (auto* item : mMongoCollections)
	{
		if (item->p_Impl->mMongoCollection.name().to_string() == stdName)
			result = item;

		if (result != NULL)
			break;
	}

	if (result == NULL)
	{
		// awe crap, query the database instead 
		try
		{
			auto collection = mMongoDatabase.collection(stdName);

			if (collection.name() == stdName)
			{
				result = UMongoCollection_impl::CreateCollection(collection);

				if (result != NULL)
					mMongoCollections.Add(result);
			}			
		}
		catch (std::exception&) {}		
	}

	return result;
}

const TArray< UMongoCollection* > UMongoDatabase_impl::GetCollections()
{
	try
	{
		auto iterator = mMongoDatabase.list_collections();

		for (auto&& collection : iterator)
		{
			auto name = collection.find("name")->get_value().get_utf8().value.to_string();
			auto collectionName = FString(UTF8_TO_TCHAR(name.c_str()));

			auto mCollection = GetCollectionByName(collectionName);

			if (mCollection == NULL)
			{
				auto tCollection = mMongoDatabase.collection(name);
				mCollection = UMongoCollection_impl::CreateCollection(tCollection);

				mMongoCollections.Add(mCollection);
			}
		}
	}
	catch (std::exception&) { } // swallow exception for now

	return mMongoCollections;
}

UMongoDatabase* UMongoDatabase_impl::CreateDatabase(FMongoDatabase database)
{
	auto result = NewObject<UMongoDatabase>();
	result->p_Impl->mMongoDatabase = database;

	try
	{
		result->GetCollections();
	}
	catch ( std::exception& ) 
	{ 
		// cannot connect to the database set the result to null;
		result->BeginDestroy();
		result = nullptr;
	}

	return result;
}


/*************************************************************************************************/


UMongoDatabase::UMongoDatabase(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	// Define the private implementation
	this->p_Impl = MakeShareable<UMongoDatabase_impl>(new UMongoDatabase_impl());
}

bool UMongoDatabase::RemoveCollection(UMongoCollection* collection)
{
	if (p_Impl.IsValid())
		return p_Impl->RemoveCollection(collection);

	return false;	
}

UMongoCollection* UMongoDatabase::CreateCollection(const FString& name)
{
	if (p_Impl.IsValid())
		return p_Impl->CreateCollection(name);

	return NULL;
}

UMongoCollection* UMongoDatabase::GetCollectionByName(const FString& name)
{
	if (p_Impl.IsValid())
		return p_Impl->GetCollectionByName(name);

	return NULL;
}

const TArray< UMongoCollection* > UMongoDatabase::GetCollections()
{
	if (p_Impl.IsValid())
		return p_Impl->GetCollections();

	return TArray<UMongoCollection*>();
}