#include "Model.h"

namespace Photon {
	Model::Model(const std::string& path, glm::vec3 pos) : Entity(pos)
	{
		Init();
		loadModel(path);

		m_model = glm::mat4(1.0);
		int global_width = PhotonApplication::instance->GetConfig().width;
		int global_height = PhotonApplication::instance->GetConfig().height;

		float position_final_x = map(m_position.x, 0, global_width, -1, 1);
		float position_final_y = map(m_position.y, 0, global_height, -1, 1);
		m_position.x = position_final_x;
		m_position.y = position_final_y;
		m_model = glm::scale(glm::vec3(0.5f, 0.5f, 0.5f));
		m_model = glm::translate(m_model, m_position);
		//m_model = glm::scale(m_model, glm::vec3(1.0f, 1.0f, 1.0f));

		m_shader = new Shader("basic_model.vert", "basic_model_texture.frag");
		m_shader->Activate();
		m_shader->SetUniformMat4("model", m_model);
		m_shader->SetUniform4f("objectColor", 0.8f, 0.8f, 0.8f, 1);
	}

	void Photon::Model::Draw()
	{
		m_shader->Activate();
		
		if (m_target_camera != nullptr)
		{
			m_target_camera->SetUniform(*m_shader, "camMatrix");
		}
		m_shader->SetUniformMat4("model", m_model);
		for (int i = 0; i < m_meshes.size(); ++i)
		{
			m_meshes[i].Draw(*m_shader);
		}
	}

	void Photon::Model::loadModel(const std::string& path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		std::cout << "Scene mesh num:  " << scene->mNumMeshes << std::endl;
		// check for errors
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return;
		}

		// retrieve the m_directory path of the filepath for loading texture
		m_directory = path.substr(0, path.find_last_of('\\'));

		processScene(scene);
	}
	void Model::processScene(const aiScene* scene)
	{
		std::cout << scene->mNumMeshes << std::endl;

		for (unsigned int i = 0; i < scene->mNumMeshes; i++) 
		{
			aiMesh* mesh = scene->mMeshes[i];
			std::cout << "Processing mesh: " << mesh->mName.C_Str() << std::endl;
			m_meshes.emplace_back(processMesh(mesh, scene));
		}

		//// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
		//for (unsigned int i = 0; i < node->mNumChildren; i++)
		//{
		//	processNode(node->mChildren[i], scene);
		//}
	}
	Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<TextureData> textures;

		vertices.reserve(mesh->mNumVertices);

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector; 

			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;
			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.normal = vector;
			}

			// texture coordinates
			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.tex_coord = vec;

				// tangent
				vector.x = mesh->mTangents[i].x;
				vector.y = mesh->mTangents[i].y;
				vector.z = mesh->mTangents[i].z;
				vertex.tangent = vector;

				// bitangent
				vector.x = mesh->mBitangents[i].x;
				vector.y = mesh->mBitangents[i].y;
				vector.z = mesh->mBitangents[i].z;
				vertex.bitangent = vector;
			}
			else
				vertex.tex_coord = glm::vec2(0.0f, 0.0f);

			vertices.emplace_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++) 
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++) 
			{
				indices.emplace_back(face.mIndices[j]);
			}
		}

		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<TextureData> diffuse_maps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());

		std::vector<TextureData> specular_maps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());

		std::vector<TextureData> normal_maps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
		textures.insert(textures.end(), normal_maps.begin(), normal_maps.end());

		std::vector<TextureData> height_maps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
		textures.insert(textures.end(), height_maps.begin(), height_maps.end());
		std::cout << "Vertices size: " << vertices.size() << std::endl;
		std::cout << "Indices size: " << indices.size() << std::endl;
		return Mesh(vertices, indices, textures);
	}
	unsigned int Model::LoadTextureFromFile(const char* path, const std::string& m_directory)
	{
		std::string filename = std::string(path);
		filename = m_directory + '/' + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		//define width, height and color channel for the texture, and load the texture
		int widthImg, heightImg, numofColorChannel;
		//Flip the image vertically when loaded
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filename.c_str(), &widthImg, &heightImg, &numofColorChannel, 0);

		if (data) 
		{
			GLenum format = GL_RGBA;
			if (numofColorChannel == 1)
				format = GL_RED;
			else if (numofColorChannel == 3)
				format = GL_RGB;
			else if (numofColorChannel == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, widthImg, heightImg, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Load texture: " << filename << " failed.\n";
		}

		return textureID;
	}
	std::vector<TextureData> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string type_name)
	{
		std::vector<TextureData> textures;
		for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
		{
			aiString str;
			material->GetTexture(type, i, &str);
			// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
			bool skip = false;
			for (unsigned int j = 0; j < m_texture_loaded.size(); j++)
			{
				if (std::strcmp(m_texture_loaded[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(m_texture_loaded[j]);
					skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
					break;
				}
			}
			if (!skip)
			{   // if texture hasn't been loaded already, load it
				TextureData texture;
				texture.id = LoadTextureFromFile(str.C_Str(), m_directory);
				texture.type = type_name;
				texture.path = str.C_Str();
				textures.push_back(texture);
				m_texture_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
			}
		}
		return textures;
	}
}