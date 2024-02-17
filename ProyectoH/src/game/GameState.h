#ifndef GAME_STATE_H_
#define GAME_STATE_H_
#include <list>
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
//#include "../systems/GameCtrlSystem.h"
using namespace std;

class GameState {
protected:
    Manager* mngr_ = nullptr;
public:
    const gmSttId_type id;
    // Constructor
    GameState(gmSttId_type _id);
    // Destructor
    virtual ~GameState();
    // Updates scene's objects
    virtual void update();
    // Draws the scene on screen
    virtual void render() {}
    // Handles the event
    virtual void handleInput() {}
    // Clears every non alive Entity
    void refresh();
    // Sends a message to the manager
    void send(const Message& m, bool delay = false);
};
#endif
