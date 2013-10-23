/*
Copyright 2013 Mona - mathieu.poux[a]gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License received along this program for more
details (or else see http://www.gnu.org/licenses/).

This file is a part of Mona.
*/

#pragma once


#include "Mona/Mona.h"
#include "Mona/HostEntry.h"


namespace Mona {

	/// This class provides an interface to the
	/// domain name service.
	///
	/// An internal DNS cache is used to speed up name lookups.

class DNS : Fix {
public:

	// Returns a HostEntry object containing the DNS information for the host with the given name
	static bool HostByName(Exception& ex, const std::string& hostname, HostEntry& host);
		
	// Returns a HostEntry object containing the DNS information for the host with the given IP address
	static bool HostByAddress(Exception& ex, const IPAddress& address, HostEntry& host);

	// Returns a HostEntry object containing the DNS information for the host with the given IP address or host name
	static bool Resolve(Exception& ex, const std::string& address, HostEntry& host);

	// Returns a HostEntry object containing the DNS information for this host
	static bool ThisHost(Exception& ex,HostEntry& host);

	// Returns the host name of this host
	static bool HostName(Exception& ex, std::string& host);

protected:

#if defined(_WIN32)
	static int LastError() { return GetLastError(); }
#elif defined(POCO_VXWORKS)
	static int LastError() { return errno; }
#else
	static int LastError() { return h_errno; }
#endif

	static void SetError(Exception& ex, int error, const std::string& argument);

	// Set the exception according to the getaddrinfo() error code
	static void SetAIError(Exception& ex, int error, const std::string& argument);
};


} // namespace Mona