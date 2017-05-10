package it.achdjian.paolo.domusviewer.temperature;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.support.annotation.NonNull;

import org.rajawali3d.materials.Material;
import org.rajawali3d.materials.textures.ATexture;
import org.rajawali3d.materials.textures.Texture;
import org.rajawali3d.math.vector.Vector3;
import org.rajawali3d.primitives.Plane;

import java.util.Locale;

/**
 * Created by Paolo Achdjian on 17/04/17.
 */

public class TemperatureLabel extends Plane {
    private float previousTemp = Float.NaN;
    public static float WIDTH =2f;
    public static float HEIGHT =0.5f;

    private static float getMaxWidth(RoomObject room){
        float minWidth = (float) (room.getMax().x-room.getMin().x);
        return minWidth < WIDTH ? minWidth : WIDTH;
    }

    private static float getMaxHeight(RoomObject room){
        float minHeight = (float) (room.getMax().y-room.getMin().y);
        return minHeight < HEIGHT ? minHeight : HEIGHT;
    }

    public TemperatureLabel(@NonNull RoomObject room) {
        super(getMaxWidth(room), getMaxHeight(room), 3, 3);
        String name = "TempSensor"+ room.name;
        setName(name);
        setText("N.D.", Color.GREEN);
        Vector3 pos = new Vector3(room.mean.x, room.mean.y, 0);
        setPosition(pos);
        setDoubleSided(true);
    }

    public void setTemperature(float temp, int background) {
        if (temp != previousTemp) {
            previousTemp = temp;
            String strTemp = String.format(Locale.US, "%.2f", temp);
            setText(strTemp, background);
        }
    }

    private void setText(@NonNull String text, int background) {
        Material temperatureMaterial = new Material(true);
        temperatureMaterial.setColor(background);
        Bitmap bitmap = textAsBitmap(text, Color.WHITE);
        try {
            int maxTextureName = 18;
            String name = getName().substring(0, getName().length() > maxTextureName ? maxTextureName : getName().length() );
            temperatureMaterial.addTexture(new Texture(name, bitmap));
            setMaterial(temperatureMaterial);
        } catch (ATexture.TextureException e) {
            e.printStackTrace();
        }
    }

    private Bitmap textAsBitmap(@NonNull String text, int textColor) {
        Paint paint = new Paint();
        paint.setTextSize(30);
        paint.setStrokeWidth(10);
        paint.setColor(textColor);
        float baseline = (int) (-paint.ascent() + 0.5f);


        Bitmap image = Bitmap.createBitmap(128, 32, Bitmap.Config.ARGB_8888);
        Canvas canvas = new Canvas(image);
        int widthText = (int) paint.measureText(text);
        canvas.drawText(text, (128 - widthText) / 2, baseline, paint);
        return image;
    }


}
