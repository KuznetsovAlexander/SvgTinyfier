#pragma once

#include <map>
#include <string>

class SvgTinyfier
{
public:
  static std::string tinyfy(const std::string& svg);

private:
  SvgTinyfier();
  ~SvgTinyfier();

  static std::string findStyleSection(const std::string& svg);
  static std::map<std::string, std::string> createStylesMap(const std::string& styleSection);
  static std::string replaceStyles(const std::string& svg, const std::map<std::string, std::string>& stylesMap);
  static void parseStyle(std::map<std::string, std::string>& styleMap, const std::string& style);
};
