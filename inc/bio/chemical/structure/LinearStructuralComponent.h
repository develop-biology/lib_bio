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

#include "bio/chemical/Class.h"
#include "bio/chemical/Element.h"
#include "bio/chemical/structure/StructuralComponent.h"
#include "bio/chemical/structure/implementation/LinearStructuralComponentImplementation.h"
#include "bio/chemical/structure/implementation/LinearStructureInterface.h"

namespace bio {
namespace chemical {

/**
 * LinearStructuralComponent objects contain pointers to Substances.
 *
 * IMPORTANT: CONTENT_TYPE MUST BE A Substance* in the StandardDimension.
 * YOU CANNOT USE LinearStructuralComponent WITH TYPES THAT ARE NOT chemical::Substance*
 *
 * Other Dimensions may be supported in a future release (see note in LinearStructuralComponentImplementation.h for why).
 *
 * The "linear" comes from the idea that instead of a 1 dimensional pile of types, as are StructuralComponents, *this can be ordered along some higher dimension (i.e. the StandardDimension). In other words, LinearStructuralComponents contain logic for handling their CONTENT_TYPE by Id, Name, and other aspects innate to the physical::Identifiable<StandardDimension>.
 *
 * @tparam CONTENT_TYPE a pointer type to a child of chemical::Substance
 */
template <typename CONTENT_TYPE>
class LinearStructuralComponent :
	virtual public LinearStructureInterface,
	public Element<LinearStructuralComponent<CONTENT_TYPE>>,
	public Class<LinearStructuralComponent<CONTENT_TYPE>>,
	public LinearStructuralComponentImplementation<CONTENT_TYPE>
{
public:

	/**
	 * Each LinearStructuralComponent may use a different Perspective for identifying its contents.
	 * This Perspective will be used for Name <-> Id matching, Wave->Clone()ing, etc.
	 * See bio/physical/Perspective.h for more details.
	 */
	Perspective <StandardDimension>* m_perspective;

	/**
	 * @return the m_perspective used by *this.
	 */
	Perspective <StandardDimension>* GetPerspective()
	{
		return m_perspective;
	}

	/**
	 * @return the m_perspective used by *this.
	 */
	const Perspective <StandardDimension>* GetPerspective() const
	{
		return m_perspective;
	}

	/**
	 * @param perspective
	 */
	explicit LinearStructuralComponent(Perspective <StandardDimension>* perspective = NULL)
		:
		Element<LinearStructuralComponent<CONTENT_TYPE>>(AbstractStructure::GetClassProperties()),
		Class(this),
		m_perspective(perspective)
	//NOTE: Writer not initialized here!
	{
		CtorCommon();
	}

	/**
	 * @param contents
	 * @param name
	 * @param perspective
	 */
	explicit LinearStructuralComponent(
		typename const StructuralComponentImplementation<CONTENT_TYPE>::Contents& contents,
		Perspective <StandardDimension>* perspective = NULL)
		:
		Element<LinearStructuralComponent<CONTENT_TYPE>>(AbstractStructure::GetClassProperties()),
		Class(this),
		StructuralComponent<CONTENT_TYPE>(contents),
		m_perspective(perspective)
	{
		CtorCommon();
	}

	/**
	 * Copying a LinearStructuralComponent will Clone all contents in toCopy into *this.
	 * Keep in mind that dtor will delete the contents of *this.
	 * @param toCopy
	 */
	LinearStructuralComponent(const LinearStructuralComponent<CONTENT_TYPE>& toCopy)
		:
		Class(this)
	{
		CtorCommon();
		m_perspective = toCopy.m_perspective;
		for (
			typename StructuralComponentImplementation<CONTENT_TYPE>::Contents::iterator cnt = toCopy.m_contents.begin();
			cnt != toCopy.m_contents.end();
			++cnt
			)
		{
			AddImplementation((*cnt)->Clone());
		}
	}

	/**
	 * Deletes all the Contents in *this.
	 * NOTE: this uses delete, not delete[].
	 * The only way to avoid this is by Clear()ing *this yourself first.
	 */
	virtual ~

	LinearStructuralComponent()
	{
		ClearImplementation();
	}


	/**
	 * Implementation for inserting a Content to *this.
	 * @param toAdd
	 * @param insertionPoint
	 * @param position
	 * @param optionalPositionArg
	 * @param transferSubContents
	 * @return status of insertion
	 */
	virtual Code InsertImplementation(
		CONTENT_TYPE toAdd,
		const typename LinearStructuralComponentImplementation<CONTENT_TYPE>::Dimensions& insertionPoint,
		const Position position = BOTTOM,
		const StandardDimension optionalPositionArg = CONTENT_TYPE::Perspective::InvalidId(),
		const bool transferSubContents = false)
	{
		return LinearStructuralComponentImplementation<CONTENT_TYPE>::Insert(
			this->GetPerspective(),
			toAdd,
			this->GetAllImplementation(),
			insertionPoint,
			position,
			optionalPositionArg,
			transferSubContents,
			this->GetLogEngine());
	}

	/**
	 * Implementation for getting by name.
	 * @param name
	 * @param recurse
	 * @return a CONTENT_TYPE of the given name or NULL.
	 */
	virtual CONTENT_TYPE GetByNameImplementation(
		Name name,
		const bool recurse = false)
	{
		return AbstractLinearStructuralComponent<CONTENT_TYPE>::FindByNameIn(
			this->GetPerspective(),
			this->GetAllImplementation(),
			name,
			recurse
		);
	}

	/**
	 * Implementation for getting by name.
	 * @param name
	 * @param recurse
	 * @return a CONTENT_TYPE of the given name or NULL.
	 */
	virtual const CONTENT_TYPE GetByNameImplementation(
		Name name,
		const bool recurse = false) const
	{
		return AbstractLinearStructuralComponent<CONTENT_TYPE>::FindByNameIn(
			this->GetPerspective(),
			this->GetAllImplementation(),
			name,
			recurse
		);
	}

	/**
	 * Create a CONTENT_TYPE from a given Id and adds it to *this.
	 * Clones the Wave associated with the given Id.
	 * This requires a valid Perspective in *this and for that Perspective to have an Wave registered with the given Id.
	 * @param id
	 * @return a newly created CONTENT_TYPE else NULL.
	 */
	virtual CONTENT_TYPE CreateImplementation(
		StandardDimension id)
	{
		BIO_SANITIZE(this->GetPerspective(), ,
			return NULL);
		return this->AddImplementation(
			this->GetPerspective()->GetNewObjectFromIdAs<CONTENT_TYPE>(id));
	}

	/**
	 * Tries to find a Content of the given id in *this and, optionally, the Contents beneath.
	 * If such an object doesn't exist, one is created from its Wave.
	 * @param id
	 * @param recurse
	 * @return A CONTENT_TYPE of the given id.
	 */
	virtual CONTENT_TYPE GetOrCreateByIdImplementation(
		StandardDimension id,
		const bool recurse = false)
	{
		CONTENT_TYPE ret = this->GetImplementation(
			id,
			recurse
		);
		if (ret)
		{
			return ret;
		}
		return this->CreateImplementation(id);
	}

	/**
	 * Tries to find a Content of the given id in *this and, optionally, the Contents beneath.
	 * If such an object doesn't exist, one is created from its Wave.
	 * @param name
	 * @param recurse
	 * @return A CONTENT_TYPE of the given id.
	 */
	virtual CONTENT_TYPE GetOrCreateByNameImplementation(
		Name name,
		const bool recurse = false)
	{
		BIO_SANITIZE(this->GetPerspective(), ,
			return NULL);
		StandardDimension id = this->GetPerspective()->GetIdFromName(name);
		CONTENT_TYPE ret = this->GetImplementation(
			id,
			recurse
		);
		if (ret)
		{
			return ret;
		}
		return this->CreateImplementation(id);
	}

private:

	/**
	 * Common constructor code.
	 */
	void CtorCommon()
	{
		BIO_SANITIZE_AT_SAFETY_LEVEL_1(Cast<Substance*>(CONTENT_TYPE), ,)
	}

};
} //chemical namespace
} //bio namespace