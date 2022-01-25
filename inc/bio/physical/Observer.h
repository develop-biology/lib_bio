/*
 * This file is a part of the Biology project by eons LLC.
 * Biology (aka Develop Biology) is a framework for approaching software
 * development from a natural sciences perspective.
 *
 * Copyright (C) 2021 Séon O'Shannon & eons LLC
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

#include "Perspective.h"
#include "bio/common/VirtualBase.h"

namespace bio {
namespace physical {

/**
 * An Observer class is one that has a PERSPECTIVE.
 * This is intended for Identifiable classes (see Identifiable.h) and any other classes that manage or work with Identifiable classes.
*/
template <typename PERSPECTIVE>
class Observer :
	public VirtualBase
{
public:
	typedef PERSPECTIVE Perspective;

	/**
	 * @param perspective
	 */
	explicit Observer(Perspective* perspective = NULL)
		:
		m_perspective(perspective)
	{
	}

	/**
	 * @param other
	 */
	Observer(const Observer& other)
		:
		m_perspective(other.m_perspective)
	{
	}

	/**
	 *
	 */
	virtual ~Observer()
	{
	}

	/**
	 * VirtualBase required method. See that class for details (in common/)
	 * @param args
	 */
	virtual void InitializeImplementation(ByteStreams args)
	{
		BIO_SANITIZE(args.size() == 1 && args[0].Is(m_perspective));
		m_perspective = args[0];
	}

	/**
	 * Sets the perspective for *this.
	 * @param perspective
	 */
	virtual void SetPerspective(Perspective* perspective)
	{
		m_perspective = perspective;
	}

	/**
	 * @return the perspective held by *this.
	 */
	Perspective* GetPerspective() const
	{
		return m_perspective;
	}

private:
	Perspective* m_perspective;
};

} //physical namespace
} //bio namespace