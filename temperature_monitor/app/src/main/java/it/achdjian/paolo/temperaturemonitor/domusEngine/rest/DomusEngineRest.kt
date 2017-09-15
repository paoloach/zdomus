package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import android.content.SharedPreferences
import android.util.Log
import it.achdjian.paolo.temperaturemonitor.Constants
import it.achdjian.paolo.temperaturemonitor.domusEngine.ConnectionStatus
import okhttp3.OkHttpClient
import okhttp3.Request
import okhttp3.RequestBody
import java.util.concurrent.TimeUnit

/**
 * Created by Paolo Achdjian on 15/04/16.
 */
class DomusEngineRest(val sharedPreferences: SharedPreferences, val connected: ConnectionStatus) {
    protected var client: OkHttpClient = OkHttpClient.Builder().connectTimeout(10, TimeUnit.SECONDS).writeTimeout(10, TimeUnit.SECONDS).readTimeout(10, TimeUnit.SECONDS).build()

    companion object {
        private val TAG = "ZIGBEE COM"
        private val JSON = okhttp3.MediaType.parse("application/json; charset=utf-8")
    }


    val address: String = sharedPreferences.getString(Constants.DOMUS_ENGINE_ADDRESS, "192.168.1.121")

    operator fun get(path: String): String {
        val url = "http://" + address + path
        Log.i(TAG, url);

        val request = Request.Builder().url(url).get().header("Accept", "application/json").header("Content-Type", "application/json").build()

        try {
            val response = client.newCall(request).execute()
            if (response.code() == 200) {
                return response.body().string()
            }
            if (response.code() == 204) {
                return ""
            }
            if (response.code() in 400..499) {
                Log.e(TAG, "Error code: " + response.code() + ": msg: " + response.message())
                return ""
            }
        } catch (ignored: Exception) {
            Log.e(TAG, "error", ignored)
        }

        Log.e(TAG, "ERROR")
        connected.connected = false
        return ""
    }



    fun post(path: String, body: String = "") {
        val url = "http://" + address + path
        val requestBody = RequestBody.create(JSON, body)
        val request = Request.Builder().url(url).post(requestBody).build()

        try {
            val response = client.newCall(request).execute()

            if (response.code() === 200 || response.code() === 204) {
                return
            }
        } catch (e: Exception) {
            Log.e("DomusEngineRest", "Post", e)
        }

        Log.e(TAG, "ERROR")
        connected.connected = false
    }

//    fun getLongRead(path: String): String? {
//        val url = "http://" + address + path
//
//        val request = Request.Builder().url(url).get().header("Accept", "application/json").header("Content-Type", "application/json").build()
//
//        try {
//            val response = clientLongTimeout.newCall(request).execute()
//            if (response.code() === 200) {
//                return response.body().string()
//            }
//            if (response.code() === 204) {
//                return ""
//            }
//        } catch (ignored: Exception) {
//            Log.e(TAG, "error", ignored)
//        }
//
//        Log.e(TAG, "ERROR")
//        return null
//    }
//
//

}
