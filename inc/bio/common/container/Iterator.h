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

#include "bio/common/container/common/Types.h"
#include "bio/common/macro/Macros.h"

namespace bio {

class Container;

/**
 * An Iterator is the preferred means of accessing the elements stored in an Container. <br />
 * Please use increment and decrement operators to move through these elements. <br />
 * While untested, it is likely that starting at the end and decrementing will be faster than starting at the beginning and incrementing, due to removing the overhead of having to keep track of where the end is. <br />
 *
 * NOTE: There are no checks to guard against being given a bad Container*. These have been neglected to increase performance. <br />
 */
class Iterator
{
public:

	/**
	 * Constructor is only built with a const Container*. <br />
	 * We cast away the cv and keep only the mutable pointer. <br />
	 * This is done in order to avoid having a separate class for const access (as is in the standard library). <br />
	 * @param container
	 * @param index
	 */
	Iterator(
		const Container* container,
		const Index index = InvalidIndex());

	/**
	 *
	 */
	virtual ~Iterator();

	/**
	 * @return the index *this is currently at.
	 */
	Index GetIndex() const;

	/**
	 * Make *this point somewhere else; <br />
	 * @param index
	 * @return whether or not *this was moved.
	 */
	bool MoveTo(const Index index);

	/**
	 * @return whether or not *this has reached the beginning of its Arrangement.
	 */
	virtual bool IsBeforeBeginning() const;

	/**
	 * @return whether or not *this has reached the end of its Arrangement.
	 */
	virtual bool IsAfterEnd() const;

	/**
	 * Move *this up a Index <br />
	 * @return *this after incrementing.
	 */
	virtual Iterator& Increment();

	/**
	 * Move *this down a Index. <br />
	 * @return *this following decrementing.
	 */
	virtual Iterator& Decrement();

	/**
	 * Dereferencing gives the datum *this is currently pointing to. <br />
	 * @return a ByteStream containing the datum requested.
	 */
	virtual ByteStream operator*();

	/**
	 * Dereferencing gives the datum *this is currently pointing to. <br />
	 * @return a ByteStream containing the datum requested.
	 */
	virtual const ByteStream operator*() const;

	/**
	 * Can check if *this is valid through multiple heuristics (e.g. Index() == InvalidIndex())
	 * @return if *this points to a usable Index.
	 */
	bool IsValid() const;

	/**
	 * Makes IsValid return false.
	 * i.e. MoveTo(InvalidIndex()).
	 */
	virtual void Invalidate();

protected:
	mutable Container* mContainer;
	Index mIndex;
}; //Iterator class.

} //bio namespace
