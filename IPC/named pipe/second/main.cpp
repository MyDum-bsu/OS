#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wformat-security"

#include <iostream>
#include "../pipe.h"

int main() {
    Pipe pipe("/tmp/A");
    printf("%s", pipe.Read());
    pipe.Write("second\n");
}
