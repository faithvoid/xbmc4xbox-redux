/*
 *      Copyright (C) 2013 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include <vector>

#include "SettingControl.h"
#include "settings/SettingDefinitions.h"
#include "utils/log.h"
#include "utils/StringUtils.h"
#include "utils/XBMCTinyXML.h"
#include "utils/XMLUtils.h"

bool CSettingControlCheckmark::SetFormat(const std::string &format)
{
  return format.empty() || StringUtils2::EqualsNoCase(format, "boolean");
}

bool CSettingControlSpinner::Deserialize(const TiXmlNode *node, bool update /* = false */)
{
  if (!ISettingControl::Deserialize(node, update))
    return false;

  if (m_format == "string")
  {
    XMLUtils::GetInt(node, SETTING_XML_ELM_CONTROL_FORMATLABEL, m_formatLabel);

    // get the minimum label from <setting><constraints><minimum label="X" />
    const TiXmlNode *settingNode = node->Parent();
    if (settingNode != NULL)
    {
      const TiXmlNode *contraintsNode = settingNode->FirstChild(SETTING_XML_ELM_CONSTRAINTS);
      if (contraintsNode != NULL)
      {
        const TiXmlNode *minimumNode = contraintsNode->FirstChild(SETTING_XML_ELM_MINIMUM);
        if (minimumNode != NULL)
        {
          const TiXmlElement *minimumElem = minimumNode->ToElement();
          if (minimumElem != NULL)
          {
            if (minimumElem->QueryIntAttribute(SETTING_XML_ATTR_LABEL, &m_minimumLabel) != TIXML_SUCCESS)
              m_minimumLabel = -1;
          }
        }
      }
    }

    if (m_minimumLabel < 0)
    {
      std::string strFormat;
      if (XMLUtils::GetString(node, SETTING_XML_ATTR_FORMAT, strFormat) && !strFormat.empty())
        m_formatString = strFormat;
    }
  }

  return true;
}

bool CSettingControlSpinner::SetFormat(const std::string &format)
{
  if (!StringUtils2::EqualsNoCase(format, "string") &&
      !StringUtils2::EqualsNoCase(format, "integer") &&
      !StringUtils2::EqualsNoCase(format, "number"))
    return false;

  m_format = format;
  StringUtils2::ToLower(m_format);

  return true;
}

bool CSettingControlEdit::Deserialize(const TiXmlNode *node, bool update /* = false */)
{
  if (!ISettingControl::Deserialize(node, update))
    return false;

  XMLUtils::GetBoolean(node, SETTING_XML_ELM_CONTROL_HIDDEN, m_hidden);
  XMLUtils::GetBoolean(node, SETTING_XML_ELM_CONTROL_VERIFYNEW, m_verifyNewValue);
  XMLUtils::GetInt(node, SETTING_XML_ELM_CONTROL_HEADING, m_heading);

  return true;
}

bool CSettingControlEdit::SetFormat(const std::string &format)
{
  if (!StringUtils2::EqualsNoCase(format, "string") &&
      !StringUtils2::EqualsNoCase(format, "integer") &&
      !StringUtils2::EqualsNoCase(format, "number") &&
      !StringUtils2::EqualsNoCase(format, "ip") &&
      !StringUtils2::EqualsNoCase(format, "md5") &&
      !StringUtils2::EqualsNoCase(format, "path")) // TODO
    return false;

  m_format = format;
  StringUtils2::ToLower(m_format);

  return true;
}

bool CSettingControlButton::Deserialize(const TiXmlNode *node, bool update /* = false */)
{
  if (!ISettingControl::Deserialize(node, update))
    return false;

  XMLUtils::GetInt(node, SETTING_XML_ELM_CONTROL_HEADING, m_heading);
  XMLUtils::GetBoolean(node, SETTING_XML_ELM_CONTROL_HIDEVALUE, m_hideValue);

  return true;
}

bool CSettingControlButton::SetFormat(const std::string &format)
{
  if (!StringUtils2::EqualsNoCase(format, "string") &&  // TODO
      !StringUtils2::EqualsNoCase(format, "integer") &&  // TODO
      !StringUtils2::EqualsNoCase(format, "number") &&  // TODO
      !StringUtils2::EqualsNoCase(format, "path") &&
      !StringUtils2::EqualsNoCase(format, "addon") &&  // TODO
      !StringUtils2::EqualsNoCase(format, "action"))
    return false;

  m_format = format;
  StringUtils2::ToLower(m_format);

  return true;
}

bool CSettingControlList::Deserialize(const TiXmlNode *node, bool update /* = false */)
{
  if (!ISettingControl::Deserialize(node, update))
    return false;

  XMLUtils::GetInt(node, SETTING_XML_ELM_CONTROL_HEADING, m_heading);

  return true;
}

bool CSettingControlList::SetFormat(const std::string &format)
{
  if (!StringUtils2::EqualsNoCase(format, "string") &&
      !StringUtils2::EqualsNoCase(format, "integer"))
    return false;

  m_format = format;
  StringUtils2::ToLower(m_format);

  return true;
}