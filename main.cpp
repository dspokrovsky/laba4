#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <map>
#include <string>
#include <team.hpp>
#include <math.h>

long long calculate_hash1(const team& dt)
{
    size_t h =0;
    size_t m = (1<<12) + 101;
    for(size_t i =0; i < dt.name().size(); i ++){
        h += dt.name()[i] << i;
    }
    return h%(m-1);
}
long long calculate_hash2(const team& dt)
{
    long long h=0;
    int p = 43;
    for(size_t i =0; i < dt.name().size(); i ++){
        h += dt.name()[i] * pow(p,i);
    }
    return h;
}
bool hashSearch(const team &dt, std::multimap<long long, team> &list, std::multimap<long long, team>::iterator my_it){
    auto range = list.equal_range(dt.hash());

    for(auto it = range.first; it != range.second; ++it){
        if( dt == it->second){
            my_it = it;
            return true;
        }
    }
    return false;
}

int main(){
    for(size_t size = 1000; size < 1200; size = size * 2)
    {
        std::fstream in;

        std::string str = std::to_string(size);
        in.open("/home/user/Projects/build-generater-Desktop-Debug/input"+str);

        std::string a="",b="",d="";
        size_t c=0;


        std::multimap<long long, team> l1;
        std::multimap<long long, team> l2;

        while(in >> a >> b >> c >> d){
           team t(a,b,c,d);
           t.hash() = calculate_hash1(t);
           l1.emplace(std::make_pair(t.hash(),t));

           t.hash() = calculate_hash2(t);
           l2.emplace(std::make_pair(t.hash(),t));
        }
        team t(a,b,c,d);//сохраним один элемент, что будем искать
        t.hash() = calculate_hash1(t);
        //считаем коллизии
        size_t count=0;
        auto end = l1.end()--;
        for(auto i = l1.begin(); i != end;){
            auto k =i;
            i++;
            if (i->first==(k)->first) count++;
        }
        std::cout << "hash1: "<<count<< std::endl;
        count=0;
        end = l2.end()--;
        for(auto i = l2.begin(); i != end;){
            auto k =i;
            i++;
            if (i->first==(k)->first) count++;
        }
        std::cout << "hash2: " << count << std::endl;

        auto it = l2.begin();
        clock_t t2;
        clock_t t1 = clock();
        hashSearch(t,l2,it);
        t2 = clock();
        std::cout << (double)(t2-t1)/(double)CLOCKS_PER_SEC << std::endl;
    }

    return 0;
}


