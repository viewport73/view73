/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2009-2009.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
//  This code was modified from the code posted by Alexandre Courpron in his
//  article "Interface Detection" in The Code Project:
///////////////////////////////////////////////////////////////////////////////
// Copyright 2007 Alexandre Courpron
//
// Permission to use, copy, modify, redistribute and sell this software, 
// provided that this copyright notice appears on all copies of the software.
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_FUNCTION_DETECTOR_HPP
#define BOOST_INTRUSIVE_DETAIL_FUNCTION_DETECTOR_HPP

#include <boost/intrusive/detail/config_begin.hpp>

namespace boost {
namespace intrusive {
namespace function_detector {

    typedef char NotFoundType;
    struct StaticFunctionType { NotFoundType x [2]; };
    struct NonStaticFunctionType { NotFoundType x [3]; };

    enum
         { NotFound          = 0,
           StaticFunction    = sizeof( StaticFunctionType )    - sizeof( NotFoundType ),
           NonStaticFunction = sizeof( NonStaticFunctionType ) - sizeof( NotFoundType )
         };

}  //namespace boost {
}  //namespace intrusive {
}  //namespace function_detector {

#define BOOST_INTRUSIVE_CREATE_FUNCTION_DETECTOR(Identifier, InstantiationKey) \
   namespace boost { \
   namespace intrusive { \
   namespace function_detector { \
   template < class T, \
            class NonStaticType, \
            class NonStaticConstType, \
            class StaticType > \
   class DetectMember_##InstantiationKey_##Identifier { \
      template < NonStaticType > \
      struct TestNonStaticNonConst ; \
      \
      template < NonStaticConstType > \
      struct TestNonStaticConst ; \
      \
      template < StaticType > \
      struct TestStatic ; \
      \
      template <class U > \
      static NonStaticFunctionType Test( TestNonStaticNonConst<&U::Identifier>*, int ); \
      \
      template <class U > \
      static NonStaticFunctionType Test( TestNonStaticConst<&U::Identifier>*, int ); \
      \
      template <class U> \
      static StaticFunctionType Test( TestStatic<&U::Identifier>*, int ); \
      \
      template <class U> \
      static NotFoundType Test( ... ); \
   public : \
      static const int check = NotFound + (sizeof(Test<T>(0, 0)) - sizeof(NotFoundType));\
   };\
}}} //namespace boost::intrusive::function_detector { 

#define BOOST_INTRUSIVE_DETECT_FUNCTION(Class, InstantiationKey, ReturnType, Identifier, Params) \
    ::boost::intrusive::function_detector::DetectMember_##InstantiationKey_##Identifier< Class,\
                                         ReturnType (Class::*)Params,\
                                         ReturnType (Class::*)Params const,\
                                         ReturnType (*)Params \
                                       >::check

#include <boost/intrusive/detail/config_end.hpp>

#endif   //@ifndef BOOST_INTRUSIVE_DETAIL_FUNCTION_DETECTOR_HPP
