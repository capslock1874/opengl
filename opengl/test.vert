out vec4 vTex;
out vec4 color ;
void main(void)
{   
	vTex = gl_Vertex ;
	gl_TexCoord[0]=gl_MultiTexCoord0;
	gl_Position = gl_Vertex ;
}
