void Model::Draw(unsigned int *shaderProgram)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw(shader);
    }
}

Model::Model(char *path)
{

}

void Model::loadModel(string path)
{
    Assimp::Importer import;

    // this is the scene object. It is the assimp interface to the data contained in the model. 
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    // some error occured while importing
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }

    directory = path.substr(0, path.find_last_of("/"));

    processNode(scene->mRootNode, scene);
}

// recursive function to process all the nodes of the graph
void Model::processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the values in the mMeshes array of each node contains indices into the mMeshes array of the scene which contains the actual pointers to the mesh objects (the aiMesh)
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];

        // once we have the pointer to the mesh, we process it, and it to the class variable meshes, which stores all the processed meshes
        meshes.push_back(processMesh(mesh, scene));
    }

    // we then recursively call the same function for all the children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, aiScene *scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
        {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    if (mesh->mMaterialIndex > 0)
    {
        
    }

    return Mesh(vertices, indices, textures);
}

