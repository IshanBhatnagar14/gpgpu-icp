#include <fstream>
#include <iostream>

#include "log.hh"
#include "parser.hh"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    init_logs();
    Log::display = true;

    Log l(__FUNCTION__);
    l << "\033[0;33m================= GPGPU ICP =================\033[0m\n";

    return 0;
}
