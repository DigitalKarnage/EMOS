// Copyright 2014 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <bsoncxx/document/view_or_value.hpp>
#include <bsoncxx/stdx/optional.hpp>
#include <mongocxx/stdx.hpp>

#include <mongocxx/config/prelude.hpp>

namespace mongocxx {
MONGOCXX_INLINE_NAMESPACE_BEGIN
namespace model {

///
/// Class representing a MongoDB update operation that replaces a single document.
///
class MONGOCXX_API replace_one {
   public:
    ///
    /// Constructs an update operation that will replace a single document matching the filter.
    ///
    /// @param filter
    ///   Document representing the criteria for replacement.
    /// @param replacement
    ///   Document that will serve as the replacement.
    ///
    replace_one(bsoncxx::document::view_or_value filter,
                bsoncxx::document::view_or_value replacement);

    ///
    /// Gets the filter for replacement.
    ///
    /// @return The filter to be used for the replacement operation.
    ///
    const bsoncxx::document::view_or_value& filter() const;

    ///
    /// Gets the replacement document.
    ///
    /// @return The document that will replace the original selected document.
    ///
    const bsoncxx::document::view_or_value& replacement() const;

    ///
    /// Sets the upsert option.
    ///
    /// When upsert is @c true, this operation will insert the replacement document as a new
    /// document if no existing documents match the filter. When upsert is @c false, the
    /// replacement operation does nothing if there are no matching documents. By default,
    /// upsert is @c false.
    ///
    /// @param upsert
    ///   If set to @c true, creates a new document when no document matches the query criteria.
    ///   The server side default is @c false, which does not insert a new document if a match
    ///   is not found.
    ///
    replace_one& upsert(bool upsert);

    ///
    /// Gets the current value of the upsert option.
    ///
    /// @return The optional value of the upsert option.
    ///
    const stdx::optional<bool>& upsert() const;

   private:
    // Required
    bsoncxx::document::view_or_value _filter;
    bsoncxx::document::view_or_value _replacement;

    // Optional
    stdx::optional<bool> _upsert;
};

}  // namespace model
MONGOCXX_INLINE_NAMESPACE_END
}  // namespace mongocxx

#include <mongocxx/config/postlude.hpp>
