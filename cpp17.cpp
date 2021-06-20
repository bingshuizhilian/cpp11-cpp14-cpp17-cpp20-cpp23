#include "common.h"
#include <any>
#include <variant>
#include <optional>

void cpp17AnyTest()
{
    using std::any;
    cout << "cpp17AnyTest start" << endl;

    /// 1
    vector<any> anyvec;
    anyvec.push_back(make_any<TYPE_A>());
    anyvec.push_back(1568);
    anyvec.push_back(TYPE_B());
    anyvec.push_back("end of anyvec");
    /// 2
    for_each(begin(anyvec), end(anyvec), [&](const auto &p){
        cout << p.type().name() << endl;
        cout << (p.type() == typeid (TYPE_A) ? "is TYPE_A" : "not TYPE_A") << endl;
    });

    cout << "cpp17AnyTest end" << endl;
}

void cpp17VarientTest()
{
    cout << "cpp17VarientTest start" << endl;

    TYPE_A a;
    variant<TYPE_A, TYPE_B, std::string> var1(a), var2((TYPE_B())), var3("visit");

    /// 1
    struct Visitor
    {
        Visitor &operator()(const TYPE_A& p)
        {
            cout << "Visitor typeA" << endl;
            return *this;
        }

        Visitor &operator()(const TYPE_B& p)
        {
            cout << "Visitor typeB" << endl;
            return *this;
        }

        Visitor &operator()(const string& p)
        {
            cout << "Visitor string" << endl;
            return *this;
        }
    };

    visit(Visitor(), var1);
    visit(Visitor(), var2);
    visit(Visitor(), var3);

    /// 2
    auto overloadedLambdas = overload{
        [](TYPE_A& a) { cout << "Lambda TYPE_A" << endl; },
        [](TYPE_B& b) { cout << "Lambda TYPE_B" << endl; },
        [](string& s) { cout << "Lambda string" << endl; },
        [](int i) { cout << "Lambda int" << endl; },
    };

    visit(overloadedLambdas, var1);
    visit(overloadedLambdas, var2);
    visit(overloadedLambdas, var3);

    /// 3
    auto lf1 = [](TYPE_A& s) { cout << "Lambda TYPE_A 2" << endl; };
    auto lf2 = [](TYPE_B& s) { cout << "Lambda TYPE_B 2" << endl; };
    auto lf3 = [](string& i) { cout << "Lambda string 2" << endl; };
    auto overloadedLambdas2 = overload{ lf1, lf2, lf3 };

    visit(overloadedLambdas2, var1);
    visit(overloadedLambdas2, var2);
    visit(overloadedLambdas2, var3);

    /// 4
    overload ol{ lf1, lf2, lf3 };

    visit(ol, var1);
    visit(ol, var2);
    visit(ol, var3);

    /// 5
    overload ol2{ Visitor() }; ///< a Visitor object satisfy the concept of 'overload'
    visit(ol2, var1);
    visit(ol2, var2);
    visit(ol2, var3);

    /// 6
    visit(overload{
              [](TYPE_A& s) { cout << "Lambda TYPE_A 3" << endl; },
              [](TYPE_B& s) { cout << "Lambda TYPE_B 3" << endl; },
              [](string& i) { cout << "Lambda string 3" << endl; }
          },
          var1);
    visit(overload{
              [](TYPE_A& s) { cout << "Lambda TYPE_A 3" << endl; },
              [](TYPE_B& s) { cout << "Lambda TYPE_B 3" << endl; },
              [](string& i) { cout << "Lambda string 3" << endl; }
          },
          var2);
    visit(overload{
              [](TYPE_A& s) { cout << "Lambda TYPE_A 3" << endl; },
              [](TYPE_B& s) { cout << "Lambda TYPE_B 3" << endl; },
              [](string& i) { cout << "Lambda string 3" << endl; }
          },
          var3);

    cout << "cpp17VarientTest end" << endl;
}

void cpp17OptionalTest()
{
    cout << "cpp17OptionalTest start" << endl;
    cout << "cpp17OptionalTest end" << endl;
}
