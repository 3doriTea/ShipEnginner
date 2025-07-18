#pragma once
#include <string>


namespace StringUtility
{
	/// <summary>
	/// wstringをstringに変換する
	/// </summary>
	/// <param name="_wstr">ワイド文字列</param>
	/// <returns>ただの文字列</returns>
	std::string ToString(const std::wstring& _wstr);
}
