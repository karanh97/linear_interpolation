#include <iostream>
#include <fstream>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/draw_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Projection_traits_xy_3<K> Gt;
typedef CGAL::Delaunay_triangulation_2<Gt> Delaunay;
typedef K::Point_3 Point;
typedef CGAL::Triangulation_2<Gt> Triangulation;


int main(int argc, char* argv[]) {
	std::ifstream in((argc > 1) ? argv[1] : "data/triangulation_prog1.cin");
	std::istream_iterator<Point> begin(in);
	std::istream_iterator<Point> end;

	Delaunay dt;
	dt.insert(begin, end);

	std::cout << dt.number_of_vertices() << std::endl;
	Triangulation t = (Triangulation)dt;
	std::cout << t.number_of_vertices() << std::endl;

	std::cout << "Attempting to draw the Delaunay Triangulation" << std::endl;
	CGAL::draw(t);
}