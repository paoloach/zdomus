package it.achdjian.paolo.temperaturemonitor.domusEngine.rest

import android.content.SharedPreferences
import android.util.Log
import it.achdjian.paolo.temperaturemonitor.Constants
import it.achdjian.paolo.temperaturemonitor.domusEngine.ConnectionStatus
import okhttp3.OkHttpClient
import okhttp3.Request
import java.util.concurrent.TimeUnit

/**
 * Created by Paolo Achdjian on 15/04/16.
 */
class DomusEngineRest(val sharedPreferences: SharedPreferences, val connected: ConnectionStatus) {
    protected var client: OkHttpClient = OkHttpClient.Builder().connectTimeout(10, TimeUnit.SECONDS).writeTimeout(10, TimeUnit.SECONDS).readTimeout(10, TimeUnit.SECONDS).build()
    private val TAG = DomusEngineRest::class.java.name
//    protected var clientLongTimeout: OkHttpClient=OkHttpClient.Builder().connectTimeout(10, TimeUnit.SECONDS).writeTimeout(10, TimeUnit.SECONDS).readTimeout(5, TimeUnit.MINUTES).build()


    val address: String = sharedPreferences.getString(Constants.DOMUS_ENGINE_ADDRESS, "192.168.1.121")

    operator fun get(path: String): String {
        val url = "http://" + address + path

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
//    @JvmOverloads fun post(path: String, body: String = "") {
//        val url = "http://" + address + path
//        val requestBody = RequestBody.create(JSON, body)
//        val request = Request.Builder().url(url).post(requestBody).build()
//
//        try {
//            val response = client.newCall(request).execute()
//
//            if (response.code() === 200 || response.code() === 204) {
//                return
//            }
//        } catch (e: Exception) {
//            Log.e("DomusEngineRest", "Post", e)
//        }
//
//        Log.e(TAG, "ERROR")
//        connected.connected = false
////        if (!WhoAreYou.isRunning) {
////            val handler = Handler()
////            handler.postDelayed(WhoAreYou(this.sharedPreferences, this.connected), 1000)
////        }
//    }

    companion object {

//        val JSON: MediaType = okhttp3.MediaType.parse("application/json; charset=utf-8")
    }
}
