package it.achdjian.paolo.temperaturemonitor

import android.content.ContentValues
import android.content.Context
import android.database.Cursor
import android.database.sqlite.SQLiteDatabase
import it.achdjian.paolo.temperaturemonitor.dagger.ForApplication
import it.achdjian.paolo.temperaturemonitor.domusEngine.DomusEngine
import it.achdjian.paolo.temperaturemonitor.ui.ZElementAdapter
import it.achdjian.paolo.temperaturemonitor.zigbee.ZDevices
import it.achdjian.paolo.temperaturemonitor.zigbee.nullZDevice
import javax.inject.Inject
import javax.inject.Singleton

/**
 * Created by Paolo Achdjian on 31/08/16.
 */
@Singleton
class TempSensorLocationDS @Inject constructor(@ForApplication val context: Context, val zDevices: ZDevices) {
    lateinit var domusEngine: DomusEngine


    fun createTempSensorLocation(networkAddress: String, endpoint: Int, location: String) {
        val domusViewDatabase = DomusViewDatabase(context)
        val database = domusViewDatabase.writableDatabase
        val values = ContentValues()
        values.put(DomusViewDatabase.NETWORK_FIELD, networkAddress)
        values.put(DomusViewDatabase.ENDPOINT, endpoint)
        values.put(DomusViewDatabase.LOCATION, location)
        database.beginTransaction()
        database.insert(DomusViewDatabase.TEMP_SENSOR_LOCATION_TABLE, null, values)
        database.setTransactionSuccessful()
        database.endTransaction()
        database.close()
    }

    fun removeTempSensorLocation(location: String) {
        val domusViewDatabase = DomusViewDatabase(context)
        val database = domusViewDatabase.writableDatabase
        val values = arrayOf(location)
        database.beginTransaction()
        database.delete(DomusViewDatabase.TEMP_SENSOR_LOCATION_TABLE, DomusViewDatabase.LOCATION + "=?", values)
        database.setTransactionSuccessful()
        database.endTransaction()
        database.close()
    }

    fun createTempSensorLocation(element: ZElementAdapter.Element, location: String) {
        val network = element.shortAddress
        val zDevices = domusEngine.zDevices
        val device = zDevices.get(network)
        createTempSensorLocation(device.extendedAddr, element.endpointId, location)
    }

    fun isLocationUsedYet(location: String?): Boolean {
        val domusViewDatabase = DomusViewDatabase(context)
        val database = domusViewDatabase.getReadableDatabase()
        var query: Cursor? = null
        try {
            query = database.query(DomusViewDatabase.TEMP_SENSOR_LOCATION_TABLE,
                    arrayOf<String>(DomusViewDatabase.NETWORK_FIELD, DomusViewDatabase.ENDPOINT),
                    DomusViewDatabase.LOCATION + "= ?",
                    arrayOf(location), null, null, null)
            return query!!.count > 0
        } finally {
            if (query != null) {
                query.close()
            }
        }
    }

    fun isUsed(networkId: Int, endpointId: Int): Boolean {
        val device = domusEngine.zDevices.get(networkId)
        val sqlQuery = StringBuilder()
        sqlQuery.
                append("SELECT ").
                append(DomusViewDatabase.LOCATION).
                append(" from ").
                append(DomusViewDatabase.TEMP_SENSOR_LOCATION_TABLE).
                append(" WHERE ").
                append(DomusViewDatabase.NETWORK_FIELD).
                append("= '").
                append(device.extendedAddr).
                append("' AND ").
                append(DomusViewDatabase.ENDPOINT).
                append(" = ").
                append(endpointId).
                append(";")
        val domusViewDatabase = DomusViewDatabase(context)
        var database: SQLiteDatabase? = null
        var query: Cursor? = null
        try {
            database = domusViewDatabase.readableDatabase
            query = database.rawQuery(sqlQuery.toString(), null)
            if (query.count <= 0) {
                return false
            }
            return true
        } finally {
            query?.close()
            database?.close()
        }
    }

    fun getRoom(networkId: Int, endpointId: Int): String {
        val device = domusEngine.zDevices.get(networkId)
        val sqlQuery = StringBuilder()
        sqlQuery.
                append("SELECT ").
                append(DomusViewDatabase.LOCATION).
                append(" from ").
                append(DomusViewDatabase.TEMP_SENSOR_LOCATION_TABLE).
                append(" WHERE ").
                append(DomusViewDatabase.NETWORK_FIELD).
                append("= '").
                append(device.extendedAddr).
                append("' AND ").
                append(DomusViewDatabase.ENDPOINT).
                append(" = ").
                append(endpointId).
                append(";")
        val domusViewDatabase = DomusViewDatabase(context)
        var database: SQLiteDatabase? = null
        var query: Cursor? = null
        try {
            database = domusViewDatabase.readableDatabase
            query = database.rawQuery(sqlQuery.toString(), null)
            if (query.count <= 0) {
                return ""
            }
            query.moveToFirst()
            return query.getString(0)
        } finally {
            query?.close()
            database?.close()
        }
    }

    fun getElement(roomName: String): ZElementAdapter.Element? {
        val domusViewDatabase = DomusViewDatabase(context)
        val database = domusViewDatabase.readableDatabase
        var query: Cursor? = null
        try {
            query = database.query(DomusViewDatabase.TEMP_SENSOR_LOCATION_TABLE,
                    arrayOf(DomusViewDatabase.NETWORK_FIELD, DomusViewDatabase.ENDPOINT),
                    DomusViewDatabase.LOCATION + "= ?",
                    arrayOf(roomName), null, null, null)
            if (query!!.count <= 0) {
                return null
            }
            query.moveToFirst()

            val extAddress = query.getString(0)

            val device = zDevices.get(extAddress)
            if (device !== nullZDevice)
                return ZElementAdapter.Element(device.shortAddress, query.getInt(1), false, null)
            else
                return null
        } finally {
            if (query != null) {
                query.close()
            }
        }
    }

}
