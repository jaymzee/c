/*
FILE:           povlex.l
AUTHOR:         Nathan Cournia <nathan@cournia.com>
NOTES:          "string" rule modified from Bison manual example.
                "string" rule can overflow if string is longer than 256 chars.
                C style comment rule modified from Bison manual example.
*/

%{
#include <iostream>
#include <cstdlib>
#include <string>
#include "parse.h"
#include "y.tab.h"
using namespace parser;

extern int povinput(char *buf, int maxlen);
extern unsigned int povline;
#undef YY_INPUT
#define YY_INPUT(buf, retval, maxlen) (retval = povinput(buf, maxlen))
#define POVRAY_DEBUG( x ) std::cerr << x << std::endl;

%}

%option noyywrap
%x str
%x comment

	char string_buf[256];
	char *string_buf_ptr;

%%

\/\/.* /* ignore c++ style comments */
-?[0-9]+(\.[0-9]+)?(e-?[0-9]+)? { povlval.number = atof( yytext ); return DOUBLE; }
[ \t] /* ignore white space */
\n { povline++; }
\{ { return O_BRACE; }
\} { return C_BRACE; }
\< { return LESS; }
\> { return GREAT; }
\, { return COMMA; }
texture { return TEXTURE; }
pigment { return PIGMENT; }
color { return COLOR; }
sphere { return SPHERE; }
polygon { return POLYGON; }
light_source { return LIGHT_SOURCE; }
camera { return CAMERA; }
look_at { return LOOK_AT; }
sky { return SKY; }
direction { return DIRECTION; }
up { return UP; }
location { return LOCATION; }
perspective { return PERSPECTIVE; }
orthographic { return ORTHOGRAPHIC; }
phong { return PHONG; }
phong_size { return PHONG_SIZE; }
ambient { return AMBIENT; }
diffuse { return DIFFUSE; }
reflection { return REFLECTION; }
finish { return FINISH; }
radius { return RADIUS; }
plane { return PLANE; }
checker { return CHECKER; }
refraction { return REFRACTION; }
ior { return IOR; }
image_map { return IMAGE_MAP; }
ppm { return PPM; }
bmp { return BMP; }
png { return PNG; }
quad { return QUAD; }
fade_distance { return FADE_DISTANCE; }
fade_power { return FADE_POWER; }
normal { return NORMAL; }
bump_map { return BUMP_MAP; }
bump_size { return BUMP_SIZE; }
translate { return TRANSLATE; }
rotate { return ROTATE; }
scale { return SCALE; }
box { return BOX; }
caustics { return CAUSTICS; }
cylinder { return CYLINDER; }
quad_light { return QUAD_LIGHT; }
roughness { return ROUGHNESS; }
specular { return SPECULAR; }
isotropy { return ISOTROPY; }
fresnel { return FRESNEL; }
nu { return NU; }
nv { return NV; }
indirect_samples { return INDIRECT_SAMPLES; }
gloss_samples { return GLOSS_SAMPLES; }
scene { return SCENE; }
ray_depth { return RAY_DEPTH; }
scene_fade_power { return SCENE_FADE_POWER; }
scene_fade_distance { return SCENE_FADE_DISTANCE; }
background { return BACKGROUND; }
rgbf { return RGBF; }
rgb { return RGB; }



\"      {
	  string_buf_ptr = string_buf; 
	  BEGIN(str);
	}

<str>\" { 
	  /* saw closing quote - all done */
	  BEGIN(INITIAL);
	  *string_buf_ptr = '\0';
	  //std::cout << "string: " << string_buf << std::endl;
	  povlval.strg = new std::string(string_buf); 
	  return STRING;
	}

<str>\n {
	  /* error - unterminated string constant */
	  /* generate error message */
	  std::cerr << "Unterminated string constant!" << std::endl;
	}

<str>\\[0-7]{1,3} {
	  /* octal escape sequence */
	  int result;

	  (void) sscanf( yytext + 1, "%o", &result );

	  if ( result > 0xff ) {
	    /* error, constant is out-of-bounds */
	    std::cerr << "string error" << std::endl;
	  }

	  *string_buf_ptr++ = result;
	}

<str>\\[0-9]+ {
	  /* generate error - bad escape sequence; something
	   * like '\48' or '\0777777'
	   */
	  std::cout << "string error 2" << std::endl;
	}

<str>\\n  *string_buf_ptr++ = '\n';
<str>\\t  *string_buf_ptr++ = '\t';
<str>\\r  *string_buf_ptr++ = '\r';
<str>\\b  *string_buf_ptr++ = '\b';
<str>\\f  *string_buf_ptr++ = '\f';

<str>\\(.|\n)  *string_buf_ptr++ = yytext[1];

<str>[^\\\n\"]+ {
	  char *yptr = yytext;

	  while ( *yptr ) *string_buf_ptr++ = *yptr++;
	}

"/*"         BEGIN(comment);
<comment>[^*]*        /* eat anything that's not a '*' */
<comment>"*"+[^*/]*   /* eat up '*'s not followed by '/'s */
<comment>"*"+"/"        BEGIN(INITIAL);

[a-zA-Z0-9_]* { return ERROR; }
.	{ return ERROR; }


%%
