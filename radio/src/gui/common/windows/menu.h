#pragma once
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

#include <functional>
#include <string>
#include <utility>
#include <vector>
#include "mainwindow.h"
#include "opentx.h"

extern RadioData g_eeGeneral;

class Menu;

class MenuWindow : public Window {
  friend class Menu;

  class MenuLine {
    friend class MenuWindow;

   public:
    MenuLine(std::string text, std::function<void()> onPress)
        : text(std::move(text)), onPress(std::move(onPress)) {}

    MenuLine(MenuLine &) = delete;

    MenuLine(MenuLine &&) = default;

   protected:
    std::string text;
    std::function<void()> onPress;
  };

 public:
  MenuWindow(Menu *parent);

  void addLine(const std::string &text, std::function<void()> onPress) {
    lines.emplace_back(text, onPress);
    invalidate();
  }

  void removeLines() {
    lines.clear();
    invalidate();
  }

  void select(int index);

  void paint(BitmapBuffer *dc) override;

  bool onTouchEnd(coord_t x, coord_t y) override;

  coord_t getLineHeight() { return lineHeight; }

 protected:
  std::vector<MenuLine> lines;
  int selectedIndex = -1;
  uint8_t lineHeight = ((g_eeGeneral.displayLargeLines) ? 50 : 40);
};

class Menu : public Window {
 public:
  Menu()
      : Window(&mainWindow, {0, 0, LCD_W, LCD_H}, TRANSPARENT),
        menuWindow(this) {}

  ~Menu() { delete toolbar; }

#if defined(DEBUG_WINDOWS)
  std::string getName() override { return "Menu"; }
#endif

  void setToolbar(Window *window) {
    toolbar = window;
    menuWindow.setLeft(window->right());
    menuWindow.setTop(window->top());
    menuWindow.setHeight(window->height());
  }

  void checkEvents() override;

  void addLine(const std::string &text, std::function<void()> onPress);

  void removeLines();

  void select(int index) {
    indexToSelect = index;
    invalidate();
  }

  bool onTouchStart(coord_t x, coord_t y) override { return true; }

  bool onTouchEnd(coord_t x, coord_t y) override;

  bool onTouchSlide(coord_t x, coord_t y, coord_t startX, coord_t startY,
                    coord_t slideX, coord_t slideY) override;

 protected:
  MenuWindow menuWindow;
  Window *toolbar = nullptr;
  void updatePosition();
  int indexToSelect = -1;
};
