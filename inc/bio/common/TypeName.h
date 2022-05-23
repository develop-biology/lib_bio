/*
 * This file is a part of the Biology project by eons LLC.
 * Biology (aka Develop Biology) is a framework for approaching software
 * development from a natural sciences perspective.
 *
 * Copyright (C) 2022 Séon O'Shannon & eons LLC
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "String.h"

namespace bio {

//Modified from: https://stackoverflow.com/questions/35941045/can-i-obtain-c-type-names-in-a-constexpr-way

/**
 * FORWARD DECLARATION <br />
 * @tparam T
 * @return Just T as a string.
 */
template < typename T >
const char* TypeName();

/**
 * @return "void"
 */
template <>
inline const char* TypeName< void >()
{
	return "void";
}

/**
 * Used to determine magic numbers in extracting symbols as type. <br />
 */
typedef void TypeNameProber;

/**
 * Converts the T symbol to a string. <br />
 * Only supported on a limited number of compilers. <br />
 * @tparam T
 * @return T as a string with wrapping symbols.
 */
template < typename T >
static const ::std::string WrappedTypeName()
{
	#ifdef __clang__
	return __PRETTY_FUNCTION__;
	#elif defined(__GNUC__)
	return __PRETTY_FUNCTION__;
	#elif defined(_MSC_VER)
	return __FUNCSIG__;
	#else
		#error "Unsupported compiler"
	#endif
}

/**
 * Used to trim leading characters from symbol string. <br />
 * @return magic number for prefix length.
 */
static const ::std::size_t WrappedTypeNamePrefixLength()
{
	return WrappedTypeName< TypeNameProber >().find(TypeName< TypeNameProber >());
}

/**
 * Used to trim trailing characters from symbol string. <br />
 * @return magic number for suffix length.
 */
static const ::std::size_t WrappedTypeNameSuffixLength()
{
	return WrappedTypeName< TypeNameProber >().length() - WrappedTypeNamePrefixLength() - strlen(TypeName< TypeNameProber >());
}

/**
 * Converts the T symbol to a string. <br />
 * @tparam T
 * @return Just T as a string.
 */
template < typename T >
static const char* TypeName()
{
	static const ::std::string wrappedName = WrappedTypeName< T >();
	static const ::std::size_t prefixLength = WrappedTypeNamePrefixLength();
	static const ::std::size_t suffixLength = WrappedTypeNameSuffixLength();
	static const ::std::size_t typeNameLength = wrappedName.length() - prefixLength - suffixLength;
	::std::string name = wrappedName.substr(
		prefixLength,
		typeNameLength
	);

	const char* ret;
	string::CloneInto(name.c_str(), ret); //TODO: Memory leak.
	return ret;
}

/**
 * Converts the T symbol to a string. <br />
 * @tparam T
 * @param t used for auto type determination.
 * @return Just T as a string.
 */
template < typename T >
static const char* TypeName(const T t)
{
	return TypeName< T >();
}

} //bio namespace
