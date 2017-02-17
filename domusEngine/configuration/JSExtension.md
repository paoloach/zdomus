zDevices
    methods
        getCountDevices() --> int --> number of devices;
        getDevices() --> zDevices --> the global instance of object zDevices
        getDevice(extendedAddress) --> zDevice --> A zDevice object of the given extendedAddress

zDevice
    attributes
        longAddress
        shortAddress
    methods
        isPan
        isFullFunctionDevice
        isMainPoweredSource
        isDisableRFInIDLE
        isSecureCapable
        getEndpoints() --> return an array of Endpoint object

zEndpoint -> global istance to ZEndpoints

Endpoint
    attributes
        endpointId
        profileId
        deviceId
        deviceVersion
        networkId
    methods
        getCluster(clusterId) --> return a Cluster Object
Cluster
    attributes

    methods
        getProperyById(attributeId) --> return a Attribute Object
        executeCmdById(cmdId, ... ) -->

Attribute
    attributes
        value
    methods
        requestValue(callbackk) --> call the callback when the attribute value arrive
        isAvailable() --> bool
        isUnsupported() --> bool
        getStatus() --> the status
        getIdentifier() --> the identifier
        getName() --> the name
        isReadOnly() --> bool

RestServer
    addPath(path, value) --> a path that the server will respond by a GET request. If value is a String or a number the return value is that value.
                             If value is a function, it will called and the return value is return by the server
