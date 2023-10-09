#ifndef SOLID_H
#define SOLID_H
#include <string>
/*

void SolidConstruct(Solid**, char*);
void SolidCenter(Solid* s);
void SolidDestruct(Solid**);
int  SolidConvexity(Solid* s);
void SolidConstructNoff(Solid**, char*);

*/
class Solid {
public:
    Solid(std::string fileName);
    ~Solid();

    //void Construct(Solid**, char*);
    void SolidCenter(Solid* s);
    void ConstructNoff(Solid**, char*);
    //void Destruct(Solid**);
    int  SolidConvexity(Solid* s);

private:

};


#endif // !SOLID_H
