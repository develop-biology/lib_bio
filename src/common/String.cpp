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

#include "bio/common/String.h"

#include <cstring>

namespace bio {
namespace string {

bool ToBool(
	const char* s,
	bool* returned
)
{
	*returned = s == "true";
	if (!returned && s != "false")
	{
		return false;
	}
	return true;
}

bool ToInt(
	const char* s,
	int32_t* value
)
{
	if (strlen(s) == 0)
	{
		return false; //FAIL: empty string
	}

	char* endptr = NULL;
	*value = strtol(
		s,
		&endptr,
		10
	);
	return ((*endptr) == '\0');
}

bool ToUInt(
	const char* s,
	uint32_t* value
)
{
	if (strlen(s) == 0)
	{
		return false; //FAIL: empty string
	}

	char* endptr = NULL;
	*value = strtoul(
		s,
		&endptr,
		10
	);
	return ((*endptr) == '\0');
}

bool ToFloat(
	const char* s,
	float* value
)
{
	if (strlen(s) == 0)
	{
		return false; //FAIL: empty string
	}

	char* endptr = NULL;
	*value = strtof(
		s,
		&endptr
	);
	return ((*endptr) == '\0');
}

StdStrings Parse(
	const ::std::string& s,
	char delimiter,
	bool trimLeadingSpaces
)
{
	std::stringstream ss(s);
	StdStrings result;
	while (ss.good())
	{

		std::string substring;
		std::getline(
			ss,
			substring,
			delimiter
		);

		if (trimLeadingSpaces)
		{
			//trim leading spaces from substring
			size_t firstcharpos = substring.find_first_not_of(' ');
			if (firstcharpos != ::std::string::npos)
			{
				substring = substring.substr(firstcharpos);
			}
		} //else: don't alter substring

		result.push_back(substring);
	}

	return result;
}

std::string FromVectorOfStrings(
	const StdStrings& v,
	char delimiter,
	bool trimLeadingSpaces
)
{
	std::string result;
	for (
		StdStrings::const_iterator iter = v.begin();
		iter != v.end();
		++iter
		)
	{
		std::string substring = *iter;

		if (trimLeadingSpaces)
		{
			//trim leading spaces from substring
			::std::size_t firstcharpos = substring.find_first_not_of(' ');
			if (firstcharpos != ::std::string::npos)
			{
				substring = substring.substr(firstcharpos);
			}
		} //else: don't alter substring

		if (result.length() == 0)
		{
			result = substring;
		}
		else
		{
			result += (delimiter + substring);
		}
	}

	return result;
}

std::string FromVectorOfStrings(
	const CharStrings& v,
	char delimiter,
	bool trimLeadingSpaces
)
{
	std::string result;
	for (
		CharStrings::const_iterator iter = v.begin();
		iter != v.end();
		++iter
		)
	{
		std::string substring(*iter);

		if (trimLeadingSpaces)
		{
			//trim leading spaces from substring
			::std::size_t firstcharpos = substring.find_first_not_of(' ');
			if (firstcharpos != ::std::string::npos)
			{
				substring = substring.substr(firstcharpos);
			}
		} //else: don't alter substring

		if (result.length() == 0)
		{
			result = substring;
		}
		else
		{
			result += (delimiter + substring);
		}
	}

	return result;
}

CharStrings ToCharStrings(const StdStrings& strings)
{
	CharStrings ret;
	for (
		StdStrings::const_iterator iter = strings.begin();
		iter != strings.end();
		++iter
		)
	{
		const char* toAdd;
		CloneInto(iter->c_str(), toAdd);
		ret.push_back(toAdd);
	}
	return ret;
}

StdStrings ToStdStrings(const CharStrings& strings)
{
	StdStrings ret;
	for (
		CharStrings::const_iterator iter = strings.begin();
		iter != strings.end();
		++iter
		)
	{
		ret.push_back(*iter);
	}
	return ret;
}

void CloneInto(
	const char* source,
	const char*& target
)
{
	//NOTE: because "new" is used here, a delete needs to be called either here or in the caller.
	const size_t len = strlen(source);
	char* tmpName = new char[len + 1];
	strncpy(
		tmpName,
		source,
		len
	);
	tmpName[len] = '\0';
	target = tmpName;
}

bool AreEqual(const char* str1, const char* str2)
{
	return strcmp(str1, str2) == 0;
}

} //string namespace
} //bio namespace
