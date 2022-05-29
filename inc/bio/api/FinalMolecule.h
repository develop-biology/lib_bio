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

#include "bio/api/internal/Final.h"
#include "bio/api/macros/Macros.h"
#include "bio/molecular/Molecule.h"

namespace bio {
namespace api {

/**
 * A FinalMolecule removes all the inheritance machinery from Molecule. <br />
 * Use this when you want to create your own Molecules but not allow anyone else to override Biology methods when inheriting from them. <br />
 */
class FinalMolecule :
	public bio::Final< bio::molecular::Molecule >
{
public:

	BIO_CONSTRUCONSTRUCTORS(FinalMolecule, bio::Final< bio::molecular::Molecule >)

	virtual ~FinalMolecule() {}

	BIO_FINAL_MOLECULE_METHODS
};

} //api namespace
} //bio namespace
