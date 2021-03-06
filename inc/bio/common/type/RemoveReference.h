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

#include "bio/common/macro/Macros.h"

//@formatter:off
#if BIO_CPP_VERSION >= 11
	#include <type_traits>
#endif
//@formatter:on

namespace bio {
namespace type {

//@formatter:off
#if BIO_CPP_VERSION < 11
	template<typename T>
	struct RemoveReferenceImplementation {typedef T Type;};

	template<typename T>
	struct RemoveReferenceImplementation<T&> {typedef T Type;};
#endif
//@formatter:on

/**
 * Strips '&' from the end of T <br />
 * @tparam T
 */
template < typename T >
struct RemoveReference
{
	//@formatter:off
	#if BIO_CPP_VERSION < 11
		typedef typename RemoveReferenceImplementation< T >::Type Type;
	#else
		typedef typename ::std::remove_reference<T>::type Type;
	#endif
	//@formatter:on
};

} //type namespace
} //bio namespace
