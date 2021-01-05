//FILE:         creation.cpp
//AUTHOR:       Nathan Cournia <nathan@cournia.com>
//DESCRIPTION:  This file contains empty functions that need to be defined
//              by the user to create objects in the user's ray tracer.

#include <iostream>
#include "parse.h"
using namespace parser;

//////////////////////////////////////////////////////////////////////////
static void print_trx( std::ostream& os, std::list<trx_t>::const_iterator i )
{
  switch( i->type ) {
    case TRANSFORM_TRANSLATE:
      os << "    translate: ";
      break;
    case TRANSFORM_ROTATE:
      os << "    rotate:    ";
      break;
    case TRANSFORM_SCALE:
      os << "    scale:     ";
      break;
    default:
      os << "    unknown:   ";
  };
  os << i->vector << std::endl;
}

//////////////////////////////////////////////////////////////////////////
static void print_traits( std::ostream& os, const shape_t *traits )
{
	std::list<trx_t>::const_iterator i;

  os << "  diffuse:         " << traits->diffuse		<< std::endl;
  os << "  ambient:         " << traits->ambient		<< std::endl;
  os << "  phong:           " << traits->phong			<< std::endl;
  os << "  phong_size:      " << traits->phong_size		<< std::endl;
  os << "  reflection:      " << traits->reflection		<< std::endl;
  os << "  refraction:      " << traits->refraction		<< std::endl;
  os << "  ior:             " << traits->ior			<< std::endl;
  os << "  specular:        " << traits->specular		<< std::endl;
  os << "  color:           ";
  color_print( os, traits->color );
  os << std::endl;
  os << "  checker color 0: ";
  color_print( os, traits->checker[0] );
  os << std::endl;
  os << "  checker color 1: "; 
  color_print( os, traits->checker[1] );
  os << std::endl;

  os << "  image type:        "; 
  switch( traits->image_type ) {
    case IMAGE_BMP:
      os << "    BMP ";
      break;
    case IMAGE_PNG:
      os << "    PNG ";
      break;
    case IMAGE_PPM:
      os << "    PPM ";
      break;
    default:
      os << "    None ";
      break;
  };
  os << std::endl;

  os << "  image map:       " << traits->image_name		<< std::endl;
  os << "  bumpmap:         " << traits->bump_map_image_name	<< std::endl;
  os << "  bumpmap size:    " << traits->bump_map_size		<< std::endl;
  os << "  tranformations:  " << std::endl;
  for( i = traits->trxs.begin( ); i != traits->trxs.end( ); ++i ) {
    print_trx( os, i );
  }
}

//////////////////////////////////////////////////////////////////////////
static void print_verteces( std::ostream& os, const vertex_t *verts )
{
//	std::list<vector_t>::const_iterator v;
//
//for( v = verts->verteces.begin( ); v != verts->verteces.end( ); ++v ) {
//  os << "   ";
//  vector_print( os, *v);
//  os << std::endl;
//}
	std::list<type_t *>::const_iterator v;

  for( v = verts->verteces.begin( ); v != verts->verteces.end( ); ++v ) {
    os << "   ";
    vector_print( os, *v);
    os << std::endl;
  }
}

//////////////////////////////////////////////////////////////////////////
void create_camera( camera_t* traits )
{ 
  std::cout << "camera parsed:" << std::endl;

  std::cout << "  type:        "; 
  switch( traits->type ) {
    case CAMERA_PERSPECTIVE:
      std::cout << "    perspective ";
      break;
    case CAMERA_ORTHOGRAPHIC:
      std::cout << "    orthographic ";
      break;
    default:
      std::cout << "    unknown   ";
  };
  std::cout << std::endl;

  std::cout << "  location:        "; 
  vector_print( std::cout, traits->location );
  std::cout << std::endl;

  std::cout << "  look_at:         "; 
  vector_print( std::cout, traits->look_at );
  std::cout << std::endl;

  std::cout << "  sky:         "; 
  vector_print( std::cout, traits->sky );
  std::cout << std::endl;

  std::cout << "  direction:         "; 
  vector_print( std::cout, traits->direction );
  std::cout << std::endl;

  std::cout << "  up:         "; 
  vector_print( std::cout, traits->up );
  std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////
void create_light( light_t* traits )
{ 
  std::cout << "light parsed:" << std::endl;
  std::cout << "  location:        "; 
  vector_print( std::cout, traits->location );
  std::cout << std::endl;
  std::cout << "  color:           "; 
  color_print( std::cout, traits->color );
  std::cout << std::endl;
  std::cout << "  fade_power:      " << traits->fade_power << std::endl;
  std::cout << "  fade_distance:   " << traits->fade_distance << std::endl;
}

//////////////////////////////////////////////////////////////////////////
void create_sphere( vector_t location, double radius, shape_t* traits )
{ 
  std::cout << "sphere parsed:    " << std::endl;
  std::cout << "  location:        "; 
  vector_print( std::cout, location );
  std::cout << std::endl;
  std::cout << "  radius:          " << radius << std::endl;
  print_traits( std::cout, traits );
}

//////////////////////////////////////////////////////////////////////////
void create_polygon( int num, vertex_t* vertex_list, shape_t* traits )
{ 
  std::cout << "polygon parsed:    " << std::endl;
  std::cout << "  num:        " << num << std::endl; 
  std::cout << "  verteces:          " << std::endl;
  print_verteces( std::cout, vertex_list );
  print_traits( std::cout, traits );
}

//////////////////////////////////////////////////////////////////////////
void create_plane( vector_t normal, double d, shape_t* traits )
{ }
