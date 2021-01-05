//FILE:         parse.h
//AUTHOR:       Nathan Cournia <nathan@cournia.com>
//DESCRIPTION:  Various data structures to hold information about objects
//              in a scene.
//NOTES:        Add what ever you need to this file.  Most of your
//              additions will appear where you see an ". . .".
//              When you add an attribute to either light_t, camera_t,
//              or shape_t, be sure to add a default value for the new
//              attribute in the structures reset( ) method.

#ifndef PARSE_H
#define PARSE_H 1

#include <list>
#include <string>
#include <iostream>
#include <cstring>

namespace parser {

// types
typedef double		type_t;

const unsigned int	vector_size = 3;
typedef type_t		vector_t[vector_size];

const unsigned int	color_size = 4;
typedef type_t		color_t[color_size];

//////////////////////////////////////////////////////////////////////////
inline void vector_assign( vector_t dst, const vector_t src )
{
  memcpy( dst, src, sizeof( vector_t ) );
}

//////////////////////////////////////////////////////////////////////////
inline void vector_set( vector_t dst, type_t x, type_t y, type_t z )
{
  dst[0] = x; dst[1] = y; dst[2] = z;
}

//////////////////////////////////////////////////////////////////////////
inline void vector_print ( std::ostream& out, const vector_t vec )
{
  out << "<" << vec[0] << ", " << vec[1] << ", " << vec[2] << ">";
}

//////////////////////////////////////////////////////////////////////////
inline void color_assign( color_t dst, const color_t src )
{
  memcpy( dst, src, sizeof( color_t ) );
}

//////////////////////////////////////////////////////////////////////////
inline void color_set( color_t dst, type_t r, type_t g, 
                       type_t b, type_t a )
{
  dst[0] = r; dst[1] = g; dst[2] = b; dst[3] = a;
}

//////////////////////////////////////////////////////////////////////////
inline void color_set( color_t dst, type_t r, type_t g, type_t b )
{
  dst[0] = r; dst[1] = g; dst[2] = b; dst[3] = 0.0;
}

//////////////////////////////////////////////////////////////////////////
inline void color_print ( std::ostream& o, const color_t c )
{
  o << "<" << c[0] << ", " << c[1] << ", " << c[2] << ", " << c[3] << ">";
}

//////////////////////////////////////////////////////////////////////////
// data structures to describe objects ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//so we know what type of image we received
enum image_type_t {
  IMAGE_PPM,
  IMAGE_BMP,
  IMAGE_PNG,
  // . . .
  IMAGE_NONE
};

//////////////////////////////////////////////////////////////////////////
enum trx_type_t {
  TRANSFORM_TRANSLATE,
  TRANSFORM_ROTATE,
  TRANSFORM_SCALE
};

//////////////////////////////////////////////////////////////////////////
enum cam_type_t {
  CAMERA_PERSPECTIVE,
  CAMERA_ORTHOGRAPHIC
};

//////////////////////////////////////////////////////////////////////////
// Transformations are stored in the order they appear in the file.
// This structure stores the vector representation of the transformation
// and also denotes the type of transformation
struct trx_t {
	trx_type_t type;
	vector_t vector;

// needed?
//	trx_t& operator= ( const trx_t& rhs ) {
//	  type = rhs.type;
//	  vector_assign( vector, rhs.vector );
//	  return *this;
//	}
};

//////////////////////////////////////////////////////////////////////////
//camera information
struct camera_t {
	cam_type_t type;
	vector_t location;
	vector_t look_at;
	vector_t sky;
	vector_t direction;
	vector_t up;
	// . . .

	//methods
	camera_t( void ) { reset( ); }
	
	//reset( ) sets all values in this struct to their default value
	void reset( void ) {
	  type = CAMERA_PERSPECTIVE;
	  vector_set( location, 0.0, 5.0, -1.0 );
	  vector_set( look_at, 0.0, 5.0, 10.0 );
	  vector_set( sky, 0.0, 1.0, 0.0 );
	  vector_set( direction, 0.0, 0.0, 1.0 );
	  vector_set( up, 0.0, 1.0, 0.0 );
	  // . . .
	}
};

//////////////////////////////////////////////////////////////////////////
//light source information
struct light_t {
	vector_t location;
	color_t color;
	double fade_power;
	double fade_distance;
	// . . .

	//methods
	light_t( void ) { reset( ); }

	//reset( ) sets all values in this struct to their default value
	void reset( void ) {
	  vector_set( location, 0.0, 0.0, 0.0 );
	  color_set( color, 0.0, 0.0, 0.0 );
	  fade_power = 0.0;
	  fade_distance = 0.0;
	  // . . .
	}
};

//////////////////////////////////////////////////////////////////////////
//shape information
//shape specific information is not stored here (i.e. the radius of a 
//sphere, the normal of a plane). what is stored here is information
//shared by all objects (i.e. diffuse coef, ambient coef, etc.)
struct shape_t {
	std::list<trx_t> trxs;
	double		diffuse;
	double		ambient;
	double		phong;
	double		phong_size;
	double		reflection;
	double		refraction;
	double		ior;
	double		specular;
	color_t		color;
	bool		checker_board;
	color_t		checker[2];
	std::string	image_name;
	image_type_t	image_type;
	image_type_t	bump_map_image_type;
	std::string	bump_map_image_name;
	double		bump_map_size;
	// . . .

	//methods
	shape_t( void ) { reset( ); }

	//reset( ) sets all values in this struct to their default value
	void reset( void ) {
	  diffuse = 0.0;
	  ambient = 0.0;
	  phong = 0.0;
	  phong_size = 0.0;
	  reflection = 0.0;
	  refraction = 0.0;
	  ior = 1.0;
	  specular = 0.0;
	  color_set( color, 0.0, 0.0, 0.0, 0.0 );
	  checker_board = false;
	  image_type = IMAGE_NONE;
	  image_name.clear();
	  bump_map_image_type = IMAGE_NONE;
	  bump_map_size = 1.0;
	  // . . .
		
	  // clear out the transformation list
	  trxs.clear( );
	}

	// adds the transformation to the transformation list.  transformations
	// are added in the order in which they are received
	void add_trx( trx_type_t type, vector_t vector ) {
		trx_t t;
	  t.type = type;
	  vector_assign( t.vector, vector );
	  trxs.push_back( t );
	}
};

//////////////////////////////////////////////////////////////////////////
//vertex_list information
struct vertex_t {
//	std::list<vector_t> verteces;
	std::list<type_t *> verteces;

	// methods
	vertex_t( void ) { reset( ); }

	// reset( ) sets all values in this struct to their default value
	void reset( void ) {
	  // clear out the vertex list
	  // MEMORY LEAK?  seems like each member should be removed and
	  //               individually delete'd
	  verteces.clear( );
	}

	// adds the vector to the vertex list.  verteces
	// are added in the order in which they are received
	void add_vertex( vector_t vertex ) {
		type_t *v = new type_t[vector_size];
	  vector_assign( v, vertex );
	  verteces.push_back( v );
	}
};

}; //end of namespace parser

#endif
