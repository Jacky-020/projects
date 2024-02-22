#include <algorithm>
#include <cmath>
#include <vector>
#include <list>

struct points{
    double x;
    double y;

    points(double x_coordinate, double y_coordinate) : x(x_coordinate), y(y_coordinate){

    }

    double sqPath(const points & rhs)const{
        return std::pow(x - rhs.x, 2) + std::pow(y - rhs.y, 2);
    }

    double xDist(double rhs)const{
        return rhs < x ? x - rhs : rhs - x;
    }
    double yDist(double rhs)const{
        return rhs < y ? y - rhs : rhs - y;
    }
};

int main(){

}

void findShortest(std::list<points> pointList){

}

double findShortest(std::vector<points> pointListX, std::vector<points> pointListY, int xBegin, int xEnd, int yBegin, int yEnd, double & currentShortest){
    points Xmid = (xBegin + xEnd) / 2;
    double tmpDist;

    for(int x = xBegin, x < xEnd; ++x){
        for(auto p2 = p1; ++p2 != pointList.end();){
            if(p1->xDist(p2->x) > currentShortest || p1->yDist(p2->y) > currentShortest){
                break;
            }else{
                if((tmpDist = p1->sqPath(*p2)) < currentShortest){
                    currentShortest = tmpDist;
                }
            }
        }
    }
    if(findShortest() < currentShortest)
}