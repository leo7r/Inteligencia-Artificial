/*
 *  Copyright (C) 2012 Universidad Simon Bolivar
 * 
 *  Permission is hereby granted to distribute this software for
 *  non-commercial research purposes, provided that this copyright
 *  notice is included with any such distribution.
 *  
 *  THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 *  EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
 *  SOFTWARE IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU
 *  ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 *  
 *  Blai Bonet, bonet@ldc.usb.ve
 *
 *  Last revision: 11/08/2012
 *
 */

#include <cassert>
#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>

#define MAX(s,t)      ((s)>(t)?(s):(t))
#define MIN(s,t)      ((s)<(t)?(s):(t))
#define MAXVALUE      1000
#define DIM           36
#define N             6
#define MIN_INT			-420
#define MAX_INT			420
const int rows[][7] = {
    { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 },
    { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 }, { 4, 5, 6, 7, 8, 9,-1 },
    {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 },
    {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 }, {10,11,12,13,14,15,-1 },
    {16,17, 0, 1,18,19,-1 }, {16,17, 0, 1,18,19,-1 },
    {16,17, 0, 1,18,19,-1 }, {16,17, 0, 1,18,19,-1 },
    {20,21, 2, 3,22,23,-1 }, {20,21, 2, 3,22,23,-1 },
    {20,21, 2, 3,22,23,-1 }, {20,21, 2, 3,22,23,-1 },
    {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 },
    {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 }, {24,25,26,27,28,29,-1 },
    {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 },
    {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 }, {30,31,32,33,34,35,-1 }
};
const int cols[][7] = {
    { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 },
    { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
    { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 },
    { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
    { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 },
    { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
    { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 },
    { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
    { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 },
    { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 },
    { 4,10,16,20,24,30,-1 }, { 5,11,17,21,25,31,-1 }, { 6,12, 0, 2,26,32,-1 },
    { 7,13, 1, 3,27,33,-1 }, { 8,14,18,22,28,34,-1 }, { 9,15,19,23,29,35,-1 }
};
const int dia1[][7] = {
    { 4,11, 0, 3,28,35,-1 }, { 5,12, 1,22,29,-1,-1 }, { 6,13,18,23,-1,-1,-1 },
    { 7,14,19,-1,-1,-1,-1 }, { 8,15,-1,-1,-1,-1,-1 }, { 9,-1,-1,-1,-1,-1,-1 },
    {10,17, 2,27,34,-1,-1 }, { 4,11, 0, 3,28,35,-1 }, { 5,12, 1,22,29,-1,-1 },
    { 6,13,18,23,-1,-1,-1 }, { 7,14,19,-1,-1,-1,-1 }, { 8,15,-1,-1,-1,-1,-1 },
    {16,21,26,33,-1,-1,-1 }, {10,17, 2,27,34,-1,-1 },
    { 6,13,18,23,-1,-1,-1 }, { 7,14,19,-1,-1,-1,-1 },
    {20,25,32,-1,-1,-1,-1 }, {16,21,26,33,-1,-1,-1 },
    { 5,12, 1,22,29,-1,-1 }, { 6,13,18,23,-1,-1,-1 },
    {24,31,-1,-1,-1,-1,-1 }, {20,25,32,-1,-1,-1,-1 }, {16,21,26,33,-1,-1,-1 },
    {10,17, 2,27,34,-1,-1 }, { 4,11, 0, 3,28,35,-1 }, { 5,12, 1,22,29,-1,-1 },
    {30,-1,-1,-1,-1,-1,-1 }, {24,31,-1,-1,-1,-1,-1 }, {20,25,32,-1,-1,-1,-1 },
    {16,21,26,33,-1,-1,-1 }, {10,17, 2,27,34,-1,-1 }, { 4,11, 0, 3,28,35,-1 }
};
const int dia2[][7] = {
    { 4,-1,-1,-1,-1,-1,-1 }, { 5,10,-1,-1,-1,-1,-1 }, { 6,11,16,-1,-1,-1,-1 },
    { 7,12,17,20,-1,-1,-1 }, { 8,13, 0,21,24,-1,-1 }, { 9,14, 1, 2,25,30,-1 },
    { 5,10,-1,-1,-1,-1,-1 }, { 6,11,16,-1,-1,-1,-1 }, { 7,12,17,20,-1,-1,-1 },
    { 8,13, 0,21,24,-1,-1 }, { 9,14, 1, 2,25,30,-1 }, {15,18, 3,26,31,-1,-1 },
    { 6,11,16,-1,-1,-1,-1 }, { 7,12,17,20,-1,-1,-1 },
    {15,18, 3,26,31,-1,-1 }, {19,22,27,32,-1,-1,-1 },
    { 7,12,17,20,-1,-1,-1 }, { 8,13, 0,21,24,-1,-1 },
    {19,22,27,32,-1,-1,-1 }, {23,28,33,-1,-1,-1,-1 },
    { 8,13, 0,21,24,-1,-1 }, { 9,14, 1, 2,25,30,-1 }, {15,18, 3,26,31,-1,-1 },
    {19,22,27,32,-1,-1,-1 }, {23,28,33,-1,-1,-1,-1 }, {29,34,-1,-1,-1,-1,-1 },
    { 9,14, 1, 2,25,30,-1 }, {15,18, 3,26,31,-1,-1 }, {19,22,27,32,-1,-1,-1 },
    {23,28,33,-1,-1,-1,-1 }, {29,34,-1,-1,-1,-1,-1 }, {35,-1,-1,-1,-1,-1,-1 }
};

// moves on the principal variation
static int PV[] = {
    12, 21, 26, 13, 22, 18,  7,  6,  5, 27, 33, 23, 17, 11, 19, 15, 14,
    31, 20, 32, 30, 10, 25, 24, 34, 28, 16,  4, 29, 35, 36,  8,  9, -1
};

static int Reverse_PV[] = { 
    9, 8, 36 , 35, 29, 4, 16, 28, 34, 24, 25, 10, 30, 32, 20, 31, 14, 15 , 19
    , 11, 17 , 23, 33, 27, 5, 6 , 7 , 18, 22, 13, 26, 21, 12 , -1
};

class state_t {
    unsigned char t_; /* Representa las 4 posiciones iniciales. Los 1 son & y los 0 son 0 */
    unsigned free_;   /* Indican que posiciones se encuentran libres en el tablero.  */
    unsigned pos_;    /* Indica las posiciones ocupadas del tablero sin tomar en cuenta las 4 del medio. */

  public:
    explicit state_t(unsigned char t = 6) : t_(t), free_(0), pos_(0) { }

    unsigned char t() const { return t_; }
    unsigned free() const { return free_; }
    unsigned pos() const { return pos_; }
    size_t hash() const { return free_ ^ pos_ ^ t_; }

    /**  
     * Nos dice de que color es la posicion pos.
     */
    bool is_color(bool color, int pos) const {
        if( color )
            return pos < 4 ? t_ & (1 << pos) : pos_ & (1 << (pos - 4));
        else
            return !(pos < 4 ? t_ & (1 << pos) : pos_ & (1 << (pos - 4)));
    }

    /**
     * Nos dice si el color es negro.
     * true es negro
     * false es blanco.
     */ 
    bool is_black(int pos) const { return is_color(true, pos); }
    bool is_white(int pos) const { return is_color(false, pos); }

    /**
     * Nos dice si el tablero esta libre en la posicion dada "pos".
     * Si la posicion es menor que 4 entonces es falso porque siempre esas posiciones estan ocupadas.
     * Si la posicion es mayor o igual que 4 entonces hay que ver si la posicion requerida es igual a 0.
     */
    bool is_free(int pos) const { return pos < 4 ? false : !(free_ & (1 << pos - 4)); }

    /**
     * Nos dice si free_ esta full.
     */
    bool is_full() const { return ~free_ == 0; }

    int value() const;
    bool terminal() const;
    bool outflank(bool color, int pos) const;
    
    /**
     * Nos dice si un movimiento es negro.
     */
    bool is_black_move(int pos) const { return (pos == DIM) || outflank(true, pos); }

    /**
     * Nos dice si un movimiento es blanco.
     */
    bool is_white_move(int pos) const { return (pos == DIM) || outflank(false, pos); }

    void set_color(bool color, int pos);
    state_t move(bool color, int pos) const;

    /**
     * Realiza un movimiento negro.
     */
    state_t black_move(int pos) { return move(true, pos); }

    /**
     * Realiza un movimiento blanco.
     */
    state_t white_move(int pos) { return move(false, pos); }

    /**
     * Obtiene un movimiento aleatorio.
     */
    int get_random_move(bool color) {
        std::vector<int> valid_moves;
        for( int pos = 0; pos < DIM; ++pos ) {
            if( (color && is_black_move(pos)) || (!color && is_white_move(pos)) ) {
                valid_moves.push_back(pos);
            }
        }
        return valid_moves.empty() ? -1 : valid_moves[0];//lrand48() % valid_moves.size()];
    }

    /** 
     * Compara dos estados con <
     */
    bool operator<(const state_t &s) const {
        return (free_ < s.free_) || ((free_ == s.free_) && (pos_ < s.pos_));
    }

    /** 
     * Compara dos estados con ==
     */
    bool operator==(const state_t &state) const {
        return (state.t_ == t_) && (state.free_ == free_) && (state.pos_ == pos_);
    }

    /**  
     * Asigna un estado a otro.
     */
    const state_t& operator=(const state_t &state) {
        t_ = state.t_;
        free_ = state.free_;
        pos_ = state.pos_;
        return *this;
    }

    void print(std::ostream &os, int depth = 0) const;
    void print_bits(std::ostream &os) const;

    /* Nuevas funciones. */

    /**
     * Retorna todos los posibles movimientos del estado dado.
     * @param color: Color del estado. 
     * Para poder optimizar podemos usar un apuntador a la lista.
     */
    std::list<int> succ(bool color){
        //std::list<int>* tmp = new std::list<int>(); 
        std::list<int>  sucesores;

        for( int i = 0; i < DIM; ++i ) {
            if((color && is_black_move(i)) || (!color && is_white_move(i))) {
                sucesores.push_back(i);
            }
        }
        
	if (sucesores.empty()){
            sucesores.push_back(DIM);
        }

        return sucesores;
    }

    std::list<int>* succ_p(bool color){
        std::list<int>* sucesores = new std::list<int>();

        for( int pos = 0; pos < DIM; ++pos ) {
            if((color && is_black_move(pos)) || (!color && is_white_move(pos))) {
                sucesores->push_back(pos);
            }
        }
        return sucesores;
    }
};
/**
 * Nos dice el valor actual del juego.
 */
inline int state_t::value() const {
    int v = 0;
    for( int pos = 0; pos < DIM; ++pos ) {
        if( !is_free(pos) ) v += is_black(pos) ? 1 : -1;
    }
    assert((-36 <= v) && (v <= 36));
    return v;
}

/**
 * Nos dice si ya se ha terminado el juego.
 */
inline bool state_t::terminal() const {
    if( is_full() ) return true;
    for( unsigned b = 0; b < DIM; ++b )
        if( is_black_move(b) || is_white_move(b) ) return false;
    return true;
}

/**
 * Revisa si se puede colocar una ficha en la posicion determinada.
 * Este metodo hay que completarlo. La parte de las diagonales.
 * Al menos tenemos ejemplos.
 */
inline bool state_t::outflank(bool color, int pos) const {
    if( !is_free(pos) ) return false;

    const int *p = 0;

    // Find if some stones are outflanked

    // Check rows
    const int *x = rows[pos - 4];
    while( *x != pos ) ++x;
    if( *(x+1) != -1 ) {
        for( p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); ++p );
        if( (p > x + 1) && (*p != -1) && !is_free(*p) ) return true;
    }
    if( x != rows[pos - 4] ) {
        for( p = x - 1; (p >= rows[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); --p );
        if( (p < x - 1) && (p >= rows[pos - 4]) && !is_free(*p) ) return true;
    }

    // Check columns
    x = cols[pos - 4];
    while( *x != pos ) ++x;
    if( *(x+1) != -1 ) {
        for( p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); ++p );
        if( (p > x + 1) && (*p != -1) && !is_free(*p) ) return true;
    }
    if( x != cols[pos - 4] ) {
        for( p = x - 1; (p >= cols[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); --p );
        if( (p < x - 1) && (p >= cols[pos - 4]) && !is_free(*p) ) return true;
    }

    // [CHECK OVER DIAGONALS REMOVED]
	
    // Check diagonal 1
    x = dia1[pos - 4];
    while( *x != pos ) ++x;
    if (*(x+1) != -1){
        for( p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); ++p );
        if( (p > x + 1) && (*p != -1) && !is_free(*p) ) return true;
    }
    if ( x != dia1[pos - 4 ]){
        for( p = x - 1; (p >= dia1[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); --p );
        if( (p < x - 1) && (p >= dia1[pos - 4]) && !is_free(*p) ) return true;
    }

    // Check diagonal 2
    x = dia2[pos - 4];
    while( *x != pos ) ++x;
    if (*(x+1) != -1){
        for( p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); ++p );
        if( (p > x + 1) && (*p != -1) && !is_free(*p) ) return true;
    }
    if ( x != dia2[pos - 4 ]){
        for( p = x - 1; (p >= dia2[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); --p );
        if( (p < x - 1) && (p >= dia2[pos - 4]) && !is_free(*p) ) return true;
    }
    
    return false;
}

inline void state_t::set_color(bool color, int pos) {
    if( color ) {
        if( pos < 4 ) {
            t_ |= 1 << pos;
        } else {
            free_ |= 1 << pos- 4;
            pos_ |= 1 << pos - 4;
        }
    } else {
        if( pos < 4 ) {
            t_ &= ~(1 << pos);
        } else {
            free_ |= 1 << pos - 4;
            pos_ &= ~(1 << pos - 4);
        }
    }
}
/**
 * Se mueve por el tablero considerando el color y la pos. 
 * Este va cambiando los colores de los discos comidos.
 * Falta las diagonales.
 */
inline state_t state_t::move(bool color, int pos) const {
    state_t s(*this);
    if( pos >= DIM ) return s; // Cuando la posicion es mayor o igual que DIM, este "pasa" la jugada

    assert(outflank(color, pos));
    s.set_color(color, pos);

    // Flip color of outflanked stones

    // Process rows
    const int *p = 0, *x = rows[pos - 4];
    while( *x != pos ) ++x;
    if( *(x+1) != -1 ) {
        for( p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); ++p );
        if( (p > x + 1) && (*p != -1) && !is_free(*p) ) {
            for( const int *q = x + 1; q < p; ++q ) s.set_color(color, *q);
        }
    }
    if( x != rows[pos - 4] ) {
        for( p = x - 1; (p >= rows[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); --p );
        if( (p < x - 1) && (p >= rows[pos - 4]) && !is_free(*p) ) {
            for( const int *q = x - 1; q > p; --q ) s.set_color(color, *q);
        }
    }

    // Process columns
    x = cols[pos - 4];
    while( *x != pos ) ++x;
    if( *(x+1) != -1 ) {
        for( p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); ++p );
        if( (p > x + 1) && (*p != -1) && !is_free(*p) ) {
            for( const int *q = x + 1; q < p; ++q ) s.set_color(color, *q);
        }
    }
    if( x != cols[pos - 4] ) {
        for( p = x - 1; (p >= cols[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); --p );
        if( (p < x - 1) && (p >= cols[pos - 4]) && !is_free(*p) ) {
            for( const int *q = x - 1; q > p; --q ) s.set_color(color, *q);
        }
    }

    // [PROCESS OF DIAGONALS REMOVED]

	// Process dia1
    x = dia1[pos - 4];
    while( *x != pos ) ++x;
    if( *(x+1) != -1 ) {
        for( p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); ++p );
        if( (p > x + 1) && (*p != -1) && !is_free(*p) ) {
            for( const int *q = x + 1; q < p; ++q ) s.set_color(color, *q);
        }
    }
    if( x != dia1[pos - 4] ) {
        for( p = x - 1; (p >= dia1[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); --p );
        if( (p < x - 1) && (p >= dia1[pos - 4]) && !is_free(*p) ) {
            for( const int *q = x - 1; q > p; --q ) s.set_color(color, *q);
        }
    }
	
	// Process dia2
    x = dia2[pos - 4];
    while( *x != pos ) ++x;
    if( *(x+1) != -1 ) {
        for( p = x + 1; (*p != -1) && !is_free(*p) && (color ^ is_black(*p)); ++p );
        if( (p > x + 1) && (*p != -1) && !is_free(*p) ) {
            for( const int *q = x + 1; q < p; ++q ) s.set_color(color, *q);
        }
    }
    if( x != dia2[pos - 4] ) {
        for( p = x - 1; (p >= dia2[pos - 4]) && !is_free(*p) && (color ^ is_black(*p)); --p );
        if( (p < x - 1) && (p >= dia2[pos - 4]) && !is_free(*p) ) {
            for( const int *q = x - 1; q > p; --q ) s.set_color(color, *q);
        }
    }
	
    return s;
}

/**
 * Imprime un state_t.
 * Toma en especial consideracion las posiciones
 * (i == 2) || (i == 3)) && ((j == 2) || (j == 3)
 * aun no se por qué.
 */
inline void state_t::print(std::ostream &os, int depth) const {
    os << "+";
    for( int j = 0; j < N; ++j ) os << "-";
    os << "+" << std::endl;

    int pos = 4;
    for( int i = 0; i < N; ++i ) {
        os << "|";
        for( int j = 0; j < N; ++j ) {
            if( ((i != 2) && (i != 3)) || ((j != 2) && (j != 3)) ) {
                os << (is_free(pos) ? '.' : (is_black(pos) ? '&' : '0'));
                ++pos;
            } else {
                assert(((i == 2) || (i == 3)) && ((j == 2) || (j == 3)));
                int p = ((i-2) << 1) + (j-2);
                os << (is_free(p) ? '.' : (is_black(p) ? '&' : '0'));
            }
        }
        os << "|" << std::endl;
    }

    os << "+";
    for( int j = 0; j < N; ++j ) os << "-";
    os << "+" << std::endl;
}

inline void state_t::print_bits(std::ostream &os) const {
    for( int i = 3; i >= 0; --i ) os << (t_ & (1 << i) ? '1' : '0');
    os << ":";
    for( int i = 31; i >= 0; --i ) os << (pos_ & (1 << i) ? '1' : '0');
    os << ":";
    for( int i = 31; i >= 0; --i ) os << (free_ & (1 << i) ? '1' : '0');
}
/**
 * Hace overhead del operador <<
 * pretty cool.
 */
inline std::ostream& operator<<(std::ostream &os, const state_t &state) {
    state.print(os);
    return os;
}

