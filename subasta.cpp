#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>


using namespace std;


class Persona {
    string nombre;
public:
    explicit Persona(const string& nombre) : nombre(nombre) {}
    string get_nombre() const {
        return nombre;
    }
};


class Oferta {
    double monto;
    Persona* ofertante;
public:
    Oferta(double monto, Persona* ofertante)
        : monto(monto), ofertante(ofertante)
        {
            if (monto<=0) throw invalid_argument("El monto debe ser mayor a cero");
        }
    double get_monto() const { return monto;}
    Persona* get_ofertante() const {return ofertante;}
};


class Lote {
    int numero;
    string nombre;
    Oferta* mejor_oferta;
public:
    Lote(int numero, const string& nombre)
        : numero(numero), nombre(nombre), mejor_oferta(nullptr) {}
    ~Lote() { delete mejor_oferta; }

    void recibir_oferta(const Oferta& oferta) {
        if (!mejor_oferta || oferta.get_monto() > mejor_oferta->get_monto()) {
            delete mejor_oferta;
            mejor_oferta = new Oferta(oferta);
        }
    }

    const Oferta* get_mejor_oferta() const { return mejor_oferta; }
    int get_numero() const { return numero; }
    string get_nombre() const { return nombre; }
};


class Subasta {
    vector<Lote*> lotes;
public:
    ~Subasta() {
        for (auto l : lotes) delete l;
    }

    void agregar_lote(Lote* lote) {
        lotes.push_back(lote);
    }

    void ofertar(int numeroLote, const Oferta& oferta) {
        for (auto l : lotes) {
            if (l->get_numero() == numeroLote) {
                l->recibir_oferta(oferta);
                return;
            }
        }
        throw out_of_range("Lote no encontrado");
    }

    const vector<Lote*>& get_lotes() const { return lotes; }
    size_t cantidad_lotes() const { return lotes.size(); }
};

int main() {
    Persona p1("Juan"), p2("María");
    Subasta sub;

    for (int i = 0; i < 10; i++)
    {   
        string nombre;
        cout << "Defina un nombre para el lote numero " << i + 1  << ": ";
        cin >>  nombre;
        sub.agregar_lote(new Lote(i, nombre));    
    }
    
    
    sub.ofertar(1, Oferta(100.0, &p1));
    sub.ofertar(1, Oferta(150.0, &p2));
    sub.ofertar(2, Oferta(200.0, &p1));

    for (auto lote : sub.get_lotes()) {
        cout << "Lote " << lote->get_numero()
             << " (" << lote->get_nombre() << "): ";
        const Oferta* o = lote->get_mejor_oferta();
        if (o) {
            cout << "Mejor oferta " << o->get_monto()
                 << " por " << o->get_ofertante()->get_nombre();
        } else {
            cout << "Sin ofertas";
        }
        cout << "\n";
    }

    return 0;
}
