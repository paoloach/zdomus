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

DbTable
    constructor
         DbTable('tablename') --> create an object linked to the table 'tablename'
    method
        insert(row) -->a DbRow object. Persist that object into the table linked to DbTable
        find('where_condition') --> Find all the Rows that match the where_condition. It return a DbResultSet point before the first object (in order to the first call to method nextRow return the first row)

DbResultSet
    method
        nextRow --> Return the next row (a DbRow object). If  DbResultSet instance point to the  last object, it returns an empty object
        prevRow --> Return the previous row (a DbRow object). If DbResultSet instance point to the first object, it returns an empty object

DbRow
    constructor
        DbRow() --> create an empty object
    method
        getValue('fieldName') --> Return the value of the field name 'fieldName'
        setValue('fieldName', value) --> Set the value of the field name 'fieldName' as value. Value can be of type string, integer, boolean, and date. Any other object is converted to string
