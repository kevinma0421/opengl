#include "utils.h"
#include <fstream>

static std::ofstream debugLog("debug.log");

void logMessage(const std::string &msg)
{
    debugLog << msg << std::endl;
    debugLog.flush();
}
