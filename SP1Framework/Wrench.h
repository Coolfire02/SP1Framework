
#include "GameObject.h"
class Wrench :
    public GameObject
{
private:
    std::string type;
public:
    Wrench();
    Wrench(std::string type);
    ~Wrench();
    std::string getType();
};
