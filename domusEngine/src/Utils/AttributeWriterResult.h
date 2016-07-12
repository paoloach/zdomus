//
// Created by paolo on 12/07/16.
//

#ifndef DOMUS_ENGINE_ATTRIBUTEWRITERRESULT_H
#define DOMUS_ENGINE_ATTRIBUTEWRITERRESULT_H

#include <set>
#include <cstddef>
#include <string>

class AttributeWriterResult {
public:
    void add(int id){
        ids.insert(id);
    }

    size_t size() const {return ids.size();}
    bool hasId(int id){return ids.count(id) > 0;}
    std::string toJSon();
private:
    std::set<int>   ids;
};


#endif //DOMUS_ENGINE_ATTRIBUTEWRITERRESULT_H
