#ifndef ROUTERREADER_H
#define ROUTERREADER_H

#include <fstream>

struct RouteReader {
    RouteReader(const std::string& filename)
        : in(filename) {
    }

    virtual ~RouteReader() {
        in.close();
    }


private:
    RouteReader(const RouteReader& src);
    RouteReader& operator = (const RouteReader& src);

    std::ifstream in;
};

#endif // ROUTERREADER_H
