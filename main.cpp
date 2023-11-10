#include <iostream>
#include "substitution.h"

/// Задача: Решить уравнение подстановок ABA^(-2) = C^(-1)XC
/// Как решить: X = CABA^(-2)C

void SolveIHW2(Substition& A, Substition& B, Substition& C) {
    std::cout << C*A*B*(A.PowIn(2)).Reverse()*C;
}

int main() {
    Substition A{ { {1, 5}, {2, 3}, {3, 4}, {4, 6}, {5, 2}, {6, 1} } };
    Substition B{ { {1, 2}, {2, 3}, {3, 5}, {4, 6}, {5, 4}, {6, 1} } };
    Substition C{ { {1, 4}, {2, 3}, {3, 5}, {4, 6}, {5, 1}, {6, 2} } };

    SolveIHW2(A, B, C);
    return 0;
}
