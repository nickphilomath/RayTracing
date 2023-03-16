#include "Model.h"


Model::Model() {
}

Model::~Model() {
	for (auto t : m_triangles)
		delete t;
}

void Model::MakeTriangles() {
	for (auto& face : m_faces) {
		Triangle* triangle = new Triangle;

		triangle->Albedo = { 1.0f, 0.0f, 1.0f };
		triangle->A = *(m_verticies[face->vertex_ins[0] - 1]);
		triangle->B = *(m_verticies[face->vertex_ins[1] - 1]);
		triangle->C = *(m_verticies[face->vertex_ins[2] - 1]);
		triangle->Normal = *(m_normals[face->normal - 1]);
		triangle->Position = { 0.0f, 0.0f, 0.0f };

		m_triangles.push_back(triangle);
	}
}

void Model::CleanTrash() {
	for (auto v : m_verticies)
		delete v;

	for (auto vn : m_normals)
		delete vn;

	for (auto f : m_faces)
		delete f;
}

int Model::LoadFromOBJ(const char* filename) {
	std::string line, prefix;
	std::stringstream ss;
	std::ifstream ifile(filename);

	if (ifile.is_open()) {
		while (getline(ifile, line)) {
			ss.clear();
			ss.str(line);
			ss >> prefix;
			if (prefix == "v") {
				glm::vec3* v = new glm::vec3;
				ss >> v->x >> v->y >> v->z;
				m_verticies.push_back(v);
				//std::cout << v.x << v.y << v.z << " " << std::endl;
			}
			else if (prefix == "vn") {
				glm::vec3* vn = new glm::vec3;
				ss >> vn->x >> vn->y >> vn->z;
				m_normals.push_back(vn);
			}
			else if (prefix == "f") {
				Face* face = new Face;

				int counter = 0, face_index_counter = 0, temp_int;
				while (ss >> temp_int) {
					if (counter == 0)
						face->vertex_ins[face_index_counter] = temp_int;
					else if (counter == 1)
						face->texture_ins[face_index_counter] = temp_int;
					else if (counter == 2)
						face->normal = temp_int;

					if (ss.peek() == '/') {
						counter++;
						ss.ignore(1, '/');
					}
					else if (ss.peek() == ' ') {
						counter++;
						ss.ignore(1, ' ');
					}

					// reset counter 
					if (counter > 2) {
						counter = 0;
						face_index_counter++;
					}
				}
				m_faces.push_back(face);
				//m_triangles.push_back(triangle);
				m_triangleCount++;
			}
		}
		ifile.close();

		MakeTriangles();
		CleanTrash();
	}
	else {
		std::cout << "could not open the file" << std::endl;
	}
}

void Model::PrintAll() {
	for (auto& v : m_verticies) {
		std::cout << "v" << " " << v->x << " " << v->y << " " << v->z << std::endl;
	}

	for (auto& v : m_normals) {
		std::cout << "vn" << " " << v->x << " " << v->y << " " << v->z << std::endl;
	}

	for (auto& f : m_faces) {
		std::cout << "f " <<
			f->vertex_ins[0] << "/" << f->texture_ins[0] << "/" << f->normal << " " <<
			f->vertex_ins[1] << "/" << f->texture_ins[1] << "/" << f->normal << " " <<
			f->vertex_ins[2] << "/" << f->texture_ins[2] << "/" << f->normal << " "
			<< std::endl;
	}

	std::cout << "total triangles: " << m_triangleCount << std::endl;
}
