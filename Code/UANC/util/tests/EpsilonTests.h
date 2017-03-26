;//
// Created by dose on 22.03.17.
//

#ifndef UANC_EPSILONTESTS_H
#define UANC_EPSILONTESTS_H


class EpsilonTests {
public:
/** \brief This class can be used to check all algorithm
 *
 * Gives a statistic for each algorithm.
 */
    EpsilonTests();


  /** \brief This methode runs all algorithm
 *
 * Runs all algorithm and test if average error is smaler than epsilon
 */
    void run(std::string path);
};


#endif //UANC_EPSILONTESTS_H
