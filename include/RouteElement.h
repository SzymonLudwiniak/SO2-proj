#include <string>

struct RouteElement
{
    std::string stationName;
    int stopTime;
    bool hasStoped {false};
};