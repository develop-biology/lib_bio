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

#include "Language.h"

//@formatter:off
#if BIO_CPP_VERSION < 11
	#ifdef BIO_OS_IS_LINUX
		#include <pthread.h>
	#endif
#else
	#include <mutex>
#endif
//@formatter:on

namespace bio {

/**
 * ThreadSafe classes are ones that can work with threads.
 * They are meant to be simple and abstract.
 * The actual implementation of ThreadSafe methods is c++ version and platform specific.
 * Fortunately, threading was standardized in c++11; however, we do still support c++98 builds.
 * At this time, ThreadSafe methods are only implemented for c++11 and on and on linux systems using c++98 and on.
 * Support for c++98 on other platforms may or may not ever happen.
 *
 * NOTE: if you do not need threading and don't want to waste time locking & unlocking a single thread all the time, check out Optimize.h (in bio/common), which will let you turn off threading for an extra performance boost.
 */
class ThreadSafe
{
public:
	/**
	 *
	 */
	ThreadSafe();

	/**
	 * @param toCopy
	 */
	ThreadSafe(const ThreadSafe& toCopy);

	/**
	 *
	 */
	virtual ~ThreadSafe();

	/**
	 * Lock the mutex member.
	 */
	virtual void LockThread();

	/**
	 * uses const_cast to call LockThread().
	 */
	void LockThread() const;

	/**
	 * Unlock the mutex member.
	 */
	virtual void UnlockThread();

	/**
	 * uses const_cast to call UnlockThread().
	 */
	void UnlockThread() const;

	//@formatter:off
	#if BIO_CPP_VERSION < 11
		#ifdef BIO_OS_IS_LINUX
			pthread_mutex_t m_lock;
		#endif
	#else
		std::mutex m_mutex;
		std::unique_lock<std::mutex> m_lock;
	#endif
	//@formatter:on
};

} //bio namespace