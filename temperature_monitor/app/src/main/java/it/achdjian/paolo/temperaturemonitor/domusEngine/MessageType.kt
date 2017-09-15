package it.achdjian.paolo.temperaturemonitor.domusEngine

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
    }
}