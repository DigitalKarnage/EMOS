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

#include <Framework/UMongoDocument_impl.h>
#include <Framework/UMongoCollection_impl.h>

UMongoDocument* UMongoCollection_impl::CreateDocument(const UScriptStruct* script, const void* document)
{
	UMongoDocument* result = NULL;

	if (script != NULL && document != NULL)
	{
		auto docReference = (FMongoDocumentTemplate*)document;

		if (docReference != NULL)
		{
			auto documentJson = FString("");
			auto newIndex = bsoncxx::oid(bsoncxx::oid::init_tag_t());

			while (docReference->_id == -(int64)0x8000000000000000)
				docReference->_id = int64(newIndex.bytes());

			if (FJsonObjectConverter::UStructToJsonObjectString(script, document, documentJson, 0, 0))
			{
				auto jDocument = bsoncxx::from_json(TCHAR_TO_UTF8(*documentJson));
				mMongoCollection.insert_one(jDocument.view());

				result = UMongoDocument_impl::CreateDocument(mMongoCollection, jDocument.view());
				mMongoDocuments.Add(result);
			}
		}
	}

	return result;
}

UMongoDocument* UMongoCollection_impl::FindDocumentByID(const int64 id)
{
	UMongoDocument* result = NULL;

	for (auto* document : mMongoDocuments)
	{
		if (document->p_Impl->GetUID() == id)
			result = document;

		if (result != NULL)
			break;
	}

	if (result == NULL)
	{
		// query the database instead
		bsoncxx::builder::stream::document filter;
		filter << "_id" << id;

		auto iterator = mMongoCollection.find_one(filter.view());
		
		if (iterator.get_ptr() != NULL)
		{
			// awe crap, we need to store a new document in our local collection reference
			result = UMongoDocument_impl::CreateDocument(mMongoCollection, iterator.get());
			mMongoDocuments.Add(result);
		}
	}

	return result;
}

const int64 UMongoCollection_impl::GetDocumentCount()
{
	return mMongoDocuments.Num();
}

void UMongoCollection_impl::StartBatchProcess() { }

bool UMongoCollection_impl::RemoveDocument(UMongoDocument* document) 
{ 
	auto result = false;

	if (document != NULL)
	{
		result = mMongoDocuments.Remove(document) != 0;		
	
		if (result)
		{
			auto jDocument = bsoncxx::from_json(TCHAR_TO_UTF8(*document->p_Impl->GetJsonResult()));

			mMongoCollection.delete_one(jDocument.view());

			jDocument.release();
			
		}
	}

	return result;
}

bool UMongoCollection_impl::UpdateDocument(UMongoDocument* document)
{
	auto result = false;

	if (document != NULL)
	{	
		// we use replace in this instance, cause I'm too lazy to build the '$set' builder document, is quite inefficient for
		// when not all values have changed, but honestly IDK. More than likely as this module evolves, this will probably get
		// some attention, but in the mean time. oh well.

		auto jDocument = bsoncxx::from_json(TCHAR_TO_UTF8(*document->p_Impl->GetJsonResult()));

		bsoncxx::builder::stream::document filter;
		filter << "_id" << document->p_Impl->GetUID();
		
		result = mMongoCollection.replace_one(filter.view(), jDocument.view()).get_ptr() != NULL;		

		jDocument.release();
	}

	return result;
}

void UMongoCollection_impl::FinishBatchProcess() { }

UMongoCollection* UMongoCollection_impl::CreateCollection(FMongoCollection collection)
{
	UMongoCollection* result = NULL;

	result = NewObject<UMongoCollection>();
	result->p_Impl->mMongoCollection = collection;

	auto iterator = collection.find({});

	for (auto&& docInstance : iterator)
	{
		auto instance = UMongoDocument_impl::CreateDocument(collection, docInstance);
		result->p_Impl->mMongoDocuments.Add(instance);
	}

	return result;
}


/*************************************************************************************************/


UMongoCollection::UMongoCollection(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	// Define the private implementation
	this->p_Impl = MakeShareable<UMongoCollection_impl>(new UMongoCollection_impl);
}

UMongoDocument* UMongoCollection::CreateDocument(UScriptStruct* script, const void* document)
{
	if (p_Impl.IsValid())
		return p_Impl->CreateDocument(script, document);

	return NULL;
}

UMongoDocument* UMongoCollection::FindDocumentByID(const int64 id)
{
	if (p_Impl.IsValid())
		return p_Impl->FindDocumentByID(id);

	return NULL;
}

const int64 UMongoCollection::GetDocumentCount()
{
	if (p_Impl.IsValid())
		return p_Impl->GetDocumentCount();

	return 0;
}

void UMongoCollection::StartBatchProcess() 
{ 
	if (p_Impl.IsValid())
		p_Impl->StartBatchProcess();
}

bool UMongoCollection::RemoveDocument(UMongoDocument* document) 
{ 
	if (p_Impl.IsValid())
		return p_Impl->RemoveDocument(document);

	return false; 
}

bool UMongoCollection::UpdateDocument(UMongoDocument* document) 
{ 
	if (p_Impl.IsValid())
		return p_Impl->UpdateDocument(document);
	
	return false; 
}

void UMongoCollection::FinishBatchProcess()
{ 
	if (p_Impl.IsValid())
		p_Impl->FinishBatchProcess();
}