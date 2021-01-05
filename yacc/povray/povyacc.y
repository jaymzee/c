/*
FILE:           povray.y
AUTHOR:         Nathan Cournia <nathan@cournia.com>
*/

%{
#include <cmath>
#include "parse.h"
using namespace parser;

/* internal yacc functions */
extern int yylex(void);
extern void yyerror(char *msg);

/* creation functions */
extern void create_camera( camera_t* traits );
extern void create_light( light_t* traits );
extern void create_polygon( int num, vertex_t* vertex_list, shape_t* traits );
extern void create_sphere( vector_t location, double radius, shape_t* traits );
extern void create_plane( vector_t normal, double d, shape_t* traits );

/* current line */
unsigned int povline = 1;

static shape_t shape_traits;
static vertex_t vertex_list;
static light_t light_traits;
static camera_t camera_traits;
%}

%union {
	double number;
	std::string* strg;
	parser::type_t *vec;
	parser::type_t *color;
	parser::image_type_t image;
}

%token O_BRACE C_BRACE LESS GREAT COMMA PIGMENT COLOR DOUBLE
%token FINISH PHONG PHONG_SIZE LIGHT_SOURCE CAMERA LOCATION LOOK_AT
%token SKY DIRECTION UP PERSPECTIVE ORTHOGRAPHIC
%token SPHERE POLYGON
%token PHONG PHONG_SIZE AMBIENT DIFFUSE REFLECTION RADIUS
%token PLANE CHECKER REFRACTION IOR PPM BMP PNG IMAGE_MAP QUAD FADE_POWER 
%token FADE_DISTANCE NORMAL BUMP_MAP BUMP_SIZE TRANSLATE ROTATE SCALE
%token BOX CAUSTICS CYLINDER QUAD_LIGHT FRESNEL ISOTROPY ROUGHNESS SPECULAR
%token NU NV INDIRECT_SAMPLES GLOSS_SAMPLES SCENE RAY_DEPTH SCENE_FADE_POWER
%token SCENE_FADE_DISTANCE BACKGROUND TEXTURE RGB RGBF ERROR

%token <strg> STRING
%token <number> DOUBLE

%type <vec> vector
%type <color> color
%type <image> image_type

%%

/* ==================================================== */
/* = BEGIN GRAMMAR ==================================== */
/* ==================================================== */

/* THIS STATEMENT MUST APPEAR FIRST, statement_list IS THE START SYMBOL */
statement_list: statement | statement_list statement
	;

/*
statement: shape | light | camera | scene
*/
statement: shape | light | camera
	;

/*
shape: sphere_decl | plane_decl | quad_decl | box_decl | cylinder_decl
*/
shape: sphere_decl | plane_decl | poly_decl
	;

light: light_decl
	;

camera: camera_decl
	;

/* ==================================================== */
/* = CAMERA =========================================== */
/* ==================================================== */

camera_decl: CAMERA O_BRACE camera_properties C_BRACE
	{
	  create_camera( &camera_traits );
	  camera_traits.reset( );
	}
	;

camera_properties: camera_prop | camera_properties camera_prop
	;

camera_prop: LOOK_AT vector
	{
	  vector_assign( camera_traits.look_at, $2 );
	  delete[] $2;
	}
           | LOCATION vector
	{
	  vector_assign( camera_traits.location, $2 );
	  delete[] $2;
	}
           | SKY vector
	{
	  vector_assign( camera_traits.sky, $2 );
	  delete[] $2;
	}
           | DIRECTION vector
	{
	  vector_assign( camera_traits.direction, $2 );
	  delete[] $2;
	}
           | UP vector
	{
	  vector_assign( camera_traits.up, $2 );
	  delete[] $2;
	}
           | PERSPECTIVE
	{
	  camera_traits.type = CAMERA_PERSPECTIVE;
	}
           | ORTHOGRAPHIC
	{
	  camera_traits.type = CAMERA_ORTHOGRAPHIC;
	}
	;

/* ==================================================== */
/* = LIGHTS =========================================== */
/* ==================================================== */

light_decl: LIGHT_SOURCE O_BRACE vector light_properties C_BRACE
	{
	  /* assign location */
	  vector_assign( light_traits.location, $3 );
	  delete[] $3;
	  create_light( &light_traits );
	  light_traits.reset( );
	}
	;

