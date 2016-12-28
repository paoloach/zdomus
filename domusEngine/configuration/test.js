var a;
var log=Log();
a=zDevices.getDevices();

if (prop == null){
  if (a.length > 0){
	var extAddress = '09-0a-0b-0c-0d-0e-0f-10'; 
	var endpoint=5
	var clusterId=3;
	var identTime=0;
	var device = zDevices.getDevice(extAddress);
	
	log.info(device.longAddress);
	var clusterDevice= zCluster(extAddress, endpoint, clusterId);
	var prop = clusterDevice.getProperyById(0);
	log.info('property'+prop);
	
	var attribute = ZUInt16(extAddress, endpoint, clusterId,0);
	log.info('attribute: ' + attribute);
	
	var table = DbTable('temperature');
	var time=0;
  }else{
	log.info('any device');
	
  }
} else {
	log.info('old property ' + prop);
	var row = DbRow();
	row.setValue('date', time);
	row.setValue('value', 10);
	table.insert(row);
	time ++;
	
}