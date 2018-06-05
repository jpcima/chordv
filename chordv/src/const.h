#ifndef CONST
#define CONST

///
/// \brief The Const class set of constant classes
///
class Const{
public:
    ///
    /// \brief The PageNumber enum can be No for no pagnumber, Center ou Outside
    ///
    enum PageNumber { No, Center, Outside };
    ///
    /// \brief The Plex enum can be Simplex it one side is printed, or Duplex if each page is printed
    ///
    enum Plex { Simplex, Duplex};
    ///
    /// \brief The PageStyle enum type of page number on button of each page
    ///  Number is 1
    ///  Number and Tiret - 1 -
    ///  NumberDivideByPageNUmber 1/50
    ///  NumberAndArrows <1>
    ///
    enum PageStyle { Number, NumberAndTiret, NumberDivideByPageNUmber, NumberAndArrows};
    ///
    /// \brief getPageNumber return No Center or Outsde from 0 1 or 2 parameter
    /// \param i
    /// \return
    ///
    static PageNumber getPageNumber( int i ) {if ( i == 1 ) return Center; else if ( i == 2 ) return Outside ; else return No; }
}
;

#endif // CONST

