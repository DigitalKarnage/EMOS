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

#include <EMOSWS.h>

// You should place include statements to your module's private header files here.  You only need to
// add includes for headers that are used in most of your module's source files though.

#ifndef _WEBSOCKETPP_CPP11_STL_

#include <cstdlib>
#include <thread>
#include <functional>
#include <system_error>
#include <random>
#include <memory>
#include <iostream>
#include <condition_variable>
#include <mutex>

#define _WEBSOCKETPP_CPP11_STL_
#define _WEBSOCKETPP_CPP11_THREAD_
#define _WEBSOCKETPP_CPP11_FUNCTIONAL_
#define _WEBSOCKETPP_CPP11_SYSTEM_ERROR_
#define _WEBSOCKETPP_CPP11_RANDOM_DEVICE_
#define _WEBSOCKETPP_CPP11_MEMORY_

#define ASIO_STANDALONE
#define ASIO_HAS_STD_ARRAY
#define ASIO_HAS_CSTDINT
#define ASIO_HAS_STD_SHARED_PTR
#define ASIO_HAS_STD_ADDRESSOF

#endif

#if defined(PLATFORM_WINDOWS)
#pragma warning( push )
#pragma warning( disable : 4592)
#pragma warning( disable : 4191)

#include "AllowWindowsPlatformTypes.h"
#endif

#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/config/asio_no_tls_client.hpp"
#include "websocketpp/server.hpp"
#include "websocketpp/client.hpp"

#if defined(PLATFORM_WINDOWS)
#pragma warning( pop )

#include "HideWindowsPlatformTypes.h"
#endif

typedef websocketpp::client<websocketpp::config::asio_client> FWebsocketClient;
typedef websocketpp::config::asio_client::message_type::ptr FWebsocketClientMessagePtr;
typedef std::shared_ptr< websocketpp::connection<websocketpp::config::asio> > FWebsocketConnection;
typedef std::shared_ptr< websocketpp::connection<websocketpp::config::asio_client> > FWebsocketClientConnection;
typedef websocketpp::connection_hdl FWebsocketConnectionHandle;

// I hate the naming convention of the alias' for the std library
using websocketpp::lib::ref;
using websocketpp::lib::bind;

// set the usings for all the available placeholders
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::placeholders::_3;
using websocketpp::lib::placeholders::_4;
using websocketpp::lib::placeholders::_5;
using websocketpp::lib::placeholders::_6;
using websocketpp::lib::placeholders::_7;
using websocketpp::lib::placeholders::_8;
using websocketpp::lib::placeholders::_9;
using websocketpp::lib::placeholders::_10;
using websocketpp::lib::placeholders::_11;
using websocketpp::lib::placeholders::_12;
using websocketpp::lib::placeholders::_13;
using websocketpp::lib::placeholders::_14;
using websocketpp::lib::placeholders::_15;
using websocketpp::lib::placeholders::_16;
using websocketpp::lib::placeholders::_17;
using websocketpp::lib::placeholders::_18;
using websocketpp::lib::placeholders::_19;
using websocketpp::lib::placeholders::_20;