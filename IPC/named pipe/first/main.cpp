#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wformat-security"

#include <iostream>
#include "../pipe.h"

int main() {
    Pipe pipe("tmp/A");
    pipe.Write("first\n");
    printf("%s", pipe.Read());
}
