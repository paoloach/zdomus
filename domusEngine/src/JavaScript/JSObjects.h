/*
 * JSObjects.h
 *
 *  Created on: 28/dic/2014
 *      Author: Paolo Achdjian
 */

#ifndef SRC_JAVASCRIPT_JSOBJECTS_H_
#define SRC_JAVASCRIPT_JSOBJECTS_H_


// Functions
static constexpr const char * JSWAIT = "wait";

// Objects
static constexpr const char * JSZDEVICES = "zDevices";
static constexpr const char * JSZDEVICE = "zDevice";
static constexpr const char * JSZENDPOINT = "zEndpoint";
static constexpr const char * JSZENDPOINTS = "zEndpoints";
static constexpr const char * JSZCLUSTER = "zCluster";
static constexpr const char * JSLOG = "Log";
static constexpr const char * JSDBTABLE = "DbTable";
static constexpr const char * JSRESULT_SET = "DbResultSet";
static constexpr const char * JSDBMANAGER = "DbManager";
static constexpr const char * JSDBROW = "DbRow";
static constexpr const char * JSRESTSERVER = "RestServer";

// zDevices methods
static constexpr const char * GETCOUNTDEVICES = "getCountDevices";
static constexpr const char * GETDEVICES = "getDevices";
static constexpr const char * GETDEVICE = "getDevice";


// zDevice attributes
static constexpr const char * GETLONGADDRESS = "longAddress";
static constexpr const char * GETSHORTADDRESS = "shortAddress";
// zDevice methods
static constexpr const char * IS_PAN = "isPan";
static constexpr const char * IS_FFD = "isFullFunctionDevice";
static constexpr const char * IS_POWEREDSOURCE = "isMainPoweredSource";
static constexpr const char * IS_DISABLE_RF_IDLE = "isDisableRFInIDLE";
static constexpr const char * IS_SECURE_CAPABILITY = "isSecureCapable";
static constexpr const char * GETENDPOINTS = "getEndpoints";

// zEndpoint attributes
static constexpr const char * ENDPOINT = "endpointId";
static constexpr const char * PROFILEID = "profileId";
static constexpr const char * DEVICEID = "deviceId";
static constexpr const char * DEVICE_VERSION = "deviceVersion";
static constexpr const char * NETWORK_ID = "networkId";
// zEndpoint method
static constexpr const char * GET_CLUSTER = "getCluster";


// zEndpoints methods
static constexpr const char * GET_ENDPOINTS_WITH_IN_CLUSTER = "getEndpointsWithInCluster";

// zCluster methods
static constexpr const char * GET_PROPERTY_BY_ID = "getProperyById";
static constexpr const char * EXECUTE_CMD_BY_ID = "executeCmdById";

// zAttribute attributes
static constexpr const char * VALUE = "value";
// zAttribute methods
static constexpr const char * REQUEST_VALUE = "requestValue";
static constexpr const char * IS_AVAILABLE="isAvailable";
static constexpr const char * IS_UNSUPPORTED="isUnsupported";
static constexpr const char * GET_STATUS = "getStatus";
static constexpr const char * GET_IDENTIFIER="getIdentifier";
static constexpr const char * GET_NAME = "getName";
static constexpr const char * IS_READONLY = "isReadOnly";

// Log methods
static constexpr const char * DEBUG="debug";
static constexpr const char * INFO="info";
static constexpr const char * WARN="warn";
static constexpr const char * ERROR="error";

// DbTable methods
static constexpr const char * FIND="find";
static constexpr const char * INSERT="insert";

// DbResultSet method
static constexpr const char * NEXTROW="nextRow";
static constexpr const char * PREVIOUSROW="previousRow";

//DBRow methods
static constexpr const char * GET_VALUE="getValue";
static constexpr const char * SET_VALUE="setValue";

// RestServer methods
static constexpr const char * ADD_PATH="addPath";


#endif /* SRC_JAVASCRIPT_JSOBJECTS_H_ */
