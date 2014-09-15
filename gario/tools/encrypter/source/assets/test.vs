String vertexShader = "attribute vec4 "
				+ ShaderProgram.POSITION_ATTRIBUTE
				+ ";\n" //
				+ "attribute vec4 "
				+ ShaderProgram.NORMAL_ATTRIBUTE
				+ ";\n" //
				+ "uniform mat4 uWorldmatrix;\n"
				+ "uniform mat4 uNormalmatrix;\n"
				+ "uniform mat4 uProjTrans;\n" //
				+ "\n" //
				+ "varying vec4 vNormal;\n"
				+ "varying vec4 vPosition;\n"
				+ "void main()\n" //
				+ "{\n" //
				+ "   gl_Position =  uProjTrans * uWorldmatrix *"
				+ ShaderProgram.POSITION_ATTRIBUTE
				+ ";\n" //
				+ "	  vNormal = uNormalmatrix * a_normal;\n"
				+ "   vPosition = uWorldmatrix * a_position;\n"
				+ "}\n";