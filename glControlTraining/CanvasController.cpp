#include "CanvasController.h"

#include <glCtrl.h>
#pragma warning(push)
#pragma warning(disable: 4996)
#include "glCtrlText.h"
#pragma warning(pop)
#include "glCtrlDebug.h"
#include "glCtrlSpace.h"
#include <iupgl.h>

#include "Utils.h"

void CanvasController::load_callback(int id)
{
  Ihandle* filedlg = IupFileDlg();
  IupSetAttribute(filedlg, "DIALOGTYPE", "OPEN");
  IupSetAttribute(filedlg, "EXTFILTER", "Text Files|*.txt|All Files|*.*|");

  IupPopup(filedlg, IUP_CENTER, IUP_CENTER);

  if (IupGetInt(filedlg, "STATUS") != -1)
  {
    const std::string filename = IupGetAttribute(filedlg, "VALUE");
    const std::string str = Utils::read_file(filename);
    IupSetStrAttribute(IupGetHandle("text_area"), "VALUE", str.c_str());
  }

  IupDestroy(filedlg);
}

void CanvasController::save_callback(int id)
{
  Ihandle* filedlg = IupFileDlg();
  IupSetAttribute(filedlg, "DIALOGTYPE", "SAVE");
  IupSetAttribute(filedlg, "EXTFILTER", "Text Files|*.txt|All Files|*.*|");

  IupPopup(filedlg, IUP_CENTER, IUP_CENTER);

  if (IupGetInt(filedlg, "STATUS") != -1)
  {
    const std::string filename = IupGetAttribute(filedlg, "VALUE");
    const char* str = IupGetAttribute(IupGetHandle("text_area"), "VALUE");
    Utils::write_file(filename, str);
  }

  IupDestroy(filedlg);
}

void CanvasController::clear_callback(int id)
{
  IupSetAttribute(IupGetHandle("text_area"), "VALUE", "");
}

CanvasController::CanvasController(Ihandle* canvas)
{
  this->m_canvas = canvas;
}

void CanvasController::add_buttons_to_box() const
{
  glCtrl::Gui::Space* space_start = new glCtrl::Gui::Space(20, glCtrl::Gui::Expandable);
  glCtrl::Gui::Space* space_end = new glCtrl::Gui::Space(*space_start);

  m_box->AddItem(space_start);
  m_box->AddItem(m_button_load);
  m_box->AddItem(m_button_save);
  m_box->AddItem(m_button_clear);
  m_box->AddItem(space_end);
}

void CanvasController::create_texture()
{
  m_button_texture = new glCtrl::Gui::Style::texture_1(
    new glCtrl::Gui::Style::color_component_1(),
    new glCtrl::Gui::Style::texture_component_8(),
    "button_bg"
  );
  m_button_texture->texture->Load("button_textures", glCtrl::Texture::Type_2D_Flex, glCtrl::ST_Set4);
  m_button_texture->color->set(0, glCtrl::Utility::ColorGet("glCtrl_white"));
}

void CanvasController::create_manager()
{
  m_manager = new glCtrl::Manager::handler(m_canvas);

}

void CanvasController::create_box()
{
  int canvas_width, canvas_height;
  IupGetIntInt(m_canvas, "DRAWSIZE", &canvas_width, &canvas_height);
  m_box = new glCtrl::Gui::box_single_line(
    glCtrl::Dir_Horizontal,
    canvas_width + 0,
    canvas_height + 0
  );
  m_box->SetColor(glCtrl::Utility::ColorF(0xF0, 0xF0, 0xF0, 0xFF));
}

void CanvasController::create_buttons()
{
  constexpr int btn_w = 120;
  constexpr int btn_h = 60;
  // Add button
  m_button_load = new glCtrl::Gui::Button(btn_w, btn_h);
  m_button_load->SetActionCb(load_callback);
  m_button_load->SetStyleBackground("button_bg");
  // Add button
  m_button_save = new glCtrl::Gui::Button(btn_w, btn_h);
  m_button_save->SetActionCb(save_callback);
  m_button_save->SetStyleBackground("button_bg");
  // Add button
  m_button_clear = new glCtrl::Gui::Button(btn_w, btn_h);
  m_button_clear->SetActionCb(clear_callback);
  m_button_clear->SetStyleBackground("button_bg");

  glCtrl::Gui::Text* text_load = new glCtrl::Gui::Text(btn_w, btn_h);
  text_load->SetText("Load");
  text_load->GetFontParam().SetColor(glCtrl::Utility::ColorF(0xFF, 0xFF, 0xFF, 0xFF));
  text_load->GetFontParam().SetBold(true);
  text_load->GetFontParam().SetSize(16);
  text_load->GetFontParam().SetFont("Arial");
  text_load->SetAlignment(glCtrl::Gui::Text::Center);

  glCtrl::Gui::Text* text_save = new glCtrl::Gui::Text(*text_load);
  text_save->SetText("Save");
  glCtrl::Gui::Text* text_clear = new glCtrl::Gui::Text(*text_load);
  text_clear->SetText("Clear");

  m_button_load->add_child(text_load);
  m_button_save->add_child(text_save);
  m_button_clear->add_child(text_clear);
}

void CanvasController::create_subwindow()
{
  m_subwindow = new glCtrl::Subwindow::handle(
    *m_manager,
    "toolbar",
    m_box,
    glCtrl::Up,
    0
  );
}

void CanvasController::initialize(const std::string& texture_directory)
{
  // Initialize glControl
  glCtrl::Initialize(R"(C:\Windows\Fonts)", texture_directory);
  IupGLMakeCurrent(m_canvas);
  glCtrl::load_styles();
  glCtrl::Debug::Initialize();

  create_manager();

  create_texture();

  create_box();

  create_buttons();

  add_buttons_to_box();

  create_subwindow();

  m_subwindow->ReArrange();
  m_subwindow->Activate(true);
  m_manager->Redisplay();
}
