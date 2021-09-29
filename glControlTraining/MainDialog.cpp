#include "MainDialog.h"

#include <iup.h>
#include <iupgl.h>

MainDialog::MainDialog(int* argc, char*** argv)
{
  if (*argc == 1)
    this->m_executable_path = *argv[0];

  IupOpen(argc, argv);
  IupGLCanvasOpen();

  build_dialog();

  IupMainLoop();

  IupClose();
}


void MainDialog::gl_ctrl_action_cb(Ihandle* canvas)
{

}

void MainDialog::build_dialog()
{
  Ihandle* canvas = IupGLCanvas(nullptr);
  IupSetAttribute(canvas, "SIZE", "x35");
  IupSetAttribute(canvas, "BORDER", "NO");
  IupSetAttribute(canvas, "EXPAND", "HORIZONTAL");
  IupSetCallback(canvas, "ACTION", (Icallback)MainDialog::gl_ctrl_action_cb);

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
