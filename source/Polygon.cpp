#include "Polygon.h"
#include "BufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include <ostream>
#include <glad.h> 
#include <GLFW/glfw3.h> 
#include <GL/glu.h>
#include <iostream>

Polygon::Polygon(float x1, float y1, bool m_IsFilled)
    : m_AnchorX(x1), m_AnchorY(y1), m_ShapeIsFilled(m_IsFilled), m_IsFinalized(false)
{
    m_Vertices = {
        m_AnchorX, m_AnchorY, 0.0f, 0.0f, 0.0f, 1.0f
    };

    m_Indices = { 0 };

    m_BufferLayout.PushFloat(2); 
    m_BufferLayout.PushFloat(4); 

    m_VertexArray = new VertexArray();
    m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(float), &m_BufferLayout);

    m_IndexBuffer = new IndexBuffer(m_Indices.data(), m_Indices.size());
}

void Polygon::AddPoint(double x, double y)
{
    m_Vertices.push_back((float)x);
    m_Vertices.push_back((float)y);
    m_Vertices.push_back(0.0f);
    m_Vertices.push_back(0.0f);
    m_Vertices.push_back(0.0f);
    m_Vertices.push_back(1.0f);

    m_Indices.push_back(m_Vertices.size() / 6 - 1);

    m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(float), &m_BufferLayout);
    m_IndexBuffer->SetData(m_Indices.data(), m_Indices.size());
}

GLenum Polygon::GetDrawnMode()
{
    return m_ShapeIsFilled ? GL_TRIANGLES : GL_LINE_LOOP;
}

Polygon::~Polygon()
{
    delete m_VertexArray;
    delete m_IndexBuffer;
}

VertexArray& Polygon::GetVAO() const { return *m_VertexArray; }
IndexBuffer& Polygon::GetIBO() const { return *m_IndexBuffer; }

void Polygon::UpdateVertices(double mouseX, double mouseY)
{
    // placeholder
}

void Polygon::AddTessVertex(void* vertex_data)
{
    float* v = (float*)vertex_data;

    m_TessVertices.push_back(v[0]); // x
    m_TessVertices.push_back(v[1]); // y
    m_TessVertices.push_back(v[2]); // r
    m_TessVertices.push_back(v[3]); // g
    m_TessVertices.push_back(v[4]); // b
    m_TessVertices.push_back(v[5]); // a

    m_TessIndices.push_back(m_TessVertices.size() / 6 - 1);
}

// ------------------------------------------------------------
// Tesselator callbacks (GLU)
// ------------------------------------------------------------
static void  tess_begin_callback(GLenum type, void* polygon_data)
{
    std::cout << "Tesselator: Starting mode" << type << std::endl;
}

static void  tess_vertex_callback(void* vertex_data, void* polygon_data)
{
    Polygon* self = (Polygon*)polygon_data;
    if (self) self->AddTessVertex(vertex_data);
}

static void  tess_end_callback(void* polygon_data)
{
    std::cout << "Tesselator: End of outline" << std::endl;
}

static void  tess_error_callback(GLenum errorCode, void* polygon_data)
{
    std::cerr << "Erro on Tesselator: " << gluErrorString(errorCode) << std::endl;
}

void Polygon::FinalizeShape()
{
    if (m_Vertices.size() / 6 < 3)
        return; 

    GLUtesselator* tess = gluNewTess();
    if (!tess) {
        std::cerr << "Failed to create the GLU Tesselator" << std::endl;
        return;
    }

    gluTessCallback(tess, GLU_TESS_BEGIN_DATA, (void(*)())tess_begin_callback);
    gluTessCallback(tess, GLU_TESS_VERTEX_DATA, (void(*)())tess_vertex_callback);
    gluTessCallback(tess, GLU_TESS_END_DATA, (void(*)())tess_end_callback);
    gluTessCallback(tess, GLU_TESS_ERROR_DATA, (void(*)())tess_error_callback);

    gluTessBeginPolygon(tess, this);
    gluTessBeginContour(tess);

    int numVertices = m_Vertices.size() / 6;
    std::vector<GLdouble> pos_data(numVertices * 3);

    for (int i = 0; i < numVertices; i++) {
        pos_data[i * 3 + 0] = m_Vertices[i * 6 + 0]; // x
        pos_data[i * 3 + 1] = m_Vertices[i * 6 + 1]; // y
        pos_data[i * 3 + 2] = 0.0;                   // z (2D)

        gluTessVertex(tess, &pos_data[i * 3], (void*)(m_Vertices.data() + (i * 6)));
    }

    gluTessEndContour(tess);
    gluTessEndPolygon(tess);

    m_Vertices = m_TessVertices;
    m_Indices = m_TessIndices;

    m_VertexArray->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(float), &m_BufferLayout);
    m_IndexBuffer->SetData(m_Indices.data(), m_Indices.size());

    gluDeleteTess(tess);

    m_IsFinalized = true;
}
