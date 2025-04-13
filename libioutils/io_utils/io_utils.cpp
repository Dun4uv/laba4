#include "io_utils.h"

#include <cstdlib>
#include <iostream>
#include <limits>

using namespace std;

void io_setup() {

#if _MSC_VER
    system("chcp 65001 > nul");
#endif
    ios_base::sync_with_stdio(false);
}
void clear_buf() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
 }
