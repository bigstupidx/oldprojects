attribute vec4 a_position;
attribute vec2 a_texCoord0;

uniform mat4 u_worldTrans;
uniform mat4 u_projTrans;
uniform mat4 u_viewTrans;

uniform float u_time;
uniform vec4 refracColor;
uniform vec3 u_cameraPosition;

varying vec2 vTextureCoord0;
varying vec2 vTextureCoord1;
varying vec4 vRefracColor;
varying vec2 v_texCoord;



void main() {

  const vec2 BUMP_SCALE0 = vec2(22.0, 20.0);
  const vec2 BUMP_SCALE1 = vec2(15.75, 15.75);
  const vec2 BUMP_VELOCITY0 = vec2(0.16, 0.14) * -0.15;
  const vec2 BUMP_VELOCITY1 = vec2(0.25, 0.3) * -0.2;

  vTextureCoord0 = a_texCoord0 * BUMP_SCALE0;
  vTextureCoord0 += u_time * BUMP_VELOCITY0;
  vTextureCoord1 = a_texCoord0 * BUMP_SCALE0;
  vTextureCoord1 += u_time * BUMP_VELOCITY0;

	vRefracColor = refracColor;
	gl_Position = u_projTrans * u_worldTrans *  a_position;

	
}