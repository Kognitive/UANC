#ifndef ACTIVENOISECANCELLING_DATA_CONTROLLER_H
#define ACTIVENOISECANCELLING_DATA_CONTROLLER_H


/** \brief This class gets used to synchronize the data between simple modules.
 *
 * This class gets used by the gui to synchronize the data between the single modules.
 * In detail this means, that it will receive messages by any publisher, and notify
 * all observers about the new data. Hence we will make use of the observer design pattern
 * for this piece of software.
 */
class DataController {

private:
    DataController();

public:

    
    static void publish();
};


#endif //ACTIVENOISECANCELLING_DATA_CONTROLLER_H
