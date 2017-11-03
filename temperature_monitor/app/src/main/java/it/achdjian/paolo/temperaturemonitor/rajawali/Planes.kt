package it.achdjian.paolo.temperaturemonitor.rajawali

import android.util.Log
import javax.inject.Inject
import javax.inject.Singleton

/**
 * Created by Paolo Achdjian on 10/31/17.
 */
@Singleton
class Planes  @Inject constructor(){
    private val rooms = ArrayList<ArrayList<RoomObject>>()
    var planeSelected = 0
    val planes = ArrayList<List<String>>()
    val selected:  ArrayList<RoomObject>
            get() = rooms[planeSelected]


    init {
        Log.i("INIT", "init rooms")
        val plane0 = listOf("Taverna", "Scale_taverna", "Sottoscala", "Ingresso-Garage", "Lavanderia")
        val plane1 = listOf("Soggiorno", "bagno-terra", "Cucina", "scale_camere", "Termostato")
        planes.add(plane0)
        planes.add(plane1)

        rooms.add(ArrayList())
        rooms.add(ArrayList())
    }

    fun getPlane(index: Int) = rooms[index];
    fun getRoom(room: String): RoomObject? {
        rooms.forEach {it.forEach{ if (it.name == room) return it }}
        return null
    }


    private fun isPlan0(name: String)= planes[0].any { it.length <= name.length && it == name.substring(0, it.length) }
    private fun isPlan1(name: String)= planes[1].any { it.length <= name.length && it == name.substring(0, it.length) }
    fun add(room:RoomObject) {
        if (isPlan0(room.name))
            rooms[0].add(room)
        if (isPlan1(room.name))
            rooms[1].add(room)
    }
}