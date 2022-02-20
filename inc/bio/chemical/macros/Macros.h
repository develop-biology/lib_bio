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

#include "bio/chemical/common/BondTypes.h"
#include "bio/physical/macros/Macros.h"

/**
 * Defines constructors for classes deriving from chemical::Class and beyond.
 * These will allow you to construct your object with either a name or an id.
 * We also define the empty constructor for when neither name nor id are supplied.
 *
 * IMPORTANT: despite using __VA_ARGS__, this will fail if nothing more than the namespace and class are provided.
 * At a minimum, you MUST ALSO INCLUDE THE Perspective AFTER class!
 * e.g. BIO_DEFAULT_IDENTIFIABLE_CONSTRUCTORS(my_namespace, MyClass, &MyClassPerspective::Instance())
 *
 * NOTE: if your class has multiple template args or otherwise uses commas in its name, you must enclose it in BIO_SINGLE_ARG() so as to not have it be considered part of the __VA_ARGS__.
 * @param ns the namespace of the class
 * @param class the name of the class
 * @param ... all arguments to the ns::Class<class>(...) constructor.
 */
#define BIO_DEFAULT_IDENTIFIABLE_CONSTRUCTORS(ns, class, ...)                  \
class() :                                                                      \
	ns::Class< class >(this, __VA_ARGS__)                                      \
{}                                                                             \
explicit class(Name name) :                                                    \
	ns::Class< class >(this, name, __VA_ARGS__)                                \
{}                                                                             \
explicit class(StandardDimension id) :                                         \
	ns::Class< class >(this, id, __VA_ARGS__)                                  \
{}

/**
 * Defines constructors for classes deriving from chemical::Class and beyond.
 * All constructors call a CtorCommon() method with no args.
 * These will allow you to construct your object with either a name or an id.
 * We also define the empty constructor for when neither name nor id are supplied.
 *
 * IMPORTANT: despite using __VA_ARGS__, this will fail if nothing more than the namespace and class are provided.
 * At a minimum, you MUST ALSO INCLUDE THE Perspective AFTER class!
 * e.g. BIO_DEFAULT_IDENTIFIABLE_CONSTRUCTORS(my_namespace, MyClass, &MyClassPerspective::Instance())
 *
 * NOTE: if your class has multiple template args or otherwise uses commas in its name, you must enclose it in BIO_SINGLE_ARG() so as to not have it be considered part of the __VA_ARGS__.
 *
 * @param ns the namespace of the class
 * @param class the name of the class
 * @param ... all arguments to the ns::Class<class>(...) constructor.
 */
#define BIO_DEFAULT_IDENTIFIABLE_CONSTRUCTORS_WITH_CTOR_COMMON(ns, class, ...) \
class() :                                                                      \
	ns::Class< class >(this, __VA_ARGS__)                                      \
{                                                                              \
	this->CtorCommon();                                                        \
}                                                                              \
explicit class(Name name) :                                                    \
	ns::Class< class >(this, name, __VA_ARGS__)                                \
{                                                                              \
	this->CtorCommon();                                                        \
}                                                                              \
explicit class(StandardDimension id) :                                         \
	ns::Class< class >(this, id, __VA_ARGS__)                                  \
{                                                                              \
	this->CtorCommon();                                                        \
}


/**
To make defining BondTypes easier, use this macro to define the function body of your BondType Function().
This will assign a value to a string that is identical to your FunctionName e.g. BondTypePerspective::Instance().GetNameFromId(Value()) would give "Value".
*/
#define BIO_CHEMICAL_BOND_TYPE_FUNCTION_BODY(functionName)                     \
BIO_ID_FUNCTION_BODY(                                                          \
    functionName,                                                              \
    ::bio::BondTypePerspective::Instance(),                                      \
    ::bio::BondType)


/**
 * Get all virtual methods defined by chemical::Class.
 * @return function signatures for use in BIO_DISAMBIGUATE_CLASS_METHODS
 */
#define BIO_GET_CLASS_METHODS_FOR_chemical()                                   \
    BIO_GET_CLASS_METHODS_FOR_physical(),                                      \
    (::bio::Properties GetProperties() const, GetProperties()),                  \
	(::bio::chemical::Atom* AsAtom(), AsAtom()),                                 \
	(const ::bio::chemical::Atom* AsAtom() const, AsAtom()),                     \
	(Code Attenuate(const ::bio::physical::Wave* other), Attenuate(other)),      \
    (Code Disattenuate(const ::bio::physical::Wave* other), Disattenuate(other))

#define BIO_EXCITATION_0(wave, ret, ...)                                       \
	ExcitationWithoutArgument< wave, ret >

#define BIO_EXCITATION_1(wave, ret, ...)                                       \
	ExcitationWithArgument< wave, ret, __VA_ARGS__ >

#define BIO_CREATE_EXCITATION_WITH_NUM(wave, ret, num, ...)                    \
	BIO_EXCITATION_##num(wave, ret, __VA_ARGS__)

/**
 * Work around for C++ < 17, where variadic macros are supported but variadic template parameters are not.
 * This will work with all versions of C++ (see undef below).
 * NOTE: only 1 argument is currently supported with C++ < 17. For 2 or more arguments, you must either extend this macro by creating your own Excitation and defining BIO_EXCITATION_2, etc. or use at least C++17.
 */
#define BIO_EXCITATION(wave, ret, ...)                                         \
	BIO_CREATE_EXCITATION_WITH_NUM(                                            \
		wave,                                                                  \
		ret,                                                                   \
		GET_NUM_ARGS(__VA_ARGS__),                                             \
		__VA_ARGS__                                                            \
	)

//@formatter:off
#if BIO_CPP_VERSION >= 17
	#undef BIO_EXCITATION
	#define BIO_EXCITATION(wave, ret ...)                                      \
		Excitation< wave, ret, ... >
#endif
//@formatter:on