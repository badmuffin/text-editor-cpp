#include <Fl/Fl.H>
#include <Fl/Fl_Double_Window.H>
#include <Fl/Fl_Text_Editor.H>
#include <Fl/Fl_Text_Buffer.H>

Fl_Text_Buffer *textbuf;

class EditorWindow : public Fl_Double_Window {
public:
    Fl_Text_Editor *editor;

    EditorWindow(int width, int height, const char* title ) : Fl_Double_Window(width, height, title) {
        editor = new Fl_Text_Editor(0, 0, width, height);

        // attach buffer
        editor->buffer(textbuf);

        //monospace font
        editor->textfont(FL_COURIER);

        end();
    }

    ~EditorWindow() {};
};

int main() {
    textbuf = new Fl_Text_Buffer; // initialize buffer
    EditorWindow *window = new EditorWindow(600, 400, "Simple Text Editor");
    
    window->show();
    return Fl::run(); // start event loop
} 
