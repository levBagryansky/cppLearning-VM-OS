/* Допустим есть какая-то формула, по которой расчитывается
вес картины.
 Создаем класс Function, хранящий последовательность действий в формуле.
 Также, в нем есть метод, разворачивающий последовательность, чтобы
 узнать первый член.
 FunctionPart- одно дествие.
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Image {
    double quality;
    double freshness;
    double rating;
};

struct Params {
    double a;
    double b;
    double c;
};

class FunctionPart{
public:
    FunctionPart(char new_operation, double new_value){
        operation = new_operation;
        value = new_value;
    }

    double Apply(double source) const{
        if (operation == '+')
            source += value;
        else if(operation == '-')
            source -= value;
        else if (operation == '*')
            source *= value;
        else if (operation == '/')
            source /= value;
        else
            source = -1;

        return source;
    }

    void Reverse(){
        if (operation == '+')
            operation = '-';
        else if (operation == '-')
            operation = '+';
        else if (operation == '*')
            operation = '/';
        else if (operation == '/')
            operation = '*';
    }

    char ShowOperation() const{
        return operation;
    }

    double ShowValue() const {
        return value;
    }

private:
    char operation;
    double value;
};

class Function{
public:
    void AddPart(char operation, double value){
        parts.push_back({operation, value});
    }

    double Apply(double source) const{
        double result = source;
        for(const auto& part: parts)
            result = part.Apply(result);

        return result;
    }

    void Invert(){
        reverse(begin(parts), end(parts));
        for(auto& part: parts)
            part.Reverse();
    }
    void Print() const{
        cout << "Printing Function:\n";
        for (const auto& part: parts){
            cout << part.ShowOperation() << ' ' << part.ShowValue() << endl;
        }

    }

private:
    vector<FunctionPart> parts;
};


Function MakeWeightFunction(const Params& params,
                            const Image& image) {
    Function function;
    function.AddPart('-', image.freshness * params.a + params.b);
    function.AddPart('+', image.rating * params.c);
    return function;
}

double ComputeImageWeight(const Params& params, const Image& image) {
    Function function = MakeWeightFunction(params, image);
    //function.Print();
    return function.Apply(image.quality);
}

double ComputeQualityByWeight(const Params& params,
                              const Image& image,
                              double weight) {
    Function function = MakeWeightFunction(params, image);
    //function.Print();
    function.Invert();
    //function.Print();
    return function.Apply(weight);
}

int main() {
    Image image = {10, 2, 6};
    Params params = {4, 2, 6};
    cout << ComputeImageWeight(params, image) << endl;
    cout << ComputeQualityByWeight(params, image, 46) << endl;
    return 0;
}
