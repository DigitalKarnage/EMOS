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

#include <MongoDBPCH.h>

#include <string>
#include <sstream>

#include <Framework/Structures/FMongoDocumentTemplate.h>
#include <Framework/UMongoCollection_impl.h>
#include <Framework/UMongoDocument_impl.h>

bool UMongoDocument_impl::UpdateValues(const UScriptStruct* script, const void* document)
{
	auto result = false;

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
				this->mJsonString = documentJson;
				this->mUID = docReference->_id;
				result = true;
			}
		}
	}

	return result;
}

bool UMongoDocument_impl::GetValues(const UScriptStruct* script, void* document)
{
	auto result = false;

	if (script != NULL && document != NULL)
	{
		bsoncxx::builder::stream::document filter;
		filter << "_id" << this->mUID;

		auto instance = mMongoCollection.find_one(filter.view());

		if (instance.get_ptr() != NULL)
		{
			auto jsonResult = bsoncxx::to_json(instance.get());

			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create( UTF8_TO_TCHAR(jsonResult.c_str()) );

			if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
			{
				if (FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), script, document, 0, 0))
				{
					mJsonString = UTF8_TO_TCHAR(jsonResult.c_str());
					result = true;
				}
			}

			instance.reset();
		}
	}

	return result;
}

FString UMongoDocument_impl::GetJsonResult() { return mJsonString; }

UMongoDocument* UMongoDocument_impl::CreateDocument(FMongoCollection collection, FBsonDocument document)
{
	auto result = NewObject<UMongoDocument>();	
	result->p_Impl->mMongoCollection = collection;

	auto value = document.find("_id");
	result->p_Impl->mUID = value->get_int64();

	std::stringstream stream;	
	stream << result->p_Impl->mUID;
	std::string idValue(stream.str());
	
	auto fIDString = FString(UTF8_TO_TCHAR(idValue.c_str()));
	result->p_Impl->mJsonString = FString("{\n\n\t\"_id\": ") + fIDString + FString("\n\n }");

	return result;
}


/*************************************************************************************************/


UMongoDocument::UMongoDocument(const FObjectInitializer& objectInitializer) : Super(objectInitializer)
{
	// Define the private implementation
	this->p_Impl = MakeShareable<UMongoDocument_impl>(new UMongoDocument_impl());
}

bool UMongoDocument::UpdateValues(UScriptStruct* script, const void* document)
{
	if (p_Impl.IsValid())
		return p_Impl->UpdateValues(script, document);

	return false;
}

bool UMongoDocument::GetValues(UScriptStruct* script, void* document)
{
	if (p_Impl.IsValid())
		return p_Impl->GetValues(script, document);

	return false;
}