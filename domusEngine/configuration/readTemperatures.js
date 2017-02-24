/**
 * Created by paolo on 27/12/16.
 */

var tempArrived = function (nwkId, endpointId, clusterId, attrId) {

    var table = DbTable('Temperatures');
    var cluster = zCluster(nwkId, endpointId, clusterId);
    var temp = cluster.getProperyById(0);
    log.info("request arrived from: " + nwkId + ", " + endpointId + ", " + clusterId + ", " + attrId + " temperature: " + temp.value);
    var row = DbRow();
    row.setValue('value', temp.value);
    row.setValue('network_id', nwkId);
    table.insert(row);
}

var temperatureResponse = function(placeholders) {
    var log = Log();
    log.info("Called callback response with network id: " + placeholders.networdid);

    var table = DbTable('Temperatures');
    var resultSet = table.find("time >= '" + placeholders.dataFrom + "' AND time <= '" + placeholders.dataTo + "' AND network_id=" + placeholders.networdid);
    var results = new Array();
    while(true){
        let row = resultSet.nextRow();
        if (row == null){
            break;
        }
        var temp = new Object();
        temp.value= row.getValue('value');
        temp.time= row.getValue('time');
        results.push(temp);
    }
    return JSON.stringify(results)+'\n\r';
}

var log = Log();
var endpoints = zEndpoints.getEndpointsWithInCluster(0x402);
log.info("endpoints with temperature cluster: " + endpoints.length);
if (endpoints.length > 0 ) {
    for (let endpoint of endpoints) {
        var cluster = endpoint.getCluster(0x402);
        var temp = cluster.getProperyById(0);
        log.info("Requesting temp to " + endpoint.networkId + ":" + endpoint.endpointId);
        temp.requestValue(tempArrived);
    }
}

var restServer = RestServer();
restServer.addPath("/temperature/{networdid}/from/{dataFrom}/to/{dataTo}", temperatureResponse);




