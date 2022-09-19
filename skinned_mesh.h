/*

    Copyright 2021 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SKINNED_MESH_H
#define SKINNED_MESH_H

#include <map>
#include <vector>
#include <iostream>
#include <GL/glew.h>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags

#include "ogldev/ogldev_util.h"
#include "ogldev/ogldev_math_3d.h"
#include "ogldev/ogldev_texture.h"
#include "ogldev/ogldev_world_transform.h"
#include "ogldev/ogldev_material.h"

class SkinnedMesh
{
public:
    SkinnedMesh() {
        //m_BoneNameToIndexMap["A_Origin"]=0;
    };

    ~SkinnedMesh();

    bool LoadMesh(const std::string& Filename);

    void Render();

    uint NumBones() const
    {
        return (uint)m_BoneNameToIndexMap.size();
    }

    WorldTrans& GetWorldTransform() { return m_worldTransform; }

    const Material& GetMaterial();

    void GetBoneTransforms(float AnimationTimeSec, vector<Matrix4f>& Transforms);

private:
    #define MAX_NUM_BONES_PER_VERTEX 4

    void Clear();

    bool InitFromScene(const aiScene* pScene, const std::string& Filename);

    void CountVerticesAndIndices(const aiScene* pScene, unsigned int& NumVertices, unsigned int& NumIndices);

    void ReserveSpace(unsigned int NumVertices, unsigned int NumIndices);

    void InitAllMeshes(const aiScene* pScene);

    void InitSingleMesh(uint MeshIndex, const aiMesh* paiMesh);

    bool InitMaterials(const aiScene* pScene, const std::string& Filename);

    void PopulateBuffers();

    void LoadTextures(const string& Dir, const aiMaterial* pMaterial, int index);

    void LoadDiffuseTexture(const string& Dir, const aiMaterial* pMaterial, int index);

    void LoadSpecularTexture(const string& Dir, const aiMaterial* pMaterial, int index);

    void LoadColors(const aiMaterial* pMaterial, int index);

    struct VertexBoneData
    {
        uint BoneIDs[MAX_NUM_BONES_PER_VERTEX] = { 0 };
        float Weights[MAX_NUM_BONES_PER_VERTEX] = { 0.0f };

        VertexBoneData()
        {
        }

        void AddBoneData(uint BoneID, float Weight)
        {
            for (uint i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(BoneIDs) ; i++) {
                if(BoneIDs[i] == BoneID){return;}
                if (Weights[i] == 0.0) {
                    BoneIDs[i] = BoneID;
                    Weights[i] = Weight;
                    //printf("Adding bone %d weight %f at index %i\n", BoneID, Weight, i);
                    return;
                }
            }

            // should never get here - more bones than we have space for
            assert(0);
        }
    };

    void LoadMeshBones(uint MeshIndex, const aiMesh* paiMesh);
    void LoadSingleBone(uint MeshIndex, const aiBone* pBone);
    int GetBoneId(const aiBone* pBone);
    void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    uint FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
    uint FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
    uint FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
    const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string& NodeName);
    void ReadNodeHierarchy(float AnimationTime, const aiNode* pNode, const Matrix4f& ParentTransform);

#define INVALID_MATERIAL 0xFFFFFFFF

    enum BUFFER_TYPE {
        INDEX_BUFFER = 0,
        POS_VB       = 1,
        TEXCOORD_VB  = 2,
        NORMAL_VB    = 3,
        BONE_VB      = 4,
        NUM_BUFFERS  = 5
    };

    WorldTrans m_worldTransform;
    GLuint m_VAO = 0;
    GLuint m_Buffers[NUM_BUFFERS] = { 0 };

    struct BasicMeshEntry {
        BasicMeshEntry()
        {
            NumIndices = 0;
            BaseVertex = 0;
            BaseIndex = 0;
            MaterialIndex = INVALID_MATERIAL;
        }

        unsigned int NumIndices;
        unsigned int BaseVertex;
        unsigned int BaseIndex;
        unsigned int MaterialIndex;
    };

    Assimp::Importer Importer;
    const aiScene* pScene = NULL;
    std::vector<BasicMeshEntry> m_Meshes;
    std::vector<Material> m_Materials;

    // Temporary space for vertex stuff before we load them into the GPU
    vector<Vector3f> m_Positions;
    vector<Vector3f> m_Normals;
    vector<Vector2f> m_TexCoords;
    vector<unsigned int> m_Indices;
    vector<VertexBoneData> m_Bones;

    map<string,uint> m_BoneNameToIndexMap;


    struct BoneInfo
    {
        Matrix4f OffsetMatrix;
        Matrix4f FinalTransformation;

        BoneInfo(const Matrix4f& Offset)
        {
            OffsetMatrix = Offset;
            FinalTransformation.SetZero();
        }
    };

    vector<BoneInfo> m_BoneInfo;
    Matrix4f m_GlobalInverseTransform;

public:
    void printBoneMap(){
        for (auto const &pair: m_BoneNameToIndexMap) {
            std::cout << "{" << pair.first << ": " << pair.second << "}\n";
        }
    }
};


#endif  /* SKINNED_MESH_H */
