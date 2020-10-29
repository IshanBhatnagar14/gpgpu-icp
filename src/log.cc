#include "log.hh"

#include <fstream>
#include <iomanip>

bool Log::display = false;
std::shared_ptr<std::ostream> NULLOSTREAM;

void init_logs()
{
    auto v = std::make_shared<std::ofstream>();
    v->open("/dev/null");
    NULLOSTREAM = v;
}

Log::Log(std::string tag)
    : tag_{ tag }
    , error_{ false }
{
}

Log::Log(std::string tag, bool error)
    : tag_{ tag }
    , error_{ error }
{
}

void Log::title()
{
    if (Log::display) {
        std::clog << "\033[0;33m==================== " << tag_
                  << " ====================\033[0m" << std::endl;
    }
}

std::ostream &Log::operator<<(std::string message)
{
    if (Log::display) {
        std::ostream &s = std::clog << "[";
        if (error_)
            s << "\033[1;31m";
        else
            s << "\033[1;32m";
        s << tag_ << "\033[0m" << std::setw(16 - tag_.length()) << "] "
          << message;
        return s;
    }
    return *NULLOSTREAM;
}
