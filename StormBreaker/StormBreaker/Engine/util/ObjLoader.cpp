#include "ObjLoader.h"

#include <fstream>
#include "Log.h"

namespace util {
	void LoadOBJ(const char* filePath,
		std::vector<Vertex>& tmpVertices,      // Verts we're assembling
		std::vector<unsigned int>& tmpIndices           // Indices of these verts
	)
	{
		// File input object
		std::ifstream obj(filePath);

		// Check for successful open
		if (!obj.is_open())
		{
			//Use error handler to get details here
			SB_ENGINE_ERROR("ERROR: Invalid path");
			return;
		}

		// Variables used while reading the file
		std::vector<glm::vec3> positions;     // Positions from the file
		std::vector<glm::vec3> normals;       // Normals from the file
		std::vector<glm::vec2> uvs;           // UVs from the file
		unsigned int vertCounter = 0;        // Count of vertices/indices
		char line[100];                     // String for line reading

		glm::vec3 pos;
		glm::vec3 tmpNormals;
		glm::vec2 tmpUV;
		// Still have data left?
		while (obj.good())
		{
			// Get the line (100 characters should be more than enough)
			obj.getline(line, 100);

			// Check the type of line
			if (line[0] == 'v' && line[1] == 'n')
			{
				// Read the 3 numbers directly into an XMFLOAT3

				sscanf_s(
					line,
					"vn %f %f %f",
					&tmpNormals.x, &tmpNormals.y, &tmpNormals.z);

				// Add to the list of normals
				normals.push_back(tmpNormals);
			}
			else if (line[0] == 'v' && line[1] == 't')
			{
				// Read the 2 numbers directly into an XMFLOAT2

				sscanf_s(
					line,
					"vt %f %f",
					&tmpUV.x, &tmpUV.y);

				// Add to the list of uv's
				uvs.push_back(tmpUV);
			}
			else if (line[0] == 'v')
			{
				// Read the 3 numbers directly into an XMFLOAT3

				sscanf_s(
					line,
					"v %f %f %f",
					&pos.x, &pos.y, &pos.z);

				// Add to the positions
				positions.push_back(pos);
			}
			else if (line[0] == 'f')
			{
				// Read the face indices into an array
				unsigned int i[12];
				int facesRead = sscanf_s(
					line,
					"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
					&i[0], &i[1], &i[2],
					&i[3], &i[4], &i[5],
					&i[6], &i[7], &i[8],
					&i[9], &i[10], &i[11]);

				// - Create the verts by looking up
				//    corresponding data from vectors
				// - OBJ File indices are 1-based, so
				//    they need to be adusted
				Vertex v1;
				v1.Position = positions[i[0] - 1];
				v1.TexCoords = uvs[i[1] - 1];
				v1.Normal = normals[i[2] - 1];

				Vertex v2;
				v2.Position = positions[i[3] - 1];
				v2.TexCoords = uvs[i[4] - 1];
				v2.Normal = normals[i[5] - 1];

				Vertex v3;
				v3.Position = positions[i[6] - 1];
				v3.TexCoords = uvs[i[7] - 1];
				v3.Normal = normals[i[8] - 1];

				// The model is most likely in a right-handed space,
				// especially if it came from Maya.  We want to convert
				// to a left-handed space for DirectX.  This means we 
				// need to:
				//  - Invert the Z position
				//  - Invert the normal's Z
				//  - Flip the winding order
				// We also need to flip the UV coordinate since DirectX
				// defines (0,0) as the top left of the texture, and many
				// 3D modeling packages use the bottom left as (0,0)

				//NOT REQURIED FOR OPENGL
				//// Flip the UV's since they're probably "upside down"
				//v1.TexCoords.y = 1.0f - v1.TexCoords.y;
				//v2.TexCoords.y = 1.0f - v2.TexCoords.y;
				//v3.TexCoords.y = 1.0f - v3.TexCoords.y;

				// Flip Z (LH vs. RH)
				//v1.Position.z *= -1.0f;
				//v2.Position.z *= -1.0f;
				//v3.Position.z *= -1.0f;

				//// Flip normal Z
				//v1.Normal.z *= -1.0f;
				//v2.Normal.z *= -1.0f;
				//v3.Normal.z *= -1.0f;

				// Add the verts to the vector (flipping the winding order)
				tmpVertices.push_back(v1);
				tmpVertices.push_back(v3);
				tmpVertices.push_back(v2);

				// Add three more indices
				tmpIndices.push_back(vertCounter); vertCounter += 1;
				tmpIndices.push_back(vertCounter); vertCounter += 1;
				tmpIndices.push_back(vertCounter); vertCounter += 1;

				// Was there a 4th face?
				if (facesRead == 12)
				{
					// Make the last vertex
					Vertex v4;
					v4.Position = positions[i[9] - 1];
					v4.TexCoords = uvs[i[10] - 1];
					v4.Normal = normals[i[11] - 1];

					// Flip the UV, Z pos and normal
					v4.TexCoords.y = 1.0f - v4.TexCoords.y;
					v4.Position.z *= -1.0f;
					v4.Normal.z *= -1.0f;

					// Add a whole triangle (flipping the winding order)
					tmpVertices.push_back(v1);
					tmpVertices.push_back(v4);
					tmpVertices.push_back(v3);

					// Add three more indices
					tmpIndices.push_back(vertCounter); vertCounter += 1;
					tmpIndices.push_back(vertCounter); vertCounter += 1;
					tmpIndices.push_back(vertCounter); vertCounter += 1;
				}
			}
		}

		// Close the file and create the actual buffers
		obj.close();
	}
}