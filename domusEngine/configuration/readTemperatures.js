/**
 * Created by paolo on 27/12/16.
 */

var fnReq = function (nwkId, endpointId, clusterId, attrId) {
    log.info("request arrived from: " + nwkId + ", " + endpointId + ", " + clusterId + ", " + attrId);

    var table = DbTable('Temperatures');
    var cluster = zCluster(nwkId, endpointId, clusterId);
    var temp = cluster.getProperyById(0);
    log.info("temperature: " + temp.value);
    var row = DbRow();
    log.info("row");
    row.setValue('value', temp.value);
    row.setValue('network_id', nwkId);
    log.info("row set");
    table.insert(row);
    log.info("insert");
}

var log = Log();
var endpoints = zEndpoints.getEndpointsWithInCluster(0x402);
log.info("endpoints size: " + endpoints.length);
if (endpoints.length > 0 ) {
    for (let endpoint of endpoints) {
        var cluster = endpoint.getCluster(0x402);
        var temp = cluster.getProperyById(0);
        log.info("Requesting temp");
        temp.requestValue(fnReq);
    }
    log.info("waiting for 5 seconds");
    var a = wait(5000);

}




