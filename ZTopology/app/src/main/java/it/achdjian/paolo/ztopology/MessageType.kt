package it.achdjian.paolo.ztopology

/**
 * Created by Paolo Achdjian on 7/10/17.
 */
class MessageType {
    companion object {
        val WHO_ARE_YOU=1000
        val GET_DEVICES=1001
        val GET_DEVICE=1002
        val NEW_DEVICE=1003
        val NEW_ENDPOINT=1004
        val GET_ATTRIBUTE=1005
        val NEW_ATTRIBUTES=1006
        val REQUEST_IDENTIFY=1007
        val REQUEST_POWER=1008
        val NEW_POWER=1009
        val NEW_DATA_TEMPERATURES=1010
        val NEW_CHILDREN=1011
        val CHILDREN_TIMEOUT=1012
        val NEW_DEVICE_INFO=1013
        val DEVICE_INFO_TIMEOUT=1014
        val DEVICE_TIMEOUT=1015
        val NEW_NODE_INFO=1016
        val NODE_INFO_TIMEOUT=1017
    }
}