/*
  Реализация класса String из библиотеки Arduino с помощью std::string
  Для использования в тестировании без подключения библиотеки Arduino
  Оригинальный файл находится здесь:
  https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Arduino.h
*/
#pragma once

#include <string>
#include <algorithm>

// The string class
class String
{
	std::string str;
	
public:
	String( const char *cstr = "" ) { str = cstr; };
	String( const String &s ) { str = s.str; };
	String( String &&rval ) { str = rval.str; };

	explicit String( char c ) { str = c; };
	explicit String( unsigned char c, unsigned char base = 10 ) { str = std::to_string( c ); }
	explicit String( int num, unsigned char base = 10 ) { str = std::to_string( num ); }
	explicit String( unsigned int num, unsigned char base = 10 ) { str = std::to_string( num ); }
	explicit String( long num, unsigned char base = 10 ) { str = std::to_string( num ); }
	explicit String( unsigned long num, unsigned char base = 10 ) { str = std::to_string( num ); }
	explicit String( float num, unsigned char decimalPlaces = 2 ) { str = std::to_string( num ); }
	explicit String( double num, unsigned char decimalPlaces = 2 ) { str = std::to_string( num ); }
	~String( void ) {};

	unsigned char reserve( unsigned int size ) { str.reserve( size ); };
	inline unsigned int length( void ) const { return str.length(); }
	
	String & operator = ( const String &rhs ) { str = rhs.str; return *this; };
	String & operator = ( const char *cstr ) { str = cstr; return *this; };
	String & operator = ( String &&rval ) { str = rval.str; return *this; };

	unsigned char concat( const String &s ) { str += s.str; return true; }
	unsigned char concat( const char *cstr ) { str += cstr; return true; }
	unsigned char concat( char c ) { str += c; return true; }
	unsigned char concat( unsigned char c ) { str += c; return true; }
	unsigned char concat( int num ) { str += std::to_string(num); return true; }
	unsigned char concat( unsigned int num ) { str += std::to_string( num ); return true; }
	unsigned char concat( long num ) { str += std::to_string( num ); return true; }
	unsigned char concat( unsigned long num ) { str += std::to_string( num ); return true; }
	unsigned char concat( float num ) { str += std::to_string( num ); return true; }
	unsigned char concat( double num ) { str += std::to_string( num ); return true; }

	String & operator += ( const String &rhs ) { concat( rhs ); return ( *this ); }
	String & operator += ( const char *cstr ) { concat( cstr ); return ( *this ); }
	String & operator += ( char c ) { concat( c ); return ( *this ); }
	String & operator += ( unsigned char num ) { concat( num ); return ( *this ); }
	String & operator += ( int num ) { concat( num ); return ( *this ); }
	String & operator += ( unsigned int num ) { concat( num ); return ( *this ); }
	String & operator += ( long num ) { concat( num ); return ( *this ); }
	String & operator += ( unsigned long num ) { concat( num ); return ( *this ); }
	String & operator += ( float num ) { concat( num ); return ( *this ); }
	String & operator += ( double num ) { concat( num ); return ( *this ); }
	
	// comparison (only works w/ Strings and "strings")
	unsigned char equals( const String &s ) const { return str == s.str; };
	unsigned char equals( const char *cstr ) const { return str == cstr; };;
	unsigned char operator == ( const String &rhs ) const { return equals( rhs ); }
	unsigned char operator == ( const char *cstr ) const { return equals( cstr ); }
	unsigned char operator != ( const String &rhs ) const { return !equals( rhs ); }
	unsigned char operator != ( const char *cstr ) const { return !equals( cstr ); }
	unsigned char operator <  ( const String &rhs ) const { return str < rhs.str; };
	unsigned char operator >  ( const String &rhs ) const { return str > rhs.str; };
	unsigned char operator <= ( const String &rhs ) const { return str <= rhs.str; };
	unsigned char operator >= ( const String &rhs ) const { return str >= rhs.str; };
	unsigned char equalsIgnoreCase( const String &s )  const
	{
		String thisLowerCase( *this );
		thisLowerCase.toLowerCase();
		String sLowerCase( s );
		sLowerCase.toLowerCase();		
		return thisLowerCase == sLowerCase;		
	}
	unsigned char startsWith( const String &prefix ) const { return startsWith( prefix, 0); }
	unsigned char startsWith( const String &prefix, unsigned int offset ) const
	{
		if( str.length() >= prefix.length() + offset )
			return str.substr( offset , prefix.length() ) == prefix.str;
		else
			return false;
	}
	unsigned char endsWith( const String &suffix ) const
	{		
		if( str.length() >= suffix.length() )
			return str.substr( str.length() - suffix.length(), suffix.length() ) == suffix.str;
		else
			return false;
	}

	// character acccess
	char charAt( unsigned int index ) const { return str[index]; }
	void setCharAt( unsigned int index, char c ) { str[index] = c; }
	char operator [] ( unsigned int index ) const { return str[index]; }
	char& operator [] ( unsigned int index ) { return str[index]; }
	void getBytes( unsigned char *buf, unsigned int bufsize, unsigned int index = 0 ) const { memcpy( buf, &str[index], bufsize); };
	void toCharArray( char *buf, unsigned int bufsize, unsigned int index = 0 ) const { getBytes( ( unsigned char * )buf, bufsize, index ); }
	const char* c_str() const { return str.c_str(); }
	char* begin() { return str.length() > 0 ? &str[0] : nullptr; }
	char* end() { return str.length() > 0 ? &str[length()-1] : nullptr; }
	const char* begin() const { return begin(); }
	const char* end() const { return end(); }

	// search
	int indexOf( char ch ) const { return indexOf( ch, 0 ); }
	int indexOf( char ch, unsigned int fromIndex ) const { return str.find( ch, fromIndex ); }
	int indexOf( const String &s ) const { return indexOf( s, 0 ); }
	int indexOf( const String &s, unsigned int fromIndex ) const { return str.find( s.c_str(), fromIndex ); }
	int lastIndexOf( char ch ) const { return lastIndexOf( ch, 0 ); }
	int lastIndexOf( char ch, unsigned int fromIndex ) const { return str.rfind( ch, fromIndex ); }
	int lastIndexOf( const String &s ) const { return lastIndexOf( s, 0 ); }
	int lastIndexOf( const String &s, unsigned int fromIndex ) const { return str.rfind( s.c_str(), fromIndex ); }
	String substring( unsigned int beginIndex ) const { return substring( beginIndex, length() ); };
	String substring( unsigned int beginIndex, unsigned int endIndex ) const { return str.substr( beginIndex, length() ).c_str(); };

	// modification
	void replace( char find, char replace ) { std::replace( str.begin(), str.end(), find, replace ); }
	void replace( const String& find, const String& replace ) { std::replace( str.begin(), str.end(), find, replace ); }
	void remove( unsigned int index ) { str.erase( index ); }
	void remove( unsigned int index, unsigned int count ) { str.erase( index, count ); }
	void toLowerCase( void ) { std::transform( str.begin(), str.end(), str.begin(), ::tolower ); }
	void toUpperCase( void ) { std::transform( str.begin(), str.end(), str.begin(), ::toupper ); }
	void trim( void )
	{
		const char* trimChars = " \n\r\t";
		str.erase( str.find_first_not_of( trimChars ) );
		str.erase( str.find_last_not_of( trimChars ) + 1 );
	}

	// parsing/conversion
	long toInt( void ) const { return std::stol( str ); }
	float toFloat( void ) const { return std::stof( str ); };
	double toDouble( void ) const { return std::stod( str ); };
};