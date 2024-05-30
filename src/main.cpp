#include <iostream>
#include <iomanip>

namespace qmcad{
  namespace Pade2ndOrderFunctor {
    int enzyme_dup;
    int enzyme_dupnoneed;
    int enzyme_out;
    int enzyme_const;

    template<typename RT, typename... Args>
    RT __enzyme_autodiff(void*, Args...);

    using real_type = double;

    inline real_type Pade2ndOrderFunctor_evaluate(real_type r, real_type A, real_type B, real_type C){
      real_type u = 1.0 / (1.0 + B * r);
      real_type v = A * r + C * r * r;
      return u * v;
    }

    inline real_type Pade2ndOrderFunctor_evaluate_dudr_analytical(real_type r, real_type A, real_type B, real_type C){
      real_type C2 = 2.0 * C;
      real_type u = 1.0 / (1.0 + B * r);
      real_type v = A * r + C * r * r;
      real_type w = A + C2 * r;
      real_type dudr        = u * (w - B * u * v);
      real_type d2udr2      = 2.0 * u * u * u * (C - B * A);
      return dudr;
    }

    inline real_type Pade2ndOrderFunctor_evaluate_dudr(real_type r, real_type A, real_type B, real_type C){
      return __enzyme_autodiff<real_type>((void*)Pade2ndOrderFunctor_evaluate,
          r,
          A,
          B,
          C        ); }

    inline real_type Pade2ndOrderFunctor_evaluate_d2udr2_analytical(real_type r, real_type A, real_type B, real_type C){
      real_type C2 = 2.0 * C;
      real_type u = 1.0 / (1.0 + B * r);
      real_type v = A * r + C * r * r;
      real_type w = A + C2 * r;
      real_type dudr        = u * (w - B * u * v);
      real_type d2udr2      = 2.0 * u * u * u * (C - B * A);
      return d2udr2;
    }

    inline real_type Pade2ndOrderFunctor_evaluate_d2udr2(real_type r, real_type A, real_type B, real_type C ){

     return __enzyme_autodiff<real_type>((void*)Pade2ndOrderFunctor_evaluate_dudr,
      r,
      A,
      B,
      C);
    }
  }

  namespace PadeTwo2ndOrderFunctor {

    int enzyme_dup;
    int enzyme_dupnoneed;
    int enzyme_out;
    int enzyme_const;

    template<typename RT, typename... Args>
    RT __enzyme_autodiff(void*, Args...);

    using real_type = double;

    inline real_type PadeTwo2ndOrderFunctor_evaluate(real_type r, real_type A, real_type B, real_type C, real_type D){
      real_type br(B * r);
      real_type dr(D * r);
      return (A * r + br * r) / (1.0 + C * C * r + dr * dr);
    }

    inline real_type PadeTwo2ndOrderFunctor_evaluate_dudr_analytical(real_type r, real_type A, real_type B, real_type C, real_type D){
      real_type ar(A * r);
      real_type br(B * r);
      real_type cr(C * r);
      real_type dr(D * r);
      real_type bttm(1.0 / (1.0 + C * cr + dr * dr));
      real_type dudr   = (A - A * dr * dr + br * (2.0 + C * cr)) * bttm * bttm;
      real_type d2udr2 = -2.0 * (A * (C * C + 3.0 * dr * D - dr * dr * dr * D) + B * (-1.0 + dr * dr * (3.0 + C * cr))) * bttm *
          bttm * bttm;
      return dudr;
    }


    inline real_type PadeTwo2ndOrderFunctor_evaluate_dudr(real_type r, real_type A, real_type B, real_type C, real_type D){
      return __enzyme_autodiff<real_type>((void*)PadeTwo2ndOrderFunctor_evaluate,
          r,
           A,
           B,
           C,
           D ); }
    
    inline real_type PadeTwo2ndOrderFunctor_evaluate_d2udr2_analytical(real_type r, real_type A, real_type B, real_type C, real_type D){
      real_type ar(A * r);
      real_type br(B * r);
      real_type cr(C * r);
      real_type dr(D * r);
      real_type bttm(1.0 / (1.0 + C * cr + dr * dr));
      real_type dudr   = (A - A * dr * dr + br * (2.0 + C * cr)) * bttm * bttm;
      real_type d2udr2 = -2.0 * (A * (C * C + 3.0 * dr * D - dr * dr * dr * D) + B * (-1.0 + dr * dr * (3.0 + C * cr))) * bttm *
          bttm * bttm;
      return d2udr2;
    }
    inline real_type PadeTwo2ndOrderFunctor_evaluate_d2udr2(real_type r, real_type A, real_type B, real_type C, real_type D){

     return __enzyme_autodiff<real_type>((void*)PadeTwo2ndOrderFunctor_evaluate_dudr,
      r,
       A,
       B,
       C,
       D);
    }
  }
}

int main() {
    double A = 1.0, B= 2.0, C = 3.0, r = 4.0, D=5.0;

    double a = qmcad::Pade2ndOrderFunctor::Pade2ndOrderFunctor_evaluate(r, A, B,  C);
    double ad_d_a = qmcad::Pade2ndOrderFunctor::Pade2ndOrderFunctor_evaluate_dudr(r, A, B,  C);
    double ad_d2_a = qmcad::Pade2ndOrderFunctor::Pade2ndOrderFunctor_evaluate_d2udr2(r, A, B,  C);
    double d_a = qmcad::Pade2ndOrderFunctor::Pade2ndOrderFunctor_evaluate_dudr_analytical(r, A, B,  C);
    double d2_a = qmcad::Pade2ndOrderFunctor::Pade2ndOrderFunctor_evaluate_d2udr2_analytical(r, A, B,  C);

    double b = qmcad::PadeTwo2ndOrderFunctor::PadeTwo2ndOrderFunctor_evaluate(r, A, B,  C, D);
    double ad_d_b = qmcad::PadeTwo2ndOrderFunctor::PadeTwo2ndOrderFunctor_evaluate_dudr(r, A, B,  C,  D);
    double ad_d2_b = qmcad::PadeTwo2ndOrderFunctor::PadeTwo2ndOrderFunctor_evaluate_d2udr2(r, A, B,  C, D);
    double d_b =  qmcad::PadeTwo2ndOrderFunctor::PadeTwo2ndOrderFunctor_evaluate_dudr_analytical(r, A, B,  C, D);
    double d2_b = qmcad::PadeTwo2ndOrderFunctor::PadeTwo2ndOrderFunctor_evaluate_d2udr2_analytical(r, A, B,  C, D);
    std::cout << std::fixed << std::showpoint;
    std::cout << std::setprecision(16);
    std::cout << "        a: " << a << std::endl;
    std::cout << "       da: " << d_a << std::endl;
    std::cout << "    ad da: " << ad_d_a << std::endl;
    std::cout << "      d2a: " << d2_a << std::endl;
    std::cout << "   ad d2a: " << ad_d2_a << std::endl;
    std::cout <<std::endl;

    std::cout << "        b: " << b << std::endl;
    std::cout << "       db: " << d_b << std::endl;
    std::cout << "    ad db: " << ad_d_b << std::endl;
    std::cout << "      d2b: " << d2_b << std::endl;
    std::cout << "   ad d2b: " << ad_d2_b << std::endl;
    std::cout <<std::endl;
}

