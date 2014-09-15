package com.kivvi.galaxy3d;

import com.badlogic.gdx.graphics.g3d.Model;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.utils.Array;

public class ParticleEmitter {
	private Model model;
	private Array<Meteorite> meteoriteArray = new Array<Meteorite>();
	private ParticleDescription d;
	
	public ParticleEmitter(Model model, ParticleDescription desciption) {
		d = desciption;
		for (int i = 0; i < d.maxParticleCount; i++) {
			createMeteorite(model);
		}
	}
	
	public ParticleEmitter(Model model) {
		d = new ParticleDescription();
		for (int i = 0; i < d.maxParticleCount; i++) {
			createMeteorite(model);
		}
	}
	
	public Array<Meteorite> getMeteoriteArray() {
		return meteoriteArray;
	}
	
	public void update(float delta) {
		Vector3 position = new Vector3();
		for (int i = 0; i < meteoriteArray.size; i++) {
			meteoriteArray.get(i).update(delta);
			meteoriteArray.get(i).instance.transform.getTranslation(position);
			if (position.z > 0 || position.x < -500 || position.x > 500) {
				meteoriteArray.removeIndex(i);
				createMeteorite(model);
			}
		}
	}
	
	private void createMeteorite(Model model) {
		this.model = model;
		float birthX = d.birthLow.x + (float)Math.random() * (d.birthHigh.x - d.birthLow.x);
		float birthY = d.birthLow.y + (float)Math.random() * (d.birthHigh.y - d.birthLow.y);
		float birthZ = d.birthLow.z + (float)Math.random() * (d.birthHigh.z - d.birthLow.z);
		
		float destX = d.destinationLow.x + (float)Math.random() * (d.destinationHigh.x - d.destinationLow.x);
		float destY = d.destinationLow.y + (float)Math.random() * (d.destinationHigh.y - d.destinationLow.y);
		float destZ = d.destinationLow.z + (float)Math.random() * (d.destinationHigh.z - d.destinationLow.z);
		
		float speed = d.speedLow + (float)Math.random() * (d.speedHigh - d.speedLow);
		float rSpeed = d.rotateSpeedLow + (float)Math.random() * (d.rotateSpeedHigh - d.rotateSpeedLow);
		
		float rotateX = (float)Math.random() * 2 - 1;
		float rotateY = (float)Math.random() * 2 - 1;
		float rotateZ = (float)Math.random() * 2 - 1;
		
		float scaleX = d.scaleLow + (float)Math.random() * (d.scaleHigh - d.scaleLow);
		float scaleY = d.scaleLow + (float)Math.random() * (d.scaleHigh - d.scaleLow);
		float scaleZ = d.scaleLow + (float)Math.random() * (d.scaleHigh - d.scaleLow);
		
		Meteorite m = new Meteorite(model, birthX, birthY, birthZ, destX, destY, destZ, speed, rotateX, rotateY, rotateZ, rSpeed, scaleX, scaleY, scaleZ);
		meteoriteArray.add(m);
	}
}
