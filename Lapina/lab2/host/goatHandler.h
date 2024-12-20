#ifndef GOAT_HANDLER_H
#define GOAT_HANDLER_H


#include <memory>
#include <atomic>
#include <sys/syslog.h>
#include <mutex>
#include <semaphore.h>

#include "../utilsConfigurations/gameWorld.h"
#include "../connections/connection.h"


class goatHandler 
{
public:
    goatHandler() = default;

    goatHandler(const goatHandler&) = default;
    goatHandler& operator=(const goatHandler&) = default;

    goatHandler (goatHandler&&) = default;
    goatHandler& operator = (goatHandler&&) = default;

    ~goatHandler(){}


    bool initGoat(pid_t goatPid, std::shared_ptr<GameWorld> gameW);

    void stopGoat();

    bool sendGoatStatus(goatStatus stGoat);
    bool getGoatNum(int *num);

    void runRounds();
    void sendStartGame();

    void setStatusWolfNumber();

private:
    const int timeInter = 5;
    std::atomic<bool> statusWolfNumber;

    std::atomic<pid_t> hostPid = -1;
    std::atomic<pid_t> goatPid = -1;
    std::atomic<bool> isOpenSem = false;

    sem_t* hostSemaphore;
    sem_t* clientSemaphore;

    std::unique_ptr<Connection> connect;
    std::shared_ptr<GameWorld> gameWorld;

    bool openSemaphores();
    bool openConnection();
};

#endif