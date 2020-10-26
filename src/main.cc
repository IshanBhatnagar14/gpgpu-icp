#include <fstream>
#include <iostream>

#include "parser.hh"
#include "log.hh"

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    init_logs();
    Log::display = true;

    Log l(__FUNCTION__, true);
    l << "test\n";

    std::cout << "\033[0;33m================= GPGPU ICP =================\033[0m\n";

    return 0;
}
