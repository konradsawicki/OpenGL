
#include "Application.h"

int main(int argc, char** argv) {
  yon::Application* app = new yon::Application();
  app->Run();
  delete app;
}