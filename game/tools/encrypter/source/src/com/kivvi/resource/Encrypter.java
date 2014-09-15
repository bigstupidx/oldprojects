package com.kivvi.resource;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.charset.Charset;

public class Encrypter {
	public static String version = "0.1.0";

	public static void log(String info) {
		System.out.println(info);
	}

	public static String getFileExt(String path) {
		return path.substring(path.lastIndexOf(".") + 1);
	}

	public static void encode(String path, String type, boolean encrypt) {
		File f = new File(path);

		// alloc byte buffer.
		byte[] buf = new byte[(int) f.length()];

		// read in all bytes.
		FileInputStream is = null;
		try {
			is = new FileInputStream(f);
			is.read(buf);
			is.close();
		} catch (Exception e) {
			e.printStackTrace();
		}

		// get the status of file.
		boolean encrypted = true;
		String extName = getFileExt(path);
		String tag;
		// jpg
		if (extName.equalsIgnoreCase("jpg") || extName.equalsIgnoreCase("jepg")) {
			if (buf[0] == (byte) 0xFF && buf[1] == (byte) 0xD8
					&& buf[2] == (byte) 0xFF && buf[3] == (byte) 0xE0) {
				encrypted = false;
			}
		} else if (extName.equalsIgnoreCase("png")) {
			if (buf[0] == (byte) 0x89 && buf[1] == 'P' && buf[2] == 'N'
					&& buf[3] == 'G') {
				encrypted = false;
			}
		} else if (extName.equalsIgnoreCase("bmp")) {
			if (buf[0] == 'B' && buf[1] == 'M') {
				encrypted = false;
			}
		} else if (extName.equalsIgnoreCase("gif")) {
			tag = new String(buf, 0, 3, Charset.forName("UTF-8"));
			if (tag.equalsIgnoreCase("gif")) {
				encrypted = false;
			}
		} else if (extName.equalsIgnoreCase("tga")) {
			tag = new String(buf, buf.length - 18, 16, Charset.forName("UTF-8"));
			if (tag.equalsIgnoreCase("TRUEVISION-XFILE")) {
				encrypted = false;
			}
		} else if (extName.equalsIgnoreCase("g3dj")) {
			if (buf[0] == (byte) 0x7B && buf[1] == (byte) 0x0D
					&& buf[2] == (byte) 0x0A && buf[3] == (byte) 0x09) {
				encrypted = false;
			}
		} else if (extName.equalsIgnoreCase("vs")
				|| extName.equalsIgnoreCase("fs")
				|| extName.equalsIgnoreCase("glsl")) {
			encrypted = false;
			for (int i = 0; i < buf.length; i++)
				if (buf[i] < 0) {
					encrypted = true;
					break;
				}
		}

		// ignore if encrypted.
		if (encrypted == encrypt) {
			return;
		}

		if (encrypt) {
			log("encrypt " + path);
		} else {
			log("decrypt " + path);
		}

		// encode.
		String magic = "kivvi studio: " + type;
		if (!type.equalsIgnoreCase("shader")) {
			// from head.
			int count = buf.length > 100 ? 100 : buf.length;
			for (int i = 0; i < count; i++) {
				buf[i] ^= magic.hashCode();
			}
			// from tail.
			if (buf.length < 100) {
				count = 0;
			} else if (buf.length < 200) {
				count = buf.length - 100;
			} else {
				count = 100;
			}
			for (int i = 0; i < count; i++) {
				buf[buf.length - 1 - i] ^= magic.hashCode();
			}
		} else {
			for (int i = 0; i < buf.length; i++) {
				buf[i] ^= magic.hashCode();
			}
		}
		// write out all bytes.
		FileOutputStream os = null;
		try {
			os = new FileOutputStream(f);
			os.write(buf);
			os.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void go(String path, boolean encrypt) {
		log("go: " + path);
		File f = new File(path);
		File[] array = f.listFiles();

		if (array != null) {
			for (int i = 0; i < array.length; i++) {
				if (array[i].isFile()) {
					String name = array[i].getPath();
					String extName = getFileExt(name);
					// log("extName = " + extName);
					if (extName.equalsIgnoreCase("jpg")
							|| extName.equalsIgnoreCase("jepg")
							|| extName.equalsIgnoreCase("png")
							|| extName.equalsIgnoreCase("bmp")
							|| extName.equalsIgnoreCase("gif")
							|| extName.equalsIgnoreCase("tga")) {
						encode(name, "pixmap", encrypt);
					}
					// //////////////////////////////////
					// TODO: handle g3d module file.
					// //////////////////////////////////
					else if (extName.equalsIgnoreCase("g3dj")) {
						// encode(name, "g3dj", encrypt);
					} else if (extName.equalsIgnoreCase("g3db")) {
						// encode(name, "g3db", encrypt);
					} else if (extName.equalsIgnoreCase("vs")
							|| extName.equalsIgnoreCase("fs")
							|| extName.equalsIgnoreCase("glsl")) {
						encode(name, "shader", encrypt);
					}

				} else if (array[i].isDirectory()) {
					go(array[i].getPath(), encrypt);
				}
			}
		}
	}
}
