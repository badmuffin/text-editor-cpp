#include <Fl/Fl.H>
#include <Fl/Fl_Double_Window.H>
#include <Fl/Fl_Text_Editor.H>
#include <Fl/Fl_Text_Buffer.H>
#include <Fl/Fl_Menu_Bar.H>
#include <Fl/fl_ask.H>
#include <Fl/Fl_File_Chooser.H>

Fl_Text_Buffer *textbuf;

char fileName[256] = "";
int changed = 0; // flag if file is modified and not saved
int loading = 0; // loading flag, used when interacting with files

class EditorWindow;

void new_cb(Fl_Widget *, void *);
void open_cb(Fl_Widget *, void *);
void save_cb(Fl_Widget *, void *);
void quit_cb(Fl_Widget *, void *);

void copy_cb(Fl_Widget *, void *);
void cut_cb(Fl_Widget *, void *);
void paste_cb(Fl_Widget *, void *);
void delete_cb(Fl_Widget *, void *);

void find_cb(Fl_Widget *, void *);
void find2_cb(Fl_Widget *, void *);

void load_file(const char *newfile)
{
    loading = 1;

    if (textbuf->loadfile(newfile))
        fl_alert("Error opening file!");
    else
    {
        strcpy(fileName, newfile);
        changed = 0;
    }

    loading = 0;
}

void save_file(const char *newfile)
{
    if (textbuf->savefile(newfile))
        fl_alert("Error saving file!");
    else
    {
        strcpy(fileName, newfile);
        changed = 0;
    }
}

void changed_cb(int, int nInserted, int nDeleted, int, const char *, void *)
{
    if (loading)
        return;

    if (nInserted || nDeleted)
        changed = 1;
}

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
    {"&File", 0, 0, 0, FL_SUBMENU},
    {"&New File", FL_CTRL + 'n', (Fl_Callback *)new_cb},
    {"&Open File...", FL_CTRL + 'o', (Fl_Callback *)open_cb},
    {"&Save File", FL_CTRL + 's', (Fl_Callback *)save_cb},
    {"E&xit", FL_CTRL + 'q', (Fl_Callback *)quit_cb},
    {0},

    {"&Edit", 0, 0, 0, FL_SUBMENU},
    {"Cu&t", FL_CTRL + 'x', (Fl_Callback *)cut_cb},
    {"&Paste", FL_CTRL + 'v', (Fl_Callback *)paste_cb},
    {"&Copy", FL_CTRL + 'c', (Fl_Callback *)copy_cb},
    {"&Delete", FL_CTRL + 'd', (Fl_Callback *)delete_cb},
    {0},

    {"&Search", 0, 0, 0, FL_SUBMENU},
    {"&Find...", FL_CTRL + 'f', (Fl_Callback *)find_cb},
    {"F&ind Again", FL_CTRL + 'g', (Fl_Callback *)find2_cb},
    {0},

    {0}};

class EditorWindow : public Fl_Double_Window
{
public:
    Fl_Text_Editor *editor;
    Fl_Menu_Bar *menu;
    char search[256];

    EditorWindow(int width, int height, const char *title) : Fl_Double_Window(width, height, title)
    {
        menu = new Fl_Menu_Bar(0, 0, width, 30);
        menu->copy(menuItems);
        // passing editor window so that menu callback can access it
        menu->user_data(this);

        editor = new Fl_Text_Editor(0, 30, width, height - 30);
        editor->buffer(textbuf);
        editor->textfont(FL_COURIER);

        search[0] = '\0';

        textbuf->add_modify_callback(changed_cb, nullptr);

        end();
    }

    ~EditorWindow() {};
};

void new_cb(Fl_Widget *, void *)
{
    textbuf->select(0, textbuf->length());
    textbuf->remove_selection();

    fileName[0] = '\0';
    changed = 0;
}

void open_cb(Fl_Widget *, void *)
{
    const char *newfile = fl_file_chooser("Open file", "*", fileName);
    if (newfile != nullptr)
        load_file(newfile);
}

// if filename not exist, ask user Save As, otherwise overwrite existing file
void save_cb(Fl_Widget *, void *)
{
    if (fileName[0] == '\0')
    {
        const char *newfile = fl_file_chooser("Save File As", "*", fileName);
        if (newfile != nullptr)
            save_file(newfile);
    }
    else
        save_file(fileName);
}

void quit_cb(Fl_Widget *, void *)
{
    if (changed)
    {
        int r = fl_choice("File not saved.\nSave before exit?", "Cancel", "Save", "Discard");
        if (r == 1)
            save_cb(nullptr, nullptr);
        else if (r == 0)
            return;
    }

    exit(0);
}

void copy_cb(Fl_Widget *w, void *)
{
    EditorWindow *editorWindow = (EditorWindow *)w->window();
    Fl_Text_Editor::kf_copy(0, editorWindow->editor);
}

void cut_cb(Fl_Widget *w, void *)
{
    EditorWindow *editorWindow = (EditorWindow *)w->window();
    Fl_Text_Editor::kf_cut(0, editorWindow->editor);
}

void paste_cb(Fl_Widget *w, void *)
{
    EditorWindow *editorWindow = (EditorWindow *)w->window();
    Fl_Text_Editor::kf_paste(0, editorWindow->editor);
}

void delete_cb(Fl_Widget *, void *)
{
    textbuf->remove_selection();
}

void find_cb(Fl_Widget *w, void *v)
{
    EditorWindow *editorWindow = (EditorWindow *)w->window();
    const char *val = fl_input("Search string ", editorWindow->search);

    if (val != nullptr)
    {
        strcpy(editorWindow->search, val);
        find2_cb(w, v);
    }
}

void find2_cb(Fl_Widget *w, void *v)
{
    EditorWindow *editorWindow = (EditorWindow *)w->window();

    if (editorWindow->search[0] == '\0')
    {
        find_cb(w, v);
        return;
    }

    int insertPos = editorWindow->editor->insert_position();
    int found = textbuf->search_forward(insertPos, editorWindow->search, &insertPos);

    if (found)
    {
        textbuf->select(insertPos, insertPos + strlen(editorWindow->search));
        editorWindow->editor->insert_position(insertPos + strlen(editorWindow->search));
        editorWindow->editor->show_insert_position();
    }
    else
        fl_alert("No occurrences of '%s' found!", editorWindow->search);
}

int main()
{
    textbuf = new Fl_Text_Buffer; // initialize buffer
    EditorWindow *window = new EditorWindow(1000, 800, "Simple Text Editor");

    window->show();
    return Fl::run(); // start event loop
}
