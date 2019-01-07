



#include "Mesh.hpp"

#include "allegro5/allegro_opengl.h"
#include "GL/gl.h"


const int TEXTURE_NONE = -1;///0xFFFFFFFF;
const unsigned int BAD_TEXTURE = (unsigned int)TEXTURE_NONE;


Edge::Edge(unsigned int from , unsigned int to) :
      vfrom(from),
      vto(to)
{}




TriFace::TriFace(unsigned int i1 , unsigned int i2 , unsigned int i3) :
      v1(i1),
      v2(i2),
      v3(i3),
      tv1(BAD_TEXTURE),
      tv2(BAD_TEXTURE),
      tv3(BAD_TEXTURE)
{}



TriFace::TriFace(unsigned int i1 , unsigned int i2 , unsigned int i3 , unsigned int ti1 , unsigned int ti2 , unsigned int ti3) :
      v1(i1),
      v2(i2),
      v3(i3),
      tv1(ti1),
      tv2(ti2),
      tv3(ti3)
{}



bool TriFace::Textured() const {
   return ((tv1 != BAD_TEXTURE) && (tv2 != BAD_TEXTURE) && (tv3 != BAD_TEXTURE));
}




unsigned int Mesh::UnsignedVIndex(int index) {
   if (index < 0) {
      index = (int)vertices.size() - index;
   }
   unsigned int uidx = index;
   assert(uidx <= vertices.size());
   return uidx;
}



unsigned int Mesh::UnsignedTIndex(int index) {
   if (index < 0) {
      index = (int)texverts.size() - index;
   }
   unsigned int uidx = index;
   assert(uidx <= texverts.size());
   return uidx;
}



ALLEGRO_TRANSFORM Mesh::SetupTransform(const SpatialInfo& info , Vec3 scale) const {
   const ALLEGRO_TRANSFORM old = *al_get_current_transform();
   
///   al_translate_transform_3d(&t , -c.x , -c.y , -c.z);/// we are already at 0,0,0, all models are centered there
   const Vec3& c = info.pos;
   const Orient& o = info.orient;
   const Vec3& theta = o.Theta();

   ALLEGRO_TRANSFORM t;/// = old;
   ALLEGRO_TRANSFORM m;

   
   float ux = UP.x;
   float uy = UP.y;
   float uz = UP.z;
   float rx = RIGHT.x;
   float ry = RIGHT.y;
   float rz = RIGHT.z;
   float fx = FORWARD.x;
   float fy = FORWARD.y;
   float fz = FORWARD.z;

   al_identity_transform(&t);
///   t = old;
   
   al_identity_transform(&m);
   al_rotate_transform_3d(&m , ux , uy , uz , theta.yaw);
   al_transform_coordinates_3d(&m , &fx , &fy , &fz);
   al_transform_coordinates_3d(&m , &rx , &ry , &rz);
   
   al_compose_transform(&t , &m);
   
   al_identity_transform(&m);
   al_rotate_transform_3d(&m , rx , ry , rz , theta.pitch);
   al_transform_coordinates_3d(&m , &fx , &fy , &fz);
   al_transform_coordinates_3d(&m , &ux , &uy , &uz);
   
   al_compose_transform(&t , &m);

   al_identity_transform(&m);
   al_rotate_transform_3d(&m , fx , fy , fz , theta.roll);
   al_transform_coordinates_3d(&m , &rx , &ry , &rz);
   al_transform_coordinates_3d(&m , &ux , &uy , &uz);
   
   al_compose_transform(&t , &m);

   al_scale_transform_3d(&t , scale.x , scale.y , scale.z);
   al_translate_transform_3d(&t , c.x , c.y , c.z);
   
   al_compose_transform(&t , &old);
   
   al_use_transform(&t);
   
   return old;
}



unsigned int Mesh::AddVertex(VERTEX v) {
   vertices.push_back(v);
   return vertices.size() - 1;
}



unsigned int Mesh::AddTexVertex(TEXTEX t) {
   texverts.push_back(t);
   return texverts.size() - 1;
}



unsigned int Mesh::AddEdge(int vfrom , int vto) {
   edges.push_back(EDGE(UnsignedVIndex(vfrom) , UnsignedVIndex(vto)));
   return edges.size() - 1;
}



unsigned int Mesh::AddTriFace(int v1 , int v2 , int v3) {
   faces.push_back(TRIFACE(UnsignedVIndex(v1) , UnsignedVIndex(v2) , UnsignedVIndex(v3) ));
   return faces.size() - 1;
}



