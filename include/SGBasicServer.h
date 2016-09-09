#include <vector>
class SGBasicServer
{
public:
    class Work
    {
    public:
        typedef enum {
            FAILED,
            WAIT,
            SUCCESS,
        }STATUS;
        Work(){}
        virtual ~Work(){}
        
        virtual STATUS vRun() = 0;
    };
    
    SGBasicServer();
    virtual ~ SGBasicServer();
    
    
    virtual bool onSetup() = 0;
    void runLoop();
    void addWork(Work* w);
    
private:
    void _runRemainWork();
    
    std::vector<Work*> mWorkQueue;
};
