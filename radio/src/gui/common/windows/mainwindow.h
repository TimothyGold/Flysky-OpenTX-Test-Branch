#include <utility>

/*
 * Copyright (C) OpenTX
 *
 * Based on code named
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "window.h"

class MainWindow: public Window {
  public:
    MainWindow():
      Window(nullptr, {0, 0, LCD_W, LCD_H}),
      invalidatedRect(rect)
    {
    }

#if defined(DEBUG_WINDOWS)
    std::string getName() override
    {
      return "MainWindow";
    }
#endif

    void checkEvents() override;

    void invalidate()
    {
      invalidate({0, 0, rect.w, rect.h});
    }

    void invalidate(const rect_t & rect) override;

    bool refresh();

    void run(bool luaActive=false);

    void resetDisplayRect();

  protected:

    void checkEvents(bool luaActive);

    void emptyTrash();

    rect_t invalidatedRect;
    bool legacyUImode;
    bool lastLuaState;
};

extern MainWindow mainWindow;

#endif // _MAINWINDOW_H_
