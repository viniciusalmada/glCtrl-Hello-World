#include "iup.h"
#include "iupgl.h"
#include "glCtrl.h"
#include "glCtrlBox.h"
#include "glCtrlSpace.h"
#pragma warning(push)
#pragma warning(disable: 4996)
#include "glCtrlText.h"
#pragma warning(pop)
#include "glCtrlDebug.h"
#include <fstream>
#include <iostream>

std::string read_file(const std::string& filepath)
{
  std::ifstream in_file;
  in_file.open(filepath);
  if (!in_file)
  {
    std::cerr << "Unable to open file";
    return {};
  }
  std::string line;
  std::string file_content;
  while (in_file >> line)
  {
    file_content.append(line);
    file_content.append("\n");
  }
  in_file.close();

  return file_content;
}

void write_file(const std::string& filepath, const std::string& content)
{
  std::ofstream out_file;
  out_file.open(filepath);
  if (!out_file)
  {
    std::cerr << "Unable to open file";
    return;
  }
  out_file << content;
  out_file.close();
}

int load_cb(int id)
{
  Ihandle* filedlg = IupFileDlg();
  IupSetAttribute(filedlg, "DIALOGTYPE", "OPEN");
  IupSetAttribute(filedlg, "EXTFILTER", "Text Files|*.txt|All Files|*.*|");

  IupPopup(filedlg, IUP_CENTER, IUP_CENTER);

  if (IupGetInt(filedlg, "STATUS") != -1)
  {
    const std::string filename = IupGetAttribute(filedlg, "VALUE");
    const std::string str = read_file(filename);
      IupSetStrAttribute(IupGetHandle("text_area"), "VALUE", str.c_str());
  }

  IupDestroy(filedlg);
  return IUP_DEFAULT;
}

int save_as_cb(int id)
{
  Ihandle* filedlg = IupFileDlg();
  IupSetAttribute(filedlg, "DIALOGTYPE", "SAVE");
  IupSetAttribute(filedlg, "EXTFILTER", "Text Files|*.txt|All Files|*.*|");

  IupPopup(filedlg, IUP_CENTER, IUP_CENTER);

  if (IupGetInt(filedlg, "STATUS") != -1)
  {
    const std::string filename = IupGetAttribute(filedlg, "VALUE");
    const char* str = IupGetAttribute(IupGetHandle("text_area"), "VALUE");
    write_file(filename, str);
  }

  IupDestroy(filedlg);
  return IUP_DEFAULT;
}

int clear_cb(int id)
{
  IupSetAttribute(IupGetHandle("text_area"), "VALUE", "");
  return IUP_DEFAULT;
}

