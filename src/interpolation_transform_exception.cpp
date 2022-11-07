#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/natural_neighbor_coordinates_2.h>
#include <boost/bind.hpp>
#include <algorithm>
#include <fstream>
#include <CGAL/Interpolation_traits_2.h>
#include <CGAL/interpolation_functions.h>
#include <chrono>
#include <future>
#include <iterator>
#include <ios>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::FT Coord_type; // for the weighted coordinates of nearest neighbours
typedef K::Point_2 Point;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;

//creating a point-coordinate pair. Points and their corresponding natural neighbour coordinates
typedef std::vector<std::pair<Point, Coord_type>> Point_coordinate_vector;
typedef std::map<Point, Coord_type, K::Less_xy_2> Coord_map;
typedef CGAL::Data_access<Coord_map> Value_access;


Coord_type linear_interpolation_vector(Point& p, Delaunay& Dt, Coord_map& value_function) {
	Point_coordinate_vector coords;
	Coord_type norm = CGAL::natural_neighbor_coordinates_2(Dt, p,
		std::back_inserter(coords)).second;

	// linear interpolation function with exception block
	try {
		if (norm == 1) {
			throw(norm);
		}
		else {
			Coord_type result = CGAL::linear_interpolation(coords.begin(), coords.end(),
				norm, Value_access(value_function));
			return result;
		}
	}
	catch (Coord_type norm) {
		Coord_type norm_0 = 0;
		return norm_0;
	}
}

int main() {

	typedef std::map<Point, Coord_type, K::Less_xy_2> Coord_map;
	// data access object is used to insert a functor to retrieve data
	// from the map

	Coord_map value_function_scatter, value_function_function;
	Delaunay T_scatter, T_function;

	auto start = std::chrono::high_resolution_clock::now();
	// importing points from file
	std::ifstream in("data_2/100000/triangulation_prog1_100000.cin");
	std::vector<Point> pts(std::istream_iterator<Point>(in), {});
	/*
	// T_scatter

	// importing scatter values from file
	std::ifstream out("data_2/100000/triangulation_prog1_vals_100000.cin");
	std::vector<int> vals(std::istream_iterator<int>(out), {});
	// std::copy(std::istream_iterator<int>(out), std::istream_iterator<int>(),
	// std::back_inserter(vals));

	T_scatter.insert(pts.begin(), pts.end());

	for (int i = 0; i < pts.size(); ++i) {
		value_function_scatter.insert(std::make_pair(pts[i], vals[i]));
	}
	*/
	
	// T_function

	// defining coefficients of polynomial 
	
	Coord_type a(0.001), b(0.002), c(0.003);

	// creating function value map
	T_function.insert(pts.begin(), pts.end());

	for (int i = 0; i < pts.size(); ++i) {
		value_function_function.insert(std::make_pair(pts[i], (a * pts[i].x() * pts[i].x()) +
			(b * pts[i].y() * pts[i].y()) + (c * pts[i].x() * pts[i].y())));
	}
	
	// vector of query points
	std::ifstream query("data_2/100000/triangulation_prog1_func_1000.cin");
	std::vector<Point> query_points(std::istream_iterator<Point>(query), {});
	// std::copy(std::istream_iterator<Point>(query), std::istream_iterator<Point>(),
	//	std::back_inserter(query_points));
		// result vector

	std::vector<Coord_type> result;

	// calling vector function
	std::transform(begin(query_points), end(query_points), back_inserter(result),
		boost::bind<Coord_type>(&linear_interpolation_vector, _1, T_function, value_function_function));
	/*
	std::ofstream outfile("data_2/100000/scatter/interpolation_100000_1000_scatter.csv", std::ios::out | std::ios::binary);
	outfile << std::setprecision(9);
	for (auto const& x : result) {
		outfile << x << "\n";
	}
	*/
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	
	for (int i = 0; i < result.size(); i++) {
		std::cout << result[i] << std::endl;
	}
	std::cout << "Duration : " << duration.count() << std::endl;
	std::cout << "Test" << std::endl;
	return EXIT_SUCCESS;
}