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

#include "bio/cellular/common/Types.h"
#include "bio/cellular/macros/Macros.h"
#include "bio/chemical/reaction/Excitation.h"
#include "bio/physical/Wave.h"
#include "bio/physical/Periodic.h"

namespace bio {
namespace cellular {

/**
 * The PeakCarrierWave will propagate Peak Excitations to all LinearMotifs
 */
class PeakCarrierWave :
	public physical::Wave
{
public:

	/**
	 *
	 */
	PeakCarrierWave();

	/**
	 *
	 */
	virtual ~PeakCarrierWave();

	/**
	 * Makes *this compatible with Motifs by copying the Properties of AbstractMotif.
	 * @return { Linear(), AbstractMotif::GetClassProperties() }
	 */
	virtual Properties GetProperties() const;

protected:
	BIO_EXCITATION_CLASS(physical::Periodic,
		Code) m_peakExcitation;
};

} //cellular namespace
} //bio namespace
