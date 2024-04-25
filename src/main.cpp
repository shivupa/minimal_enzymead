#include <iostream>

double square(double x) {
    return x * x;
}

double __enzyme_autodiff(void*, double);

int main(int argc, char **argv) {
    double x = 3.14;
    // Evaluates to 2 * x = 6.28
    double grad_x = __enzyme_autodiff((void*)square, x);

      std::cout << "Enzyme Example" << std::endl;
      std::cout << " x =          " << x << std::endl;
      std::cout << " f(x) = x^2 = " << square(x) << std::endl;
      std::cout << " f'(x) = 2x = " << grad_x << std::endl;
}