/// Returns the index of the first of the four faces added by this function, also adds a new vertice
unsigned int Mesh::AddQuadFace(int vtl , int vbl , int vbr , int vtr) {
   
   /// A quad is made up of two or more triangles - we'll use 4 based on the center, so it creates a pyramid
   const unsigned int tl = UnsignedVIndex(vtl);
   const unsigned int bl = UnsignedVIndex(vbl);
   const unsigned int br = UnsignedVIndex(vbr);
   const unsigned int tr = UnsignedVIndex(vtr);

   VERTEX center(MidPoint(MidPoint(GetVertex(tl).pos , GetVertex(tr).pos) , MidPoint(GetVertex(bl).pos , GetVertex(br).pos)));
   
   const unsigned int c = AddVertex(center);

   const unsigned int f1 = AddTriFace(c,tl,bl);
   const unsigned int f2 = AddTriFace(c,bl,br);
   const unsigned int f3 = AddTriFace(c,br,tr);
   const unsigned int f4 = AddTriFace(c,tr,tl);
   
   (void)f2;
   (void)f3;
   (void)f4;
   
   return f1;
}



/// Returns the index of the first of the two faces added by this function, also adds a new vertice
unsigned int Mesh::AddFlatQuadFace(int vtl , int vbl , int vbr , int vtr) {
   
   /// A quad is made up of two or more triangles - we'll use 4 based on the center, so it creates a pyramid
   const unsigned int tl = UnsignedVIndex(vtl);
   const unsigned int bl = UnsignedVIndex(vbl);
   const unsigned int br = UnsignedVIndex(vbr);
   const unsigned int tr = UnsignedVIndex(vtr);

   const unsigned int f1 = AddTriFace(tl,bl,br);
   const unsigned int f2 = AddTriFace(br,tr,tl);
   
   (void)f2;
   
   return f1;
}



unsigned int Mesh::AddTexturedTriFace(int v1 , int v2 , int v3 ,
                                int tv1 , int tv2 , int tv3) {
   
   faces.push_back(TRIFACE(UnsignedVIndex(v1) , UnsignedVIndex(v2) , UnsignedVIndex(v3) ,
                           UnsignedTIndex(tv1) , UnsignedTIndex(tv2) , UnsignedTIndex(tv3)));
   return faces.size() - 1;
}



unsigned int Mesh::AddTexturedQuadFace(int vtl , int vbl , int vbr , int vtr,
                                 int ttl , int tbl , int tbr , int ttr) {
   
   
   
   /// A quad is made up of two or more triangles - we'll use 4 based on the center, so it creates a pyramid
   const unsigned int tl = UnsignedVIndex(vtl);
   const unsigned int bl = UnsignedVIndex(vbl);
   const unsigned int br = UnsignedVIndex(vbr);
   const unsigned int tr = UnsignedVIndex(vtr);

   VERTEX center(MidPoint(MidPoint(GetVertex(tl).pos , GetVertex(tr).pos) , MidPoint(GetVertex(bl).pos , GetVertex(br).pos)));
   
   const unsigned int c = AddVertex(center);

   const unsigned int textl = UnsignedTIndex(ttl);
   const unsigned int texbl = UnsignedTIndex(tbl);
   const unsigned int texbr = UnsignedTIndex(tbr);
   const unsigned int textr = UnsignedTIndex(ttr);

   Vec2 texcenter(MidPoint(MidPoint(GetTexVertex(textl).uv , GetTexVertex(textr).uv) , MidPoint(GetTexVertex(texbl).uv , GetTexVertex(texbr).uv)));

   const unsigned int ctex = AddTexVertex(TEXTEX(GetTexVertex(textl).bmp , texcenter));
   
   const unsigned int f1 = AddTexturedTriFace(c,tl,bl , ctex , textl , texbl);
   const unsigned int f2 = AddTexturedTriFace(c,bl,br , ctex , texbl , texbr);
   const unsigned int f3 = AddTexturedTriFace(c,br,tr , ctex , texbr , textr);
   const unsigned int f4 = AddTexturedTriFace(c,tr,tl , ctex , textr , textl);
   
   (void)f2;
   (void)f3;
   (void)f4;
   
   return f1;
}



