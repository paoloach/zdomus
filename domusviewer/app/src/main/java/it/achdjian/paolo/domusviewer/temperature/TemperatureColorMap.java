package it.achdjian.paolo.domusviewer.temperature;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by Paolo Achdjian on 07/09/16.
 */
public class TemperatureColorMap {
    private static Map<Integer, Integer> MAP_TEMP_COLOR = new HashMap<>();

    static {
        MAP_TEMP_COLOR.put(13, 0xFF0000E0);
        MAP_TEMP_COLOR.put(14, 0xFF0000C0);
        MAP_TEMP_COLOR.put(15, 0xFF0000A0);
        MAP_TEMP_COLOR.put(16, 0xFF000080);
        MAP_TEMP_COLOR.put(17, 0xFF000060);
        MAP_TEMP_COLOR.put(18, 0xFF000040);
        MAP_TEMP_COLOR.put(19, 0xFF008020);
        MAP_TEMP_COLOR.put(20, 0xFF00FA00);
        MAP_TEMP_COLOR.put(21, 0xFF19E100);
        MAP_TEMP_COLOR.put(22, 0xFF32C800);
        MAP_TEMP_COLOR.put(23, 0xFF4BAF00);
        MAP_TEMP_COLOR.put(24, 0xFF649600);
        MAP_TEMP_COLOR.put(25, 0xFF7D7D00);
        MAP_TEMP_COLOR.put(26, 0xFF966400);
        MAP_TEMP_COLOR.put(27, 0xFFAF4B00);
        MAP_TEMP_COLOR.put(28, 0xFFC83200);
        MAP_TEMP_COLOR.put(29, 0xFFE11900);
        MAP_TEMP_COLOR.put(30, 0xFFFA0000);
    }

    public static int getColor(int temperature){
        int temp = temperature / 100;
        int color;
        if (temp < 13) {
            color = 0xFF0000FF;
        } else if (temp > 30) {
            color = 0xFFFF0000;
        } else {
            color = MAP_TEMP_COLOR.get(temp);
        }
        return color;
    }
}
