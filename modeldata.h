//=====================================================================
// Copyright 2008 (c), ATI Technologies Inc. All rights reserved.
// Copyright 2016 (c), Advanced Micro Devices, Inc. All rights reserved.
//=====================================================================
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef _MODELDATA_H
#define _MODELDATA_H

#define USE_TOOTLE
#define USE_MESHOPTIMIZER

#include <vector>
#include <string>

#ifdef USE_MESHOPTIMIZER
#include "meshoptimizer.h"
#endif

// Header files, Assimp.
#ifdef USE_ASSIMP
#include <assimp/scene.h>
#endif

#include <stdlib.h>


#ifdef USE_TOOTLE
#// 3D Vector ( for position and normals )
struct ObjVertex3D {
    float x;
    float y;
    float z;
}; // End of ObjVertex3D

// 2D Vector ( for texture coordinates )
struct ObjVertex2D {
    float x;
    float y;
}; // End of ObjVertex2D

//..............................................................................................................//
//..............................................................................................................//
//..............................................................................................................//
// OBJ File structure
//..............................................................................................................//
//..............................................................................................................//
//..............................................................................................................//

// Final Vertex Structure
struct ObjVertexFinal {
    ObjVertexFinal() {
        pos.x = 0.0f;
        pos.y = 0.0f;
        pos.z = 0.0f;

        normal.x = 0.0f;
        normal.y = 0.0f;
        normal.z = 0.0f;

        texCoord.x = 0.0f;
        texCoord.y = 0.0f;
    }; // End of Constructor

    ObjVertex3D pos;
    ObjVertex3D normal;
    ObjVertex2D texCoord;

    // indices of vertex, normal, and texcoord that make up this vertex
    unsigned int nVertexIndex;
    unsigned int nNormalIndex;
    unsigned int nTexcoordIndex;

}; // End of ObjVertexFinal


// Face
struct ObjFace {
    ObjFace() {
        int i;

        for (i = 0; i < 3; i++) {
            vertexIndices[i] = 0;
            texCoordIndices[i] = 0;
            normalIndices[i] = 0;

            finalVertexIndices[i] = 0;
        } // End for
    }; // End of ObjFace

    unsigned int vertexIndices[3];
    unsigned int texCoordIndices[3];
    unsigned int normalIndices[3];

    // This is the index used to for rendering
    unsigned int finalVertexIndices[3];
}; // End of ObjFace
#endif


#ifdef USE_MESHOPTIMIZER
struct Vertex {
    float px, py, pz;
    float nx, ny, nz;
    float tx, ty;
    inline Vertex& operator=(const Vertex& a) {
        px = a.px;
        py = a.py;
        pz = a.pz;
        nx = a.nx;
        ny = a.ny;
        nz = a.nz;
        tx = a.tx;
        ty = a.ty;
        return *this;
    }
};

struct CMP_Mesh {
    std::vector<Vertex>         vertices;
    std::vector<unsigned int>   indices;
};
#endif

class CMODEL_DATA {
  public:
    CMODEL_DATA();
    ~CMODEL_DATA();

    // Model Info
    std::string m_model_name;

    // Basic Model Stats obtained from vertices arround center data
    float m_center[3];      // Vertices center
    float m_width;          // Max Model Width
    float m_height;         // Max Model Height
    float m_length;         // Max Model length
    float m_radius;         // Model Radius
    unsigned long m_LoadTime = 0;

#ifdef USE_MESHOPTIMIZER
    std::vector<CMP_Mesh>        m_meshData;
#endif

#ifdef USE_TOOTLE
    ObjVertex3D min_vertex; // used for bounding box
    ObjVertex3D max_vertex; // used for bounding box
    //the mesh from the model file
    std::vector<ObjVertexFinal> m_objVertices;
    std::vector<ObjFace>        m_objFaces;
#endif

#ifdef USE_ASSIMP
    //pointer to the loaded scene
    const aiScene* m_Scene;
#endif


};

#endif
