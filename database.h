#pragma once
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include "date.h"

template <typename T, typename K>
ostream& operator<<(ostream& stream, const pair<T,K>& p) {
    stream << p.first << " " << p.second;
    return stream;
}

class Database {
public:
    
    void Add(const Date& date, const string& event);
    
    void Print(ostream& os) const;
    
    template <typename Predicate>
    int RemoveIf(Predicate p) {

        int count = 0;
        vector<Date> to_erase;
        for (auto& [date,events] : storage) {
            
            Date _date = date;
            
            auto to_remove = stable_partition(begin(events), end(events), [p, _date](const string& event) {
                return !p(_date,event);
            } );
            
            for (auto it = to_remove; it != end(events);) {
                unique_storage[date].erase(*it);
                it = events.erase(it);
                count++;
            }
            if (events.empty()) {
                to_erase.push_back(_date);
            }
        }
        
        for (const auto& i : to_erase) {
            unique_storage.erase(i);
            storage.erase(i);
        }
        return count;
    }
    
    template <typename Predicate>
    vector<pair<Date, string>> FindIf(Predicate p) const{
        vector<pair<Date, string>> result;
        result.clear();
        
        for (auto& [date,events] : storage) {
            Date _date = date;
            auto it = begin(events);
            while (it != end(events)) {
                auto found = find_if(it, end(events), [p, _date](const string& event) {
                    return p(_date,event);
                } );
                if (found != end(events)) {
                    result.push_back({_date, *found});
                    it = found + 1;
                } else {
                    it = found;
                }
            }
        }
        return result;
    }
    
    pair<Date, string> Last(const Date& date) const;
    
private:
    
    map<Date, vector<string>> storage;
    map<Date, set<string>> unique_storage;
};
