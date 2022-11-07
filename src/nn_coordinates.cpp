#include <iostream>
#include <iterator>
#include <vector>
#include <utility>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/natural_neighbor_coordinates_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::FT Coord_type;
typedef K::Point_2 Point;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;

//creating a point-coordinate pair. Points and their corresponding natural neighbour coordinates
typedef std::vector<std::pair<Point, Coord_type>> Point_coordinate_vector;

int main() {
	Delaunay dt;

	// inserting points into delaunay

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			dt.insert(Point(i, j));

	// computing natural neighbour coordinates
	Point p(1.2, 0.7);
	Point_coordinate_vector coords;
	// create a function to return three parameter
	// first parameter must be an output iterator of the point_coord-type vector.
	CGAL::Triple<std::back_insert_iterator<Point_coordinate_vector>, K::FT, bool> result =
		CGAL::natural_neighbor_coordinates_2(dt, p, std::back_inserter(coords));

	// checking if the computation took place through the bool variable

	if (!result.third) {
		std::cout << "The computation was not successful!" << std::endl;
	}

	K::FT normalize = result.second;

	std::cout << "The area of the Voronoi cell of the query point is " << normalize << std::endl;

	std::cout << "Coordinates for point: (" << p << ") are the following: " << std::endl;
	for (std::size_t i = 0; i < coords.size(); ++i)
		std::cout << "  Point: (" << coords[i].first << ") coeff: " << coords[i].second << std::endl;

	return EXIT_SUCCESS;
}
