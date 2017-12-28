package it.achdjian.paolo.cs5463.Register

import android.widget.EditText
import javax.inject.Inject
import javax.inject.Singleton

/**
 * Created by Paolo Achdjian on 12/28/17.
 */
@Singleton
class Register2View @Inject constructor() {
    val map = HashMap<RegistersWithValues,EditText>()

    operator fun get(register: RegistersWithValues):EditText?{
        return map[register];
    }

    operator fun set(register: RegistersWithValues, editText: EditText){
        map[register] = editText
    }
}