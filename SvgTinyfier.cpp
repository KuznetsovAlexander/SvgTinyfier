#include "SvgTinyfier.h"

#include <vector>

SvgTinyfier::SvgTinyfier()
{

}

SvgTinyfier::~SvgTinyfier()
{

}

std::string SvgTinyfier::tinyfy(const std::string& svg)
{
  std::string styleSection = findStyleSection(svg);
  std::map<std::string, std::string> stylesMap = createStylesMap(styleSection);
  std::string tinyfied = replaceStyles(svg, stylesMap);
  return tinyfied;
}

std::string SvgTinyfier::findStyleSection(const std::string& svg)
{
  std::vector<std::string> openingTags = {
    "<style>",
    "<style type=\"text/css\">"
  };
  int size = 0;
  size_t openTagPos = 0;
  for (auto tag : openingTags) {
    openTagPos = svg.find(tag);
    if (openTagPos != std::string::npos) {
      size = tag.size();
      break;
    }
  }
  size_t closeTagPos = svg.find("</style>");
  std::string styleSection = svg.substr(openTagPos + size, closeTagPos - openTagPos - 7);
  return styleSection;
}

std::map<std::string, std::string> SvgTinyfier::createStylesMap(const std::string& styleSection)
{
  std::map<std::string, std::string> result;

  std::vector<size_t> stylesSeparatorPos;
  stylesSeparatorPos.push_back(0);
  size_t startPos = 0;
  size_t pos = styleSection.find('}', startPos);
  while (pos != std::string::npos) {
    stylesSeparatorPos.push_back(pos + 1);
    startPos = pos + 1;
    pos = styleSection.find('}', startPos);
  }

  std::vector<std::string> styles;
  for (int i = 0; i < stylesSeparatorPos.size() - 1; ++i) {
    std::string style = styleSection.substr(stylesSeparatorPos[i], stylesSeparatorPos[i + 1] - stylesSeparatorPos[i]);
    size_t begin_pos = style.find_first_not_of(" \n\t");
    style = style.substr(begin_pos);
    styles.push_back(style);
  }

  for (auto s : styles) {
    parseStyle(result, s);
  }

  return result;
}

void SvgTinyfier::parseStyle(std::map<std::string, std::string>& styleMap, const std::string& style)
{
  size_t nameContentSeparatorPos = style.find('{');
  std::string names = style.substr(0, nameContentSeparatorPos);
  std::string styleContent = style.substr(nameContentSeparatorPos);

  std::vector<std::string> styleNames;
  std::vector<size_t> positions;
  positions.push_back(0);
  size_t startPos = 0;
  size_t pos = names.find(',', startPos);
  while (pos != std::string::npos) {
    positions.push_back(pos + 1);
    startPos = pos + 1;
    pos = names.find(',', startPos);
  }
  positions.push_back(names.size() + 1);
  for (int i = 0; i < positions.size() - 1; ++i) {
    std::string name = names.substr(positions[i] + 1, positions[i + 1] - positions[i] - 2);
    styleNames.push_back(name);
  }

  styleContent = styleContent.substr(1, styleContent.size() - 2);
  std::string modifiedStyle;
  for (int i = 0; i < styleContent.size(); ++i) {
    if (styleContent[i] == ':') {
      modifiedStyle += "=\"";
    } else if (styleContent[i] == ';') {
      modifiedStyle += "\" ";
    } else {
      modifiedStyle += styleContent[i];
    }
  }

  for (auto n : styleNames) {
    styleMap[n] += modifiedStyle;
  }
}

std::string SvgTinyfier::replaceStyles(const std::string& svg, const std::map<std::string, std::string>& stylesMap)
{
  std::string result = svg;

  for (auto style : stylesMap) {
    std::string stringToFind = "class=\"" + style.first + "\"";
    size_t pos = 0;
    while ((pos = result.find(stringToFind)) != std::string::npos) {
      result.erase(pos, stringToFind.size());
      result.insert(pos, style.second);
    }
  }

  return result;
}
