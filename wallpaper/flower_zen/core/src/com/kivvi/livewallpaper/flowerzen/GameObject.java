package com.kivvi.livewallpaper.flowerzen;

import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g3d.Model;
import com.badlogic.gdx.graphics.g3d.ModelInstance;
import com.badlogic.gdx.graphics.g3d.Renderable;
import com.badlogic.gdx.graphics.g3d.attributes.TextureAttribute;
import com.badlogic.gdx.math.Vector3;

public class GameObject extends ModelInstance {
	public Vector3 position;
	private Renderable renderable;
	
	public GameObject(Model model, String node){
		super(model, node);
		renderable = new Renderable();
		// init renderable

		
	}
	
	public void update(float delta) {
		
	}
	public Renderable getMyRenderable() {
		return this.getRenderable(renderable);
	}

	 
	public void setDiffuseTexture(Texture texture) {
	this.materials.get(0).set(TextureAttribute.createDiffuse(texture));	
	}
}
