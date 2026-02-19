#include "utilities.h"
#include <algorithm>
#include <string>

bool parse_line(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex + 1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}
vector<Movie> parse_movies(ifstream &fs) {
    string line, name;
    double rating;
    vector<Movie> movies;
    while (getline(fs, line) && parse_line(line, name, rating)) {
        movies.push_back({name, rating});
    }
    return movies;
}
vector<string> parse_prefixes(ifstream &fs) {
    vector<string> prefixes;
    string line;
    while (getline(fs, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }
    return prefixes;
}
vector<Movie>
filter_by_prefix(const vector<Movie> &movies, const string &prefix) {
    // binary search
    auto lower = lower_bound(
        movies.begin(),
        movies.end(),
        prefix,
        [](const Movie &m, const string &p) {
            return m.name < p;
        });

    // next string past the last one
    string upper = prefix;
    upper.back()++;
    auto hi = lower_bound(
        lower,
        movies.end(),
        upper,
        [](const Movie &m, const string &p) {
            return m.name < p;
        });

    return vector<Movie>(lower, hi);
}
