#include <string>
using namespace std;

#ifndef MOVIES_H
#define MOVIES_H

struct Movie {
    string name;
    double rating;

    struct Ordering {
        struct Alphabetic {
            bool operator()(const Movie&, const Movie&);
        };
        struct Rating {
            bool operator()(const Movie&, const Movie&);
        };
    };
};

#endif
