#include "CanvasController.h"

#include <glCtrl.h>
#include <glCtrlText.h>
#include <iupgl.h>

CanvasController::CanvasController(Ihandle* canvas)
{
  this->m_canvas = canvas;
}

void CanvasController::create_texture()
{
  m_button_texture = new glCtrl::Gui::Style::texture_1(
    new glCtrl::Gui::Style::color_component_1(),
    new glCtrl::Gui::Style::texture_component_8(),
    "button_bg"
  );
  m_button_texture->texture->Load("game_bt", glCtrl::Texture::Type_2D_Flex, glCtrl::ST_Set4);
  m_button_texture->color->set(0, glCtrl::Utility::ColorGet("glCtrl_white"));
}

void CanvasController::create_manager()
{
  m_manager = new glCtrl::Manager::handler(m_canvas);
}

void CanvasController::create_box()
{
  // Create box
  int canvas_width, canvas_height;
  IupGetIntInt(m_canvas, "DRAWSIZE", &canvas_width, &canvas_height);
  m_box = new glCtrl::Gui::box_single_line(
    glCtrl::Dir_Horizontal,
    canvas_width,
    canvas_height
  );
  m_box->SetColor(glCtrl::Utility::ColorF(0xF0, 0xF0, 0xF0, 0xFF));
}

void CanvasController::create_buttons()
{
  constexpr int btn_w = 120;
  constexpr int btn_h = 60;
  // Add button
  m_button_load = new glCtrl::Gui::Button(btn_w, btn_h);
  m_button_load->SetActionCb(load_cb);
  m_button_load->SetStyleBackground("button_bg");
  // Add button
  m_button_save = new glCtrl::Gui::Button(btn_w, btn_h);
  m_button_save->SetActionCb(save_as_cb);
  m_button_save->SetStyleBackground("button_bg");
  // Add button
  m_button_clear = new glCtrl::Gui::Button(btn_w, btn_h);
  m_button_clear->SetActionCb(clear_cb);
  m_button_clear->SetStyleBackground("button_bg");

  glCtrl::Gui::Text text_load = glCtrl::Gui::Text(btn_w, btn_h);
  text_load.SetText("Load");
  text_load.GetFontParam().SetColor(glCtrl::Utility::ColorF(0xFF, 0xFF, 0xFF, 0xFF));
  text_load.GetFontParam().SetBold(true);
  text_load.GetFontParam().SetSize(16);
  text_load.GetFontParam().SetFont("Arial");
  text_load.SetAlignment(glCtrl::Gui::Text::Center);

  glCtrl::Gui::Text text_save = glCtrl::Gui::Text(text_load);
  text_save.SetText("Save");
  glCtrl::Gui::Text text_clear = glCtrl::Gui::Text(text_load);
  text_clear.SetText("Clear");

  m_button_load->add_child(&text_load);
  m_button_save->add_child(&text_save);
  m_button_clear->add_child(&text_clear);
}

void CanvasController::initialize(const std::string& texture_directory)
{
  glCtrl::Initialize(R"(C:\Windows\Fonts)", texture_directory);
  IupGLMakeCurrent(m_canvas);
  glCtrl::load_styles();

  create_manager();

  create_texture();

  create_box();

  create_buttons();
}
