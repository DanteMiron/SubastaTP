#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>


using namespace std;

class Persona {
    string nombre;
public:
    explicit Persona(const string& nombre) : nombre(nombre) {}
    string getName() const {
        return nombre;
    }
};



int main(){

    Persona dante("Dante");

    cout << "Nombre" << dante.getName() << endl;

    return 0;

}