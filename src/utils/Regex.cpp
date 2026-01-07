#include "Regex.hpp"

namespace gsclib
{
	void Regex::Split()
	{
		CHECK_PARAMS(2, "Usage: RegexSplit(<string>, <regex>)\n");

		const char* subject = Plugin_Scr_GetString(0);
		const char* regex = Plugin_Scr_GetString(1);

		std::vector<RegexValue> values =
			Compile(reinterpret_cast<PCRE2_SPTR>(subject), reinterpret_cast<PCRE2_SPTR>(regex));
		if (values.empty())
			return;

		Plugin_Scr_MakeArray();
		for (const auto& value : values)
		{
			if (!value.Matched)
			{
				Plugin_Scr_AddString(value.String.c_str());
				Plugin_Scr_AddArray();
			}
		}
	}

	void Regex::Match()
	{
		CHECK_PARAMS(2, "Usage: RegexMatch(<string>, <regex>)\n");

		const char* subject = Plugin_Scr_GetString(0);
		const char* regex = Plugin_Scr_GetString(1);

		std::vector<RegexValue> values =
			Compile(reinterpret_cast<PCRE2_SPTR>(subject), reinterpret_cast<PCRE2_SPTR>(regex));
		if (values.empty())
			return;

		Plugin_Scr_MakeArray();
		for (const auto& value : values)
		{
			if (value.Matched)
			{
				Plugin_Scr_AddString(value.String.c_str());
				Plugin_Scr_AddArray();
			}
		}
	}

	void Regex::Replace()
	{
		CHECK_PARAMS(3, "Usage: RegexReplace(<string>, <replace>, <regex>)\n");

		const char* subject = Plugin_Scr_GetString(0);
		const char* replace = Plugin_Scr_GetString(1);
		const char* regex = Plugin_Scr_GetString(2);

		std::vector<RegexValue> values =
			Compile(reinterpret_cast<PCRE2_SPTR>(subject), reinterpret_cast<PCRE2_SPTR>(regex));
		if (values.empty())
			return;

		std::string result;
		for (const auto& value : values)
			result += value.Matched ? replace : value.String;

		Plugin_Scr_AddString(result.c_str());
	}

	bool Regex::GetUTFOption(pcre2_code* re, uint32_t* optionBits)
	{
		pcre2_pattern_info(re, PCRE2_INFO_ALLOPTIONS, optionBits);
		return (*optionBits & PCRE2_UTF) != 0;
	}

	bool Regex::IsNewlineCRLF(pcre2_code* re, uint32_t* newline)
	{
		pcre2_pattern_info(re, PCRE2_INFO_NEWLINE, newline);
		return *newline == PCRE2_NEWLINE_ANY || *newline == PCRE2_NEWLINE_CRLF || *newline == PCRE2_NEWLINE_ANYCRLF;
	}

	bool Regex::HasMatches(int rc, pcre2_code* re, pcre2_match_data* matchData)
	{
		if (rc < 0)
		{
			switch (rc)
			{
			case PCRE2_ERROR_NOMATCH:
				break;
			default:
				Plugin_Scr_Error(std::format("Matching error {}\n", rc).c_str());
				break;
			}
			pcre2_match_data_free(matchData);
			pcre2_code_free(re);
			return false;
		}
		return true;
	}

	bool Regex::CompileSuccess(pcre2_code* re, int* errorCode, PCRE2_SIZE* errorOffset)
	{
		if (re != nullptr)
			return true;

		PCRE2_UCHAR buffer[256];
		pcre2_get_error_message(*errorCode, buffer, sizeof(buffer));

		Plugin_Scr_Error(std::format("PCRE2 compilation failed at offset {} {}\n", static_cast<int>(*errorOffset),
			reinterpret_cast<char*>(buffer))
							 .c_str());
		pcre2_code_free(re);
		return false;
	}

	std::vector<RegexValue> Regex::Compile(PCRE2_SPTR subject, PCRE2_SPTR regex)
	{
		std::vector<RegexValue> values;
		std::string_view subjectView(reinterpret_cast<const char*>(subject));
		PCRE2_SIZE subjectLength = subjectView.size();
		PCRE2_SIZE errorOffset;
		const int groupIndex = 0;
		int errorCode;
		std::vector<RegexVector> vectors;

		pcre2_code* re = pcre2_compile(regex, PCRE2_ZERO_TERMINATED, 0, &errorCode, &errorOffset, nullptr);
		if (!CompileSuccess(re, &errorCode, &errorOffset))
			return values;

		pcre2_match_data* matchData = pcre2_match_data_create_from_pattern(re, nullptr);
		int rc = pcre2_match(re, subject, subjectLength, 0, 0, matchData, nullptr);
		if (!HasMatches(rc, re, matchData))
			return values;

		PCRE2_SIZE* ovector = pcre2_get_ovector_pointer(matchData);

		RegexVector firstVector;
		firstVector.Position = static_cast<int>(ovector[2 * groupIndex]);
		firstVector.Length = ovector[2 * groupIndex + 1] - ovector[2 * groupIndex];
		vectors.push_back(firstVector);

		uint32_t optionBits;
		bool utf8 = GetUTFOption(re, &optionBits);

		uint32_t newline;
		bool isNewlineCRLF = IsNewlineCRLF(re, &newline);

		for (;;)
		{
			uint32_t options = 0;
			PCRE2_SIZE startOffset = ovector[1];

			if (ovector[0] == ovector[1])
			{
				if (ovector[0] == subjectLength)
					break;
				options = PCRE2_NOTEMPTY_ATSTART | PCRE2_ANCHORED;
			}
			rc = pcre2_match(re, subject, subjectLength, startOffset, options, matchData, nullptr);
			if (rc == PCRE2_ERROR_NOMATCH)
			{
				if (options == 0)
					break;
				ovector[1] = startOffset + 1;

				if (isNewlineCRLF && startOffset < subjectLength - 1 && subject[startOffset] == '\r'
					&& subject[startOffset + 1] == '\n')
					ovector[1] += 1;
				else if (utf8)
				{
					while (ovector[1] < subjectLength)
					{
						if ((subject[ovector[1]] & 0xc0) != 0x80)
							break;
						ovector[1] += 1;
					}
				}
				continue;
			}
			if (!HasMatches(rc, re, matchData))
				break;

			RegexVector vec;
			vec.Position = static_cast<int>(ovector[2 * groupIndex]);
			vec.Length = ovector[2 * groupIndex + 1] - ovector[2 * groupIndex];
			vectors.push_back(vec);
		}
		for (size_t i = 0; i < vectors.size(); i++)
		{
			RegexVector current = vectors[i];

			if (current.Position != 0)
			{
				if (i == 0)
				{
					RegexValue value;
					value.String = std::string(reinterpret_cast<const char*>(subject), current.Position);
					value.Matched = false;
					values.push_back(value);
				}
				else
				{
					RegexVector last = vectors[i - 1];
					int pos = last.Position + static_cast<int>(last.Length);
					if (pos != current.Position)
					{
						RegexValue value;
						value.String =
							std::string(reinterpret_cast<const char*>(subject) + pos, current.Position - pos);
						value.Matched = false;
						values.push_back(value);
					}
				}
			}
			RegexValue matchedValue;
			matchedValue.String =
				std::string(reinterpret_cast<const char*>(subject) + current.Position, current.Length);
			matchedValue.Matched = true;
			values.push_back(matchedValue);
		}
		pcre2_match_data_free(matchData);
		pcre2_code_free(re);
		return values;
	}
}
