//
// Created by paolo on 03/04/16.
//

#ifndef DOMUS_ENGINE_BINDTABLEPT_H
#define DOMUS_ENGINE_BINDTABLEPT_H

#include <boost/property_tree/ptree.hpp>
#include "../BindTable.h"

namespace zigbee {
  namespace http {

    class BindTablePT : public boost::property_tree::ptree {
    public:
        BindTablePT(BindTable &bindTable) noexcept;

        virtual ~BindTablePT() noexcept = default;

    };
  }
}


#endif //DOMUS_ENGINE_BINDTABLEPT_H
