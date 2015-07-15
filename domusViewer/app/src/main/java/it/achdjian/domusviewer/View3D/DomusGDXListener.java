package it.achdjian.domusviewer.View3D;

import android.util.Log;

import com.badlogic.gdx.ApplicationListener;
import com.badlogic.gdx.Files;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.PerspectiveCamera;
import com.badlogic.gdx.graphics.g3d.Environment;
import com.badlogic.gdx.graphics.g3d.Model;
import com.badlogic.gdx.graphics.g3d.ModelBatch;
import com.badlogic.gdx.graphics.g3d.ModelInstance;
import com.badlogic.gdx.graphics.g3d.attributes.ColorAttribute;
import com.badlogic.gdx.graphics.g3d.environment.DirectionalLight;
import com.badlogic.gdx.graphics.g3d.loader.G3dModelLoader;
import com.badlogic.gdx.graphics.g3d.utils.CameraInputController;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.math.collision.BoundingBox;
import com.badlogic.gdx.utils.UBJsonReader;

/**
 * Created by Paolo Achdjian on 06/07/15.
 * Copyright Paolo Achdjian
 */
public class DomusGDXListener implements ApplicationListener {
	private static final String TAG = DomusGDXListener.class.getName();

	private PerspectiveCamera camera;
	private Model model;
	private ModelInstance modelInstance;
	private ModelBatch modelBatch;
	private Environment environment;
	private int screenWidth;
	private int screenHeight;
	private float posZ = 1.7f;
	private CameraInputController cameraController;
	private Vector3 target;
	private NotifyCreation notifyCreation;

	public DomusGDXListener(Vector3 startingTarget, NotifyCreation notifyCreation) {
		target = startingTarget;
		this.notifyCreation = notifyCreation;
	}

	public Vector3 getTarget() {
		return target;
	}

	public void setTarget(Vector3 target) {
		this.target = target;
		camera.lookAt(target);
		camera.update();
	}

	@Override
	public void create() {
		Log.d(DomusGDXListener.class.getName(), "create");

		// Get screen dimensions
		screenWidth = Gdx.graphics.getWidth();
		screenHeight = Gdx.graphics.getHeight();

		// Move the camera 5 units back along the z-axis and look at the origin
		camera = new PerspectiveCamera(70, screenWidth, screenHeight);
		camera.position.set(-1f,0f,posZ);
		camera.direction.set(Vector3.X);
		camera.up.set(Vector3.Y);

		// Near and Far (plane) represent the minimum and maximum ranges of the camera in, um, units
		camera.near = 0.1f;
		camera.far = 300.0f;
		camera.update();
		cameraController = new CameraInputController(camera);
		Gdx.input.setInputProcessor(cameraController);

		// A ModelBatch is like a SpriteBatch, just for models.  Use it to batch up geometry for OpenGL
		modelBatch = new ModelBatch();

		// Model loader needs a binary json reader to decode
		UBJsonReader jsonReader = new UBJsonReader();
		// Create a model loader passing in our json reader
		G3dModelLoader modelLoader = new G3dModelLoader(jsonReader);
		// Now load the model by name
		// Note, the model (g3db file ) and textures need to be added to the assets folder of the Android proj
		FileHandle fileHandle = Gdx.files.getFileHandle("PianoTerra2.g3db",Files.FileType.Internal);
		model = modelLoader.loadModel(fileHandle);
		BoundingBox inBounding = new BoundingBox();
		BoundingBox boundingBox = model.calculateBoundingBox(inBounding);
		Log.d(TAG, "model bounding box: " +  boundingBox.toString());

		modelInstance = new ModelInstance(model);
		modelInstance.transform.rotate(1, 0, 0, -90);
		modelInstance.calculateTransforms();

		BoundingBox boundingBoxInstance = modelInstance.calculateBoundingBox(inBounding);
		Log.d(TAG, "instance bounding box: " +  boundingBoxInstance.toString());

		// Set up environment with simple lighting
		environment = new Environment();
		environment.set(new ColorAttribute(ColorAttribute.AmbientLight, 0.4f, 0.4f, 0.4f, 1f));
		environment.add(new DirectionalLight().set(0.8f, 0.8f, 0.8f, -0.8f, 0.3f, -1f));

		renderMesh();

		notifyCreation.create();
	}

	private void renderMesh() {
		modelBatch.begin(camera);
		modelBatch.render(modelInstance, environment);
		modelBatch.end();
	}

	@Override
	public void resize(int width, int height) {
		Log.d(DomusGDXListener.class.getName(), "resize");
	}

	@Override
	public void render() {
		Gdx.gl.glViewport(0, 0, Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
		Gdx.gl.glClearColor(0.5f, 0.5f, 0.5f, 1);
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT | GL20.GL_DEPTH_BUFFER_BIT);
		camera.update();
		renderMesh();
	}

	@Override
	public void pause() {
		Log.d(DomusGDXListener.class.getName(), "pause");
	}

	@Override
	public void resume() {
		Log.d(DomusGDXListener.class.getName(), "resume");
	}

	@Override
	public void dispose() {
		Log.d(DomusGDXListener.class.getName(), "dispose");
	}

	public Vector3 getDirection() {
		return camera.direction;
	}

	public Vector3 getPosition() {
		return camera.position;
	}

	public PerspectiveCamera getCamera() {
		return camera;
	}
}
