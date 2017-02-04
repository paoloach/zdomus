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

