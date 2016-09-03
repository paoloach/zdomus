package it.achdjian.paolo.domusviewer.database;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import org.androidannotations.annotations.EBean;
import org.androidannotations.annotations.RootContext;

/**
 * Created by Paolo Achdjian on 31/08/16.
 */
public class DomusViewDatabase extends SQLiteOpenHelper {
    private static int VERSION=1;
    private static String DATABASE_NAME = "DomusViewDatabase.db";
    public static final String TEMP_SENSOR_LOCATION_TABLE = "temp_sensor_location";
    public static final String NETWORK_FIELD = "network_address";
    public static final String ENDPOINT = "endpoint";
    public static final String LOCATION = "location";
    private static String TEMP_SENSOR_LOCATION =
            "CREATE TABLE " + TEMP_SENSOR_LOCATION_TABLE + " ( " +
                    NETWORK_FIELD + " TEXT, " +
                    ENDPOINT + " INTEGER, " +
                    LOCATION + " TEXT);";

     DomusViewDatabase(Context context) {
        super(context, DATABASE_NAME, null, VERSION);
    }



    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(TEMP_SENSOR_LOCATION);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        Log.w(getClass().getName(), "Request to upgrade " + DATABASE_NAME + " from " + oldVersion + " to version " + newVersion);
    }
}
