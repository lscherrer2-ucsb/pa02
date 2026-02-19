#include "movies.h"
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#ifndef UTIL_H
#define UTIL_H

vector<Movie> parse_movies(ifstream &f);
void display_movies(vector<Movie> &movies);
vector<string> parse_prefixes(ifstream &fs);
vector<Movie> filter_by_prefix(const vector<Movie> &movies, const string &prefix);

#endif
