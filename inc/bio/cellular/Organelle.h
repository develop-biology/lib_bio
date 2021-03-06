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

#include "bio/cellular/common/Class.h"
#include "bio/cellular/common/Types.h"
#include "bio/cellular/common/Filters.h"
#include "bio/cellular/macro/Macros.h"

namespace bio {
namespace cellular {

class Cell;

/**
 * Organelles are functionally grouped sets of Proteins. <br />
 * Create an Organelle for your Cells if you have complex behavior that you would like to isolate, conserve, and/or transport across your system. <br />
 */
class Organelle :
	public Class< Organelle >,
	public molecular::EnvironmentDependent< Cell >
{
public:

	/**
	 * Ensure virtual methods point to Class implementations. <br />
	 */
	BIO_DISAMBIGUATE_ALL_CLASS_METHODS(cellular,
		Organelle)

	/**
	 * Standard ctors. <br />
	 */ BIO_DEFAULT_IDENTIFIABLE_CONSTRUCTORS(cellular,
		Organelle,
		&OrganellePerspective::Instance(),
		filter::Molecular())

	/**
	 *
	 */
	virtual ~Organelle();

	/**
	 * Peak()s occur at Periodic::mIntervals. <br />
	 * Define your main Periodic logic here. <br />
	 * This method must be fast: <br />
	 *	* do not read slow hardware here <br />
	 *	* do not block for a long time <br />
	 *	* do not sleep <br />
	 * If derived classes must do slow work to oscillate, that slow logic MUST BE placed in a separate thread. <br />
	 * This method would then get the data stored by that thread and returns the data *quickly*. MAKE SURE that the thread never causes a long mutex wait as a side-effect in this Peak method. <br />
	 * Please call this method when you're done :) <br />
	 */
	virtual Code Peak()
	{

		//     YOU CODE GOES HERE!

		return cellular::Class< Organelle >::Peak();
	}
};

} //cellular namespace
} //bio namespace
