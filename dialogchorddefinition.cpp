#include "dialogchorddefinition.h"
#include "ui_dialogchorddefinition.h"

DialogChordDefinition::DialogChordDefinition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChordDefinition)
{
    ui->setupUi(this);
    InitialSetup();
    connect ( ui->pushButtonCancel,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect ( ui->pushButtonSave,SIGNAL(clicked(bool)),this,SLOT(save()));
}

DialogChordDefinition::~DialogChordDefinition()
{
    delete ui;
}


void DialogChordDefinition::InitialSetup()
{
    m_chords["C"]="0 3 3 2 0 1 0";
    m_chords["C7"]="3 0 3 2 3 1 0";
    m_chords["C-"]="5 2 x 1 2 2 x";
    m_chords["C-6(V)"]="5 2 x 1 2 2 x";
    m_chords["C7(III)"]="3 1 1 3 1 3 1";
    m_chords["C9"]="0 3 3 2 3 3 3";
    m_chords["C(III)"]="3 1 1 3 3 3 1";
    m_chords["C7(III)"]="3 1 1 3 1 3 1";
    m_chords["C(VIII)"]="8 1 3 3 2 1 1";
    m_chords["C#"]="4 1 1 3 3 3 1";
    m_chords["C#-"]="4 1 1 3 3 2 1";
    m_chords["C#7"]="4 1 1 3 1 3 1";
    m_chords["C7°(IV)"]="4 x 2 3 1 3 x";
    m_chords["C#7°(V)"]="5 x 2 3 1 3 x";
    m_chords["C#-7b5(III)"]="3 x 1 2 1 2 x";
    m_chords["Db(IV)"]="4 1 1 3 3 3 1";
    m_chords["Db9"]="0 4 4 3 4 4 4";
    m_chords["DbM7"]="4 x 1 3 2 3 1";
    m_chords["Db-"]="4 1 1 3 3 2 1";
    m_chords["D"]="0 x x 0 2 3 2";
    m_chords["D-"]="0 x x 0 2 3 1";
    m_chords["D7"]="0 x x 0 2 1 2";
    m_chords["D-(V)"]="5 1 1 3 3 2 1";
    m_chords["D-6"]="0 x 2 3 2 3 x";
    m_chords["D-11(VII)"]="7 3 x 3 3 1 x";
    m_chords["D"]="0 x x 0 2 3 2";
    m_chords["D(V)"]="5 1 1 3 3 3 1";
    m_chords["D7(V)"]="5 1 1 3 1 3 1";
    m_chords["D#"]="6 1 1 3 3 3 1";
    m_chords["D#7"]="6 1 1 3 1 3 1";
    m_chords["D#°(VI)"]="6 x 2 3 1 3 x";
    m_chords["D9"]="4 2 2 1 2 2 2";
    m_chords["D°"]="0 x x 0 1 0 1";
    m_chords["E"]="0 0 2 2 1 0 0";
    m_chords["E7(VII)"]="7 x 3 2 3 1 x";
    m_chords["E7"]="0 0 2 2 1 3 0";
    m_chords["E-7b5(VI)"]="6 x 1 2 1 2 x";
    m_chords["E7b9(V)"]="5 x 2 1 2 1 x";
    m_chords["E°"]="0 x x 2 3 2 3";
    m_chords["E°7(III)"]="3 x 2 3 1 3 x";
    m_chords["E°7(VI)"]="6 x 2 3 1 3 x";
    m_chords["E-"]="0 0 2 2 0 0 0";
    m_chords["E-6(IV)"]="4 x 1 2 1 2 x";
    m_chords["E-(VII)"]="7 1 1 3 3 2 1";
    m_chords["E9(VI)"]="6 2 2 1 2 2 2";
    m_chords["F"]="0 1 3 3 2 1 1";
    m_chords["F-"]="0 1 3 3 1 1 1";
    m_chords["F-(VIII)"]="8 1 1 3 3 2 1";
    m_chords[" F-9/13"]="0 x x 3 1 3 3";
    m_chords["F°"]="0 x x 3 4 3 4";
    m_chords["F7(VIII)"]="0 1 3 1 2 4 1";
    m_chords["F#"]="0 2 4 4 3 2 2";
    m_chords["F#-"]="0 2 4 4 2 2 2";
    m_chords["F#7"]="2 1 3 1 2 4 1";
    m_chords["F#°7(VIII)"]="8 x 2 3 1 3 x";
    m_chords["G"]="3 3 2 0 0 0 3";
    m_chords["G7"]="3 3 2 0 0 0 1";
    m_chords["G(III)"]="3 1 3 3 2 1 1";
    m_chords["G7(III)"]="3 1 3 1 2 4 1";
    m_chords["G-"]="3 1 3 3 1 1 1";
    m_chords["G-7"]="3 1 3 1 1 4 1";
    m_chords["G-6"]="0 3 x 2 3 3 3";
    m_chords["G-9/13(III)"]="3 x x 3 1 3 3";
    m_chords["G#"]="4 1 3 3 2 1 1";
    m_chords["G#-"]="4 1 3 3 1 1 1";
    m_chords["G#-6(III)"]="3 2 x 1 2 2 x";
    m_chords["G#7"]="3 2 1 2 2 2 2";
    m_chords["A"]="0 x 0 2 2 2 0";
    m_chords["A(V)"]="5 1 3 3 2 1 1";
    m_chords["A-"]="0 x 0 2 2 1 0";
    m_chords["A-(V)"]="5 1 3 3 1 1 1";
    m_chords["A-(XII)"]="12 1 1 3 3 2 1";
    m_chords["A-6(IV)"]="4 2 x 1 2 2 x";
    m_chords["A-11(II)"]="2 3 x 3 3 1 x";
    m_chords["A7"]="0 x 0 2 0 2 0";
    m_chords["A7(V)"]="5 1 3 1 2 4 1";
    m_chords["A7(IV)"]="4 2 1 2 2 2 2";
    m_chords["A#7(VI)"]="6 1 3 1 2 4 1";
    m_chords["A7b9(X)"]="10 x 2 1 2 1 x";
    m_chords["A7(IX)"]="9 x 3 2 3 1 x";
    m_chords["A#"]="6 1 3 3 2 1 1";
    m_chords["A#7(V)"]="5 2 1 2 2 2 2";
    m_chords["A#7°"]="0 x 3 4 2 4 x";
    m_chords["Bb"]="1 1 1 3 3 3 1";
    m_chords["Bb7"]="1 1 1 3 1 3 1";
    m_chords["Bb-"]="1 1 1 3 3 2 1";
    m_chords["B"]="2 1 1 3 3 3 1";
    m_chords["B(VII)"]="7 1 3 3 2 1 1";
    m_chords["B-"]="2 1 1 3 3 2 1";
    m_chords["B7"]="0 2 2 4 2 4 2";
    m_chords["B7(VI)"]="6 2 1 2 2 2 2";
    m_chords["B7°(III)"]="3 x 2 3 1 3 x";
    m_chords["B-6(VI)"]="6 2 x 1 2 2 x";
    m_chords["B-11"]="4 3 x 3 3 1 x";
    m_chords["NO"]="0 x x x x x x";
}
