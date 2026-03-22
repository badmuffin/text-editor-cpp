#include <Fl/Fl.H>
#include <Fl/Fl_Double_Window.H>
#include <Fl/Fl_Text_Editor.H>
#include <Fl/Fl_Text_Buffer.H>
#include <Fl/Fl_Menu_Bar.H>

Fl_Text_Buffer *textbuf;

// callbacks
void new_cb(Fl_Widget*, void*) {}
void open_cb(Fl_Widget*, void*) {}
void save_cb(Fl_Widget*, void*) {}
void quit_cb(Fl_Widget*, void*) {}

void copy_cb(Fl_Widget*, void*) {}
void cut_cb(Fl_Widget*, void*) {}
void paste_cb(Fl_Widget*, void*) {}
void find_cb(Fl_Widget*, void*) {}

/* 
{ 0 } marks end of the submenu
"&t" means t with underline
 
internal structure of Menu Items
struct Fl_Menu_Item {
    const char* text;      // label
    int shortcut;          // keyboard shortcut
    Fl_Callback* callback; // function
    void* user_data;       // extra data
    int flags;             // behavior
};
*/

Fl_Menu_Item menuItems[] = {
    { "&File", 0, 0, 0, FL_SUBMENU },
        { "&New File", FL_CTRL + 'n', (Fl_Callback*)new_cb },
        { "&Open File...", FL_CTRL + 'o', (Fl_Callback*)open_cb },
        { "&Save File", FL_CTRL + 's', (Fl_Callback*)save_cb },
        { "E&xit", FL_CTRL + 'q', (Fl_Callback*)quit_cb },
    { 0 },

    { "&Edit", 0, 0, 0, FL_SUBMENU },
        { "Cu&t", FL_CTRL + 'x', (Fl_Callback*)cut_cb },
        { "&Paste", FL_CTRL + 'v', (Fl_Callback*)paste_cb },
        { "&Copy", FL_CTRL + 'c', (Fl_Callback*)copy_cb },
    { 0 },

    { "&Search", 0, 0, 0, FL_SUBMENU },
        { "&Find...", FL_CTRL + 'f', (Fl_Callback*)find_cb },
    { 0 },

    { 0 }
};

class EditorWindow : public Fl_Double_Window {
public:
    Fl_Text_Editor *editor;
    Fl_Menu_Bar *menu;

    EditorWindow(int width, int height, const char* title ) : Fl_Double_Window(width, height, title) {
        menu = new Fl_Menu_Bar(0, 0, width, 30);
        menu->copy(menuItems);

        editor = new Fl_Text_Editor(0, 30, width, height - 30);
        editor->buffer(textbuf);
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
