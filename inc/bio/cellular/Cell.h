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

#include "bio/cellular/common/Class.h"
#include "bio/cellular/common/Types.h"
#include "bio/cellular/common/Filters.h"
#include "bio/cellular/macros/Macros.h"
#include "bio/genetic/Expressor.h"
#include "bio/genetic/Plasmid.h"

namespace bio {

namespace cellular {
class Tissue;
}

namespace cellular {

class Organelle;

/**
 * A Cell is the basic unit of function-driven organization within Biology.
 * Cells use Proteins & Organelles to accomplish tasks. You can think of each Protein as a stand-in for a class method except, instead of hard-coding your classes, you instead code in (hard or soft) the TranscriptionFactors and Plasmids present in a Cell. The Cell then determines its functionality at runtime.
 *
 * In order to simplify the arbitrarily complex behavior that a Cell can perform, Cells are made to Peak, allowing their main function to be called on a clock at a regular interval.
 * Programming a Cell this way is similar to programming an Arduino with a main loop.
 * Of course, you are allowed to modify this behavior in any way you'd like ;)
 */
class Cell :
	public Class< Cell >,
	public chemical::LinearMotif< Organelle* >,
	public molecular::EnvironmentDependent< cellular::Tissue >,
	virtual public genetic::Expressor
{
public:

	/**
	 * Ensure virtual methods point to Class implementations.
	 */
	BIO_DISAMBIGUATE_ALL_CLASS_METHODS(cellular,
		Cell)

	/**
	 * Standard ctors.
	 */
	 BIO_DEFAULT_IDENTIFIABLE_CONSTRUCTORS(cellular,
		Cell,
		&CellPerspective::Instance(),
		filter::Cellular())

	/**
	 *
	 */
	virtual ~Cell();

	/**
	 * Peak()s occur at Periodic::m_intervals.
	 * Define your main Periodic logic here.
	 * This method must be fast:
	 *	* do not read slow hardware here
	 *	* do not block for a long time
	 *	* do not sleep
	 * If derived classes must do slow work to oscillate, that slow logic MUST BE placed in a separate thread.
	 * This method would then get the data stored by that thread and returns the data *quickly*. MAKE SURE that the thread never causes a long mutex wait as a side-effect in this Peak method.
	 * Please call this method when you're done :)
	 */
	virtual Code Peak()
	{

		//     YOU CODE GOES HERE!

		return cellular::Class< Cell >::Peak();
	}

};

} //cellular namespace
} //bio namespace
