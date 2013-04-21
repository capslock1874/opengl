#include <stdlib.h>
#include <glew.h>
#include <glut.h>
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
#include "stdio.h"
#include <string.h>
#include <cstring>
#include <iostream>
#include "textfile.h"

using namespace std ;

GLuint v,f,f2,p;
GLfloat texCoordOffsets[18];
GLuint textures[10] ;
GLuint text0 ;
GLuint text1 ;
const int imageNum = 3 ;
static const GLenum textNum[10] = { GL_TEXTURE0 , GL_TEXTURE1 , GL_TEXTURE2 ,
															GL_TEXTURE3 , GL_TEXTURE4 , GL_TEXTURE5 ,
															GL_TEXTURE6 , GL_TEXTURE7 , GL_TEXTURE8 ,
															GL_TEXTURE9
														} ;
static const int PATCH_SIZE = 3 ;
static int WIDTH = 1280 ;
static int HEIGHT = 720 ;
#define printOpenGLError() printOglError(__FILE__, __LINE__)

int printOglError(char *file, int line)
{
	//
	// Returns 1 if an OpenGL error occurred, 0 otherwise.
	//
	GLenum glErr;
	int    retCode = 0;

	glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		printf("glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
		retCode = 1;
		glErr = glGetError();
	}
	return retCode;
}


void printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
		free(infoLog);
	}
}

void printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
		free(infoLog);
	}
}


void setShaders( ) {
	char *vs = NULL,*fs = NULL,*fs2 = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);	
	f2 = glCreateShader(GL_FRAGMENT_SHADER);
	vs = textFileRead("test.vert");
	fs2 = textFileRead("test.frag");
	const char * ff2 = fs2;
	const char * vv = vs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f2, 1, &ff2,NULL);
	free(vs);
	free(fs);
	glCompileShader(f2);
	glCompileShader(v);
	printShaderInfoLog(f2);
	printShaderInfoLog(v);
	p = glCreateProgram();
	glAttachShader(p,f2);
	glAttachShader(p,v);
	glLinkProgram(p);
	printProgramInfoLog(p);
	glUseProgram(p);

}

void myInit(int start , int end)
{
	glClearColor(1.0,0.2,0.5,0.5);
	glColor3ub(255,0,0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	char fileName[20] ;
	glGenTextures(2, textures);	 
	glEnable(GL_TEXTURE_2D);
	for(int i = start ; i < end ; i++) {
		glActiveTexture(textNum[i]);
		sprintf(fileName , "%04d.jpg",i);
		cout << "filename" << fileName << endl ;
		IplImage *img = cvLoadImage(fileName);	
		glBindTexture(GL_TEXTURE_2D, textures[i-start]);

		glTexImage2D(GL_TEXTURE_2D, 0, 3,
			img->width, img->height,
			0, GL_BGR_EXT, GL_UNSIGNED_BYTE, (unsigned char *)img->imageData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
	}
	//glActiveTexture(GL_TEXTURE0);
	//IplImage *img = cvLoadImage("0001.jpg");	
	//glBindTexture(GL_TEXTURE_2D, textures[0]);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3,
	//	img->width, img->height,
	//	0, GL_BGR_EXT, GL_UNSIGNED_BYTE, (unsigned char *)img->imageData);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	//glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

	////glGenTextures(1, &text1);	
	//glActiveTexture(GL_TEXTURE1);
	//IplImage *img2 = cvLoadImage("0000.jpg");	
	//glBindTexture(GL_TEXTURE_2D, textures[1]);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3,
	//	img2->width, img2->height,
	//	0, GL_BGR_EXT, GL_UNSIGNED_BYTE, (unsigned char *)img2->imageData);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	//glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

	glShadeModel(GL_FLAT);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	/*将纹理映射到四边形上*/
	glBegin(GL_QUADS);
	/*纹理的坐标和四边形顶点的对应*/
	glTexCoord2f(0.0,0.0); glVertex3f(-1.0,1.0,0.0);
	glTexCoord2f(0.0,1.0); glVertex3f(-1.0,-1.0,0.0);
	glTexCoord2f(1.0,1.0); glVertex3f(1.0,-1.0,0.0);
	glTexCoord2f(1.0,0.0); glVertex3f(1.0,1.0,0.0);
	
	glEnd();
	glFlush();
}

void myReshape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
 GLint i, j;
    GLfloat xInc, yInc;
	xInc = 1.0f / (GLfloat)w;
	yInc = 1.0f / (GLfloat)h;
	printf("w %d h %d\n",w, h);
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			texCoordOffsets[(((i*3)+j)*2)+0] = (-1.0f * xInc) + ((GLfloat)i * xInc);
			texCoordOffsets[(((i*3)+j)*2)+1] = (-1.0f * yInc) + ((GLfloat)j * yInc);
		}
	}
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80.0,1.0-(GLfloat)w/(GLfloat)h,1.0,30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/
}

