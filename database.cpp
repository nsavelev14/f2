#include "database.h"

void Database::Add(const Date& date, const string& event) {
    
    auto it = storage.find(date);
    
    if (it == end(storage)) {
        unique_storage[date].insert(event);
        storage[date].push_back(event);
    } else {
        if (unique_storage[date].count(event) == 0) {
            unique_storage[date].insert(event);
            storage[date].push_back(event);
        } else {
            return;
        }
    }
}

void Database::Print(ostream& os) const {
    for(const auto& [date,events] : storage)
        for(const auto& event : events)
            os << date << " " << event << endl;
}

pair<Date, string> Database::Last(const Date& date) const {
    if (storage.empty())
        throw invalid_argument("No entries");
    if (date < begin(storage)->first)
        throw invalid_argument("No entries");
    
    auto it = storage.upper_bound(date);
    if (it == begin(storage)) {
        throw invalid_argument("No entries");
    }
    it = prev(it);
    
    if (it == end(storage))
        it = prev(it);
    
    pair<Date, string> p {it->first, " "};
    string s = it->second.back();
    Date d = it->first;
    return {d,s};
}

