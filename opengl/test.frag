uniform sampler2D sampler[3];
uniform sampler2D sampler0 ;
uniform sampler2D sampler1 ;
uniform vec2 tc_offset[9];
uniform vec2 grid[36864];
uniform float patch_r ;
uniform float patch_c ;
uniform int width ;
uniform int height ;
in vec4 vTex;
in vec4 color;

void main(void)
{
	vec4 texel ;
	vec4 sample[9] ;
//for (int i = 0; i < 9; i++)
//  {
//      sample[i] = texture2D(sampler[0], 
//                            gl_TexCoord[0].st + tc_offset[i]);
//  }
	
    texel = texture2D(sampler[0],gl_TexCoord[0].st) * 0.5 +  
          texture2D(sampler[1],gl_TexCoord[0].st) * 0.5 + 
		  texture2D(sampler[2],gl_TexCoord[0].st) * 0.5 ;  
	gl_FragColor = texel ;
//int x = gl_TexCoord[0].s * width ;
//int y =  gl_TexCoord[0].t * height ;
//	gl_FragColor = vec4(0.3,0.4,0.5,1.0);
	//gl_FragColor = (sample[0] + (3.0*sample[1]) + sample[2] + 
    //                (3.0*sample[3]) + sample[4] + (3.0*sample[5]) + 
    //                sample[6] + (3.0*sample[7]) + sample[8]) / 13.0; 
                    
	
}
