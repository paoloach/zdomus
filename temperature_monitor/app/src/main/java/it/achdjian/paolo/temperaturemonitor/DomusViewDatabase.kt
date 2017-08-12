package it.achdjian.paolo.temperaturemonitor

import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import android.util.Log

/**
 * Created by Paolo Achdjian on 31/08/16.
 */
class DomusViewDatabase(context: Context) : SQLiteOpenHelper(context, DATABASE_NAME, null, VERSION) {

    override fun onCreate(db: SQLiteDatabase) {
        db.execSQL(TEMP_SENSOR_LOCATION)
    }

    override fun onUpgrade(db: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
        Log.w(javaClass.name, "Request to upgrade $DATABASE_NAME from $oldVersion to version $newVersion")
    }

    companion object {
        private val VERSION = 1
        private val DATABASE_NAME = "DomusViewDatabase.db"
        val TEMP_SENSOR_LOCATION_TABLE = "temp_sensor_location"
        val NETWORK_FIELD = "network_address"
        val ENDPOINT = "endpoint"
        val LOCATION = "location"
        private val TEMP_SENSOR_LOCATION =
                "CREATE TABLE " + TEMP_SENSOR_LOCATION_TABLE + " ( " +
                        NETWORK_FIELD + " TEXT, " +
                        ENDPOINT + " INTEGER, " +
                        LOCATION + " TEXT);"
    }
}
