/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
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

#include "dialogs/GUIDialogOK.h"
#include "GUIWindowManager.h"

CGUIDialogOK::CGUIDialogOK(void)
    : CGUIDialogBoxBase(WINDOW_DIALOG_OK, "DialogConfirm.xml")
{
}

CGUIDialogOK::~CGUIDialogOK(void)
{}

bool CGUIDialogOK::OnMessage(CGUIMessage& message)
{
  switch ( message.GetMessage() )
  {
  case GUI_MSG_CLICKED:
    {
      int iControl = message.GetSenderId();
      if (iControl == CONTROL_YES_BUTTON)
      {
        m_bConfirmed = true;
        Close();
        return true;
      }
    }
    break;
  }
  return CGUIDialogBoxBase::OnMessage(message);
}

// \brief Show CGUIDialogOK dialog, then wait for user to dismiss it.
void CGUIDialogOK::ShowAndGetInput(const CVariant &heading, const CVariant &text)
{
  CGUIDialogOK *dialog = (CGUIDialogOK *)g_windowManager.GetWindow(WINDOW_DIALOG_OK);
  if (!dialog)
    return;
  dialog->SetHeading(heading);
  dialog->SetText(text);
  dialog->Open();
}

// \brief Show CGUIDialogOK dialog, then wait for user to dismiss it.
void CGUIDialogOK::ShowAndGetInput(const CVariant &heading, const CVariant &line0, const CVariant &line1, const CVariant &line2)
{
  CGUIDialogOK *dialog = (CGUIDialogOK *)g_windowManager.GetWindow(WINDOW_DIALOG_OK);
  if (!dialog)
    return;
  dialog->SetHeading( heading );
  dialog->SetLine( 0, line0 );
  dialog->SetLine( 1, line1 );
  dialog->SetLine( 2, line2 );
  dialog->Open();
}

void CGUIDialogOK::OnInitWindow()
{
  CGUIDialogBoxBase::OnInitWindow();

  SET_CONTROL_VISIBLE(CONTROL_YES_BUTTON);
  SET_CONTROL_FOCUS(CONTROL_YES_BUTTON, 0);
}

int CGUIDialogOK::GetDefaultLabelID(int controlId) const
{
  if (controlId == CONTROL_YES_BUTTON)
    return 186;
  return CGUIDialogBoxBase::GetDefaultLabelID(controlId);
}
