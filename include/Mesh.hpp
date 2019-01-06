



#ifndef Mesh_HPP
#define Mesh_HPP

#include "Vertex.hpp"
#include "Orient.hpp"
#include "SpatialInfo.hpp"



#include <vector>

extern const int TEXTURE_NONE;

class Edge {
public :
   Edge(unsigned int from , unsigned int to);
   unsigned int vfrom;
   unsigned int vto;
};
typedef Edge EDGE;


class TriFace {
public :
   TriFace(unsigned int i1 , unsigned int i2 , unsigned int i3);
   TriFace(unsigned int i1 , unsigned int i2 , unsigned int i3 , unsigned int ti1 , unsigned int ti2 , unsigned int ti3);
   unsigned int v1;
   unsigned int v2;
   unsigned int v3;
   unsigned int tv1;
   unsigned int tv2;
   unsigned int tv3;
};
typedef TriFace TRIFACE;

class QuadFace {
   
public :
   QuadFace(unsigned int tl , unsigned int bl , unsigned int br , unsigned int tr);
   QuadFace(unsigned int tl , unsigned int bl , unsigned int br , unsigned int tr,
            unsigned int titl , unsigned int tibl  , unsigned int tibr , unsigned int titr);
   unsigned int vtl;
   unsigned int vbl;
   unsigned int vbr;
   unsigned int vtr;
   unsigned int ttl;
   unsigned int tbl;
   unsigned int tbr;
   unsigned int ttr;
};
typedef QuadFace QUADFACE;



class Mesh {
   
protected :
   std::vector<VERTEX> vertices;
   std::vector<TEXTEX> texverts;

   std::vector<EDGE> edges;
   std::vector<TRIFACE> faces;
   
   unsigned int UnsignedVIndex(int index);
   unsigned int UnsignedTIndex(int index);
   
   ALLEGRO_TRANSFORM SetupTransform(const SpatialInfo& info , Vec3 scale) const;
   
   
public :
   
   public :
   
   unsigned int AddVertex(VERTEX v);
   unsigned int AddTexVertex(TEXTEX t);

   unsigned int AddEdge(int vfrom , int vto);/// returns the absolute index of the new edge
   unsigned int AddTriFace(int v1 , int v2 , int v3);/// returns the absolute index of the new triangle face
   unsigned int AddQuadFace(int vtl , int vbl , int vbr , int vtr);/// returns the absoulte index of the new triangle faces start
   unsigned int AddFlatQuadFace(int vtl , int vbl , int vbr , int vtr);/// returns the absolute index of the new triangle faces start
   
   unsigned int AddTexturedTriFace(int v1 , int v2 , int v3 , int tv1 , int tv2 , int tv3);
   unsigned int AddTexturedQuadFace(int vtl , int vbl , int vbr , int vtr,
                                    int vitl , int vibl , int vibr , int vitr);
   unsigned int AddTexturedFlatQuadFace(int vtl , int vbl , int vbr , int vtr,
                                        int vitl , int vibl , int vibr , int vitr);
   
   
   inline const VERTEX&  GetVertex   (unsigned int index) {return vertices[index];}
   inline const TEXTEX&  GetTexVertex(unsigned int index) {return texverts[index];}
   inline const EDGE&    GetEdge     (unsigned int index) {return edges[index];}
   inline const TRIFACE& GetTriFace  (unsigned int index) {return faces[index];}
   
   
   void RenderFaces     (const SpatialInfo& o , Vec3 scale) const;
   void RenderFacesFront(const SpatialInfo& o , Vec3 scale) const;
   void RenderFacesBack (const SpatialInfo& o , Vec3 scale) const;
   void RenderEdges     (const SpatialInfo& o , Vec3 scale , ALLEGRO_COLOR col) const;

};








#endif // Mesh_HPP
