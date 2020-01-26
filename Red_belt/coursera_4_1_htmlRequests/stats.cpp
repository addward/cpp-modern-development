#include "stats.h"
#include <iostream>

using namespace std;

Stats::Stats() {
    cout << "Hello";
    for(auto& elem: uri_) {
        uriStats_[elem] = 0;
    }
    for(auto& elem: method_) {

        methodStats_[elem] = 0;
    }
}

void Stats::AddMethod(string_view method) {
    if (methodStats_.count(method) != 1) {
        ++methodStats_[UNKNOWN_METHOD_];
    } else {
        ++methodStats_[method];
    }
}

void Stats::AddUri(string_view uri) {
    if (uriStats_.count(uri) != 1) {
        ++uriStats_[UNKNOWN_URI_];
    } else {
        ++uriStats_[uri];
    }
}

const map<string_view, int>& Stats::GetMethodStats() const {
    return methodStats_;
}

const map<string_view, int>& Stats::GetUriStats() const {
    return uriStats_;
}
HttpRequest ParseRequest(string_view line) {
    line.remove_prefix(line.find_first_not_of(' '));

    size_t methodEnd = line.find(' ');
    size_t uriEnd = line.find(' ', methodEnd + 1);

    string_view method = line.substr(0, methodEnd);
    string_view uri = line.substr(methodEnd + 1, uriEnd - methodEnd - 1);
    string_view protocol = line.substr(uriEnd + 1, line.size());
    //cout << "---" << endl << line << endl;
    //cout << "<" << method << ">" << uri << endl;
    return {method, uri, protocol};
}
