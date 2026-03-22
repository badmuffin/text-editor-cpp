#include <Fl/Fl.H>
#include <Fl/Fl_Window.H>

int main() {
    Fl_Window *window = new Fl_Window(400, 300, "Test Window");
    window->end();
    window->show();
    return Fl::run();
}