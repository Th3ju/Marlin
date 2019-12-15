#pragma once
#define SHORT_BUILD_VERSION "B450"

// =  disabled - remove // enabled

//Step 1) enable 1 model
//GT2560 Boards - vscode: default_envs = megaatmega2560 in platformio.ini
#define GTA10       // A10 & Variants - tested working
//#define GTA20       // A20 & Variants - tested working
//#define MECREATOR2  // Mecreator2     - tested working
//#define I3PROA      // PI3A Pro       - testing
//#define I3PROB      // I3PROB         - testing
//#define I3PROC      // I3PROC         - testing
//#define I3PROW      // I3PROW         - testing
//#define I3PROX      // I3PROX         - testing

//GTM32 Boards - vscode: default_envs = STM32F103VE_longer in platformio.ini
//#define GTA30       // A30  - Tested mostly works - set jumpers base on board for flashing and use serial to upload
//#define GTE180      // E180 - Tested mostly works - set jumpers base on board for flashing and use serial to upload
//#define GTM201      // M201 - experimental, set jumpers base on board for flashing and use serial to upload
//#define GTD200      // D200 - experimental, set jumpers base on board for flashing and use serial to upload
//--------------------------------------------------------------------------------------------------------------------------------------------------------
//Step 2) enable 1 driver timing set. 
//#define STOCK     // Enable A4988   on all drivers (stock drivers)
#define T2208    // Enable TMC2208 Standalone on all drivers
//#define T2209    // Enable TMC2209 Standalone on all drivers
//#define T2130    // Enable TMC2130 Standalone on all drivers
//#define T2160    // Enable TMC2160 Standalone on all drivers
//#define T26X     // Enable TMC226X Standalone on all drivers
//#define T2660    // Enable TMC2660 Standalone on all drivers
//#define T5130    // Enable TMC5130 Standalone on all drivers
//#define T5160    // Enable TMC5160 Standalone on all drivers
//#define A598     // Enable A5984   on all drivers
//#define D8825    // Enable DRV8825 on all drivers
//#define L8729    // Enable LV8729  on all drivers
//#define L647     // Enable L6470   on all drivers
//#define T6560    // Enable TB6560  on all drivers
//#define T6600    // Enable TB6600  on all drivers
//#define CUSTOM   // Fill in #elif ENABLED (CUSTOM) in configuration.h with a custom set & invert if needed below #if ENABLED (CUSTOM)
//--------------------------------------------------------------------------------------------------------------------------------------------------------
//Step 3) enable 1 if you have mixing or multi extruder
//#define MIX      // Enable Mixing    2 in 1 - Virtual Motor Control 
//#define MIXT     // Enable Mixing    3 in 1 - Virtual Motor Control
//#define CYCLOPS  // Enable Cyclops   2 in 1 - Physical Motor Control
//#define CYCLOPST // Enable Cyclops   3 in 1 - Physical Motor Control
//#define DUALEX   // 2 Extruder       2 in 2 - Physical Motor Control 
//#define TRIEX    // 3 Extruder       3 in 3 - Physical Motor Control 
//-------------------------------------------------------------------------------------------------------------------------------------------------------- 
//Step 4) enable 1 probe type & edit other bed leveling options
//#define MANUALBL    // Enable Manual Bed Leveling (stock)
#define TOUCHPROBE    // Enable Bltouch Type Probe.
//#define FMP         // Enable Fixed Mounted Type Probe
//--------------------------------------------------------------------------------------------------------------------------------------------------------
//Other variables DO NOT DISABLE edit only.
#define XMP -11 //0        // X Min Position - distance from endstop to bed, adjust to nozzle front left bed edge X0
#define YMP -5  //0        // Y Min Position - distance from endstop to bed, adjust to nozzle front left bed edge Y0
#define MPE 1              // As needed Min:0 Max:30 if you have bed clips, if set to large it will cause max X crash
#define GRIDSIZE 5         // 5x5 mesh grid adjust as needed
#define ZPROBESPEED 240    // Probe speed reduce if accuracy is poor
#define MAXHOTENDTEMP 260  // Max hotend temp 260
#define MAXBEDTEMP    110  // Max bed temp 110

//logic used to reduce setup steps.
#if ANY(MIX, MIXT, CYCLOPS, CYCLOPST, DUALEX, TRIEX)
#define MULTIEXTRUDER
#endif

#if ANY(T2208, T2209, T2130, T2160, T26X, T2660,  T5130, T5160)
#define TMCCHIPS 
#endif

//Probe offset logic
#if DISABLED (MULTIEXTRUDER)
#define NPO { -38, 4, 0 } // Nozzle To Probe offset XYZ A10/A20 calibration suggested 
#elif ENABLED (MULTIEXTRUDER)
#define NPO { -40, 0, 0 }  // Nozzle To Probe offset XYZ A10M/A20M calibration suggested
#else
#error Probe offset logic error
#endif

//Steps selection logic
#if DISABLED (MULTIEXTRUDER) 
#define XYZESTEPS  { 80, 80, 400, 98 }  // ungeared extruder found on a10/a20/a30/i3pro
//#define XYZESTEPS  { 80, 80, 2560, 98 } // M8 Z rod steps 2560 found on old I3pro
#elif ENABLED (MIX) || ENABLED (CYCLOPS) || ENABLED (DUALEX)
#define XYZESTEPS  { 80, 80, 400, 430, 430 } // geared extruder found on M & T variants
//#define XYZESTEPS  { 80, 80, 2560,430, 430 } // M8 Z rod steps 2560 found on old I3pro
#elif ENABLED (MIXT) || ENABLED (CYCLOPST) || ENABLED (TRIEX)
#define XYZESTEPS  { 80, 80, 400, 430, 430, 430 } // geared extruder found on M & T variants
//#define XYZESTEPS  { 80, 80, 2560,430, 430, 430 } // M8 Z rod steps 2560 found on old I3pro
#else
#error Steps logic error
#endif

//Motor direction logic
#if ENABLED (TMCCHIPS) && DISABLED (MULTIEXTRUDER) || DISABLED (CUSTOM) && ENABLED (MULTIEXTRUDER) 
#define INVERTE     // Invert E direction disabe if wrong direction - M & T variants invert E (stock)
#endif

#if ENABLED (TMCCHIPS)
#define INVERTXYZ   // Invert XYZ direction disable if wrong direction. 
#endif

#if ENABLED (CUSTOM)
//#define INVERTE     // Invert E direction disabe if wrong direction - M & T variants invert E (stock)
#define INVERTXYZ   // Invert XYZ direction disable if wrong direction. adjust for custom
#endif