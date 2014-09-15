
package com.badlogic.gdx;

public class Configs {
	private static boolean assetEncrypt = false;

	public static void setAssetEncrypt (boolean encrypt) {
		Configs.assetEncrypt = encrypt;
	}

	public static boolean getAssetEncrypt () {
		return Configs.assetEncrypt;
	}
}
