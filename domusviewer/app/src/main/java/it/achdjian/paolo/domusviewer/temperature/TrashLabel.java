package it.achdjian.paolo.domusviewer.temperature;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.support.v7.widget.AppCompatDrawableManager;

import org.rajawali3d.materials.Material;
import org.rajawali3d.materials.textures.ATexture;
import org.rajawali3d.materials.textures.Texture;
import org.rajawali3d.math.vector.Vector3;
import org.rajawali3d.primitives.Plane;

import it.achdjian.paolo.domusviewer.R;

/**
 * Created by Paolo Achdjian on 18/04/17.
 */

public class TrashLabel extends Plane  {
    private static Texture TEXTURE;
    public static float WIDTH =0.4f;
    public static float HEIGHT =0.4f;

    private static float getMaxWidth(RoomObject room){
        float minWidth = (float) (room.getMax().x-room.getMin().x);
        return minWidth < WIDTH ? minWidth : WIDTH;
    }

    private static float getMaxHeight(RoomObject room){
        float minHeight = (float) (room.getMax().y-room.getMin().y);
        return minHeight < HEIGHT ? minHeight : HEIGHT;
    }

    public TrashLabel(Context context, RoomObject room, int background){
        super(getMaxWidth(room), getMaxHeight(room), 3, 3);

        Vector3 position = room.temperatureLabel.getPosition().clone();
        position.add((TemperatureLabel.WIDTH +TrashLabel.WIDTH)/2,0,0);
        setPosition(position);
        setName("RemoveSensorFor"+ room.name);
        try {
            if (TEXTURE == null){
                TEXTURE = new Texture("trash", createTrashBitmap(context));
            }
            Material temperatureMaterial = new Material(true);
            temperatureMaterial.setColor(background);
            temperatureMaterial.addTexture(TEXTURE);
            setMaterial(temperatureMaterial);
        } catch (ATexture.TextureException e) {
            e.printStackTrace();
        }
    }

    private Bitmap createTrashBitmap(Context context) {
        Bitmap image = Bitmap.createBitmap(32, 32, Bitmap.Config.ARGB_8888);
        image.eraseColor(Color.WHITE);
        Canvas canvas = new Canvas(image);
        Drawable drawable = AppCompatDrawableManager.get().getDrawable(context, R.drawable.trash_can);
        drawable.setBounds(0, 0, 32, 32);
        drawable.draw(canvas);
        return  image;
    }

}
