#ifndef ___MODEL
#define ___MODEL

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <string>
#include "mesh.h"
using namespace std;

class Model {
    private:
        vector<Mesh> meshes;
        string directory;
        vector<Texture> textures_loaded;
        void loadModel(string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typename);
    public:
        Model(char *path);
        void Draw(unsigned int *shaderProgram);
};

#endif