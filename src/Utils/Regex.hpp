#pragma once
#include "Base.hpp"

#define PCRE2_CODE_UNIT_WIDTH 8

#include <pcre2.h>
#include <string>
#include <vector>

namespace gsclib
{
	struct RegexValue
	{
		std::string String;
		bool Matched;
	};

	struct RegexVector
	{
		int Position;
		size_t Length;
	};

	class Regex
	{
	public:
		static void Split();
		static void Match();
		static void Replace();

	private:
		static bool GetUTFOption(pcre2_code* re, uint32_t* optionBits);
		static bool IsNewlineCRLF(pcre2_code* re, uint32_t* newline);
		static bool HasMatches(int rc, pcre2_code* re, pcre2_match_data* matchData);
		static bool CompileSuccess(pcre2_code* re, int* errorCode, PCRE2_SIZE* errorOffset);
		static std::vector<RegexValue> Compile(PCRE2_SPTR subject, PCRE2_SPTR regex);
	};
}
