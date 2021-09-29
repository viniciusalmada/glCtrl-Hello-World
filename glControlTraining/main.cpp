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
  


  

  glCtrl::Gui::Space* space_start = new glCtrl::Gui::Space(20, glCtrl::Gui::Expandable);
  glCtrl::Gui::Space* space_end = new glCtrl::Gui::Space(*space_start);

  
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
  
}

int main(int argc, char* argv[])
{
  

  return 0;
}
