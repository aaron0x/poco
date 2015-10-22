//
// Socket.cpp
//
// $Id: //poco/1.4/Net/src/Socket.cpp#3 $
//
// Library: Net
// Package: Sockets
// Module:  Socket
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Net/Socket.h"
#include "Poco/Net/StreamSocketImpl.h"
#include "Poco/Net/SocketIOWatcher.h"


namespace Poco {
namespace Net {


Socket::Socket():
	_pImpl(new StreamSocketImpl)
{
}


Socket::Socket(SocketImpl* pImpl):
	_pImpl(pImpl)
{
	poco_check_ptr (_pImpl);
}


Socket::Socket(const Socket& socket):
	_pImpl(socket._pImpl)
{
	poco_check_ptr (_pImpl);

	_pImpl->duplicate();
}

	
Socket& Socket::operator = (const Socket& socket)
{
	if (&socket != this)
	{
		if (_pImpl) _pImpl->release();
		_pImpl = socket._pImpl;
		if (_pImpl) _pImpl->duplicate();
	}
	return *this;
}


Socket::~Socket()
{
	_pImpl->release();
}


int Socket::select(SocketList& readList, SocketList& writeList, SocketList& exceptList, const Poco::Timespan& timeout)
{
	return Impl::SocketIOWatcher::select(readList, writeList, exceptList, timeout);
}


} } // namespace Poco::Net
