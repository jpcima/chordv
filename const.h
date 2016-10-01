#ifndef CONST
#define CONST

class Const{
public:
    enum PageNumber { No, Center, Outside };
    static PageNumber getPageNumber( int i ) {if ( i == 1 ) return Center; else if ( i == 2 ) return Outside ; else return No; }
}
;

#endif // CONST

