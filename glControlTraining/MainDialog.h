#ifndef GL_CTRL_MAIN_DIALOG
#define GL_CTRL_MAIN_DIALOG
#include <iup.h>
#include <string>

class MainDialog
{

  static void build_dialog();

public:
  MainDialog(int* argc, char*** argv);

  static std::string executable_path;

  static int gl_ctrl_action_cb(Ihandle* canvas);
};

#endif
