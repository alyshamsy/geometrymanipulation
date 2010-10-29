#ifndef Vertex_H
#define Vertex_H

class Vertex {
public:
	Vertex();
	Vertex(double a, double b, double c);
	Vertex(const Vertex& source);
	~Vertex();
	void set_vertex(double a, double b, double c);

	Vertex& operator=(const Vertex& rhs);
	ostream& operator<<(ostream& ostr, const Face& current_face);

	double x, y, z;
};
#endif