light_properties: light_prop | light_properties light_prop
	;

light_prop: color
	{
	  color_assign( light_traits.color, $1 );
	  delete[] $1;
	}
	| FADE_POWER DOUBLE
	{
	  light_traits.fade_power = $2;
	}
	| FADE_DISTANCE DOUBLE
	{
	  light_traits.fade_distance = $2;
	}
	;

/* ==================================================== */
/* = POLYGON ========================================== */
/* ==================================================== */

poly_decl: POLYGON O_BRACE DOUBLE COMMA poly_properties shape_properties C_BRACE
	{
	  create_polygon( (int)$3, &vertex_list, &shape_traits );
	  shape_traits.reset( );
	  vertex_list.reset( );
	}
	;

poly_properties: vertex | vertex COMMA poly_properties
	;

vertex: vector
	{
	  vertex_list.add_vertex( $1 );
	  delete[] $1;
	}
	;

/* ==================================================== */
/* = SPHERE =========================================== */
/* ==================================================== */

sphere_decl: SPHERE O_BRACE vector COMMA DOUBLE shape_properties C_BRACE
	{
	  create_sphere( $3, $5, &shape_traits );
	  delete[] $3;
	  shape_traits.reset( );
	}
	;

/* ==================================================== */
/* = PLANE  =========================================== */
/* ==================================================== */

plane_decl: PLANE O_BRACE vector COMMA DOUBLE shape_properties C_BRACE
	{
	  create_plane( $3, $5, &shape_traits );
	  delete[] $3;
	  shape_traits.reset( );
	}
	;

/* ==================================================== */
/* = SHAPE PROPERTIES ================================= */
/* ==================================================== */

shape_properties: shape_prop | shape_properties shape_prop
	;

shape_prop: texture_decl
	| TRANSLATE vector
	{
	  shape_traits.add_trx( TRANSFORM_TRANSLATE, $2 );
	  delete[] $2;
	}
	| SCALE vector
	{
	  shape_traits.add_trx( TRANSFORM_SCALE, $2 );
	  delete[] $2;
	}
	| ROTATE vector
	{
	  /* convert degrees to radians */
	  $2[0] = $2[0] * M_PI / 180.0;
	  $2[1] = $2[2] * M_PI / 180.0;
	  $2[2] = $2[2] * M_PI / 180.0;

	  /* add the transformation */
	  shape_traits.add_trx( TRANSFORM_ROTATE, $2 );
	  delete[] $2;
	}
	;

/* ==================================================== */
/* = TEXTURE ========================================== */
/* ==================================================== */

texture_decl: TEXTURE O_BRACE texture_properties C_BRACE
	| texture_properties
	;

texture_properties: texture_prop | texture_properties texture_prop
	;

texture_prop: pigment_decl | finish_decl | normal_decl
	;

/* ==================================================== */
/* = PIGMENT ========================================== */
/* ==================================================== */

pigment_decl: PIGMENT O_BRACE pigment_prop C_BRACE
	;

pigment_prop: color
	{
	  color_assign( shape_traits.color, $1 );
	  delete[] $1;
	}
	| CHECKER color COMMA color
	{
	  shape_traits.checker_board = true;
	  color_assign( shape_traits.checker[0], $2 );
	  color_assign( shape_traits.checker[1], $4 );
	  delete[] $2;
	  delete[] $4;
	}
	| IMAGE_MAP O_BRACE image_type STRING C_BRACE
	{
	  /* determine image type */
	  switch ( $3 ) {
	    case IMAGE_PPM:	/* portable pixmap image */
	      shape_traits.image_type = IMAGE_PPM;
	      break;
	    case IMAGE_BMP:	/* bitmap */
	      shape_traits.image_type = IMAGE_BMP;
	      break;
	    case IMAGE_PNG:	/* png */
	      shape_traits.image_type = IMAGE_PNG;
	      break;
	    default:
	      shape_traits.image_type = IMAGE_NONE;
	      break;
	  }
		
	  /* pass the image filename */
	  shape_traits.image_name = *$4;
		
	  /* STRING is dynamically allocated memory owned */
	  /* by the parser.  new memory is allocated for  */
	  /* every string.  we need to delete the memory  */
	  /* when we are done with it (which is now).     */
	  delete $4;
	}
	;

