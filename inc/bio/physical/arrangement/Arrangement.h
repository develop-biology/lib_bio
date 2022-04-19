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

#include "bio/common/container/Container.h"
#include "bio/physical/macros/Macros.h"

namespace bio {
namespace physical {

/**
 * Arrangements provide a more memory-efficient interface of the Container interface for a single type. <br />
 * @tparam TYPE
 */
template < typename TYPE >
class Arrangement :
	public Container
{
public:

	/**
	 * @param expectedSize
	 */
	Arrangement(const Index expectedSize = 2)
		:
		Container(
			expectedSize,
			sizeof(TYPE))
	{

	}

	/**
	 *
	 */
	virtual ~Arrangement()
	{

	}

	Index Add(const ByteStream content)
	{
		BIO_SANITIZE(content.Is< TYPE >(), ,
			return InvalidIndex())
		Index ret = this->GetNextAvailableIndex();
		BIO_SANITIZE(ret, ,
			return InvalidIndex())
		TYPE toAdd = content;
		std::memcpy(
			&this->m_store[ret * sizeof(TYPE)],
			&toAdd,
			sizeof(TYPE));
		return ret;
	}

	ByteStream Access(const Index index)
	{
		BIO_SANITIZE(this->IsAllocated(index), ,
			return NULL)
		TYPE* ret; 
		std::memcpy(
			ret,
			&this->m_store[index * sizeof(TYPE)],
			sizeof(TYPE));
		return *ret;
	}

	const ByteStream Access(const Index index) const
	{
		BIO_SANITIZE(this->IsAllocated(index), ,
			return NULL)
		TYPE* ret; 
		std::memcpy(
			ret,
			&this->m_store[index * sizeof(TYPE)],
			sizeof(TYPE));
		return *ret;
	}

	bool Erase(const Index index)
	{
		BIO_SANITIZE(this->IsAllocated(index), ,
			return false)
		TYPE* toDelete; 
		std::memcpy(
			toDelete,
			&this->m_store[index * sizeof(TYPE)],
			sizeof(TYPE));
		delete toDelete;
		this->m_deallocated.push_back(index);
		return true;
	}

	virtual bool AreEqual(
		Index internal,
		const ByteStream external
	) const
	{
		BIO_SANITIZE(external.Is< TYPE >(), ,
			return false)
		return this->Access(internal).template As< TYPE >() == external.template As< TYPE >();
	}

	/**
	 * Convenience wrapper for accessing without casting. <br />
	 * @param index
	 * @return the given position in *this as a TYPE.
	 */
	virtual TYPE OptimizedAccess(Index index)
	{
		return this->Access(index);
	}

	/**
	 * Convenience wrapper for accessing without casting. <br />
	 * @param index
	 * @return the given position in *this as a TYPE.
	 */
	virtual const TYPE OptimizedAccess(Index index) const
	{
		return this->Access(index).template As< TYPE >();
	}

	/**
	 * Please override this to return the size of the type your Container interface is working with. <br />
	 * @return the size of the data type stored in *this.
	 */
	virtual const ::std::size_t GetStepSize() const
	{
		return sizeof(TYPE);
	}
};

} //physical namespace
} //bio namespace
