#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include <windows.h>

namespace {
  std::string to_utf8_formC(const std::vector<wchar_t>& wstr) {
    // w3 validator says text should use Unicode Normalization Form C
    std::vector<wchar_t> buf(wstr.size() * 2);
    int normalizedLen = NormalizeString(NormalizationC, wstr.data(), wstr.size(), buf.data(), buf.size());
    buf.resize(normalizedLen);

    int utf8Len = WideCharToMultiByte(CP_UTF8, 0, buf.data(), buf.size(), 0, 0, 0, 0);
    std::string rv;
    rv.resize(utf8Len);
    WideCharToMultiByte(CP_UTF8, 0, buf.data(), buf.size(), &rv[0], rv.size(), 0, 0);
    return rv;
  }

  unsigned long getLocaleInfoDword(const wchar_t* localeName, LCTYPE type) {
    unsigned long value = ~0;
    GetLocaleInfoEx(localeName,
      type | LOCALE_RETURN_NUMBER,
      reinterpret_cast<wchar_t*>(&value),
      sizeof(value) / sizeof(WCHAR));
    return value;
  }

  std::vector<wchar_t> getLocaleInfoStringW(const wchar_t* localeName, LCTYPE type) {
    std::vector<wchar_t> buf;
    int len = GetLocaleInfoEx(localeName, type, 0, 0);
    buf.resize(len);
    GetLocaleInfoEx(localeName, type, buf.data(), len);
    buf.pop_back(); // needless zero byte, length is determined by the length of the vector
    return buf;
  }

  std::string getLocaleInfoString(const wchar_t* localeName, LCTYPE type) {
    return to_utf8_formC(getLocaleInfoStringW(localeName, type));
  }
}

int main()
{
  std::cout << "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><title>Windows Locale Database</title></head><body><table><tbody>\n";
  std::cout << "<tr><th>LCID (hex)</th><th>Name</th><th>Display Name</th><th>Language</th><th>Native Display Name</th><th>ANSI codepage</th><th>OEM codepage</th><th>MAC codepage</th><th>Country/Region name abbreviation</th><th>Language name abbreviation</th></tr>";
  EnumSystemLocalesEx([](auto localeName, auto, auto) -> int {
    std::cout
      << "<tr>"
      << "<td>" << std::hex << std::setfill('0') << std::setw(4) << LocaleNameToLCID(localeName, 0) << std::dec << "</td>"
      << "<td>" << getLocaleInfoString(localeName, LOCALE_SNAME) << "</td>"
      << "<td>" << getLocaleInfoString(localeName, LOCALE_SENGLISHDISPLAYNAME) << "</td>"
      << "<td>" << getLocaleInfoString(localeName, LOCALE_SENGLISHLANGUAGENAME) << "</td>"
      << "<td>" << getLocaleInfoString(localeName, LOCALE_SNATIVEDISPLAYNAME) << "</td>"
      << "<td>" << getLocaleInfoDword(localeName, LOCALE_IDEFAULTANSICODEPAGE) << "</td>"
      << "<td>" << getLocaleInfoDword(localeName, LOCALE_IDEFAULTCODEPAGE) << "</td>"
      << "<td>" << getLocaleInfoDword(localeName, LOCALE_IDEFAULTMACCODEPAGE) << "</td>"
      << "<td>" << getLocaleInfoString(localeName, LOCALE_SABBREVCTRYNAME) << "</td>"
      << "<td>" << getLocaleInfoString(localeName, LOCALE_SABBREVLANGNAME) << "</td>"
      << "</tr>\n";
    return 1;
    }, LOCALE_WINDOWS, 0L, nullptr);
  std::cout << "</tbody></table></body></html>\n";
  return 0;
}
