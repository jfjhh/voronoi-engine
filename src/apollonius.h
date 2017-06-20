/**
 * Uses the Apollonius graph of the stage's bullets to decide where the player
 * should move.
 * Alex Striff.
 */

#ifndef APOLLONIUS_H
#define APOLLONIUS_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Point_2.h>
#include <CGAL/Apollonius_graph_2.h>
#include <CGAL/Triangulation_data_structure_2.h>
#include <CGAL/Apollonius_graph_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Apollonius_graph_filtered_traits_2.h>

#include "stage.h"
#include "shape.h"

// typedef for the kernel.
typedef CGAL::Simple_cartesian<double> Rep;

// typedef for sites.
typedef CGAL::Point_2<Rep> Point_2;
typedef CGAL::Apollonius_site_2<Rep> Site_2;

// typedef for the traits; the filtered traits class is used
typedef CGAL::Apollonius_graph_filtered_traits_2<Rep> Traits;

// typedefs for the algorithm

// With the second template argument in the vertex base class being
// false, we indicate that there is no need to store the hidden sites.
// One case where this is indeed not needed is when we only do
// insertions, like in the main program below.
typedef CGAL::Apollonius_graph_vertex_base_2<Traits, false> Vb;
typedef CGAL::Triangulation_face_base_2<Traits> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Agds;
typedef CGAL::Apollonius_graph_2<Traits, Agds> Apollonius_graph;

VoronoiVertex apollonius_direction(coord x, coord y, const VoronoiHull& v);

#endif /* APOLLONIUS_H */

