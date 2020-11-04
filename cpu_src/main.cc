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

   // Points p("data/data_students/cow_ref.txt");
   // Points model("data/data_students/cow_tr2.txt");
    
    Points p(argv[1]);
    Points model(argv[2]);

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
