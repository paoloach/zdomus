# zdomus

##General description

An Domotic HUB with the goal to link the low level zigbee sensors and actuactors and high level applications

The sensors zigbee data are availabe as basic REST api by the ZEngine application. The same application makes availabe other basic REST API in order to manage the zigbee actuactors.

Further the basic REST API, it is possible use Java script in order to make availabe new services.

The Javascript run with special extensions in order to accede to all the zigbee data and comand, to manage the underlaing database and to create new REST path.

For example the following Javascript save on database the temperature of all the zigbee sensors that offer a temperature service:

'
var tempArrived = function (nwkId, endpointId, clusterId, attrId) {
  # This function is called when a sensor respond.
  # Save the temperature value into the database
   var table = DbTable('Temperatures');
    var cluster = zCluster(nwkId, endpointId, clusterId);
    var temp = cluster.getProperyById(0);
    var row = DbRow();
    row.setValue('value', temp.value);
    row.setValue('network_id', nwkId);
    table.insert(row);
}

  # cluster 0x402 are the temperature service
var endpoints = zEndpoints.getEndpointsWithInCluster(0x402);
if (endpoints.length > 0 ) {
    for (let endpoint of endpoints) {
        var cluster = endpoint.getCluster(0x402);
        var temp = cluster.getProperyById(0);
        # request the temperature and when the sensor responds it call the callback 
        temp.requestValue(tempArrived);
    }
}
'


If you want also export a REST service to get the temperature, is enough to register a REST path and a callback



## projects
There are several subprojects in order to deal with different aspcted of the problem

### zEngine
It is the main and real project. The hearth of all the others subprojects

### zigbee_lib
Library used by zEngine. It export the data structere in zigbee

### domusViews
A android application that use the zEngine to manage a Domotic house.









