#include <fstream>
#include <iostream>

#include "log.hh"
#include "points.hh"
#include "aligment.hh"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    init_logs();
    Log::display = true;

    Log l(__FUNCTION__);
    l << "\033[0;33m================= GPGPU ICP =================\033[0m\n";

    Points dataset("data/data_students/cow_ref.txt");

    l << "Parse OK";
    /*for (auto v : dataset.getPoints()) {
        std::cout << v;
    }*/

    /* test moyenne payet
    Points payet("data/data_students/perso.txt");
    Vect3f m = mean(payet);
    l << " "<<  m.x << " " << m.y << " " << m.z; 
    */

    return 0;
}
