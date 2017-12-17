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
package it.achdjian.paolo.opengl.materials.shaders;

import java.util.Hashtable;
import java.util.List;

import it.achdjian.paolo.opengl.materials.Material;


public interface IShaderFragment {
	/**
	 * Where to insert the plugin. The {@link Material} class needs to know at
	 * what location the shader fragments should be inserted when assembling the
	 * shaders. The locations are defined in the {@link Material.PluginInsertLocation}
	 * enum.
	 * @return
	 */
	Material.PluginInsertLocation getInsertLocation();
	String getShaderId();

	List<String> getPreprocessorDirectives();
	Hashtable<String, AShaderBase.ShaderVar> getUniforms();
	Hashtable<String, AShaderBase.ShaderVar> getAttributes();
	Hashtable<String, AShaderBase.ShaderVar> getVaryings();
	Hashtable<String, AShaderBase.ShaderVar> getGlobals();
	Hashtable<String, AShaderBase.ShaderVar> getConsts();
	void setStringBuilder(StringBuilder stringBuilder);
	void main();
	void applyParams();
	void setLocations(int programHandle);
	void bindTextures(int nextIndex);
	void unbindTextures();
}
