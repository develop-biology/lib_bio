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

#include "Class.h"
#include "Symmetry.h"
#include "SymmetryTypes.h"
#include "bio/common/Macros.h"
#include "bio/common/TypeName.h"

namespace bio {
namespace physical {

/**
 * Quanta are simple Waves intended for built-in types.
 * They allow anything to be treated as a Biological Wave.
 * Iff you cannot derive from Wave, use Quantum<> instead.
 * Each Quantum<T> will store a pointer to a T which it will new on creation and delete on destruction.
 * @tparam T
 */
template <typename T>
class Quantum : public Class<Quantum<T>>
{
public:
	/**
	 *
	 */
	Quantum() :
		Class(this, new Symmetry(TypeName(T), symmetry_type::DefineVariable())),
		m_quantized(new T())
	{

	}

	/**
	 * @param assignment
	 */
	Quantum(const T& assignment) :
		Class(this, new Symmetry(TypeName(T), symmetry_type::DefineVariable())),
		m_quantized(new T(assignment))
	{
	}

	/**
	 * @param other
	 */
	Quantum(const Quantum<T>& other) :
		Class(this, new Symmetry(TypeName(T), symmetry_type::DefineVariable())),
		m_quantized(new T(other)),
	{

	}

	/**
	 *
	 */
	virtual ~Quantum()
	{
		delete m_quantized;
	}

	/**
	 * *this can be treated as a T* directly.
	 * @return *this as a T*.
	 */
	T* operator T*()
	{
		return m_quantized;
	}

	/**
	 * @return *this as a const T*.
	 */
	const T* operator T*() const
	{
		return m_quantized;
	}

	/**
	 * Read only access to the value of *this.
	 * For ease of use.
	 * @return *this as a T.
	 */
	T operator T() const
	{
		BIO_SANITIZE(m_quantized, return *m_quantized, return T());
	}

	/**
	 * Required method from Wave. See that class for details.
	 * @return a Symmetrical image of *this
	 */
	virtual Symmetry* Spin() const
	{
		m_symmetry->AccessValue()->Set(m_quantized);
		return Wave::Spin();
	}

	/**
	 * Required method from Wave. See that class for details.
	 * Reconstruct *this from the given Symmetry.
	 * @param symmetry
	 */
	virtual void Reify(Symmetry* symmetry)
	{
		BIO_SANITIZE(symmetry,,return);
		//Wave::Reify(symmetry); //this does nothing useful.
		m_quantized = symmetry->GetValue();
	}

	/**
	 * Forwards += to m_quantized.
	 * @param other
	 */
	virtual void operator += (const Quantum<T>* other)
	{
		BIO_SANITIZE(other, , return NULL);
		m_quantized += other->m_quantized;
	}

	/**
	 * Forwards -= to m_quantized.
	 * @param other
	 */
	virtual void operator -= (const Quantum<T>* other)
	{
		BIO_SANITIZE(other, , return NULL);
		m_quantized -= other->m_quantized;
	}

protected:
	T* m_quantized;
};

} //physical namespace
} //bio namespace