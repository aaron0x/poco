//
// SocketIOWatcher.h
//
// $Id: //poco/1.4/Net/include/Poco/Net/SocketIOWatcher.h#1 $
//
// Library: Net
// Package: NetCore
// Module:  SocketIOWatcher
//
// Definition of the SocketIOWatcher class.
//
// Copyright (c) 2005-2011, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:   BSL-1.0
//


#ifndef Net_SocketIOWatcher_INCLUDED
#define Net_SocketIOWatcher_INCLUDED


#include "Poco/Net/Socket.h"


namespace Poco {
namespace Net {
namespace Impl {

class SocketIOWatcher
{
public:
   typedef Socket::SocketList SocketList;
   static int select(SocketList& readList, SocketList& writeList, SocketList& exceptList, const Poco::Timespan& timeout);
      /// Determines the status of one or more sockets, 
      /// using a call to select().
      ///
      /// ReadList contains the list of sockets which should be
      /// checked for readability.
      ///
      /// WriteList contains the list of sockets which should be
      /// checked for writeability.
      ///
      /// ExceptList contains a list of sockets which should be
      /// checked for a pending error.
      ///
      /// Returns the number of sockets ready.
      ///
      /// After return, 
      ///   * readList contains those sockets ready for reading,
      ///   * writeList contains those sockets ready for writing,
      ///   * exceptList contains those sockets with a pending error.
      ///
      /// If the total number of sockets passed in readList, writeList and
      /// exceptList is zero, select() will return immediately and the
      /// return value will be 0.
      ///
      /// If one of the sockets passed to select() is closed while
      /// select() runs, select will return immediately. However,
      /// the closed socket will not be included in any list.
      /// In this case, the return value may be greater than the sum
      /// of all sockets in all list.

   static bool poll(SocketImpl* socket, const Poco::Timespan& timeout, int mode);
      /// Determines the status of the socket, using a 
      /// call to select().
      /// 
      /// The mode argument is constructed by combining the values
      /// of the SelectMode enumeration.
      ///
      /// Returns true if the next operation corresponding to
      /// mode will not block, false otherwise.

private:

#if defined(POCO_HAVE_FD_POLL)
class FDCompare
   /// Utility functor used to compare socket file descriptors.
   /// Used in poll() member function.
{
public:
   FDCompare(int fd): _fd(fd) { }
   inline bool operator()(const Socket& socket) const
   { return socket.sockfd() == _fd; }

private:
   FDCompare();
   int _fd;
};
#endif
};

} } } // namespace Poco::Net::Impl


#endif // Net_SocketIOWatcher_INCLUDED
