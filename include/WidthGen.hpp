



#ifndef WidthGen_HPP
#define WidthGen_HPP

class WidthGeneratorBase {
   
public :   
   virtual double EvalWidth(double pct)=0;
};

class WidthGenerator {
protected :
   std::shared_ptr<WidthGeneratorBase> genptr;
   
public :
   WidthGenerator(WidthGeneratorBase* pwgen) : genptr(pwgen) {}
   
   double EvalWidth(double pct) {return genptr->EvalWidth(pct);}
};

#endif // WidthGen_HPP
