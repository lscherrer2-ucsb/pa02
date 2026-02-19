#include "movies.h"
using namespace std;

bool Movie::Ordering::Alphabetic::operator()(const Movie &l, const Movie &r) {
    return l.name > r.name;
}
bool Movie::Ordering::Rating::operator()(const Movie &l, const Movie &r) {
    if (l.rating == r.rating) {
        return l.name > r.name;
    }
    return l.rating < r.rating;
}
