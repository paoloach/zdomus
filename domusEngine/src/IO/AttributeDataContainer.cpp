/*
 * AttributeDataContainer.cpp
 *
 *  Created on: 01/dic/2014
 *      Author: Paolo Achdjian
 */

#include <boost/log/trivial.hpp>

#include "AttributeDataContainer.h"
#include "jsonFields.h"
#include "DataPropertyTree.h"

namespace zigbee {

    using boost::property_tree::ptree;

    void AttributeDataContainer::push(AttributeData &&attribute) {
        AttributeDataContainer::Data data{attribute, tokenUpdate};

        BOOST_LOG_TRIVIAL(debug) << "push data size: " << attribute.getData().size();
        attributes.push_back(std::move(data));
        if (attributes.size() > maxElements) {
            attributes.pop_front();
        }
        tokenUpdate++;
    }

    ptree AttributeDataContainer::getPropery(const zigbee::AttributeData &attribute) {
        ptree attributeP{};

        attributeP.put(ATTR_ID_NAME, attribute.getAttrId());
        attributeP.put(CLUSTER_ID_NAME, attribute.getClusterId());
        attributeP.put(ENDPOINT_ID_NAME, attribute.getEndpoint());
        attributeP.put(SHORT_ADDR_NAME, attribute.getNetworkAddr());
        attributeP.put(PAN_ID_NAME, attribute.getPanId());
        attributeP.put(STATUS_NAME, attribute.getStatus());
        attributeP.put(TYPE_NAME, attribute.getType());
        attributeP.put_child(DATA_NAME, DataPropertyTree{attribute.getData()});

        return attributeP;
    }

    ptree AttributeDataContainer::get(uint64_t token) {
        ptree update{};

        update.put(TOKEN_ATTRIBUTE_NAME, tokenUpdate);
        for (const Data &data : attributes) {
            if (data.tokenUpdate >= token) {
                update.push_back({ATTRIBUTE_MESSAGE_NAME, getPropery(data.attribute)});
            }
        }

        return update;
    }


} /* namespace zigbee */
