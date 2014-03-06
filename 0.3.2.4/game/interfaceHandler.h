#ifndef INTERFACEHANDLER_H
#define INTERFACEHANDLER_H
#include <string>

class interfaceHandler
{
    public:
        interfaceHandler();
        ~interfaceHandler();
        void renderInterface(std::string time, std::string money, std::string genmat, std::string H, std::string He, std::string C);
        void interfaceHover();
    protected:
    private:
};

#endif // INTERFACEHANDLER_H
