#include <QCoreApplication>
#include <QDebug>
#include <QMap>

enum TIPO

{
    tipo1 = 0,
    tipo2,
    tipo3
};


class Base
{
public:
    Base() {}
    virtual void implementOnDerived() = 0;
};

class Derived1 : public Base
{
public:
    Derived1() {}
    void implementOnDerived() { qDebug() << "derived 1"; }
};

class Derived2 : public Base
{
public:
    Derived2() {}
    void implementOnDerived() { qDebug() << "derived 2"; }

};

class Derived3 : public Base
{
public:
    Derived3() {}
    void implementOnDerived() { qDebug() << "derived 3"; }

};

class Pai
{
public:
    Pai(){proximo = nullptr;}
    virtual void Tratar(TIPO tp) = 0;
    void SetProximoTratar(Pai *proximoTratar)
    {
        proximo = proximoTratar;
    }
protected:
    Pai *proximo;
};

class Filha1 : public Pai
{
public:
    virtual void Tratar(TIPO tp) override
    {
        if (tp == TIPO::tipo1)
        {
            qDebug() << "filha 1";
        }
        else
        {
            proximo->Tratar(tp);
        }
    }
};

class Filha2 : public Pai
{
public:

    virtual void Tratar(TIPO tp) override
    {
        if (tp == TIPO::tipo2)
        {
            qDebug() << "filha 2";
        }
        else
        {
            proximo->Tratar(tp);
        }
    }
};

class Filha3 : public Pai
{
public:
    virtual void Tratar(TIPO tp) override
    {
        if (tp == TIPO::tipo3)
        {
            qDebug() << "filha 3";
        }
        else
        {
            proximo->Tratar(tp);
        }
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    //switch / case convencional para tratar vários statements
    //e abaixo possíveis soluções para deixar o codigo mais reusable, e com menos acoplamento
    //utilizando design patterns chain of responsability e strategy
    TIPO t;

    //
    switch (t) {
    case tipo1:
        //tratar aqui
        break;
    case tipo2:
        //tratar aqui
        break;
    case tipo3:
        //tratar aqui
        break;

    }

    //classe Base, Derived1, Derived2, Derived3 : solução utilizando pattern Strategy
    Derived1 *der1 = new Derived1();
    Derived2 *der2 = new Derived2();
    Derived3 *der3 = new Derived3();

    QMap<TIPO, Base*> Strategies;

    Strategies[TIPO::tipo1] = der1;
    Strategies[TIPO::tipo2] = der2;
    Strategies[TIPO::tipo3] = der3;

    TIPO t = TIPO::tipo3;

    QMap<TIPO, Base*>::iterator itr = Strategies.find(t);
    itr.value()->implementOnDerived();
    //fim strategy pattern

    TIPO tp = TIPO::tipo3;

    //classe pai, filha1, filha2 : solução utilizando pattern chain of responsability
    Filha1 *filha1 = new Filha1();
    Filha2 *filha2 = new Filha2();
    Filha3 *filha3 = new Filha3();

    filha1->SetProximoTratar(filha2);
    filha2->SetProximoTratar(filha3);

    filha1->Tratar(tp);

    //fim chain of responsability

    return a.exec();
}
