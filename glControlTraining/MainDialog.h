#ifndef GL_CTRL_MAIN_DIALOG
#define GL_CTRL_MAIN_DIALOG
#include <iup.h>
#include <string>

class MainDialog
{
  static void gl_ctrl_action_cb(Ihandle* canvas);

  std::string m_executable_path;

  void build_dialog();

public:
  MainDialog(int* argc, char*** argv);
};

#endif
