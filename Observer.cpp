#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class PCD;

class Observer {
private:
    std::string nome;

public:
    Observer() : nome("") {}

    void setNome(const std::string& nome) {
        this->nome = nome;
    }

    std::string getNome() const {
        return nome;
    }

    void update(PCD* pcd);
};

class PCD {
private:
    int id;
    std::vector<Observer*> observers;
    double temperatura;
    double umidade;
    double pressao;
    double ph;

public:
    PCD() : id(0), temperatura(0.0), umidade(0.0), pressao(0.0), ph(0.0) {}

    void setId(int id) {
        this->id = id;
    }

    int getId() const {
        return id;
    }

    double getTemperatura() const {
        return temperatura;
    }

    double getUmidade() const {
        return umidade;
    }

    double getPressao() const {
        return pressao;
    }

    double getPh() const {
        return ph;
    }

    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(
            std::remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    void notifyObservers() {
        for (Observer* observer : observers) {
            observer->update(this);
        }
    }

    void setTemperatura(double temperatura) {
        this->temperatura = temperatura;
        notifyObservers();
    }

    void setUmidade(double umidade) {
        this->umidade = umidade;
        notifyObservers();
    }

    void setPressao(double pressao) {
        this->pressao = pressao;
        notifyObservers();
    }

    void setPh(double ph) {
        this->ph = ph;
        notifyObservers();
    }
};

void Observer::update(PCD* pcd) {
    std::cout << nome << ": Houve atualizacao no PCD "<< pcd->getId() << ".\n";
    std::cout << "Temperatura: " << pcd->getTemperatura() << "\n";
    std::cout << "Umidade: " << pcd->getUmidade() << "\n";
    std::cout << "Pressao: " << pcd->getPressao() << "\n";
    std::cout << "pH: " << pcd->getPh() << "\n\n";
}

int main() {
    PCD rio1;
    rio1.setId(1);

    PCD rio2;
    rio2.setId(2);

    PCD rio3;
    rio3.setId(3);

    Observer ufrgs;
    ufrgs.setNome("ufrgs");

    Observer pucrs;
    pucrs.setNome("PUC-RS");

    Observer pelotinhas;
    pelotinhas.setNome("Pelotas Business School");

    rio1.addObserver(&ufrgs);
    rio1.addObserver(&pucrs);

    rio2.addObserver(&ufrgs);
    rio2.addObserver(&pelotinhas);

    rio3.addObserver(&pucrs);
    rio3.addObserver(&pelotinhas);

    rio1.setTemperatura(25.0);
    rio2.setUmidade(80.0);
    rio3.setPressao(1013.0);

    return 0;
}