unsigned int Mesh::AddTexturedFlatQuadFace(int vtl , int vbl , int vbr , int vtr,
                                     int ttl , int tbl , int tbr , int ttr) {
   
   const unsigned int tl = UnsignedVIndex(vtl);
   const unsigned int bl = UnsignedVIndex(vbl);
   const unsigned int br = UnsignedVIndex(vbr);
   const unsigned int tr = UnsignedVIndex(vtr);

   const unsigned int textl = UnsignedTIndex(ttl);
   const unsigned int texbl = UnsignedTIndex(tbl);
   const unsigned int texbr = UnsignedTIndex(tbr);
   const unsigned int textr = UnsignedTIndex(ttr);

   const unsigned int f1 = AddTexturedTriFace(tl,bl,br , textl , texbl , texbr);
   const unsigned int f2 = AddTexturedTriFace(br,tr,tl , texbr , textr , textl);
   
   (void)f2;
   
   return f1;
}



void Mesh::RenderFaces(const SpatialInfo& info , Vec3 scale) const {
   glColor4d(1.0 , 1.0 , 1.0 , 1.0);
   RenderFacesFront(info , scale);
///   RenderFacesBack(info , scale);
///   RenderEdges(info , scale , al_map_rgba(0,127,0,255));
}



void Mesh::RenderFacesFront(const SpatialInfo& info , Vec3 scale) const {
   
   ALLEGRO_TRANSFORM old = SetupTransform(info , scale);
//      glEnable(GL_COLOR);
   for (unsigned int f = 0 ; f < faces.size() ; ++f) {
      const TRIFACE& face = faces[f];
      const VERTEX* v[3] = {&vertices[face.v1] , &vertices[face.v2] , &vertices[face.v3]};
      
      const unsigned int texfaces[3] = {face.tv1 , face.tv2 , face.tv3};
      
      bool textured = face.Textured();
      if (textured) {
         ALLEGRO_BITMAP* bmp = texverts[face.tv1].bmp;
         assert(bmp);
         GLuint texid = al_get_opengl_texture(bmp);
         glBindTexture(GL_TEXTURE_2D , texid);
      }
      
   glBegin(GL_TRIANGLES);
      for (unsigned int i = 0 ; i < 3 ; ++i) {
         unsigned char c[4] = {0};
         al_unmap_rgba(v[i]->col , &c[0] , &c[1] , &c[2] , &c[3]);
         glColor4ub(c[0] , c[1] , c[2] , c[3]);
         if (textured) {
            glTexCoord2d(texverts[texfaces[i]].uv.u , texverts[texfaces[i]].uv.v);
         }
         glVertex3d(v[i]->pos.x , v[i]->pos.y , v[i]->pos.z);
///         glNormal3d(v[i].nml.x , v[i].nml.y , v[i].nml.z);
      }
   glEnd();
   }

   al_use_transform(&old);
}



void Mesh::RenderFacesBack(const SpatialInfo& info , Vec3 scale) const {
   
   ALLEGRO_TRANSFORM old = SetupTransform(info , scale);
//      glEnable(GL_COLOR);
   glBegin(GL_TRIANGLES);
   for (unsigned int f = 0 ; f < faces.size() ; ++f) {
      const TRIFACE& face = faces[f];
      const VERTEX* v[3] = {&vertices[face.v3] , &vertices[face.v2] , &vertices[face.v1]};
      
      for (unsigned int i = 0 ; i < 3 ; ++i) {
         unsigned char c[4] = {0};
         al_unmap_rgba(v[i]->col , &c[0] , &c[1] , &c[2] , &c[3]);
         glColor4ub(c[0] , c[1] , c[2] , c[3]);
         glVertex3d(v[i]->pos.x , v[i]->pos.y , v[i]->pos.z);
///         glNormal3d(v[i].nml.x , v[i].nml.y , v[i].nml.z);
      }
   }
   glEnd();

   al_use_transform(&old);
}



void Mesh::RenderEdges(const SpatialInfo& info , Vec3 scale , ALLEGRO_COLOR col) const {

   ALLEGRO_TRANSFORM old = SetupTransform(info , scale);
   
   unsigned char rgba[4];
   al_unmap_rgba(col , &rgba[0] , &rgba[1] , &rgba[2] , &rgba[3]);
//      glEnable(GL_COLOR);
   glBegin(GL_LINES);
   glColor4ub(rgba[0] , rgba[1] , rgba[2] , rgba[3]);
   for (unsigned int e = 0 ; e < edges.size() ; ++e) {
      const EDGE& edge = edges[e];
      const VERTEX& v1 = vertices[edge.vfrom];
      const VERTEX& v2 = vertices[edge.vto];
      glVertex3d(v1.pos.x , v1.pos.y , v1.pos.z);
      glVertex3d(v2.pos.x , v2.pos.y , v2.pos.z);
   }
   glEnd();
   
   al_use_transform(&old);
}



void Mesh::ClearAll() {
   vertices.clear();
   texverts.clear();
   edges.clear();
   faces.clear();
}

