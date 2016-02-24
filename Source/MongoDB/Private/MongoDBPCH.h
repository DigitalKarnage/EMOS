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

#include "MongoDB.h"

// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.

#include <JsonUtilities.h>
#include <Json.h>

#if defined (USE_WINDOWSPLATFORMTYPES)
#include "AllowWindowsPlatformTypes.h"
#endif

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/types.hpp>

#include <bsoncxx/v_noabi/bsoncxx/json.hpp>
#include <bsoncxx/v_noabi/bsoncxx/oid.hpp>
#include <bsoncxx/v_noabi/bsoncxx/types.hpp>
#include <bsoncxx/v_noabi/bsoncxx/validate.hpp>
#include <bsoncxx/v_noabi/bsoncxx/view_or_value.hpp>

#include <mongocxx/v_noabi/mongocxx/client.hpp>
#include <mongocxx/v_noabi/mongocxx/collection.hpp>
#include <mongocxx/v_noabi/mongocxx/database.hpp>
#include <mongocxx/v_noabi/mongocxx/instance.hpp>
#include <mongocxx/v_noabi/mongocxx/uri.hpp>

#if defined (USE_WINDOWSPLATFORMTYPES)
#include "HideWindowsPlatformTypes.h"
#endif

#include <Framework/Structures/FMongoDocumentTemplate.h>

typedef bsoncxx::document::view FBsonDocument;

typedef mongocxx::client FMongoClient;
typedef mongocxx::collection FMongoCollection;
typedef mongocxx::database FMongoDatabase;
typedef mongocxx::instance FMongoInstance;
typedef mongocxx::uri FMongoUrl;