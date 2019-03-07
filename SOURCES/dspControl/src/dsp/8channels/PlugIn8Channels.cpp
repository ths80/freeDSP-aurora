#include <cstdint>

#include <QObject>

#include "PlugIn8Channels.hpp"

#include "QChannel.hpp"
#include "QDspBlock.hpp"
#include "QHighPass.hpp"
#include "QLowPass.hpp"
#include "QPeq.hpp"
#include "QPhase.hpp"
#include "QDelay.hpp"
#include "QLowShelv.hpp"
#include "QHighShelv.hpp"
#include "QInputSelect.hpp"
#include "QOutputSelect.hpp"

using namespace Vektorraum;

//==============================================================================
/*! Constructor
 *
 */
CPlugIn8Channels::CPlugIn8Channels( tfloat samplerate )
{
  fs = samplerate;

  //----------------------------------------------------------------------------
  //--- Init frequency vector
  //----------------------------------------------------------------------------
  tuint n = 0;
  tfloat pointsperdecade = 100.0;
  tfloat fstart = 1.0;
  tfloat fstop = 20000.0;

  for( tfloat k = 1.0; k < 10.0; k = k + 10.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
      n++;
  }
  for( tfloat k = 10.0; k < 100.0; k = k + 100.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
      n++;
  }
  for( tfloat k = 100.0; k < 1000.0; k = k + 1000.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
      n++;
  }
  for( tfloat k = 1000.0; k < 10000.0; k = k + 10000.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
      n++;
  }
  for( tfloat k = 10000.0; k < 20001.0; k = k + 100000.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
      n++;
  }

  tvector<tfloat> f( n );
  n = 0;
  for( tfloat k = 1.0; k < 10.0; k = k + 10.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
    {
      f[n] = k;
      n++;
    }
  }
  for( tfloat k = 10.0; k < 100.0; k = k + 100.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
    {
      f[n] = k;
      n++;
    }
  }
  for( tfloat k = 100.0; k < 1000.0; k = k + 1000.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) ) {
      f[n] = k;
      n++;
    }
  }
  for( tfloat k = 1000.0; k < 10000.0; k = k + 10000.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
    {
      f[n] = k;
      n++;
    }
  }
  for( tfloat k = 10000.0; k < 20001.0; k = k + 100000.0/pointsperdecade )
  {
    if( (k >= fstart) && (k <= fstop) )
    {
      f[n] = k;
      n++;
    }
  }
  freq = f;
}

//==============================================================================
/*! Destructor
 *
 */
CPlugIn8Channels::~CPlugIn8Channels( void )
{

}

//==============================================================================
/*!
 *
 */
