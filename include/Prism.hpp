



#ifndef Prism_HPP
#define Prism_HPP



#include "Vec3.hpp"


#include "Mesh.hpp"



class UnitCube {
   Mesh cube;
   
   unsigned int FACE_LEFT;
   unsigned int FACE_RIGHT;
   unsigned int FACE_TOP;
   unsigned int FACE_BOTTOM;
   unsigned int FACE_FRONT;
   unsigned int FACE_BACK;


//   void CreateMesh();
   void CreateMesh() {
      
      /// A cube has 8 vertices
      ALLEGRO_COLOR white = al_map_rgb(255,255,255);
      
      const unsigned int LBB = cube.AddVertex(VERTEX(Vec3(-0.5 , -0.5 ,  0.5) , white)); 
      const unsigned int LBF = cube.AddVertex(VERTEX(Vec3(-0.5 , -0.5 , -0.5) , white)); 
      const unsigned int LTF = cube.AddVertex(VERTEX(Vec3(-0.5 ,  0.5 , -0.5) , white)); 
      const unsigned int LTB = cube.AddVertex(VERTEX(Vec3(-0.5 ,  0.5 ,  0.5) , white)); 
      const unsigned int RBB = cube.AddVertex(VERTEX(Vec3( 0.5 , -0.5 ,  0.5) , white)); 
      const unsigned int RBF = cube.AddVertex(VERTEX(Vec3( 0.5 , -0.5 , -0.5) , white)); 
      const unsigned int RTF = cube.AddVertex(VERTEX(Vec3( 0.5 ,  0.5 , -0.5) , white)); 
      const unsigned int RTB = cube.AddVertex(VERTEX(Vec3( 0.5 ,  0.5 ,  0.5) , white)); 
      
      /// A cube has 12 edges

      /// left edges
      cube.AddEdge(LBB , LBF);
      cube.AddEdge(LBF , LTF);
      cube.AddEdge(LTF , LTB);
      cube.AddEdge(LTB , LBB);
      
      /// Right edges
      cube.AddEdge(RBB , RBF);
      cube.AddEdge(RBF , RTF);
      cube.AddEdge(RTF , RTB);
      cube.AddEdge(RTB , RBB);

      /// Cross edges
      cube.AddEdge(LBB , RBB);
      cube.AddEdge(LBF , RBF);
      cube.AddEdge(LTF , RTF);
      cube.AddEdge(LTB , RTB);
      
      /// A cube has six faces
      
      /// Left side
      cube.AddFlatQuadFace(LTB , LBB , LBF , LTF);
      
      /// Right side
      cube.AddFlatQuadFace(RTF , RBF , RBB , RTB);
      
      /// Front side
      cube.AddFlatQuadFace(LTF , LBF , RBF , RTF);

      /// Back side
      cube.AddFlatQuadFace(RTB , RBB , LBB , LTB);
      
      /// Top side
      cube.AddFlatQuadFace(LTB , LTF , RTF , RTB);
      
      /// Bottom side
      cube.AddFlatQuadFace(LBF , LBB , RBB , RBF);
   }
   
public :
//   UnitCube();
   UnitCube() :
         cube()
   {
      CreateMesh();
   }
};




class Prism {
   
   Vec3 tlb;
   double w;
   double h;
   double d;
   
public :
   
   Prism() : tlb() , w(1) , h(1) , d(1) {
      SetCenter(Vec3(0,0,0));
   }
   
   Prism(Vec3 center , double width , double height , double depth) : tlb() , w(abs(width)) , h(abs(height)) , d(abs(depth)) {
      SetCenter(center);
   }
   
   inline double Width()  {return w;}
   inline double Height() {return h;}
   inline double Depth()  {return d;}
   
   inline double LeftX()  const {return tlb.x;    }
   inline double RightX() const {return tlb.x + w;}
   inline double TopY()   const {return tlb.y;    }
   inline double BotY()   const {return tlb.y - h;}
   inline double BackZ()  const {return tlb.z;    }
   inline double FrontZ() const {return tlb.z - d;}
   
   inline Vec3 TopLeftBack()   const {return Vec3(LeftX()  , TopY() , BackZ()  );}
   inline Vec3 TopLeftFront()  const {return Vec3(LeftX()  , TopY() , FrontZ() );}
   inline Vec3 TopRightBack()  const {return Vec3(RightX() , TopY() , BackZ()  );}
   inline Vec3 TopRightFront() const {return Vec3(RightX() , TopY() , FrontZ() );}
   inline Vec3 BotLeftBack()   const {return Vec3(LeftX()  , BotY() , BackZ()  );}
   inline Vec3 BotLeftFront()  const {return Vec3(LeftX()  , BotY() , FrontZ() );}
   inline Vec3 BotRightBack()  const {return Vec3(RightX() , BotY() , BackZ()  );}
   inline Vec3 BotRightFront() const {return Vec3(RightX() , BotY() , FrontZ() );}
   
   inline void SetCenter(Vec3 c) {tlb = Vec3(c.x - w/2.0 , c.y + h/2.0 , c.z + d/2.0);}
   inline Vec3 Center() const {return Vec3(tlb.x + w/2.0 , tlb.y - h/2.0 , tlb.z - d/2.0);}
};

#endif // Prism_HPP
