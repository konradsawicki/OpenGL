
#include "Application.h"

int main(int argc, char** argv) {
  auto app = yon::Application::Get();
  app->Run();
}
