package com.cooee.wallpaper.common;

import java.io.IOException;

import android.content.Context;

import com.cooee.wallpaper.framework.ConfigMode;
import com.cooee.wallpaper.framework.Logger;
import com.threed.jpct.Loader;
import com.threed.jpct.Matrix;
import com.threed.jpct.Object3D;
import com.threed.jpct.SimpleVector;
import com.threed.jpct.Texture;
import com.threed.jpct.TextureManager;
import com.threed.jpct.World;

public class ResourceManager {
	private World mWorld;
	private Context mContext;

	public ResourceManager(Context context) {
		mContext = context;
	}

	public void setWorld(World world) {
		mWorld = world;
	}

	private String getTexname(String textureFile, int textureId) {
		// generate texname
		String texname = null;
		if (textureFile == null) {
			texname = "" + textureId;
		} else {
			texname = textureFile;
		}
		return texname;
	}

	private Texture createTexture(String file, boolean useAlpha) {
		Texture tex = null;
		try {
			tex = new Texture(mContext.getResources().getAssets().open(file),
					useAlpha);
		} catch (IOException e) {
			e.printStackTrace();
		}
		return tex;
	}

	private Texture createTexture(int textureId, boolean useAlpha) {
		Texture tex = null;
		tex = new Texture(mContext.getResources().getDrawable(textureId),
				useAlpha);
		return tex;
	}

	public Texture loadTexture(int textureId) {
		return loadTexture(null, textureId, false);
	}

	public Texture loadTexture(int textureId, boolean useAlpha) {
		return loadTexture(null, textureId, useAlpha);
	}

	public Texture loadTexture(String file) {
		return loadTexture(file, 0, false);
	}

	public Texture loadTexture(String file, boolean useAlpha) {
		return loadTexture(file, 0, useAlpha);
	}

	private Texture loadTexture(String file, int textureId, boolean useAlpha) {
		String texname = getTexname(file, textureId);

		Logger.ps("loadTexture: " + texname);
		Texture tex = null;
		if (!TextureManager.getInstance().containsTexture(texname)) {
			if (file == null) {
				tex = createTexture(textureId, useAlpha);
			} else {
				tex = createTexture(file, useAlpha);
			}

			// set compress texture to save memory
			// if (context.getResources().getDrawable(textureId).getOpacity() ==
			// PixelFormat.OPAQUE) {
			// tex.compress();
			tex.setTextureCompression(ConfigMode.getTextureCompression());
			// }
			TextureManager.getInstance().addTexture(texname, tex);
		}
		Logger.pt("loadTexture: " + texname);

		return tex;
	}

	public Object3D load3ds(String modelName, String textureFile)
			throws IOException {
		return load3ds(modelName, textureFile, 0, false);
	}

	public Object3D load3ds(String modelName, String textureFile,
			boolean useAlpha) throws IOException {
		return load3ds(modelName, textureFile, 0, useAlpha);
	}

	public Object3D load3ds(String modelName, int textureId) throws IOException {
		return load3ds(modelName, null, textureId, false);
	}

	public Object3D load3ds(String modelName, int textureId, boolean useAlpha)
			throws IOException {
		return load3ds(modelName, null, textureId, useAlpha);
	}

	private Object3D load3ds(String modelName, String textureFile,
			int textureId, boolean useAlpha) throws IOException {
		String texname = getTexname(textureFile, textureId);
		Logger.ps("load3ds: " + modelName);

		loadTexture(textureFile, textureId, useAlpha);

		Object3D obj = null;
		obj = loadModel(modelName, 1.0f);
		obj.setTexture(texname);
		obj.build();

		if (useAlpha) {
			obj.setTransparency(255);
		}

		mWorld.addObject(obj);

		Logger.pt("load3ds: " + modelName);

		return obj;
	}

	// 载入模型
	private Object3D loadModel(String filename, float scale) throws IOException {
		// 将载入的3ds文件保存到model数组中
		Object3D[] model = Loader.load3DS(mContext.getResources().getAssets()
				.open(filename), scale);
		// 取第一个3ds文件
		Object3D o3d = new Object3D(0);
		// 临时变量temp
		Object3D temp = null;
		// 遍历model数组
		for (int i = 0; i < model.length; i++) {
			// 给temp赋予model数组中的某一个
			temp = model[i];
			// 设置temp的中心为 origin (0,0,0)
			temp.setCenter(SimpleVector.ORIGIN);
			// 沿x轴旋转坐标系到正常的坐标系(jpct-ae的坐标中的y,x是反的)
			temp.rotateX((float) (-.5 * Math.PI));
			// 使用旋转矩阵指定此对象旋转网格的原始数据
			temp.rotateMesh();
			// new 一个矩阵来作为旋转矩阵
			temp.setRotationMatrix(new Matrix());
			// 合并o3d与temp
			o3d = Object3D.mergeObjects(o3d, temp);
			// 主要是为了从桌面版JPCT到android版的移徝(桌面版此处为o3d.build())
			o3d.compile();
		}
		// 返回o3d对象
		return o3d;
	}

	public Object3D loadmd2(String modelName, String textureFile)
			throws IOException {
		return loadmd2(modelName, textureFile, 0);
	}

	public Object3D loadmd2(String modelName, int textureId) throws IOException {
		return loadmd2(modelName, null, textureId);
	}

	public Object3D loadmd2(String modelName, String textureFile, int textureId)
			throws IOException {
		return loadmd2(modelName, textureFile, textureId, false);
	}

	public Object3D loadmd2(String modelName, String textureFile,
			int textureId, boolean useAlpha) throws IOException {
		String texname = getTexname(textureFile, textureId);

		loadTexture(textureFile, textureId, useAlpha);

		Object3D obj = null;
		obj = Loader.loadMD2(mContext.getResources().getAssets()
				.open(modelName), 1.0f);
		obj.setTexture(texname);
		obj.build();

		mWorld.addObject(obj);

		// default to set culling false
		obj.setCulling(false);

		return obj;
	}
}
