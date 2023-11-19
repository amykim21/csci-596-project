
/*
 * Gz.h - include file for the cs580 rendering library
 */

/*
 * universal constants
 */
#define GZ_SUCCESS      0
#define GZ_FAILURE      1

/*
 * name list tokens
 */
#define GZ_NULL_TOKEN			0    /* triangle vert attributes */
#define GZ_POSITION             1
#define GZ_NORMAL               2
#define GZ_TEXTURE_INDEX        3

/* renderer-state default pixel color */
#define GZ_RGB_COLOR            99	

#define GZ_INTERPOLATE			95		/* interpolation mode */

#define GZ_DIRECTIONAL_LIGHT	79	/* directional light */
#define GZ_AMBIENT_LIGHT		78	/* ambient light type */

#define GZ_AMBIENT_COEFFICIENT		1001	/* Ka material property */
#define GZ_DIFFUSE_COEFFICIENT		1002	/* Kd material property */
#define GZ_SPECULAR_COEFFICIENT		1003	/* Ks material property */
#define GZ_DISTRIBUTION_COEFFICIENT	1004	/* specular power of material */

#define	GZ_TEXTURE_MAP	1010		/* texture function ptr */

/*
 * value-list attributes
 */

/* select interpolation mode of the shader */
#define GZ_FLAT			0	/* do flat shading with GZ_RBG_COLOR */
#define	GZ_COLOR		1	/* interpolate vertex color */
#define	GZ_NORMALS		2	/* interpolate normals */
typedef struct GzVertex
{
    float position[3];
    float color_diffuse[3];
    float color_specular[3];
    float normal[3];
    float shininess;
    GzVertex(GzCoord position_, GzCoord normal_) {
        memcpy(position, position_, sizeof(position));
        memcpy(normal, normal_, sizeof(normal));
        // color_diffuse 和 color_specular 添加默认值也可以
        memset(color_diffuse, 0, sizeof(color_diffuse));
        memset(color_specular, 0, sizeof(color_specular));
        shininess = 0;
    }
    GzVertex(float x, float y, float z) {
        position[0]=x;
        position[1]=y;
        position[2]=z;
    }
    GzVertex() {
        
    }
} GzVertex;

typedef struct GzTriangle
{
    GzVertex v[3];

    // Source:https://en.wikipedia.org/wiki/List_of_refractive_indices
    // Use plate glass(window glass) refractive index as default
    float refract_index = 1.52; 

    GzTriangle(GzVertex v0, GzVertex v1, GzVertex v2) {
        v[0] = v0;
        v[1] = v1;
        v[2] = v2;
    }
    GzTriangle() {}
} GzTriangle;

typedef struct GzRay {
  public:
    GzRay() {}
    GzRay(GzVertex start, GzVertex dir) {
        startPoint = start;
        direction = dir;
    };
    GzVertex startPoint, direction;
}GzRay;

typedef struct GzSphere
{
    double position[3];
    double color_diffuse[3];
    double color_specular[3];
    double shininess;
    double radius;
} GzSphere;

typedef struct GzLight {
    double position[3];
    double color[3];
} GzLight;

typedef int     GzToken;
typedef void    *GzPointer;
typedef float   GzColor[3];
typedef short   GzIntensity;	/* 0-4095 in lower 12-bits for RGBA */
typedef float	GzCoord[3];
typedef float	GzTextureIndex[2];
typedef float	GzMatrix[4][4];
typedef int	GzDepth;		/* signed z for clipping */

typedef	int	(*GzTexture)(float u, float v, GzColor color);	/* pointer to texture lookup method */
/* u,v parameters [0,1] are defined tex_fun(float u, float v, GzColor color) */

/*
 * Gz camera definition
 */
#ifndef GZCAMERA
#define GZCAMERA
typedef struct  GzCamera
{
  GzMatrix			Xiw;  	/* xform from world to image space */
  GzMatrix			Xpi;     /* perspective projection xform */
  GzCoord			position;  /* position of image plane origin */
  GzCoord			lookat;         /* position of look-at-point */
  GzCoord			worldup;   /* world up-vector (almost screen up) */
  float				FOV;            /* horizontal field of view */
} GzCamera;
#endif

#ifndef GZLIGHT
#define GZLIGHT
typedef struct  GzLight
{
  GzCoord        direction;    /* vector from surface to light */
  GzColor        color;		/* light color intensity */
} GzLight;
#endif

#ifndef GZINPUT
#define GZINPUT
typedef struct  GzInput
{
	GzCoord         rotation;       /* object rotation */
	GzCoord			translation;	/* object translation */
	GzCoord			scale;			/* object scaling */
	GzCamera		camera;			/* camera */
} GzInput;
#endif

#define RED     0         /* array indicies for color vector */
#define GREEN   1
#define BLUE    2

#define X       0      /* array indicies for position vector */
#define Y       1
#define Z       2

#define U       0       /* array indicies for texture coords */
#define V       1


#ifndef GZ_PIXEL
typedef	struct {
  GzIntensity    red;	
  GzIntensity    green;
  GzIntensity    blue;
  GzIntensity    alpha;
  GzDepth	 z;
} GzPixel;
#define GZ_PIXEL
#endif;

#define	MAXXRES	1024	/* put some bounds on size in case of error */
#define	MAXYRES	1024