static void transTextures( ){
	char textName[20] ;
	for(int i = 0 ; i < imageNum ; i++){
		glActiveTexture( textNum[i] );
		glBindTexture( textNum[i], textures[i]/*假设是0号贴图*/  );
		sprintf(textName , "sampler[%d]",i);
		cout << "sampler" << textName << endl ;
		glUniform1i(glGetUniformLocation(p ,textName) , i);
	}
}
static void setGrid(GLfloat* grid , int grid_r , int grid_c ){
	GLfloat xInc, yInc;
	xInc = 1.0f / (GLfloat)WIDTH;
	yInc = 1.0f / (GLfloat)HEIGHT;
	for(int i = 0 ; i < grid_r ; i++)
		for(int j = 0 ; j < grid_c ; j++){
			grid[((grid_c *i) + j)*2] = ((i+1) * (PATCH_SIZE / 2)) * xInc ;
			grid[((grid_c *i) + j)*2 + 1] = ((j+1) * (PATCH_SIZE/2)) * yInc ;
		}
}

int main(int argc,char **argv)
{
	/*初始化*/
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowSize(1280,720);
	glutInitWindowPosition(200,200);

	/*创建窗口*/
	glutCreateWindow(" Texture ");

	/*绘制与显示*/
	;
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glewInit();
	setShaders();
	myInit(0 , 3);
	transTextures();
	myReshape(WIDTH,HEIGHT);

	//glActiveTexture( textNum[0] );
	//glBindTexture(textNum[0], textures[0]/*假设是0号贴图*/  );
	//glUniform1i(glGetUniformLocation(p ,"sampler[0]") , 0);

	//glActiveTexture( textNum[1] );
	//glBindTexture( textNum[1], textures[1]/*假设是1号贴图*/  );
	//glUniform1i(glGetUniformLocation(p ,"sampler[1]") , 1);

	int grid_r = ( HEIGHT - PATCH_SIZE/2 - 1) / (PATCH_SIZE / 2) ;
	int grid_c = ( WIDTH - PATCH_SIZE/2 - 1) / (PATCH_SIZE / 2) ;
	GLfloat* grid = new GLfloat[grid_r * grid_c * 2];
	GLfloat xInc, yInc;
	xInc = 1.0f / (GLfloat)WIDTH;
	yInc = 1.0f / (GLfloat)HEIGHT;
	GLfloat patch_r = PATCH_SIZE / 2 * yInc ;
	GLfloat patch_c = PATCH_SIZE / 2 * xInc ;
	setGrid(grid , grid_r , grid_c );
	GLint uniformLoc;
	uniformLoc =  glGetUniformLocation(p,"tc_offset");  
	if (uniformLoc != -1)
	{
		glUniform2fv(uniformLoc, 9, texCoordOffsets);
	}
	uniformLoc =  glGetUniformLocation(p,"grid");  
	if (uniformLoc != -1)
	{
		glUniform2fv(uniformLoc, grid_r * grid_c, texCoordOffsets);
	}
	uniformLoc =  glGetUniformLocation(p,"patch_r");  
	if (uniformLoc != -1)
	{
		glUniform1f(uniformLoc, patch_r);
	}

	uniformLoc =  glGetUniformLocation(p,"patch_c");  
	if (uniformLoc != -1)
	{
		glUniform1f(uniformLoc, patch_c);
	}
	glUniform1i(glGetUniformLocation(p,"width"), WIDTH);
	glUniform1i(glGetUniformLocation(p,"height"), HEIGHT);
	glutMainLoop();
	return 0;
}