#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cassert>

class Hero{

    public:

        enum attribute_t { ATTACK, DEFENSE, HEALING, N_ATTRIBUTES };

        Hero( std::string _n = "" ) : m_name( _n ) {
            m_points.resize( N_ATTRIBUTES );
            std::fill( m_points.begin(), m_points.end(), 0 );
        }

        void set_attribute( attribute_t _at, int _val ) {
            m_points[ _at ] = _val;
        }

        int get_attribute( attribute_t _at ) const {
            return m_points[ _at ];
        }

        std::string get_name( void ) const {
            return m_name;
        }

    private:
        std::string m_name;
        std::vector< int > m_points; //!< Stores hero's attributes

};

std::ostream & operator<< ( std::ostream & _os, const Hero & _h ){

    _os << "{<" << _h.get_name() << ">"
                << ", A=" << _h.get_attribute( Hero::attribute_t::ATTACK)
                << ", D=" << _h.get_attribute( Hero::attribute_t::DEFENSE)
                << ", H=" << _h.get_attribute( Hero::attribute_t::HEALING)
                << "}";
    return _os;

}

struct SortingPolicy{
    public:
        enum sorting_order_t{ASCENDING = 0, DESCENDING}; 
    private:
        Hero::attribute_t att;
        sorting_order_t type;

    public:
        SortingPolicy(Hero::attribute_t a_ = Hero::ATTACK, sorting_order_t t_ = ASCENDING)
            : att(a_)
            , type(t_)
            { /* Empty */ }

        void set_order(sorting_order_t so_){
            type = so_;
        }

        bool operator()(const Hero& h1_, const Hero& h2_){
            if(type == ASCENDING){
                return h1_.get_attribute(att) < h2_.get_attribute(att);
            }else if(type == DESCENDING){
                return h1_.get_attribute(att) > h2_.get_attribute(att);
            }else{
                assert(false);
            }
            return true;
        }
};

bool compare_by_name( const Hero& _h1, const Hero& _h2 ){
    return (_h1.get_name() < _h2.get_name());
}
 
int main() {

    std::vector< Hero > heros =
    {
        Hero("Hulk"),
        Hero("Batman"),
        Hero("Wolverine"),
        Hero("Superman")
    };

    enum heros_t { HULK, BATMAN, WOLVERINE, SUPERMAN };

    heros[HULK].set_attribute( Hero::ATTACK, 10000 );
    heros[HULK].set_attribute( Hero::DEFENSE, 10000 );
    heros[HULK].set_attribute( Hero::HEALING, 10 );

    heros[BATMAN].set_attribute( Hero::ATTACK, 100 );
    heros[BATMAN].set_attribute( Hero::DEFENSE, 10 );
    heros[BATMAN].set_attribute( Hero::HEALING, 10 );

    heros[SUPERMAN].set_attribute( Hero::ATTACK, 200000 );
    heros[SUPERMAN].set_attribute( Hero::DEFENSE, 200000 );
    heros[SUPERMAN].set_attribute( Hero::HEALING, 20000 );

    heros[WOLVERINE].set_attribute( Hero::ATTACK, 560 );
    heros[WOLVERINE].set_attribute( Hero::DEFENSE, 800 );
    heros[WOLVERINE].set_attribute( Hero::HEALING, 10000000 );

    std::cout << ">>> Hero list BEFORE sorting: \n";
    std::copy( heros.begin(), heros.end(), std::ostream_iterator< Hero >( std::cout, "\n") );
    std::cout << "\n";
    
    SortingPolicy p(Hero::ATTACK);
    p.set_order(heros.begin(), heros.end(), p);

    std::cout << ">>> Hero list AFTER sorting: \n";
    std::copy( heros.begin(), heros.end(), std::ostream_iterator< Hero >( std::cout, "\n") );
    std::cout << "\n";

    return EXIT_SUCCESS;

}
