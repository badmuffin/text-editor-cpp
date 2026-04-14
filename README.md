## Simple Text Editor

A lightweight C++ text editor built with FLTK (Fast Light Toolkit).

https://github.com/user-attachments/assets/0a52e78c-0bd6-46e0-9770-5210e13a685d

### Features

#### File Operations

- New File (Ctrl+N) - Create new document
- Open File (Ctrl+O) - Open existing files
- Save File (Ctrl+S) - Save current document
- Exit (Ctrl+Q) - Quit with unsaved changes warning

#### Edit Operations

- Cut (Ctrl+X) - Cut selected text
- Copy (Ctrl+C) - Copy selected text
- Paste (Ctrl+V) - Paste from clipboard
- Delete (Ctrl+D) - Delete selected text

#### Search Operations

- Find (Ctrl+F) - Search for text
- Find Again (Ctrl+G) - Repeat last search
- Replace (Ctrl+R) - Replace text content

### How to Run
Step 1: Install FLTK
```Bash
sudo apt install libfltk1.3-dev
```

Step 2: Compile the project
```Bash
fltk-config --compile main.cpp
```


Step 3: Run the application
```Bash
./main
```
