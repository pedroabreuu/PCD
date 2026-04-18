#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Subject;

class Observer {
public:
    virtual void update(Subject* s) = 0;
    virtual ~Observer() = default;
};

class Subject {
private:
    std::vector<Observer*> observers;

public:
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
        for (Observer* obs : observers) {
            obs->update(this);
        }
    }

    virtual ~Subject() = default;
};

class PCD: public Subject {
private:
    std::string id;
    std::string estado;
    double temperatura;
    double pressao;
    double umidade;
    double ph;

public:
    PCD(const std::string& id, const std::string& estado): id(id), estado(estado), temperatura(0.0), pressao(0.0), umidade(0.0), ph(0.0) {}

    std::string getId() const {
        return id;
    }

    std::string getEstado() const {
        return estado;
    }

    double getTemperatura() const {
        return temperatura;
    }

    double getPressao() const {
        return pressao;
    }

    double getUmidade() const {
        return umidade;
    }

    double getPh() const {
        return ph;
    }

    void setTemperatura(double temperatura) {
        this->temperatura = temperatura;
        notifyObservers();
    }

    void setPressao(double pressao) {
        this->pressao = pressao;
        notifyObservers();
    }

    void setUmidade(double umidade) {
        this->umidade = umidade;
        notifyObservers();
    }

    void setPh(double ph) {
        this->ph = ph;
        notifyObservers();
    }
};

class Universidade: public Observer {
private:
    std::string nome;
    std::string estado;

public:
    Universidade(const std::string& nome, const std::string& estado): nome(nome), estado(estado) {}

    void update(Subject* s) override {
        PCD* pcd = dynamic_cast<PCD*>(s);

        if (pcd != nullptr) {
            std::cout << "Houve atualizacao no PCD " << pcd->getId() << " do estado " << pcd->getEstado() << ".\n";
            std::cout << "Universidade notificada: " << nome << " | Estado: " << estado << "\n";
            std::cout << "Novo valor da temperatura: " << pcd->getTemperatura() << " Celsius\n";
            std::cout << "Novo valor da pressao atmosferica: " << pcd->getPressao() << " hPa\n";
            std::cout << "Novo valor da umidade relativa do ar: " << pcd->getUmidade() << " %\n";
            std::cout << "Novo valor do pH: " << pcd->getPh() << "\n";
            std::cout << "\n";
        }
    }
};

int main() {
    PCD pcd1("PCD1", "Amazonas");
    PCD pcd2("PCD2", "Pará");

    Universidade ufrgs("UFRGS", "RioPequenoDoSul");
    Universidade pucrs("PUC-RS", "RioPequenoDoSul");
    Universidade pelotinhas("Pelotas Business School", "RioMuitoGrandeDoSul");

    pcd1.addObserver(&ufrgs);
    pcd1.addObserver(&pelotinhas);

    pcd2.addObserver(&pucrs);
    pcd2.addObserver(&pelotinhas);

    pcd1.setTemperatura(32.4);
    pcd1.setPressao(1009.2);
    pcd1.setUmidade(88.0);
    pcd1.setPh(6.8);

    pcd2.setTemperatura(30.1);
    pcd2.setPressao(1011.0);
    pcd2.setUmidade(93.5);
    pcd2.setPh(7.2);

    return 0;
}