#include <fstream>
#include <iostream>

#include "icp.hh"
#include "log.hh"
#include "points.hh"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    init_logs();
    Log::display = true;

    Log l("GPGPU ICP");
    l.title();

    Points p;
    Points model;

    if (argc < 2)
    {
        p = Points("data/data_students/cow_ref.txt");
        model = Points("data/data_students/cow_tr2.txt");
    }
    else
    {
        p = Points(argv[1]);
        model = Points(argv[2]);
    }

    l << "Parse OK" << std::endl;

    if (p.size() != model.size())
    {
        Log l("Parsing", true);
        l << "Points sets need to have the same number of points" << std::endl;
        return 1;
    }

    
    apply_alignment(p, model);

    l << "find_aligment() OK" << std::endl;

    return 0;
}
