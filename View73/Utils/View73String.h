/********************************************************************
	filename: 	View73String
	author:		Pramod S
	
	purpose:	Game Engine created for learning
*********************************************************************/

#ifndef __View73String_h__
#define __View73String_h__

#include <string>
#include <stdlib.h>

# if defined(_MSC_VER)
# ifndef _CRT_SECURE_NO_DEPRECATE
# define _CRT_SECURE_NO_DEPRECATE (1)
# endif
# pragma warning(disable : 4996)//The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name
# endif

namespace View73
{
	class String
	{
	private:
		std::string m_String;

	public:

		String(){}
		String(const char* _cStr):m_String(_cStr){}
		String(const std::string& _str):m_String(_str){}
		~String(){}

		inline const char* CString() const	{	return m_String.c_str();				}
		inline const std::string& StdString() const {	return m_String;				}
		inline unsigned int Length() const	{	return (unsigned int)(m_String.size());	}

		inline String operator + ( const String& _right ) const
		{
			return String(m_String + _right.m_String);
		}

		inline String operator + ( const char* _right ) const
		{
			return String(m_String + _right);
		}

		inline String operator + ( int _value ) const
		{
			char strng[32];
			return String(m_String + itoa(_value,strng,10));
		}

		inline String operator + ( unsigned int _value ) const
		{
			//TODO: check itoa for unsigned int
			char strng[32];
			return String(m_String + itoa(_value,strng,10));
		}

		inline String operator + ( long _value ) const
		{
			char strng[32];
			return String(m_String + ltoa(_value,strng,10));
		}

		inline String operator + ( unsigned long _value ) const
		{
			char strng[32];
			return String(m_String + ultoa(_value,strng,10));
		}

		inline bool operator == ( const String& _right ) const
		{
			return (m_String == _right.m_String);	
		}

		inline bool operator != ( const String& _right ) const
		{
			return (m_String != _right.m_String);	
		}

		inline bool operator >= ( const String& _right ) const
		{
			return (m_String >= _right.m_String);	
		}

		inline bool operator > ( const String& _right ) const
		{
			return (m_String > _right.m_String);	
		}

		inline bool operator <= ( const String& _right ) const
		{
			return (m_String <= _right.m_String);	
		}

		inline bool operator < ( const String& _right ) const
		{
			return (m_String < _right.m_String);	
		}

		//friend functions
		inline friend String operator + ( const std::string& _left, const String& _right)
		{
			return (String(_left) + String(_right));
		}

		inline friend String operator + ( const char* _left, const String& _right)
		{
			return (String(_left) + String(_right));
		}

		inline friend String operator + ( const std::string& _left, const char* _right)
		{
			return (String(_left) + String(_right));
		}

		//TODO: Error if used as "string1" + 1 + "string2"
		//Don't know how to fix
		inline friend String operator + ( int _value , const String& _right)
		{
			return (String() + _value + _right);
		}

		inline friend String operator + ( unsigned int _value , const String& _right)
		{
			return (String() + _value + _right);
		}

		inline friend String operator + ( long _value , const String& _right )
		{
			return (String() + _value + _right);
		}

		inline friend String operator + ( unsigned long _value , const String& _right )
		{
			return (String() + _value + _right);
		}
	};


}

#endif