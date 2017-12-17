/**
 * Copyright 2013 Dennis Ippel
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */
package it.achdjian.paolo.opengl.bounds;


import it.achdjian.paolo.opengl.Geometry3D;
import it.achdjian.paolo.opengl.math.Matrix4;
import it.achdjian.paolo.opengl.math.vector.Vector3;

public interface IBoundingVolume {

	public static final int DEFAULT_COLOR = 0xFFFFFF00;

	public void calculateBounds(Geometry3D geometry);
	public void transform(Matrix4 matrix);
	public boolean intersectsWith(IBoundingVolume boundingVolume);
	public Vector3 getPosition();

	public void setBoundingColor(int color);
	public int getBoundingColor();
}

