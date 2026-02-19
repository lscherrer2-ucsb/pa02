// Winter'24
// Instructor: Diba Mirza
// Student name:
#include <algorithm>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#include "movies.h"
#include "utilities.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "Not enough arguments provided (need at least 1 argument)."
             << endl;
        cerr << "Usage: " << argv[0] << " moviesFilename prefixFilename "
             << endl;
        exit(1);
    }

    ifstream movieFile(argv[1]);

    if (movieFile.fail()) {
        cerr << "Could not open file " << argv[1];
        exit(1);
    }

    vector<Movie> movies = parse_movies(movieFile);
    sort(movies.begin(), movies.end(), [](const Movie &a, const Movie &b) {
        return a.name < b.name;
    });

    movieFile.close();

    if (argc == 2) {
        for (const auto &m : movies) {
            cout << m.name << ", " << m.rating << endl;
        }
        return 0;
    }

    ifstream prefixFile(argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes = parse_prefixes(prefixFile);

    ostringstream oss;
    for (const auto &p : prefixes) {
        vector<Movie> filtered = filter_by_prefix(movies, p);
        if (filtered.empty()) {
            cout << "No movies found with prefix " << p << endl;
            continue;
        }
        priority_queue<Movie, vector<Movie>, Movie::Ordering::Rating> pq;
        for (const auto &m : filtered) {
            pq.push(m);
        }
        Movie best = pq.top();
        oss << "Best movie with prefix " << p << " is: " << best.name
            << " with rating " << std::fixed << std::setprecision(1)
            << best.rating << endl;
        while (!pq.empty()) {
            Movie m = pq.top();
            cout << m.name << ", " << m.rating << endl;
            pq.pop();
        }
        cout << endl;
    }
    cout << oss.str();
    return 0;
}

/*
PART 3 (a)

Time Complexity
n movies
m prefixes
k with each prefix
l characters in a name

Sort:
    n*l*log(n) comparisons
Outer for loop:
    m iterations
Filter:
    l*log(n) per prefix (because binary search)
Queue pushes:
    k O(l log k) pushes
Queue pops:
    k O(l log k) pops

The total expression is:
nl(log n) + m [l*log(n) + (k*l*log k) + (k*l*log k)]
nl(log n) + ml(log n) + 2mkl(log k)

Final Time Complexity:
O(nl(log n) + ml(log n) + mkl(log k))
*/

/*
PART 3 (b)

Space Complexity
n movies
m prefixes
k with each prefix
l characters in a name

filtered:
    k movies with l chars
    k*l
pq:
    k movies with l chars
    k*l

The filtered and pq objects are deallocated after each loop,
which means that there does not have to be an m factor

The space complexity expression is
(k*l) + (k*l)
2(k*l)

Final space complexity:
O(kl)
*/

/*
PART 3 (c)

If you designed your algorithm for a low time complexity,
Were you able to achieve a low space complexity as well?
    Yes
Why or why not?
    It achieved a low space complexity by accident. The solution just happens
    to only take up O(kl) space.
*/
