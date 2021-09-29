#pragma once
#include <glCtrlBox.h>
#include <glCtrlManager.h>
#include <glCtrlStyle.h>
#include <iup.h>
#include <string>

class CanvasController
{
  Ihandle* m_canvas = nullptr;
  glCtrl::Manager::handler* m_manager = nullptr;
  glCtrl::Gui::Style::texture_1* m_button_texture = nullptr;
  glCtrl::Gui::Box* m_box = nullptr;
  glCtrl::Gui::Button* m_button_load = nullptr;
  glCtrl::Gui::Button* m_button_save = nullptr;
  glCtrl::Gui::Button* m_button_clear = nullptr;

  

public:
  explicit CanvasController(Ihandle* canvas);
  void create_texture();
  void create_manager();
  void create_box();
  void create_buttons();
  void initialize(const std::string& texture_directory);
};
