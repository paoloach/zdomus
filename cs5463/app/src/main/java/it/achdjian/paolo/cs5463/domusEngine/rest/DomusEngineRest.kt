package it.achdjian.paolo.cs5463.domusEngine.rest

import android.util.Log
import it.achdjian.paolo.cs5463.domusEngine.ConnectionStatus
import okhttp3.OkHttpClient
import okhttp3.Request
import okhttp3.RequestBody
import java.util.concurrent.TimeUnit

/**
 * Created by Paolo Achdjian on 15/04/16.
 */
object DomusEngineRest {
    var client: OkHttpClient = OkHttpClient.Builder().connectTimeout(10, TimeUnit.SECONDS).writeTimeout(10, TimeUnit.SECONDS).readTimeout(10, TimeUnit.SECONDS).build()

    private val TAG = "ZIGBEE COM"
    private val JSON = okhttp3.MediaType.parse("application/json; charset=utf-8")
    var address = "192.168.1.121:8080"

    operator fun get(path: String): String {
  //      val address: String = sharedPreferences.getString(Constants.DOMUS_ENGINE_ADDRESS, "192.168.1.121:8080")
        val url = "http://" + address + path
        Log.i(TAG, url)

        val request = Request.Builder().url(url).get().header("Accept", "application/json").header("Content-Type", "application/json").build()

        try {
            val response = client.newCall(request).execute()
            if (response.code() == 200) {
                ConnectionStatus.connected = true
                return response.body().string()
            }
            if (response.code() == 204) {
                ConnectionStatus.connected = true
                return ""
            }
            ConnectionStatus.connected = true
            Log.e(TAG, "Error code: " + response.code() + ": msg: " + response.message())
            return ""
        } catch (ignored: Exception) {
            Log.e(TAG, "error", ignored)
        }

        Log.e(TAG, "CONNECTION ERROR")
        ConnectionStatus.connected = false
        return ""
    }


    fun post(path: String, body: String = "") {
 //       val address: String = sharedPreferences.getString(Constants.DOMUS_ENGINE_ADDRESS, "192.168.1.121")
        val url = "http://" + address + path
        val requestBody = RequestBody.create(JSON, body)
        val request = Request.Builder().url(url).post(requestBody).build()

        try {
            val response = client.newCall(request).execute()

            if (response.code() == 200 || response.code() == 204) {
                return
            }
        } catch (e: Exception) {
            Log.e("DomusEngineRest", "Post", e)
        }

        Log.e(TAG, "ERROR")
        ConnectionStatus.connected = false
    }

}