tDspChannel CPlugIn8Channels::getGuiForChannel( unsigned int chn, tfloat fs, CFreeDspAurora* ptrdsp, QWidget* parent )
{
  tDspChannel dspChannel;

  QInputSelect* input;
  QHighPass* hp;
  QLowShelv* lshelv;
  QPeq* peq01;
  QPeq* peq02;
  QPeq* peq03;
  QPeq* peq04;
  QPeq* peq05;
  QPeq* peq06;
  QPeq* peq07;
  QPeq* peq08;
  QPeq* peq09;
  QPeq* peq10;
  QHighShelv* hshelv;
  QLowPass* lp;
  QPhase* phase;
  QDelay* dly;
  QGain* gain = nullptr;
  QOutputSelect* output;

  QHBoxLayout* layout = new QHBoxLayout;
  QChannel* channel = new QChannel;

  if( chn == 0 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 1
    dspChannel.name = QString( "Channel 1" );

    input = new QInputSelect( 0, MOD_NX1_1_1_MONOMUXSIGMA300NS1INDEX_ADDR, ptrdsp );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                      MOD_HP1_1_ALG0_STAGE0_B2_ADDR, MOD_HP1_1_ALG0_STAGE0_B1_ADDR, MOD_HP1_1_ALG0_STAGE0_B0_ADDR,
                      MOD_HP1_1_ALG0_STAGE0_A2_ADDR, MOD_HP1_1_ALG0_STAGE0_A1_ADDR,
                      MOD_HP1_2_ALG0_STAGE0_B2_ADDR, MOD_HP1_2_ALG0_STAGE0_B1_ADDR, MOD_HP1_2_ALG0_STAGE0_B0_ADDR,
                      MOD_HP1_2_ALG0_STAGE0_A2_ADDR, MOD_HP1_2_ALG0_STAGE0_A1_ADDR,
                      MOD_HP1_3_ALG0_STAGE0_B2_ADDR, MOD_HP1_3_ALG0_STAGE0_B1_ADDR, MOD_HP1_3_ALG0_STAGE0_B0_ADDR,
                      MOD_HP1_3_ALG0_STAGE0_A2_ADDR, MOD_HP1_3_ALG0_STAGE0_A1_ADDR,
                      MOD_HP1_4_ALG0_STAGE0_B2_ADDR, MOD_HP1_4_ALG0_STAGE0_B1_ADDR, MOD_HP1_4_ALG0_STAGE0_B0_ADDR,
                      MOD_HP1_4_ALG0_STAGE0_A2_ADDR, MOD_HP1_4_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp );
    layout->addWidget( hp );
    channel->addDspBlock( hp );

    lshelv = new QLowShelv( 0.0, 100.0, 1.0,
                            MOD_LOWSHELV1_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV1_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV1_ALG0_STAGE0_B0_ADDR,
                            MOD_LOWSHELV1_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV1_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 0.0, 1000.0, 1.0,
                  MOD_PARAMEQ1_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE0_B0_ADDR,
                  MOD_PARAMEQ1_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE0_A1_ADDR,
                  fs,
                  ptrdsp,
                  channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );
    channel->addPeq( peq01 );

    peq02 = new QPeq( 0.0, 2000.0, 2.0,
                    MOD_PARAMEQ1_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE1_B0_ADDR,
                    MOD_PARAMEQ1_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE1_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );
    channel->addPeq( peq02 );

    peq03 = new QPeq( 0.0, 3000.0, 2.0,
                    MOD_PARAMEQ1_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE2_B0_ADDR,
                    MOD_PARAMEQ1_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE2_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );
    channel->addPeq( peq03 );

    peq04 = new QPeq( 0.0, 4000.0, 2.0,
                    MOD_PARAMEQ1_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE3_B0_ADDR,
                    MOD_PARAMEQ1_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE3_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );
    channel->addPeq( peq04 );

    peq05 = new QPeq( 0.0, 5000.0, 2.0,
                  MOD_PARAMEQ1_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE4_B0_ADDR,
                  MOD_PARAMEQ1_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE4_A1_ADDR,
                  fs,
                  ptrdsp,
                  channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );
    channel->addPeq( peq05 );

    peq06 = new QPeq( 0.0, 6000.0, 2.0,
                    MOD_PARAMEQ1_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE5_B0_ADDR,
                    MOD_PARAMEQ1_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE5_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );
    channel->addPeq( peq06 );

    peq07 = new QPeq( 0.0, 7000.0, 2.0,
                    MOD_PARAMEQ1_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE6_B0_ADDR,
                    MOD_PARAMEQ1_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE6_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );
    channel->addPeq( peq07 );

    peq08 = new QPeq( 0.0, 8000.0, 2.0,
                    MOD_PARAMEQ1_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE7_B0_ADDR,
                    MOD_PARAMEQ1_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE7_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );
    channel->addPeq( peq08 );

    peq09 = new QPeq( 0.0, 9000.0, 2.0,
                    MOD_PARAMEQ1_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE8_B0_ADDR,
                    MOD_PARAMEQ1_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE8_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );
    channel->addPeq( peq09 );

    peq10 = new QPeq( 0.0, 10000.0, 2.0,
                  MOD_PARAMEQ1_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ1_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ1_ALG0_STAGE9_B0_ADDR,
                  MOD_PARAMEQ1_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ1_ALG0_STAGE9_A1_ADDR,
                  fs,
                  ptrdsp,
                  channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );
    channel->addPeq( peq10 );

    hshelv = new QHighShelv( 0.0, 5000.0, 1.0,
                            MOD_HIGHSHELV1_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV1_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV1_ALG0_STAGE0_B0_ADDR,
                            MOD_HIGHSHELV1_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV1_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                      MOD_LP1_1_ALG0_STAGE0_B2_ADDR, MOD_LP1_1_ALG0_STAGE0_B1_ADDR, MOD_LP1_1_ALG0_STAGE0_B0_ADDR,
                      MOD_LP1_1_ALG0_STAGE0_A2_ADDR, MOD_LP1_1_ALG0_STAGE0_A1_ADDR,
                      MOD_LP1_2_ALG0_STAGE0_B2_ADDR, MOD_LP1_2_ALG0_STAGE0_B1_ADDR, MOD_LP1_2_ALG0_STAGE0_B0_ADDR,
                      MOD_LP1_2_ALG0_STAGE0_A2_ADDR, MOD_LP1_2_ALG0_STAGE0_A1_ADDR,
                      MOD_LP1_3_ALG0_STAGE0_B2_ADDR, MOD_LP1_3_ALG0_STAGE0_B1_ADDR, MOD_LP1_3_ALG0_STAGE0_B0_ADDR,
                      MOD_LP1_3_ALG0_STAGE0_A2_ADDR, MOD_LP1_3_ALG0_STAGE0_A1_ADDR,
                      MOD_LP1_4_ALG0_STAGE0_B2_ADDR, MOD_LP1_4_ALG0_STAGE0_B1_ADDR, MOD_LP1_4_ALG0_STAGE0_B0_ADDR,
                      MOD_LP1_4_ALG0_STAGE0_A2_ADDR, MOD_LP1_4_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp );
    layout->addWidget( lp );
    channel->addDspBlock( lp );

    phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE1_ALG0_STAGE0_B2_ADDR, MOD_PHASE1_ALG0_STAGE0_B1_ADDR, MOD_PHASE1_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE1_ALG0_STAGE0_A2_ADDR, MOD_PHASE1_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp );
    layout->addWidget( phase );
    channel->addDspBlock( phase );
    
    dly = new QDelay( 0.0, fs, MOD_DELAY1_DELAYAMT_ADDR, ptrdsp );
    layout->addWidget( dly );
    channel->addDspBlock( dly ); 

    gain = new QGain( 0.0, MOD_GAIN1_ALG0_TARGET_ADDR, ptrdsp );
    layout->addWidget( gain );
    channel->addDspBlock( gain );
 
    output = new QOutputSelect( 1, 0, ptrdsp );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( hp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
  }
  else if( chn == 1 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 2
    dspChannel.name = QString( "Channel 2" );

    input = new QInputSelect( 1, MOD_NX1_1_2_MONOMUXSIGMA300NS2INDEX_ADDR, ptrdsp );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                      MOD_HP2_1_ALG0_STAGE0_B2_ADDR, MOD_HP2_1_ALG0_STAGE0_B1_ADDR, MOD_HP2_1_ALG0_STAGE0_B0_ADDR,
                      MOD_HP2_1_ALG0_STAGE0_A2_ADDR, MOD_HP2_1_ALG0_STAGE0_A1_ADDR,
                      MOD_HP2_2_ALG0_STAGE0_B2_ADDR, MOD_HP2_2_ALG0_STAGE0_B1_ADDR, MOD_HP2_2_ALG0_STAGE0_B0_ADDR,
                      MOD_HP2_2_ALG0_STAGE0_A2_ADDR, MOD_HP2_2_ALG0_STAGE0_A1_ADDR,
                      MOD_HP2_3_ALG0_STAGE0_B2_ADDR, MOD_HP2_3_ALG0_STAGE0_B1_ADDR, MOD_HP2_3_ALG0_STAGE0_B0_ADDR,
                      MOD_HP2_3_ALG0_STAGE0_A2_ADDR, MOD_HP2_3_ALG0_STAGE0_A1_ADDR,
                      MOD_HP2_4_ALG0_STAGE0_B2_ADDR, MOD_HP2_4_ALG0_STAGE0_B1_ADDR, MOD_HP2_4_ALG0_STAGE0_B0_ADDR,
                      MOD_HP2_4_ALG0_STAGE0_A2_ADDR, MOD_HP2_4_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp );
    layout->addWidget( hp );
    channel->addDspBlock( hp );

    lshelv = new QLowShelv( 0.0, 100.0, 1.0,
                            MOD_LOWSHELV2_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV2_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV2_ALG0_STAGE0_B0_ADDR,
                            MOD_LOWSHELV2_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV2_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 0.0, 1000.0, 1.0,
                      MOD_PARAMEQ2_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE0_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );
    channel->addPeq( peq01 );

    peq02 = new QPeq( 0.0, 2000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE1_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE1_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );
    channel->addPeq( peq02 );

    peq03 = new QPeq( 0.0, 3000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE2_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE2_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );
    channel->addPeq( peq03 );

    peq04 = new QPeq( 0.0, 4000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE3_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE3_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );
    channel->addPeq( peq04 );

    peq05 = new QPeq( 0.0, 5000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE4_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE4_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );
    channel->addPeq( peq05 );

    peq06 = new QPeq( 0.0, 6000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE5_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE5_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );
    channel->addPeq( peq06 );

    peq07 = new QPeq( 0.0, 7000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE6_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE6_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );
    channel->addPeq( peq07 );

    peq08 = new QPeq( 0.0, 8000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE7_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE7_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );
    channel->addPeq( peq08 );

    peq09 = new QPeq( 0.0, 9000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE8_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE8_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );
    channel->addPeq( peq09 );

    peq10 = new QPeq( 0.0, 10000.0, 2.0,
                      MOD_PARAMEQ2_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ2_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ2_ALG0_STAGE9_B0_ADDR,
                      MOD_PARAMEQ2_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ2_ALG0_STAGE9_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );
    channel->addPeq( peq10 );

    hshelv = new QHighShelv( 0.0, 5000.0, 1.0,
                           MOD_HIGHSHELV2_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV2_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV2_ALG0_STAGE0_B0_ADDR,
                           MOD_HIGHSHELV2_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV2_ALG0_STAGE0_A1_ADDR,
                           fs,
                           ptrdsp );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                      MOD_LP2_1_ALG0_STAGE0_B2_ADDR, MOD_LP2_1_ALG0_STAGE0_B1_ADDR, MOD_LP2_1_ALG0_STAGE0_B0_ADDR,
                      MOD_LP2_1_ALG0_STAGE0_A2_ADDR, MOD_LP2_1_ALG0_STAGE0_A1_ADDR,
                      MOD_LP2_2_ALG0_STAGE0_B2_ADDR, MOD_LP2_2_ALG0_STAGE0_B1_ADDR, MOD_LP2_2_ALG0_STAGE0_B0_ADDR,
                      MOD_LP2_2_ALG0_STAGE0_A2_ADDR, MOD_LP2_2_ALG0_STAGE0_A1_ADDR,
                      MOD_LP2_3_ALG0_STAGE0_B2_ADDR, MOD_LP2_3_ALG0_STAGE0_B1_ADDR, MOD_LP2_3_ALG0_STAGE0_B0_ADDR,
                      MOD_LP2_3_ALG0_STAGE0_A2_ADDR, MOD_LP2_3_ALG0_STAGE0_A1_ADDR,
                      MOD_LP2_4_ALG0_STAGE0_B2_ADDR, MOD_LP2_4_ALG0_STAGE0_B1_ADDR, MOD_LP2_4_ALG0_STAGE0_B0_ADDR,
                      MOD_LP2_4_ALG0_STAGE0_A2_ADDR, MOD_LP2_4_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp );
    layout->addWidget( lp );
    channel->addDspBlock( lp );

    phase = new QPhase( 1000.0, 1.0,
                        MOD_PHASE2_ALG0_STAGE0_B2_ADDR, MOD_PHASE2_ALG0_STAGE0_B1_ADDR, MOD_PHASE2_ALG0_STAGE0_B0_ADDR,
                        MOD_PHASE2_ALG0_STAGE0_A2_ADDR, MOD_PHASE2_ALG0_STAGE0_A1_ADDR,
                        fs,
                        ptrdsp );
    layout->addWidget( phase );
    channel->addDspBlock( phase );

    dly = new QDelay( 0.0, fs, MOD_DELAY2_DELAYAMT_ADDR, ptrdsp );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN2_ALG0_TARGET_ADDR, ptrdsp );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( hp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
  }
  else if( chn == 2 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 3
    dspChannel.name = QString( "Channel 3" );

    input = new QInputSelect( 2, MOD_NX1_1_3_MONOMUXSIGMA300NS3INDEX_ADDR, ptrdsp );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                        MOD_HP3_1_ALG0_STAGE0_B2_ADDR, MOD_HP3_1_ALG0_STAGE0_B1_ADDR, MOD_HP3_1_ALG0_STAGE0_B0_ADDR,
                        MOD_HP3_1_ALG0_STAGE0_A2_ADDR, MOD_HP3_1_ALG0_STAGE0_A1_ADDR,
                        MOD_HP3_2_ALG0_STAGE0_B2_ADDR, MOD_HP3_2_ALG0_STAGE0_B1_ADDR, MOD_HP3_2_ALG0_STAGE0_B0_ADDR,
                        MOD_HP3_2_ALG0_STAGE0_A2_ADDR, MOD_HP3_2_ALG0_STAGE0_A1_ADDR,
                        MOD_HP3_3_ALG0_STAGE0_B2_ADDR, MOD_HP3_3_ALG0_STAGE0_B1_ADDR, MOD_HP3_3_ALG0_STAGE0_B0_ADDR,
                        MOD_HP3_3_ALG0_STAGE0_A2_ADDR, MOD_HP3_3_ALG0_STAGE0_A1_ADDR,
                        MOD_HP3_4_ALG0_STAGE0_B2_ADDR, MOD_HP3_4_ALG0_STAGE0_B1_ADDR, MOD_HP3_4_ALG0_STAGE0_B0_ADDR,
                        MOD_HP3_4_ALG0_STAGE0_A2_ADDR, MOD_HP3_4_ALG0_STAGE0_A1_ADDR,
                        fs,
                        ptrdsp );
    layout->addWidget( hp );
    channel->addDspBlock( hp );

    lshelv = new QLowShelv( 6.0, 100.0, 1.0,
                            MOD_LOWSHELV3_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV3_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV3_ALG0_STAGE0_B0_ADDR,
                            MOD_LOWSHELV3_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV3_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 6.0, 1000.0, 1.0,
                      MOD_PARAMEQ3_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE0_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );
    channel->addPeq( peq01 );

    peq02 = new QPeq( -6.0, 2000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE1_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE1_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );
    channel->addPeq( peq02 );

    peq03 = new QPeq( 6.0, 3000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE2_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE2_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );
    channel->addPeq( peq03 );

    peq04 = new QPeq( -6.0, 4000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE3_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE3_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );
    channel->addPeq( peq04 );

    peq05 = new QPeq( 6.0, 5000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE4_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE4_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );
    channel->addPeq( peq05 );

    peq06 = new QPeq( -6.0, 6000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE5_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE5_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );
    channel->addPeq( peq06 );

    peq07 = new QPeq( 6.0, 7000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE6_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE6_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );
    channel->addPeq( peq07 );

    peq08 = new QPeq( -6.0, 8000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE7_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE7_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );
    channel->addPeq( peq08 );

    peq09 = new QPeq( 6.0, 9000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE8_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE8_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );
    channel->addPeq( peq09 );

    peq10 = new QPeq( -6.0, 10000.0, 2.0,
                      MOD_PARAMEQ3_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ3_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ3_ALG0_STAGE9_B0_ADDR,
                      MOD_PARAMEQ3_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ3_ALG0_STAGE9_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );
    channel->addPeq( peq10 );

    hshelv = new QHighShelv( 6.0, 5000.0, 1.0,
                            MOD_HIGHSHELV3_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV3_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV3_ALG0_STAGE0_B0_ADDR,
                            MOD_HIGHSHELV3_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV3_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                     MOD_LP3_1_ALG0_STAGE0_B2_ADDR, MOD_LP3_1_ALG0_STAGE0_B1_ADDR, MOD_LP3_1_ALG0_STAGE0_B0_ADDR,
                     MOD_LP3_1_ALG0_STAGE0_A2_ADDR, MOD_LP3_1_ALG0_STAGE0_A1_ADDR,
                     MOD_LP3_2_ALG0_STAGE0_B2_ADDR, MOD_LP3_2_ALG0_STAGE0_B1_ADDR, MOD_LP3_2_ALG0_STAGE0_B0_ADDR,
                     MOD_LP3_2_ALG0_STAGE0_A2_ADDR, MOD_LP3_2_ALG0_STAGE0_A1_ADDR,
                     MOD_LP3_3_ALG0_STAGE0_B2_ADDR, MOD_LP3_3_ALG0_STAGE0_B1_ADDR, MOD_LP3_3_ALG0_STAGE0_B0_ADDR,
                     MOD_LP3_3_ALG0_STAGE0_A2_ADDR, MOD_LP3_3_ALG0_STAGE0_A1_ADDR,
                     MOD_LP3_4_ALG0_STAGE0_B2_ADDR, MOD_LP3_4_ALG0_STAGE0_B1_ADDR, MOD_LP3_4_ALG0_STAGE0_B0_ADDR,
                     MOD_LP3_4_ALG0_STAGE0_A2_ADDR, MOD_LP3_4_ALG0_STAGE0_A1_ADDR,
                     fs,
                     ptrdsp );
    layout->addWidget( lp );
    channel->addDspBlock( lp );

    phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE3_ALG0_STAGE0_B2_ADDR, MOD_PHASE3_ALG0_STAGE0_B1_ADDR, MOD_PHASE3_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE3_ALG0_STAGE0_A2_ADDR, MOD_PHASE3_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp );
    layout->addWidget( phase );
    channel->addDspBlock( phase );

    dly = new QDelay( 0.0, 48000.0, MOD_DELAY3_DELAYAMT_ADDR, ptrdsp );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN3_ALG0_TARGET_ADDR, ptrdsp );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( hp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
  }
  else if( chn == 3 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 4
    dspChannel.name = QString( "Channel 4" );

    input = new QInputSelect( 3, MOD_NX1_1_4_MONOMUXSIGMA300NS4INDEX_ADDR, ptrdsp );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                        MOD_HP4_1_ALG0_STAGE0_B2_ADDR, MOD_HP4_1_ALG0_STAGE0_B1_ADDR, MOD_HP4_1_ALG0_STAGE0_B0_ADDR,
                        MOD_HP4_1_ALG0_STAGE0_A2_ADDR, MOD_HP4_1_ALG0_STAGE0_A1_ADDR,
                        MOD_HP4_2_ALG0_STAGE0_B2_ADDR, MOD_HP4_2_ALG0_STAGE0_B1_ADDR, MOD_HP4_2_ALG0_STAGE0_B0_ADDR,
                        MOD_HP4_2_ALG0_STAGE0_A2_ADDR, MOD_HP4_2_ALG0_STAGE0_A1_ADDR,
                        MOD_HP4_3_ALG0_STAGE0_B2_ADDR, MOD_HP4_3_ALG0_STAGE0_B1_ADDR, MOD_HP4_3_ALG0_STAGE0_B0_ADDR,
                        MOD_HP4_3_ALG0_STAGE0_A2_ADDR, MOD_HP4_3_ALG0_STAGE0_A1_ADDR,
                        MOD_HP4_4_ALG0_STAGE0_B2_ADDR, MOD_HP4_4_ALG0_STAGE0_B1_ADDR, MOD_HP4_4_ALG0_STAGE0_B0_ADDR,
                        MOD_HP4_4_ALG0_STAGE0_A2_ADDR, MOD_HP4_4_ALG0_STAGE0_A1_ADDR,
                        fs,
                        ptrdsp );
    layout->addWidget( hp );
    channel->addDspBlock( hp );

    lshelv = new QLowShelv( 6.0, 100.0, 1.0,
                            MOD_LOWSHELV4_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV4_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV4_ALG0_STAGE0_B0_ADDR,
                            MOD_LOWSHELV4_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV4_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 6.0, 1000.0, 1.0,
                      MOD_PARAMEQ4_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE0_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );
    channel->addPeq( peq01 );

    peq02 = new QPeq( -6.0, 2000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE1_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE1_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );
    channel->addPeq( peq02 );

    peq03 = new QPeq( 6.0, 3000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE2_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE2_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );
    channel->addPeq( peq03 );

    peq04 = new QPeq( -6.0, 4000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE3_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE3_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );
    channel->addPeq( peq04 );

    peq05 = new QPeq( 6.0, 5000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE4_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE4_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );
    channel->addPeq( peq05 );

    peq06 = new QPeq( -6.0, 6000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE5_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE5_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );
    channel->addPeq( peq06 );

    peq07 = new QPeq( 6.0, 7000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE6_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE6_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );
    channel->addPeq( peq07 );

    peq08 = new QPeq( -6.0, 8000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE7_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE7_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );
    channel->addPeq( peq08 );

    peq09 = new QPeq( 6.0, 9000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE8_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE8_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );
    channel->addPeq( peq09 );

    peq10 = new QPeq( -6.0, 10000.0, 2.0,
                      MOD_PARAMEQ4_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ4_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ4_ALG0_STAGE9_B0_ADDR,
                      MOD_PARAMEQ4_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ4_ALG0_STAGE9_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );
    channel->addPeq( peq10 );

    hshelv = new QHighShelv( 6.0, 5000.0, 1.0,
                            MOD_HIGHSHELV4_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV4_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV4_ALG0_STAGE0_B0_ADDR,
                            MOD_HIGHSHELV4_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV4_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                     MOD_LP4_1_ALG0_STAGE0_B2_ADDR, MOD_LP4_1_ALG0_STAGE0_B1_ADDR, MOD_LP4_1_ALG0_STAGE0_B0_ADDR,
                     MOD_LP4_1_ALG0_STAGE0_A2_ADDR, MOD_LP4_1_ALG0_STAGE0_A1_ADDR,
                     MOD_LP4_2_ALG0_STAGE0_B2_ADDR, MOD_LP4_2_ALG0_STAGE0_B1_ADDR, MOD_LP4_2_ALG0_STAGE0_B0_ADDR,
                     MOD_LP4_2_ALG0_STAGE0_A2_ADDR, MOD_LP4_2_ALG0_STAGE0_A1_ADDR,
                     MOD_LP4_3_ALG0_STAGE0_B2_ADDR, MOD_LP4_3_ALG0_STAGE0_B1_ADDR, MOD_LP4_3_ALG0_STAGE0_B0_ADDR,
                     MOD_LP4_3_ALG0_STAGE0_A2_ADDR, MOD_LP4_3_ALG0_STAGE0_A1_ADDR,
                     MOD_LP4_4_ALG0_STAGE0_B2_ADDR, MOD_LP4_4_ALG0_STAGE0_B1_ADDR, MOD_LP4_4_ALG0_STAGE0_B0_ADDR,
                     MOD_LP4_4_ALG0_STAGE0_A2_ADDR, MOD_LP4_4_ALG0_STAGE0_A1_ADDR,
                     fs,
                     ptrdsp );
    layout->addWidget( lp );
    channel->addDspBlock( lp );

    phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE4_ALG0_STAGE0_B2_ADDR, MOD_PHASE4_ALG0_STAGE0_B1_ADDR, MOD_PHASE4_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE4_ALG0_STAGE0_A2_ADDR, MOD_PHASE4_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp );
    layout->addWidget( phase );
    channel->addDspBlock( phase );

    dly = new QDelay( 0.0, 48000.0, MOD_DELAY4_DELAYAMT_ADDR, ptrdsp );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN4_ALG0_TARGET_ADDR, ptrdsp );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( hp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
  }
  else if( chn == 4 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 5
    dspChannel.name = QString( "Channel 5" );

    input = new QInputSelect( 4, MOD_NX1_1_5_MONOMUXSIGMA300NS5INDEX_ADDR, ptrdsp );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                        MOD_HP5_1_ALG0_STAGE0_B2_ADDR, MOD_HP5_1_ALG0_STAGE0_B1_ADDR, MOD_HP5_1_ALG0_STAGE0_B0_ADDR,
                        MOD_HP5_1_ALG0_STAGE0_A2_ADDR, MOD_HP5_1_ALG0_STAGE0_A1_ADDR,
                        MOD_HP5_2_ALG0_STAGE0_B2_ADDR, MOD_HP5_2_ALG0_STAGE0_B1_ADDR, MOD_HP5_2_ALG0_STAGE0_B0_ADDR,
                        MOD_HP5_2_ALG0_STAGE0_A2_ADDR, MOD_HP5_2_ALG0_STAGE0_A1_ADDR,
                        MOD_HP5_3_ALG0_STAGE0_B2_ADDR, MOD_HP5_3_ALG0_STAGE0_B1_ADDR, MOD_HP5_3_ALG0_STAGE0_B0_ADDR,
                        MOD_HP5_3_ALG0_STAGE0_A2_ADDR, MOD_HP5_3_ALG0_STAGE0_A1_ADDR,
                        MOD_HP5_4_ALG0_STAGE0_B2_ADDR, MOD_HP5_4_ALG0_STAGE0_B1_ADDR, MOD_HP5_4_ALG0_STAGE0_B0_ADDR,
                        MOD_HP5_4_ALG0_STAGE0_A2_ADDR, MOD_HP5_4_ALG0_STAGE0_A1_ADDR,
                        fs,
                        ptrdsp );
    layout->addWidget( hp );
    channel->addDspBlock( hp );

    lshelv = new QLowShelv( 6.0, 100.0, 1.0,
                            MOD_LOWSHELV5_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV5_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV5_ALG0_STAGE0_B0_ADDR,
                            MOD_LOWSHELV5_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV5_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 6.0, 1000.0, 1.0,
                      MOD_PARAMEQ5_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE0_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );
    channel->addPeq( peq01 );

    peq02 = new QPeq( -6.0, 2000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE1_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE1_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );
    channel->addPeq( peq02 );

    peq03 = new QPeq( 6.0, 3000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE2_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE2_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );
    channel->addPeq( peq03 );

    peq04 = new QPeq( -6.0, 4000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE3_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE3_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );
    channel->addPeq( peq04 );

    peq05 = new QPeq( 6.0, 5000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE4_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE4_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );
    channel->addPeq( peq05 );

    peq06 = new QPeq( -6.0, 6000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE5_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE5_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );
    channel->addPeq( peq06 );

    peq07 = new QPeq( 6.0, 7000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE6_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE6_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );
    channel->addPeq( peq07 );

    peq08 = new QPeq( -6.0, 8000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE7_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE7_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );
    channel->addPeq( peq08 );

    peq09 = new QPeq( 6.0, 9000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE8_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE8_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );
    channel->addPeq( peq09 );

    peq10 = new QPeq( -6.0, 10000.0, 2.0,
                      MOD_PARAMEQ5_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ5_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ5_ALG0_STAGE9_B0_ADDR,
                      MOD_PARAMEQ5_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ5_ALG0_STAGE9_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );
    channel->addPeq( peq10 );

    hshelv = new QHighShelv( 6.0, 5000.0, 1.0,
                            MOD_HIGHSHELV5_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV5_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV5_ALG0_STAGE0_B0_ADDR,
                            MOD_HIGHSHELV5_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV5_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                     MOD_LP5_1_ALG0_STAGE0_B2_ADDR, MOD_LP5_1_ALG0_STAGE0_B1_ADDR, MOD_LP5_1_ALG0_STAGE0_B0_ADDR,
                     MOD_LP5_1_ALG0_STAGE0_A2_ADDR, MOD_LP5_1_ALG0_STAGE0_A1_ADDR,
                     MOD_LP5_2_ALG0_STAGE0_B2_ADDR, MOD_LP5_2_ALG0_STAGE0_B1_ADDR, MOD_LP5_2_ALG0_STAGE0_B0_ADDR,
                     MOD_LP5_2_ALG0_STAGE0_A2_ADDR, MOD_LP5_2_ALG0_STAGE0_A1_ADDR,
                     MOD_LP5_3_ALG0_STAGE0_B2_ADDR, MOD_LP5_3_ALG0_STAGE0_B1_ADDR, MOD_LP5_3_ALG0_STAGE0_B0_ADDR,
                     MOD_LP5_3_ALG0_STAGE0_A2_ADDR, MOD_LP5_3_ALG0_STAGE0_A1_ADDR,
                     MOD_LP5_4_ALG0_STAGE0_B2_ADDR, MOD_LP5_4_ALG0_STAGE0_B1_ADDR, MOD_LP5_4_ALG0_STAGE0_B0_ADDR,
                     MOD_LP5_4_ALG0_STAGE0_A2_ADDR, MOD_LP5_4_ALG0_STAGE0_A1_ADDR,
                     fs,
                     ptrdsp );
    layout->addWidget( lp );
    channel->addDspBlock( lp );

    phase = new QPhase( 1000.0, 1.0,
                        MOD_PHASE5_ALG0_STAGE0_B2_ADDR, MOD_PHASE5_ALG0_STAGE0_B1_ADDR, MOD_PHASE5_ALG0_STAGE0_B0_ADDR,
                        MOD_PHASE5_ALG0_STAGE0_A2_ADDR, MOD_PHASE5_ALG0_STAGE0_A1_ADDR,
                        fs,
                        ptrdsp );
    layout->addWidget( phase );
    channel->addDspBlock( phase );

    dly = new QDelay( 0.0, 48000.0, MOD_DELAY5_DELAYAMT_ADDR, ptrdsp );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN5_ALG0_TARGET_ADDR, ptrdsp );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( hp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
  }
  else if( chn == 5 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 6
    dspChannel.name = QString( "Channel 6" );

    input = new QInputSelect( 5, MOD_NX1_1_6_MONOMUXSIGMA300NS6INDEX_ADDR, ptrdsp );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                        MOD_HP6_1_ALG0_STAGE0_B2_ADDR, MOD_HP6_1_ALG0_STAGE0_B1_ADDR, MOD_HP6_1_ALG0_STAGE0_B0_ADDR,
                        MOD_HP6_1_ALG0_STAGE0_A2_ADDR, MOD_HP6_1_ALG0_STAGE0_A1_ADDR,
                        MOD_HP6_2_ALG0_STAGE0_B2_ADDR, MOD_HP6_2_ALG0_STAGE0_B1_ADDR, MOD_HP6_2_ALG0_STAGE0_B0_ADDR,
                        MOD_HP6_2_ALG0_STAGE0_A2_ADDR, MOD_HP6_2_ALG0_STAGE0_A1_ADDR,
                        MOD_HP6_3_ALG0_STAGE0_B2_ADDR, MOD_HP6_3_ALG0_STAGE0_B1_ADDR, MOD_HP6_3_ALG0_STAGE0_B0_ADDR,
                        MOD_HP6_3_ALG0_STAGE0_A2_ADDR, MOD_HP6_3_ALG0_STAGE0_A1_ADDR,
                        MOD_HP6_4_ALG0_STAGE0_B2_ADDR, MOD_HP6_4_ALG0_STAGE0_B1_ADDR, MOD_HP6_4_ALG0_STAGE0_B0_ADDR,
                        MOD_HP6_4_ALG0_STAGE0_A2_ADDR, MOD_HP6_4_ALG0_STAGE0_A1_ADDR,
                        fs,
                        ptrdsp );
    layout->addWidget( hp );
    channel->addDspBlock( hp );

    lshelv = new QLowShelv( 6.0, 100.0, 1.0,
                          MOD_LOWSHELV6_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV6_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV6_ALG0_STAGE0_B0_ADDR,
                          MOD_LOWSHELV6_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV6_ALG0_STAGE0_A1_ADDR,
                          fs,
                          ptrdsp );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 6.0, 1000.0, 1.0,
                    MOD_PARAMEQ6_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE0_B0_ADDR,
                    MOD_PARAMEQ6_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE0_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );
    channel->addPeq( peq01 );

    peq02 = new QPeq( -6.0, 2000.0, 2.0,
                    MOD_PARAMEQ6_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE1_B0_ADDR,
                    MOD_PARAMEQ6_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE1_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );
    channel->addPeq( peq02 );

    peq03 = new QPeq( 6.0, 3000.0, 2.0,
                    MOD_PARAMEQ6_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE2_B0_ADDR,
                    MOD_PARAMEQ6_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE2_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );
    channel->addPeq( peq03 );

    peq04 = new QPeq( -6.0, 4000.0, 2.0,
                    MOD_PARAMEQ6_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE3_B0_ADDR,
                    MOD_PARAMEQ6_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE3_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );
    channel->addPeq( peq04 );

    peq05 = new QPeq( 6.0, 5000.0, 2.0,
                    MOD_PARAMEQ6_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE4_B0_ADDR,
                    MOD_PARAMEQ6_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE4_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );
    channel->addPeq( peq05 );

    peq06 = new QPeq( -6.0, 6000.0, 2.0,
                    MOD_PARAMEQ6_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE5_B0_ADDR,
                    MOD_PARAMEQ6_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE5_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );
    channel->addPeq( peq06 );

    peq07 = new QPeq( 6.0, 7000.0, 2.0,
                    MOD_PARAMEQ6_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE6_B0_ADDR,
                    MOD_PARAMEQ6_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE6_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );
    channel->addPeq( peq07 );

    peq08 = new QPeq( -6.0, 8000.0, 2.0,
                    MOD_PARAMEQ6_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE7_B0_ADDR,
                    MOD_PARAMEQ6_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE7_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );
    channel->addPeq( peq08 );

    peq09 = new QPeq( 6.0, 9000.0, 2.0,
                    MOD_PARAMEQ6_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE8_B0_ADDR,
                    MOD_PARAMEQ6_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE8_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );
    channel->addPeq( peq09 );

    peq10 = new QPeq( -6.0, 10000.0, 2.0,
                    MOD_PARAMEQ6_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ6_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ6_ALG0_STAGE9_B0_ADDR,
                    MOD_PARAMEQ6_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ6_ALG0_STAGE9_A1_ADDR,
                    fs,
                    ptrdsp,
                    channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );
    channel->addPeq( peq10 );

    hshelv = new QHighShelv( 6.0, 5000.0, 1.0,
                            MOD_HIGHSHELV6_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV6_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV6_ALG0_STAGE0_B0_ADDR,
                            MOD_HIGHSHELV6_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV6_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                     MOD_LP6_1_ALG0_STAGE0_B2_ADDR, MOD_LP6_1_ALG0_STAGE0_B1_ADDR, MOD_LP6_1_ALG0_STAGE0_B0_ADDR,
                     MOD_LP6_1_ALG0_STAGE0_A2_ADDR, MOD_LP6_1_ALG0_STAGE0_A1_ADDR,
                     MOD_LP6_2_ALG0_STAGE0_B2_ADDR, MOD_LP6_2_ALG0_STAGE0_B1_ADDR, MOD_LP6_2_ALG0_STAGE0_B0_ADDR,
                     MOD_LP6_2_ALG0_STAGE0_A2_ADDR, MOD_LP6_2_ALG0_STAGE0_A1_ADDR,
                     MOD_LP6_3_ALG0_STAGE0_B2_ADDR, MOD_LP6_3_ALG0_STAGE0_B1_ADDR, MOD_LP6_3_ALG0_STAGE0_B0_ADDR,
                     MOD_LP6_3_ALG0_STAGE0_A2_ADDR, MOD_LP6_3_ALG0_STAGE0_A1_ADDR,
                     MOD_LP6_4_ALG0_STAGE0_B2_ADDR, MOD_LP6_4_ALG0_STAGE0_B1_ADDR, MOD_LP6_4_ALG0_STAGE0_B0_ADDR,
                     MOD_LP6_4_ALG0_STAGE0_A2_ADDR, MOD_LP6_4_ALG0_STAGE0_A1_ADDR,
                     fs,
                     ptrdsp );
    layout->addWidget( lp );
    channel->addDspBlock( lp );

    phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE6_ALG0_STAGE0_B2_ADDR, MOD_PHASE6_ALG0_STAGE0_B1_ADDR, MOD_PHASE6_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE6_ALG0_STAGE0_A2_ADDR, MOD_PHASE6_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp );
    layout->addWidget( phase );
    channel->addDspBlock( phase );

    dly = new QDelay( 0.0, 48000.0, MOD_DELAY6_DELAYAMT_ADDR, ptrdsp );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN6_ALG0_TARGET_ADDR, ptrdsp );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( hp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
  }
  else if( chn == 6 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 7
    dspChannel.name = QString( "Channel 7" );

    input = new QInputSelect( 6, MOD_NX1_1_7_MONOMUXSIGMA300NS7INDEX_ADDR, ptrdsp );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                        MOD_HP7_1_ALG0_STAGE0_B2_ADDR, MOD_HP7_1_ALG0_STAGE0_B1_ADDR, MOD_HP7_1_ALG0_STAGE0_B0_ADDR,
                        MOD_HP7_1_ALG0_STAGE0_A2_ADDR, MOD_HP7_1_ALG0_STAGE0_A1_ADDR,
                        MOD_HP7_2_ALG0_STAGE0_B2_ADDR, MOD_HP7_2_ALG0_STAGE0_B1_ADDR, MOD_HP7_2_ALG0_STAGE0_B0_ADDR,
                        MOD_HP7_2_ALG0_STAGE0_A2_ADDR, MOD_HP7_2_ALG0_STAGE0_A1_ADDR,
                        MOD_HP7_3_ALG0_STAGE0_B2_ADDR, MOD_HP7_3_ALG0_STAGE0_B1_ADDR, MOD_HP7_3_ALG0_STAGE0_B0_ADDR,
                        MOD_HP7_3_ALG0_STAGE0_A2_ADDR, MOD_HP7_3_ALG0_STAGE0_A1_ADDR,
                        MOD_HP7_4_ALG0_STAGE0_B2_ADDR, MOD_HP7_4_ALG0_STAGE0_B1_ADDR, MOD_HP7_4_ALG0_STAGE0_B0_ADDR,
                        MOD_HP7_4_ALG0_STAGE0_A2_ADDR, MOD_HP7_4_ALG0_STAGE0_A1_ADDR,
                        fs,
                        ptrdsp );
    layout->addWidget( hp );
    channel->addDspBlock( hp );

    lshelv = new QLowShelv( 6.0, 100.0, 1.0,
                          MOD_LOWSHELV7_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV7_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV7_ALG0_STAGE0_B0_ADDR,
                          MOD_LOWSHELV7_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV7_ALG0_STAGE0_A1_ADDR,
                          fs,
                          ptrdsp );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 6.0, 1000.0, 1.0,
                      MOD_PARAMEQ7_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE0_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );
    channel->addPeq( peq01 );

    peq02 = new QPeq( -6.0, 2000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE1_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE1_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );
    channel->addPeq( peq02 );

    peq03 = new QPeq( 6.0, 3000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE2_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE2_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );
    channel->addPeq( peq03 );

    peq04 = new QPeq( -6.0, 4000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE3_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE3_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );
    channel->addPeq( peq04 );

    peq05 = new QPeq( 6.0, 5000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE4_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE4_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );
    channel->addPeq( peq05 );

    peq06 = new QPeq( -6.0, 6000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE5_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE5_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );
    channel->addPeq( peq06 );

    peq07 = new QPeq( 6.0, 7000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE6_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE6_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );
    channel->addPeq( peq07 );

    peq08 = new QPeq( -6.0, 8000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE7_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE7_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );
    channel->addPeq( peq08 );

    peq09 = new QPeq( 6.0, 9000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE8_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE8_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );
    channel->addPeq( peq09 );

    peq10 = new QPeq( -6.0, 10000.0, 2.0,
                      MOD_PARAMEQ7_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ7_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ7_ALG0_STAGE9_B0_ADDR,
                      MOD_PARAMEQ7_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ7_ALG0_STAGE9_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );
    channel->addPeq( peq10 );

    hshelv = new QHighShelv( 6.0, 5000.0, 1.0,
                           MOD_HIGHSHELV7_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV7_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV7_ALG0_STAGE0_B0_ADDR,
                           MOD_HIGHSHELV7_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV7_ALG0_STAGE0_A1_ADDR,
                           fs,
                           ptrdsp );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                      MOD_LP7_1_ALG0_STAGE0_B2_ADDR, MOD_LP7_1_ALG0_STAGE0_B1_ADDR, MOD_LP7_1_ALG0_STAGE0_B0_ADDR,
                      MOD_LP7_1_ALG0_STAGE0_A2_ADDR, MOD_LP7_1_ALG0_STAGE0_A1_ADDR,
                      MOD_LP7_2_ALG0_STAGE0_B2_ADDR, MOD_LP7_2_ALG0_STAGE0_B1_ADDR, MOD_LP7_2_ALG0_STAGE0_B0_ADDR,
                      MOD_LP7_2_ALG0_STAGE0_A2_ADDR, MOD_LP7_2_ALG0_STAGE0_A1_ADDR,
                      MOD_LP7_3_ALG0_STAGE0_B2_ADDR, MOD_LP7_3_ALG0_STAGE0_B1_ADDR, MOD_LP7_3_ALG0_STAGE0_B0_ADDR,
                      MOD_LP7_3_ALG0_STAGE0_A2_ADDR, MOD_LP7_3_ALG0_STAGE0_A1_ADDR,
                      MOD_LP7_4_ALG0_STAGE0_B2_ADDR, MOD_LP7_4_ALG0_STAGE0_B1_ADDR, MOD_LP7_4_ALG0_STAGE0_B0_ADDR,
                      MOD_LP7_4_ALG0_STAGE0_A2_ADDR, MOD_LP7_4_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp );
    layout->addWidget( lp );
    channel->addDspBlock( lp );

    phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE7_ALG0_STAGE0_B2_ADDR, MOD_PHASE7_ALG0_STAGE0_B1_ADDR, MOD_PHASE7_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE7_ALG0_STAGE0_A2_ADDR, MOD_PHASE7_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp );
    layout->addWidget( phase );
    channel->addDspBlock( phase );

    dly = new QDelay( 0.0, 48000.0, MOD_DELAY7_DELAYAMT_ADDR, ptrdsp );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN7_ALG0_TARGET_ADDR, ptrdsp );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( hp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
  }
  else if( chn == 7 )
  {
    //--------------------------------------------------------------------------
    //--- Channel 8
    dspChannel.name = QString( "Channel 8" );

    input = new QInputSelect( 7, MOD_NX1_1_8_MONOMUXSIGMA300NS8INDEX_ADDR, ptrdsp );
    layout->addWidget( input );
    channel->addDspBlock( input );
    channel->setName( dspChannel.name );

    hp = new QHighPass( QHighPass::kLinkwitzRiley12, 100.0,
                        MOD_HP8_1_ALG0_STAGE0_B2_ADDR, MOD_HP8_1_ALG0_STAGE0_B1_ADDR, MOD_HP8_1_ALG0_STAGE0_B0_ADDR,
                        MOD_HP8_1_ALG0_STAGE0_A2_ADDR, MOD_HP8_1_ALG0_STAGE0_A1_ADDR,
                        MOD_HP8_2_ALG0_STAGE0_B2_ADDR, MOD_HP8_2_ALG0_STAGE0_B1_ADDR, MOD_HP8_2_ALG0_STAGE0_B0_ADDR,
                        MOD_HP8_2_ALG0_STAGE0_A2_ADDR, MOD_HP8_2_ALG0_STAGE0_A1_ADDR,
                        MOD_HP8_3_ALG0_STAGE0_B2_ADDR, MOD_HP8_3_ALG0_STAGE0_B1_ADDR, MOD_HP8_3_ALG0_STAGE0_B0_ADDR,
                        MOD_HP8_3_ALG0_STAGE0_A2_ADDR, MOD_HP8_3_ALG0_STAGE0_A1_ADDR,
                        MOD_HP8_4_ALG0_STAGE0_B2_ADDR, MOD_HP8_4_ALG0_STAGE0_B1_ADDR, MOD_HP8_4_ALG0_STAGE0_B0_ADDR,
                        MOD_HP8_4_ALG0_STAGE0_A2_ADDR, MOD_HP8_4_ALG0_STAGE0_A1_ADDR,
                        fs,
                        ptrdsp );
    layout->addWidget( hp );
    channel->addDspBlock( hp );

    lshelv = new QLowShelv( 6.0, 100.0, 1.0,
                            MOD_LOWSHELV8_ALG0_STAGE0_B2_ADDR, MOD_LOWSHELV8_ALG0_STAGE0_B1_ADDR, MOD_LOWSHELV8_ALG0_STAGE0_B0_ADDR,
                            MOD_LOWSHELV8_ALG0_STAGE0_A2_ADDR, MOD_LOWSHELV8_ALG0_STAGE0_A1_ADDR,
                            fs,
                            ptrdsp );
    layout->addWidget( lshelv );
    channel->addDspBlock( lshelv );

    peq01 = new QPeq( 6.0, 1000.0, 1.0,
                      MOD_PARAMEQ8_ALG0_STAGE0_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE0_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE0_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE0_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq01 );
    channel->addDspBlock( peq01 );
    channel->addPeq( peq01 );

    peq02 = new QPeq( -6.0, 2000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE1_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE1_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE1_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE1_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE1_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq02 );
    channel->addDspBlock( peq02 );
    channel->addPeq( peq02 );

    peq03 = new QPeq( 6.0, 3000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE2_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE2_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE2_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE2_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE2_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq03 );
    channel->addDspBlock( peq03 );
    channel->addPeq( peq03 );

    peq04 = new QPeq( -6.0, 4000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE3_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE3_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE3_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE3_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE3_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq04 );
    channel->addDspBlock( peq04 );
    channel->addPeq( peq04 );

    peq05 = new QPeq( 6.0, 5000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE4_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE4_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE4_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE4_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE4_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq05 );
    channel->addDspBlock( peq05 );
    channel->addPeq( peq05 );

    peq06 = new QPeq( -6.0, 6000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE5_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE5_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE5_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE5_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE5_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq06 );
    channel->addDspBlock( peq06 );
    channel->addPeq( peq06 );

    peq07 = new QPeq( 6.0, 7000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE6_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE6_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE6_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE6_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE6_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq07 );
    channel->addDspBlock( peq07 );
    channel->addPeq( peq07 );

    peq08 = new QPeq( -6.0, 8000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE7_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE7_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE7_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE7_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE7_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq08 );
    channel->addDspBlock( peq08 );
    channel->addPeq( peq08 );

    peq09 = new QPeq( 6.0, 9000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE8_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE8_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE8_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE8_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE8_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq09 );
    channel->addDspBlock( peq09 );
    channel->addPeq( peq09 );

    peq10 = new QPeq( -6.0, 10000.0, 2.0,
                      MOD_PARAMEQ8_ALG0_STAGE9_B2_ADDR, MOD_PARAMEQ8_ALG0_STAGE9_B1_ADDR, MOD_PARAMEQ8_ALG0_STAGE9_B0_ADDR,
                      MOD_PARAMEQ8_ALG0_STAGE9_A2_ADDR, MOD_PARAMEQ8_ALG0_STAGE9_A1_ADDR,
                      fs,
                      ptrdsp,
                      channel );
    layout->addWidget( peq10 );
    channel->addDspBlock( peq10 );
    channel->addPeq( peq10 );

    hshelv = new QHighShelv( 6.0, 5000.0, 1.0,
                           MOD_HIGHSHELV8_ALG0_STAGE0_B2_ADDR, MOD_HIGHSHELV8_ALG0_STAGE0_B1_ADDR, MOD_HIGHSHELV8_ALG0_STAGE0_B0_ADDR,
                           MOD_HIGHSHELV8_ALG0_STAGE0_A2_ADDR, MOD_HIGHSHELV8_ALG0_STAGE0_A1_ADDR,
                           fs,
                           ptrdsp );
    layout->addWidget( hshelv );
    channel->addDspBlock( hshelv );

    lp = new QLowPass( QLowPass::kLinkwitzRiley12, 10000.0,
                      MOD_LP8_1_ALG0_STAGE0_B2_ADDR, MOD_LP8_1_ALG0_STAGE0_B1_ADDR, MOD_LP8_1_ALG0_STAGE0_B0_ADDR,
                      MOD_LP8_1_ALG0_STAGE0_A2_ADDR, MOD_LP8_1_ALG0_STAGE0_A1_ADDR,
                      MOD_LP8_2_ALG0_STAGE0_B2_ADDR, MOD_LP8_2_ALG0_STAGE0_B1_ADDR, MOD_LP8_2_ALG0_STAGE0_B0_ADDR,
                      MOD_LP8_2_ALG0_STAGE0_A2_ADDR, MOD_LP8_2_ALG0_STAGE0_A1_ADDR,
                      MOD_LP8_3_ALG0_STAGE0_B2_ADDR, MOD_LP8_3_ALG0_STAGE0_B1_ADDR, MOD_LP8_3_ALG0_STAGE0_B0_ADDR,
                      MOD_LP8_3_ALG0_STAGE0_A2_ADDR, MOD_LP8_3_ALG0_STAGE0_A1_ADDR,
                      MOD_LP8_4_ALG0_STAGE0_B2_ADDR, MOD_LP8_4_ALG0_STAGE0_B1_ADDR, MOD_LP8_4_ALG0_STAGE0_B0_ADDR,
                      MOD_LP8_4_ALG0_STAGE0_A2_ADDR, MOD_LP8_4_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp );
    layout->addWidget( lp );
    channel->addDspBlock( lp );

    phase = new QPhase( 1000.0, 1.0,
                      MOD_PHASE8_ALG0_STAGE0_B2_ADDR, MOD_PHASE8_ALG0_STAGE0_B1_ADDR, MOD_PHASE8_ALG0_STAGE0_B0_ADDR,
                      MOD_PHASE8_ALG0_STAGE0_A2_ADDR, MOD_PHASE8_ALG0_STAGE0_A1_ADDR,
                      fs,
                      ptrdsp );
    layout->addWidget( phase );
    channel->addDspBlock( phase );

    dly = new QDelay( 0.0, 48000.0, MOD_DELAY8_DELAYAMT_ADDR, ptrdsp );
    layout->addWidget( dly );
    channel->addDspBlock( dly );

    gain = new QGain( 0.0, MOD_GAIN8_ALG0_TARGET_ADDR, ptrdsp );
    layout->addWidget( gain );
    channel->addDspBlock( gain );

    output = new QOutputSelect( 1, 0, ptrdsp );
    layout->addWidget( output );
    channel->addDspBlock( output );

    QObject::connect( hp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq01,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq02,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq03,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq04,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq05,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq06,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq07,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq08,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq09,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( peq10,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( hshelv, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( lp,     SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( phase,  SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( dly,    SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( gain,   SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );
    QObject::connect( output, SIGNAL(valueChanged()), parent, SLOT(updatePlots()) );

    QObject::connect( peq01,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq02,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq03,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq04,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq05,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq06,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq07,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq08,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq09,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );
    QObject::connect( peq10,  SIGNAL(importRewPeqs( QWidget* )), parent, SLOT(importRewPeqs( QWidget* )) );

  }


  dspChannel.layout = layout;
  dspChannel.channel = channel;
  dspChannel.gain = gain;

  flagSummation = true;

  return dspChannel;
}