void start_gl_control(Ihandle* canvas)
{
  // Initialize glControl
  glCtrl::Initialize(R"(C:\Windows\Fonts)", R"(N:\textures)");
  IupGLMakeCurrent(canvas);
  glCtrl::load_styles();
  glCtrl::Debug::Initialize();

  // Create manager
  glCtrl::Manager::handler* manager = new glCtrl::Manager::handler(canvas);

  // Create texture
  const glCtrl::Gui::Style::texture_1* tex = new glCtrl::Gui::Style::texture_1(
    new glCtrl::Gui::Style::color_component_1(),
    new glCtrl::Gui::Style::texture_component_8(),
    "button_bg"
  );
  tex->texture->Load("game_bt", glCtrl::Texture::Type_2D_Flex, glCtrl::ST_Set4);
  tex->color->set(0, glCtrl::Utility::ColorGet("glCtrl_white"));

  // Create box
  int canvas_width, canvas_height;
  IupGetIntInt(canvas, "DRAWSIZE", &canvas_width, &canvas_height);
  glCtrl::Gui::Box* box = new glCtrl::Gui::box_single_line(
    glCtrl::Dir_Horizontal,
    canvas_width + 0,
    canvas_height + 0
  );
  box->SetColor(glCtrl::Utility::ColorF(0xF0, 0xF0, 0xF0, 0xFF));

  glCtrl::Gui::Space* space_start = new glCtrl::Gui::Space(20, glCtrl::Gui::Expandable);
  glCtrl::Gui::Space* space_end = new glCtrl::Gui::Space(*space_start);

  constexpr int btn_w = 120;
  constexpr int btn_h = 60;
  // Add button
  glCtrl::Gui::Button* btn1 = new glCtrl::Gui::Button(btn_w, btn_h);
  btn1->SetActionCb(load_cb);
  btn1->SetStyleBackground("button_bg");
  // Add button
  glCtrl::Gui::Button* btn2 = new glCtrl::Gui::Button(btn_w, btn_h);
  btn2->SetActionCb(save_as_cb);
  btn2->SetStyleBackground("button_bg");
  // Add button
  glCtrl::Gui::Button* btn3 = new glCtrl::Gui::Button(btn_w, btn_h);
  btn3->SetActionCb(clear_cb);
  btn3->SetStyleBackground("button_bg");

  glCtrl::Gui::Text* t1 = new glCtrl::Gui::Text(btn_w, btn_h);
  t1->SetText("Load");
  t1->GetFontParam().SetColor(glCtrl::Utility::ColorF(0xFF, 0xFF, 0xFF, 0xFF));
  t1->GetFontParam().SetBold(true);
  t1->GetFontParam().SetSize(16);
  t1->GetFontParam().SetFont("Arial");
  t1->SetAlignment(glCtrl::Gui::Text::Center);

  glCtrl::Gui::Text* t2 = new glCtrl::Gui::Text(*t1);
  t2->SetText("Save");
  glCtrl::Gui::Text* t3 = new glCtrl::Gui::Text(*t1);
  t3->SetText("Clear");

  btn1->add_child(t1);
  btn2->add_child(t2);
  btn3->add_child(t3);

  box->AddItem(space_start);
  box->AddItem(btn1);
  box->AddItem(btn2);
  box->AddItem(btn3);
  box->AddItem(space_end);

  // Create subwindow
  glCtrl::Subwindow::handle* sw = new glCtrl::Subwindow::handle(
    *manager,
    "toolbar",
    box,
    glCtrl::Up,
    0
  );

  sw->ReArrange();
  sw->Activate(true);
  manager->Redisplay();
}

void build_dialog()
{
  Ihandle* canvas = IupGLCanvas(nullptr);
  IupSetAttribute(canvas, "SIZE", "x35");
  IupSetAttribute(canvas, "BORDER", "NO");
  IupSetAttribute(canvas, "EXPAND", "HORIZONTAL");
  IupSetCallback(canvas, "ACTION", (Icallback)start_gl_control);

  Ihandle* text_area = IupText(nullptr);
  IupSetHandle("text_area", text_area);
  IupSetAttribute(text_area, "MULTILINE", "YES");
  IupSetAttribute(text_area, "SCROLLBAR", "VERTICAL");
  IupSetAttribute(text_area, "EXPAND", "YES");
  IupSetAttribute(text_area, "FONTSIZE", "14");
   
  Ihandle* vbox = IupVbox(canvas, text_area, nullptr);
  IupSetAttribute(vbox, "MARGIN", "28x28");
  IupSetAttribute(vbox, "GAP", "20");

  Ihandle* dlg = IupDialog(vbox);
  IupSetAttribute(dlg, "TITLE", "glControl training");
  IupSetAttribute(dlg, "SIZE", "400x210");
  IupSetAttribute(dlg, "RESIZE", "NO");

  IupShowXY(dlg, IUP_CENTER, IUP_CENTER);

  IupRedraw(dlg, true);
}


int main(int argc, char* argv[])
{
  IupOpen(&argc, &argv);
  IupGLCanvasOpen();

  build_dialog();

  IupMainLoop();

  IupClose();

  return 0;
}