/* ==================================================== */
/* = FINISH =========================================== */
/* ==================================================== */

finish_decl: FINISH O_BRACE finish_properties C_BRACE
	;

finish_properties: finish_prop | finish_properties finish_prop
	;

finish_prop: phong | phong_size | diffuse | ambient | reflection | refraction
	| ior | specular 
	;

phong: PHONG DOUBLE
	{ 
	  shape_traits.phong = $2;
	}
	;

phong_size: PHONG_SIZE DOUBLE
	{ 
	  shape_traits.phong_size = $2;
	}
	;

diffuse: DIFFUSE DOUBLE
	{ 
	  shape_traits.diffuse = $2;
	}
	;

ambient: AMBIENT DOUBLE
	{ 
	  shape_traits.ambient = $2;
	}
	;

reflection: REFLECTION DOUBLE
	{ 
	  shape_traits.reflection = $2;
	}
	;

refraction: REFRACTION DOUBLE
	{ 
	  shape_traits.refraction = $2;
	}
	;

ior: IOR DOUBLE
	{ 
	  shape_traits.ior = $2;
	}
	;

specular: SPECULAR DOUBLE
	{ 
	  shape_traits.specular = $2;
	}
	;

/* ==================================================== */
/* = NORMAL =========================================== */
/* ==================================================== */

normal_decl: NORMAL O_BRACE normal_prop C_BRACE
	;

normal_prop: bump_map_decl
	;

bump_map_decl: BUMP_MAP O_BRACE image_type STRING bump_map_prop C_BRACE
	{
	  /* determine image type */
	  if( $3 == IMAGE_PPM ) {
	    /* portable pixmap image */
	    shape_traits.bump_map_image_type = IMAGE_PPM;
	  } else if( $3 == IMAGE_BMP ) {
	    /* bitmap */
	    shape_traits.bump_map_image_type = IMAGE_BMP;
	  } else if( $3 == IMAGE_PNG ) {
	    /* bitmap */
	    shape_traits.bump_map_image_type = IMAGE_PNG;
	  }
		
	  /* pass the image filename */
	  shape_traits.bump_map_image_name = *$4;
		
	  /* STRING is dynamically allocated memory owned */
	  /* by the parser.  new memory is allocated for  */
	  /* every string.  we need to delete the memory  */
	  /* when we are done with it (which is now).     */
	  delete $4;
	}
	;

bump_map_prop: /* empty */
	{
	  shape_traits.bump_map_size = 1.0;
	}
	| BUMP_SIZE DOUBLE
	{
	  shape_traits.bump_map_size = $2;
	}
	;

/* ==================================================== */
/* = COMMON KEYWORDS ================================== */
/* ==================================================== */

vector: LESS DOUBLE COMMA DOUBLE COMMA DOUBLE GREAT
	{
	  /* create a new vector.  be sure to delete it when done */
	  type_t *tmp = new vector_t;
	  tmp[0] = $2;
	  tmp[1] = $4;
	  tmp[2] = $6;
	  $$ = tmp;
	}
	;

color: COLOR RGBF LESS DOUBLE COMMA DOUBLE COMMA DOUBLE COMMA DOUBLE GREAT
	{
	  // rgbf
	  type_t *tmp = new color_t;
	  tmp[0] = $4;
	  tmp[1] = $6;
	  tmp[2] = $8;
	  tmp[3] = $10;
	  $$ = tmp;
	}
	| COLOR RGB LESS DOUBLE COMMA DOUBLE COMMA DOUBLE GREAT
	{
	  // rgb
	  type_t *tmp = new color_t;
	  tmp[0] = $4;
	  tmp[1] = $6;
	  tmp[2] = $8;
	  tmp[3] = 0.0;
	  $$ = tmp;
	}
	;

image_type: PPM
	{
	  $$ = IMAGE_PPM;
	}
	| BMP
	{
	  $$ = IMAGE_BMP;
	}
	| PNG
	{
	  $$ = IMAGE_PNG;
	}
	;

%%

extern char *povtext;

void yyerror(char *message)
{
  /* not the best error checking in the world, but it works */
  std::cerr << message
            << " near line " << povline
            << " near "      << povtext << std::endl;
}
