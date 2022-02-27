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

#include "bio/genetic/Genome.h"

namespace bio {
namespace genetic {

GenomeImplementation::GenomeImplementation() :
	genetic::Class < GenomeImplementation >(this, "Genome", NULL, filter::Genetic())
{

}

GenomeImplementation::~GenomeImplementation()
{

}

void GenomeImplementation::CacheProteins()
{
	mc_registerPlasmid = RotateTo("RegisterPlasmid");
	mc_fetchPlasmid = RotateTo("FetchPlasmid");
	mc_registrationSite = mc_registerPlasmid.GetIdWithoutCreation("Plasmid Binding Site");
	mc_nameSite = mc_fetchPlasmid->GetIdWithoutCreation("Name Binding Site");
	mc_idSite = mc_fetchPlasmid->GetIdWithoutCreation("Id Binding Site");
	mc_fetchSite = mc_fetchPlasmid->GetIdWithoutCreation("Return Site");
}

StandardDimension GenomeImplementation::RegisterPlasmid(Plasmid* toRegister)
{
	StandardDimension ret = PlasmidPerspective::InvalidId();
	LockThread();
	mc_registerPlasmid->RotateTo(mc_registrationSite)->Bind(toRegister);
	ret = mc_registerPlasmid->Activate();
	UnlockThread();
	return ret;
}

Plasmid* GenomeImplementation::FetchPlasmid(StandardDimension plasmidId)
{
	Plasmid* ret = NULL;
	LockThread();
	mc_fetchPlasmid->RotateTo(mc_idSite)->Bind(plasmidId);
	mc_fetchPlasmid->Activate();
	ret = mc_fetchPlasmid->RotateTo< Plasmid* >(mc_fetchSite);
	UnlockThread();
	return ret;

}

Plasmid* GenomeImplementation::FetchPlasmid(Name plasmidName)
{
	Plasmid* ret = NULL;
	LockThread();
	mc_fetchPlasmid->RotateTo(mc_nameSite)->Bind(plasmidName);
	mc_fetchPlasmid->Activate();
	ret = mc_fetchPlasmid->RotateTo< Plasmid* >(mc_fetchSite);
	UnlockThread();
	return ret;
}

} //genetic namespace
} //bio namespace
