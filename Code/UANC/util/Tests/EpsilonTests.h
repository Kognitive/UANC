;//
// Created by dose on 22.03.17.
//

#ifndef UANC_EPSILONTESTS_H
#define UANC_EPSILONTESTS_H


class EpsilonTests {
public:
    /**
 * Contructor
 */
    EpsilonTests();

    //Test if average error is smaler than epsilon
    void run(std::string path);
};


#endif //UANC_EPSILONTESTS_H
