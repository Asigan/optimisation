#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "Reader.h"

int main() {
    Reader r;
    r.lectureFichier(R"(C:\Users\antho\Desktop\Projets\optimisation\Tests\A3205.txt)");
    return 0;
}
