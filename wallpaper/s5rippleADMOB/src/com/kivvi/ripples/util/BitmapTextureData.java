package com.kivvi.ripples.util;

import android.graphics.Bitmap;
import android.opengl.GLUtils;


import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.TextureData;
import com.badlogic.gdx.graphics.Pixmap.Format;
import com.badlogic.gdx.graphics.TextureData.TextureDataType;


public class BitmapTextureData implements TextureData{
	private Bitmap bmp;
	public boolean disposed = false;
	public boolean change = false;
	private int width = 0;
	private int height = 0;
	
	public BitmapTextureData(Bitmap bitmap){
		//if(ConfigBase.releaseGL)
		//	this.bmp = bitmap.copy(bitmap.getConfig(), true);
		//else 
		this.bmp = bitmap;
		width = bmp.getWidth();
		height = bmp.getHeight();
	}
	
	public void setBitmap(Bitmap bitmap){
		//if(ConfigBase.releaseGL)
		//	this.bmp = bitmap.copy(bitmap.getConfig(), true);
		//else 
			this.bmp = bitmap;
		width = bmp.getWidth();
		height = bmp.getHeight();
		disposed = false;
	}
	
	public void changeBitmap(Bitmap bitmap){
		//if(ConfigBase.releaseGL)
		//	this.bmp = bitmap.copy(bitmap.getConfig(), true);
		//else 
		this.bmp = bitmap;
		width = bmp.getWidth();
		height = bmp.getHeight();
		change = true;
	}
	
	@Override
	public int getWidth() {
		//if(bmp == null || bmp.isRecycled())return 0;
		return width;
	}

	@Override
	public int getHeight() {
		//if(bmp == null || bmp.isRecycled())return 0;
		return height;
	}

	@Override
	public TextureDataType getType() {
		return TextureDataType.Compressed;
	}

	@Override
	public boolean isPrepared() {
		return true;
	}

	@Override
	public void prepare() {
	}

	@Override
	public Pixmap consumePixmap() {
		return null;
	}

	@Override
	public boolean disposePixmap() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void consumeCompressedData(int target) {
		// TODO Auto-generated method stub
		if(bmp!=null&&!bmp.isRecycled()){
			if(!change)GLUtils.texImage2D(GL20.GL_TEXTURE_2D, 0, bmp, 0);
			else GLUtils.texSubImage2D(GL20.GL_TEXTURE_2D, 0, 0, 0, bmp);
			bmp = null;
		}	
		else{
			disposed = true;
		}
	}

	@Override
	public Format getFormat() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean useMipMaps() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean isManaged() {
		// TODO Auto-generated method stub
		return true;
	}
}
