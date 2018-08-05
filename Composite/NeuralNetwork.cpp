#include <array>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using ID = size_t;

template<typename Iter>
std::ostream &printList(std::ostream &os, Iter begin, Iter end, std::function<std::string(const typename std::iterator_traits<Iter>::value_type &)> &f) {
    bool isFirst = true;
    os << '[';
    std::for_each(begin, end, [&](const typename std::iterator_traits<Iter>::value_type &v) {
        if (!isFirst) os << ',';
        isFirst = false;
        os << f(v);
    });
    return os << ']';
}

/**
 * We want to be able to connect_to:
 * 1. Neuron to Neuron
 * 2. Neuron to NeuronLayer
 * 3. NeuronLayer to NeuronLayer
 * 4. NeuronLayer to Neuron
 * Once again, this is a state-space explosion.
 *
 * We want a single method to do this instead of four. For this, we introduce an interface with two templates so that
 * we can connect all four of the above combinations with one method. This means that we will need Neuron to have a
 * begin() and end() method to act like a container, and same for NeuronLayer (it already is a container).
 */

/// CRTP = curiosly recurring template pattern.
template<typename Self>
struct SomeNeurons {
    /**
     * Enumerate our neurons, and the neurons of the other object.
     */
    template<typename T>
    void connectTo(T &other);
};

struct Neuron : SomeNeurons<Neuron> {
    using NeuronVector = std::vector<Neuron*>;

    NeuronVector in;
    NeuronVector out;
    ID id;

    Neuron() : id(id_gen++) {}

    Neuron *begin() { return this; }

    /// This seems very crude, but it will work.
    Neuron *end() { return this+1; }

    friend std::ostream &operator<<(std::ostream &os, const Neuron &neuron);

private:
    static size_t id_gen;
};

size_t Neuron::id_gen{1};

std::ostream &operator<<(std::ostream &os, const Neuron &neuron) {
    os << "Neuron" << neuron.id << '{';

    /// This function was damned hard to get right.
    std::function<std::string(Neuron* const&)> nout = [](Neuron* const &n) {
        return "N" + std::to_string(n->id);
    };

    os << "in";
    printList(os, std::cbegin(neuron.in), std::cend(neuron.in), nout);

    os << ",out";
    printList(os, std::cbegin(neuron.out), std::cend(neuron.out), nout);

    os << '}';
    return os;
}

/// Cardinal sin: inheriting from std collection!
struct NeuronLayer : std::vector<Neuron>, SomeNeurons<NeuronLayer> {
    NeuronLayer(int count) {
        /// Sneaky use of -- and > that looks cool.
        while (count --> 0) {
            emplace_back(Neuron{});
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const NeuronLayer &layer) {
        os << "NeuronLayer{";

        /// This function was damned hard to get right.
        std::function<std::string(const Neuron&)> nout = [](const Neuron &n) {
            std::ostringstream osstr;
            osstr << n;
            return osstr.str();
        };
        printList(os, std::cbegin(layer), std::cend(layer), nout);
        os << '}';
        return os;
    }
};

template<typename Self>
template<typename T>
void SomeNeurons<Self>::connectTo(T &other) {
    /**
     * Turn this ptr into Self* ptr: so for Neuron, this will turn this into Neuron, and for NeuronLayer, it will
     * turn this into NeuronLayer. Then we can call the appropriate begin and end functions on it, which is needed
     * for iteration.
     */
    for (Neuron &to: *static_cast<Self*>(this))
        for (Neuron &from: other) {
            from.out.emplace_back(&to);
            to.in.emplace_back(&from);
        }
}

int main() {
    std::array<Neuron, 3> inputNeurons;
    NeuronLayer nl1{4};
    NeuronLayer nl2{3};

    for (auto &in: inputNeurons)
        for (auto &out: nl1)
            in.connectTo(out);

    nl1[0].connectTo(nl2[0]);
    nl1[0].connectTo(nl2[1]);
    nl1[1].connectTo(nl2[1]);
    nl1[1].connectTo(nl2[2]);
    nl1[2].connectTo(nl2[0]);
    nl1[2].connectTo(nl2[2]);
    nl1[3].connectTo(nl2[2]);

    std::vector<Neuron> outputNeurons{Neuron{}, Neuron{}};
    for (auto &in: nl2)
        for (auto &out: outputNeurons)
            in.connectTo(out);

    std::vector<NeuronLayer*> layers{&nl1, &nl2};

    std::cout << "*** Inputs ***" << std::endl;
    for (auto &n: inputNeurons)
        std::cout << n << std::endl;
    std::cout << std::endl;

    for (int i=0; i < layers.size(); ++i) {
        std::cout << "*** Layer ***" << i+1 << std::endl;
        for (auto &n: *layers[i])
            std::cout << n << std::endl;
        std::cout << std::endl;
    }

    std::cout << "*** Outputs ***" << std::endl;
    for (auto &n: outputNeurons)
        std::cout << n << std::endl;
}