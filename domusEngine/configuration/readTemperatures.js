/**
 * Created by paolo on 27/12/16.
 */
var log=Log();
var endpoints = zEndpoints.getEndpointsWithInCluster(0x402);
log.info("endpoints size: " + endpoints.length);
for (let endpoint of endpoints){
    var cluster = endpoint.getCluster(0x402);
    var temp = cluster.getProperyById(0);
    log.info("temperature: " + temp);
}