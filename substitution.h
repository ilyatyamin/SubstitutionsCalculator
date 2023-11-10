//
// Created by Илья Тямин on 10.11.2023.
//

#ifndef SUBSTITUTIONSCALCULATOR_SUBSTITUTION_H
#define SUBSTITUTIONSCALCULATOR_SUBSTITUTION_H

#include <map>
#include <utility>
#include <string>

class Substition {
public:
    explicit Substition() {
        dict = {};
    }

    explicit Substition(std::map<int, int> dictionary) {
        dict = std::move(dictionary);
    }

    Substition operator*(const Substition& substMult) {
        // умножаем СПРАВА НАЛЕВО
        Substition result;

        for (const auto element : substMult.dict) {
            result.InsertElement(element.first, dict[element.second]);
        }

        return result;
    }

    Substition Reverse() {
        Substition result;

        for (const auto element : dict) {
            result.InsertElement(element.second, element.first);
        }

        return result;
    }

    Substition PowIn(int pow) {
        Substition result{*this};

        for (int i = 0; i < pow - 1; ++i) {
            result = result * result;
        }

        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Substition& ratio) {
        std::string result;
        for (const auto element : ratio.dict) {
            result += std::to_string(element.first) + "\t";
        }
        result += "\n";

        for (const auto element : ratio.dict) {
            result += std::to_string(element.second) + "\t";
        }

        return os << result;
    }


private:
    std::map<int, int> dict;

    void InsertElement(int key, int value) {
        dict[key] = value;
    }
};

#endif //SUBSTITUTIONSCALCULATOR_SUBSTITUTION_H
