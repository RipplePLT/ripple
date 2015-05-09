#include "debug_tools.h"

void d(string m) {
#ifdef DEBUG
    cout << m << endl;
#endif
}
