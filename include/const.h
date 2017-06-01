#ifndef CONST
#define CONST

class Const{
public:
    enum PageNumber { No, Center, Outside };
    enum Plex { Simplex, Duplex};
    static PageNumber getPageNumber( int i ) {if ( i == 1 ) return Center; else if ( i == 2 ) return Outside ; else return No; }
}
;

#endif // CONST

