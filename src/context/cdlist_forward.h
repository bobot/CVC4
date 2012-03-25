/*********************                                                        */
/*! \file cdlist_forward.h
 ** \verbatim
 ** Original author: mdeters
 ** Major contributors: none
 ** Minor contributors (to current version): none
 ** This file is part of the CVC4 prototype.
 ** Copyright (c) 2009, 2010, 2011  The Analysis of Computer Systems Group (ACSys)
 ** Courant Institute of Mathematical Sciences
 ** New York University
 ** See the file COPYING in the top-level source directory for licensing
 ** information.\endverbatim
 **
 ** \brief This is a forward declaration header to declare the
 ** CDList<> template
 **
 ** This is a forward declaration header to declare the CDList<>
 ** template.  It's useful if you want to forward-declare CDList<>
 ** without including the full cdlist.h or cdlist_context_memory.h
 ** header, for example, in a public header context, or to keep
 ** compile times low when only a forward declaration is needed.
 **
 ** Note that all specializations of the template should be listed
 ** here as well, since different specializations are defined in
 ** different headers (cdlist.h and cdlist_context_memory.h).
 ** Explicitly declaring both specializations here ensure that if you
 ** define one, you'll get an error if you didn't include the correct
 ** header (avoiding different, incompatible instantiations in
 ** different compilation units).
 **/

#include "cvc4_public.h"

#ifndef __CVC4__CONTEXT__CDLIST_FORWARD_H
#define __CVC4__CONTEXT__CDLIST_FORWARD_H

#include <memory>

namespace __gnu_cxx {
  template <class Key> struct hash;
}/* __gnu_cxx namespace */

namespace CVC4 {
  namespace context {

    template <class T>
    class ContextMemoryAllocator;

    template <class T, class Allocator>
    class CleanUpDestruct {
    public:
      inline static void cleanup (T * e, Allocator & alloc){
        alloc.destroy(e);
      };
    };

    class CleanUpNothing;

    template <class T, class Allocator = std::allocator<T>,
              class CleanUp = CleanUpDestruct< T, Allocator > >
    class CDList;

  template <class T> //currently choosed by the constructor (TODO)
  class CDList<T, ContextMemoryAllocator<T>,
               CleanUpDestruct<T,ContextMemoryAllocator<T> > >;
  }/* CVC4::context namespace */
}/* CVC4 namespace */

#endif /* __CVC4__CONTEXT__CDLIST_FORWARD_H */
