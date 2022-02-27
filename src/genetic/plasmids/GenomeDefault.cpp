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

#include "bio/genetic/plasmids/GenomeDefault.h"
#include "bio/genetic/proteins/RegisterPlasmid.h"
#include "bio/genetic/proteins/FetchPlasmid.h"

namespace bio {
namespace genetic {

GenomeDefault::GenomeDefault()
{
	Gene* registerPlasmid = new Gene("Register Plasmid Default");
	registerPlasmid->SetProtein(new RegistrePlasmid());
	registerPlasmid->Add< TranscriptionFactor >(transcription_factor::Genome());
	Add< Gene* >(registerPlasmid);

	Gene* registerPlasmid = new Gene("Fetch Plasmid Default");
	fetchPlasmid->SetProtein(new FetchPlasmid());
	fetchPlasmid->Add< TranscriptionFactor >(transcription_factor::Genome());
	Add< Gene* >(fetchPlasmid);
}

GenomeDefault::~GenomeDefault()
{
	//Gene*s will be automatically deleted.
}

} //genetic namespace
} //bio namespace
