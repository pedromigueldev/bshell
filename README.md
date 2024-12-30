# BSHELL

A personal shell library to use with some other projects like Biblioteca

## How to setup BSHELL

Follow these steps to integrate and use BSHELL in your C project:
```bash
git clone https://github.com/pedromigueldev/bshell
cd bshell
make
```
Include the header file in your code
```c
#include "./bshell/src/libbshell.h" // Adjust the path if necessary
```
Compile your program with the library:
```bash
gcc -o my_program my_program.c -L/bshell/lib -lbshell
```

## How to use BSHELL

In your main C file:
```c
int clear() {
    #ifdef _WIN32
        system("cls");  // For Windows
    #else
        system("clear");  // For Linux/macOS
    #endif
    return 1;
}

int main(int argc, char** argv)
{
    ConfigStruct config_struct = bshell_config_init();
    config_struct.wellcome_message = "TITLE";
    config_struct.help_message =  "Helper message";
    config_struct.prompt = "some instructions before accepting input from user:\n";
    config_struct.add_extra_f("clear", &clear);

    return bshell_main(config_struct);
}
```
Run your program in the terminal:
```bash
./my_program
TITLE
some instructions before accepting input from user:

```
