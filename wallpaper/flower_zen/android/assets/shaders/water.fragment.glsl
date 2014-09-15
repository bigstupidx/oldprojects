#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D u_texture;
uniform sampler2D u_normalTexture;
uniform vec2 u_resolution; // view port size

varying vec2 vTextureCoord0;
varying vec2 vTextureCoord1;
varying vec4 vRefracColor;
varying vec2 v_texCoord;

void main() {
	const float WAVE_DISTORTION = 0.04;
	
	vec3 bump = vec3(0,0,0);
	bump += texture2D(u_normalTexture, vTextureCoord0).rgb;
	bump += texture2D(u_normalTexture, vTextureCoord1).rgb;
	bump -= 0.5;
         
	// use screen coord 
	vec2 tmpUV = gl_FragCoord.xy / u_resolution ;
	vec2 uv = vec2(1.0 - tmpUV.x, tmpUV.y);   
	 
   vec2 vTmp = bump.xz;
 vTmp.x *= 0.2; 
    uv.xy -= (vTmp * WAVE_DISTORTION);

     vec4 reflectionTextureColor = texture2D (u_texture, uv);
	 
	gl_FragColor = reflectionTextureColor ;
}
