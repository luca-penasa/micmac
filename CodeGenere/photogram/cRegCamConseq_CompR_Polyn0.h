// File Automatically generated by eLiSe
#include "StdAfx.h"


class cRegCamConseq_CompR_Polyn0: public cElCompiledFonc
{
   public :

      cRegCamConseq_CompR_Polyn0();
      void ComputeVal();
      void ComputeValDeriv();
      void ComputeValDerivHessian();
      double * AdrVarLocFromString(const std::string &);
      void SetRay_x(double);
      void SetRay_y(double);
      void SetRay_z(double);


      static cAutoAddEntry  mTheAuto;
      static cElCompiledFonc *  Alloc();
   private :

      double mLocRay_x;
      double mLocRay_y;
      double mLocRay_z;
};