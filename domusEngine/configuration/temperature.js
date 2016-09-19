var log=Log();
var devices=zDevices.getDevices();

if (devices.length > 0){
    for(var i = 0; i < devices.length; i++){
        var endpoints = devices[i].getEndpoints();
        for (var j=0; j < endpoints.length; j++){
            if (endpoints[j].deviceId == 0x0302){
                zCluster(extAddress, endpoints[j], 0x402);

            }
        }
    }
}