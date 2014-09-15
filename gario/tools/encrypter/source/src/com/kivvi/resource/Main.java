package com.kivvi.resource;

public class Main {
	public static void main(String[] args) {
		// System.out.println("args.length = " + args.length);
		// for (int i = 0; i < args.length; i++) {
		// System.out.println("args[" + i + "]: " + args[i]);
		// }
		boolean error = false;

		if (args.length != 2) {
			error = true;
		} else {
			String path = args[1];
			boolean encrypt = true;

			if (args[0].equalsIgnoreCase("d")
					|| args[0].equalsIgnoreCase("decrypt")) {
				encrypt = false;
			} else if (args[0].equalsIgnoreCase("e")
					|| args[0].equalsIgnoreCase("encrypt")) {
				encrypt = true;
			} else {
				error = true;
			}

			if (!error) {
				Encrypter.go(path, encrypt);
			}
		}

		if (error) {
			System.out.println("Encrypter v" + Encrypter.version
					+ " - a tool for assets guard");
			System.out
					.println("The file with following extensions would be handled:");
			System.out.println("NOW:");
			System.out.println("\tpixmap: jpg, jpeg, png, bmp, gif, tga");
			System.out.println("\tshader: vs, fs, glsl");
			System.out.println("TODO:\n\tg3d module: g3dj, g3db\n");

			System.out.println("Usage: java -jar encrypter.jar COMMANDS <dir>");
			System.out.println("COMMANDS are:");
			System.out.println("\te[ncrypt]");
			System.out.println("\td[ecrypt]");
		}
	}
}
