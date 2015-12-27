#pragma once

#include <string>

namespace mce
{
	class UUID
	{
	public:
		long long part[2];

		void fromString(const std::string &);
		std::string toString() const;
	};
};
