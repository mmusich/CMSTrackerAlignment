#include "TGaxis.h"
#include "tdrstyle.C"
#include "TBox.h"
#include "TLegend.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TString.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TLatex.h"

double xMax = 30;
double yMax = 50;
double zMax = 130;
double xRotMax = 300;
double yRotMax = 200;
double zRotMax = 150;

static const int NRuns = 148;
int runs[NRuns] = {256801, 256843, 256867, 256868, 256869, 256936, 256941, 257394, 257396, 257397, 257399, 257400, 257461, 257487, 257490, 257531, 257599, 257613, 257645, 257682, 257734, 257751, 257805, 257816, 257823, 257968, 257969, 258129, 258157, 258158, 258159, 258175, 258177, 258211, 258213, 258214, 258287, 258313, 258403, 258425, 258427, 258428, 258434, 258440, 258443, 258444, 258445, 258446, 258448, 258656, 258694, 258702, 258703, 258705, 258706, 258712, 258714, 258741, 258742, 258745, 258749, 258750, 259208, 259431, 259626, 259636, 259637, 259685, 259686, 259721, 259809, 259810, 259811, 259818, 259820, 259821, 259822, 259861, 259862, 259884, 259890, 259891, 260039, 260041, 260043, 260066, 260101, 260105, 260108, 260132, 260136, 260230, 260232, 260233, 260234, 260373, 260427, 260490, 260493, 260532, 260536, 260538, 260576, 260627, 262163, 262167, 262204, 262205, 262235, 262250, 262252, 262254, 262270, 262271, 262273, 262274, 262277, 262328, 262620, 262640, 262656, 262694, 262695, 262703, 262726, 262733, 262735, 262768, 262777, 262784, 262811, 262816, 262818, 262819, 262834, 262836, 262837, 262893, 262921, 262987, 262988, 263005, 263007, 263022, 263031, 263033, 263035, 263233 };

string collisionSystem[NRuns] = { "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502" };

double runBField[NRuns] = {3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.8, 3.8, 0, 0, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8 };

static const int runRange = 148;

bool zeroFitError = 1;

const char * det0[6] = {"FPIX", "FPIX", "BPIX", "BPIX", "FPIX", "FPIX"};
const char * det1[6] = {"xpzm", "xmzm", "xp", "xm", "xpzp", "xmzp"};
const char * det2[6] = {"Xpos", "Xrot", "Ypos", "Yrot", "Zpos", "Zrot"};

int colors[] = {36, kViolet-7, 4, 6, 8, 28};
int markers[] = {20, 21, 33, 34, 24, 25};

TLatex * latex;
TLatex * latex2;
TLatex * latex3;
TLatex * latex4;

TH1F * Xpos[NRuns];
TH1F * Xrot[NRuns];
TH1F * Ypos[NRuns];
TH1F * Yrot[NRuns];
TH1F * Zpos[NRuns];
TH1F * Zrot[NRuns];

TFile * runFile[NRuns];
TCanvas * runCanv[NRuns];

//--Positions and rotations for past runs
float FPIX_xpzm_Xpos[runRange];
float FPIX_xmzm_Xpos[runRange];
float BPIX_xp_Xpos[runRange];
float BPIX_xm_Xpos[runRange];
float FPIX_xpzp_Xpos[runRange];
float FPIX_xmzp_Xpos[runRange];

float FPIX_xpzm_Xrot[runRange];
float FPIX_xmzm_Xrot[runRange];
float BPIX_xp_Xrot[runRange];
float BPIX_xm_Xrot[runRange];
float FPIX_xpzp_Xrot[runRange];
float FPIX_xmzp_Xrot[runRange];

float FPIX_xpzm_Ypos[runRange];
float FPIX_xmzm_Ypos[runRange];
float BPIX_xp_Ypos[runRange];
float BPIX_xm_Ypos[runRange];
float FPIX_xpzp_Ypos[runRange];
float FPIX_xmzp_Ypos[runRange];

float FPIX_xpzm_Yrot[runRange];
float FPIX_xmzm_Yrot[runRange];
float BPIX_xp_Yrot[runRange];
float BPIX_xm_Yrot[runRange];
float FPIX_xpzp_Yrot[runRange];
float FPIX_xmzp_Yrot[runRange];

float FPIX_xpzm_Zpos[runRange];
float FPIX_xmzm_Zpos[runRange];
float BPIX_xp_Zpos[runRange];
float BPIX_xm_Zpos[runRange];
float FPIX_xpzp_Zpos[runRange];
float FPIX_xmzp_Zpos[runRange];

float FPIX_xpzm_Zrot[runRange];
float FPIX_xmzm_Zrot[runRange];
float BPIX_xp_Zrot[runRange];
float BPIX_xm_Zrot[runRange];
float FPIX_xpzp_Zrot[runRange];
float FPIX_xmzp_Zrot[runRange];

//--Errors on positions and rotations for past runs
float FPIX_xpzm_Xpos_Error[runRange];
float FPIX_xmzm_Xpos_Error[runRange];
float BPIX_xp_Xpos_Error[runRange];
float BPIX_xm_Xpos_Error[runRange];
float FPIX_xpzp_Xpos_Error[runRange];
float FPIX_xmzp_Xpos_Error[runRange];

float FPIX_xpzm_Xrot_Error[runRange];
float FPIX_xmzm_Xrot_Error[runRange];
float BPIX_xp_Xrot_Error[runRange];
float BPIX_xm_Xrot_Error[runRange];
float FPIX_xpzp_Xrot_Error[runRange];
float FPIX_xmzp_Xrot_Error[runRange];

float FPIX_xpzm_Ypos_Error[runRange];
float FPIX_xmzm_Ypos_Error[runRange];
float BPIX_xp_Ypos_Error[runRange];
float BPIX_xm_Ypos_Error[runRange];
float FPIX_xpzp_Ypos_Error[runRange];
float FPIX_xmzp_Ypos_Error[runRange];

float FPIX_xpzm_Yrot_Error[runRange];
float FPIX_xmzm_Yrot_Error[runRange];
float BPIX_xp_Yrot_Error[runRange];
float BPIX_xm_Yrot_Error[runRange];
float FPIX_xpzp_Yrot_Error[runRange];
float FPIX_xmzp_Yrot_Error[runRange];

float FPIX_xpzm_Zpos_Error[runRange];
float FPIX_xmzm_Zpos_Error[runRange];
float BPIX_xp_Zpos_Error[runRange];
float BPIX_xm_Zpos_Error[runRange];
float FPIX_xpzp_Zpos_Error[runRange];
float FPIX_xmzp_Zpos_Error[runRange];

float FPIX_xpzm_Zrot_Error[runRange];
float FPIX_xmzm_Zrot_Error[runRange];
float BPIX_xp_Zrot_Error[runRange];
float BPIX_xm_Zrot_Error[runRange];
float FPIX_xpzp_Zrot_Error[runRange];
float FPIX_xmzp_Zrot_Error[runRange];

//--Runs used for this plot
float usedRuns[runRange];
float runError[runRange];
float fitErrorZero[runRange];

//--Trend Graphs
TGraphErrors * gXpos[6];
TGraphErrors * gXrot[6];
TGraphErrors * gYpos[6];
TGraphErrors * gYrot[6];
TGraphErrors * gZpos[6];
TGraphErrors * gZrot[6];

TGraphErrors * dummyGraph_xPos;
TGraphErrors * dummyGraph_yPos;
TGraphErrors * dummyGraph_zPos;
TGraphErrors * dummyGraph_xRot;
TGraphErrors * dummyGraph_yRot;
TGraphErrors * dummyGraph_zRot;

//
//-- MAIN
//
void makeTrendPlot(){
  setTDRStyle();
  gStyle->SetPadTopMargin(0.1);
  TGaxis::SetMaxDigits(6);
  latex = new TLatex();
  latex->SetNDC();
  latex->SetTextFont(62);
  latex2 = new TLatex();
  latex2->SetNDC();
  latex2->SetTextSize(0.03);
  latex3 = new TLatex();
  latex3->SetNDC();
  latex3->SetTextFont(52);
  latex4 = new TLatex();
  latex4->SetNDC();
  latex4->SetTextFont(42);
  latex4->SetTextSize(0.035);


  int i = 0;

  for(int iRun = NRuns - runRange; iRun < NRuns; iRun++){

    if(collisionSystem[iRun] == "pp13"){
      if(runBField[iRun] == 3.8) runFile[iRun] = new TFile(Form("/afs/cern.ch/user/j/jcastle/public/pp3.8T_PCL_Alignment/Results%i/MinBias_2015/PCL_SiPixAl_DQM.root",runs[iRun]));
      if(runBField[iRun] == 0) runFile[iRun] = new TFile(Form("/afs/cern.ch/user/j/jcastle/public/pp0T_PCL_Alignment/Results%i/MinBias_2015/PCL_SiPixAl_DQM.root",runs[iRun]));
    }
    if(collisionSystem[iRun] == "pp502") runFile[iRun] = new TFile(Form("/afs/cern.ch/user/j/jcastle/public/HeavyIonRun2015_PseudoPCL/pp3.8T_PCL_Alignment/Results%i/MinBias_2015/PCL_SiPixAl_DQM.root",runs[iRun]));
    if(collisionSystem[iRun] == "PbPb502") runFile[iRun] = new TFile(Form("/afs/cern.ch/user/j/jcastle/public/HeavyIonRun2015_PseudoPCL/PbPb3.8T_PCL_Alignment/Results%i/MinBias_2015/PCL_SiPixAl_DQM.root",runs[iRun]));

    runCanv[iRun] = (TCanvas*) runFile[iRun]->Get("PCL_SiPixAl_Expert");

    Xpos[iRun] = (TH1F*) runCanv[iRun]->FindObject("Xpos_1");
    Xrot[iRun] = (TH1F*) runCanv[iRun]->FindObject("Xrot_1");
    Ypos[iRun] = (TH1F*) runCanv[iRun]->FindObject("Ypos_1");
    Yrot[iRun] = (TH1F*) runCanv[iRun]->FindObject("Yrot_1");
    Zpos[iRun] = (TH1F*) runCanv[iRun]->FindObject("Zpos_1");
    Zrot[iRun] = (TH1F*) runCanv[iRun]->FindObject("Zrot_1");

    //--Get positions and rotations
    FPIX_xpzm_Xpos[i] = Xpos[iRun]->GetBinContent(1);
    FPIX_xmzm_Xpos[i] = Xpos[iRun]->GetBinContent(2);
    BPIX_xp_Xpos[i] = Xpos[iRun]->GetBinContent(3);
    BPIX_xm_Xpos[i] = Xpos[iRun]->GetBinContent(4);
    FPIX_xpzp_Xpos[i] = Xpos[iRun]->GetBinContent(5);
    FPIX_xmzp_Xpos[i] = Xpos[iRun]->GetBinContent(6);

    FPIX_xpzm_Xrot[i] = Xrot[iRun]->GetBinContent(1);
    FPIX_xmzm_Xrot[i] = Xrot[iRun]->GetBinContent(2);
    BPIX_xp_Xrot[i] = Xrot[iRun]->GetBinContent(3);
    BPIX_xm_Xrot[i] = Xrot[iRun]->GetBinContent(4);
    FPIX_xpzp_Xrot[i] = Xrot[iRun]->GetBinContent(5);
    FPIX_xmzp_Xrot[i] = Xrot[iRun]->GetBinContent(6);

    FPIX_xpzm_Ypos[i] = Ypos[iRun]->GetBinContent(1);
    FPIX_xmzm_Ypos[i] = Ypos[iRun]->GetBinContent(2);
    BPIX_xp_Ypos[i] = Ypos[iRun]->GetBinContent(3);
    BPIX_xm_Ypos[i] = Ypos[iRun]->GetBinContent(4);
    FPIX_xpzp_Ypos[i] = Ypos[iRun]->GetBinContent(5);
    FPIX_xmzp_Ypos[i] = Ypos[iRun]->GetBinContent(6);

    FPIX_xpzm_Yrot[i] = Yrot[iRun]->GetBinContent(1);
    FPIX_xmzm_Yrot[i] = Yrot[iRun]->GetBinContent(2);
    BPIX_xp_Yrot[i] = Yrot[iRun]->GetBinContent(3);
    BPIX_xm_Yrot[i] = Yrot[iRun]->GetBinContent(4);
    FPIX_xpzp_Yrot[i] = Yrot[iRun]->GetBinContent(5);
    FPIX_xmzp_Yrot[i] = Yrot[iRun]->GetBinContent(6);

    FPIX_xpzm_Zpos[i] = Zpos[iRun]->GetBinContent(1);
    FPIX_xmzm_Zpos[i] = Zpos[iRun]->GetBinContent(2);
    BPIX_xp_Zpos[i] = Zpos[iRun]->GetBinContent(3);
    BPIX_xm_Zpos[i] = Zpos[iRun]->GetBinContent(4);
    FPIX_xpzp_Zpos[i] = Zpos[iRun]->GetBinContent(5);
    FPIX_xmzp_Zpos[i] = Zpos[iRun]->GetBinContent(6);

    FPIX_xpzm_Zrot[i] = Zrot[iRun]->GetBinContent(1);
    FPIX_xmzm_Zrot[i] = Zrot[iRun]->GetBinContent(2);
    BPIX_xp_Zrot[i] = Zrot[iRun]->GetBinContent(3);
    BPIX_xm_Zrot[i] = Zrot[iRun]->GetBinContent(4);
    FPIX_xpzp_Zrot[i] = Zrot[iRun]->GetBinContent(5);
    FPIX_xmzp_Zrot[i] = Zrot[iRun]->GetBinContent(6);

    //--Get position and rotation errors
    FPIX_xpzm_Xpos_Error[i] = Xpos[iRun]->GetBinError(1);
    FPIX_xmzm_Xpos_Error[i] = Xpos[iRun]->GetBinError(2);
    BPIX_xp_Xpos_Error[i] = Xpos[iRun]->GetBinError(3);
    BPIX_xm_Xpos_Error[i] = Xpos[iRun]->GetBinError(4);
    FPIX_xpzp_Xpos_Error[i] = Xpos[iRun]->GetBinError(5);
    FPIX_xmzp_Xpos_Error[i] = Xpos[iRun]->GetBinError(6);

    FPIX_xpzm_Xrot_Error[i] = Xrot[iRun]->GetBinError(1);
    FPIX_xmzm_Xrot_Error[i] = Xrot[iRun]->GetBinError(2);
    BPIX_xp_Xrot_Error[i] = Xrot[iRun]->GetBinError(3);
    BPIX_xm_Xrot_Error[i] = Xrot[iRun]->GetBinError(4);
    FPIX_xpzp_Xrot_Error[i] = Xrot[iRun]->GetBinError(5);
    FPIX_xmzp_Xrot_Error[i] = Xrot[iRun]->GetBinError(6);

    FPIX_xpzm_Ypos_Error[i] = Ypos[iRun]->GetBinError(1);
    FPIX_xmzm_Ypos_Error[i] = Ypos[iRun]->GetBinError(2);
    BPIX_xp_Ypos_Error[i] = Ypos[iRun]->GetBinError(3);
    BPIX_xm_Ypos_Error[i] = Ypos[iRun]->GetBinError(4);
    FPIX_xpzp_Ypos_Error[i] = Ypos[iRun]->GetBinError(5);
    FPIX_xmzp_Ypos_Error[i] = Ypos[iRun]->GetBinError(6);

    FPIX_xpzm_Yrot_Error[i] = Yrot[iRun]->GetBinError(1);
    FPIX_xmzm_Yrot_Error[i] = Yrot[iRun]->GetBinError(2);
    BPIX_xp_Yrot_Error[i] = Yrot[iRun]->GetBinError(3);
    BPIX_xm_Yrot_Error[i] = Yrot[iRun]->GetBinError(4);
    FPIX_xpzp_Yrot_Error[i] = Yrot[iRun]->GetBinError(5);
    FPIX_xmzp_Yrot_Error[i] = Yrot[iRun]->GetBinError(6);

    FPIX_xpzm_Zpos_Error[i] = Zpos[iRun]->GetBinError(1);
    FPIX_xmzm_Zpos_Error[i] = Zpos[iRun]->GetBinError(2);
    BPIX_xp_Zpos_Error[i] = Zpos[iRun]->GetBinError(3);
    BPIX_xm_Zpos_Error[i] = Zpos[iRun]->GetBinError(4);
    FPIX_xpzp_Zpos_Error[i] = Zpos[iRun]->GetBinError(5);
    FPIX_xmzp_Zpos_Error[i] = Zpos[iRun]->GetBinError(6);

    FPIX_xpzm_Zrot_Error[i] = Zrot[iRun]->GetBinError(1);
    FPIX_xmzm_Zrot_Error[i] = Zrot[iRun]->GetBinError(2);
    BPIX_xp_Zrot_Error[i] = Zrot[iRun]->GetBinError(3);
    BPIX_xm_Zrot_Error[i] = Zrot[iRun]->GetBinError(4);
    FPIX_xpzp_Zrot_Error[i] = Zrot[iRun]->GetBinError(5);
    FPIX_xmzp_Zrot_Error[i] = Zrot[iRun]->GetBinError(6);

    //--Set a zero error array for alignment fits if desired 
    if( zeroFitError ) fitErrorZero[i] = 0;

    //--Fill Used Run array
    usedRuns[i] = runs[iRun];
    runError[i] = 0;
    i++;

  }

  //--Array of arrays containing rotations and positions for parts of the pixel tracker
  float *  XposDet[6] = {FPIX_xpzm_Xpos, FPIX_xmzm_Xpos, BPIX_xp_Xpos, BPIX_xm_Xpos, FPIX_xpzp_Xpos, FPIX_xmzp_Xpos};
  float *  XposErrDet[6] = {FPIX_xpzm_Xpos_Error, FPIX_xmzm_Xpos_Error, BPIX_xp_Xpos_Error, BPIX_xm_Xpos_Error, FPIX_xpzp_Xpos_Error, FPIX_xmzp_Xpos_Error};
  float *  XrotDet[6] = {FPIX_xpzm_Xrot, FPIX_xmzm_Xrot, BPIX_xp_Xrot, BPIX_xm_Xrot, FPIX_xpzp_Xrot, FPIX_xmzp_Xrot};
  float *  XrotErrDet[6] = {FPIX_xpzm_Xrot_Error, FPIX_xmzm_Xrot_Error, BPIX_xp_Xrot_Error, BPIX_xm_Xrot_Error, FPIX_xpzp_Xrot_Error, FPIX_xmzp_Xrot_Error};
  float *  YposDet[6] = {FPIX_xpzm_Ypos, FPIX_xmzm_Ypos, BPIX_xp_Ypos, BPIX_xm_Ypos, FPIX_xpzp_Ypos, FPIX_xmzp_Ypos};
  float *  YposErrDet[6] = {FPIX_xpzm_Ypos_Error, FPIX_xmzm_Ypos_Error, BPIX_xp_Ypos_Error, BPIX_xm_Ypos_Error, FPIX_xpzp_Ypos_Error, FPIX_xmzp_Ypos_Error};
  float *  YrotDet[6] = {FPIX_xpzm_Yrot, FPIX_xmzm_Yrot, BPIX_xp_Yrot, BPIX_xm_Yrot, FPIX_xpzp_Yrot, FPIX_xmzp_Yrot};
  float *  YrotErrDet[6] = {FPIX_xpzm_Yrot_Error, FPIX_xmzm_Yrot_Error, BPIX_xp_Yrot_Error, BPIX_xm_Yrot_Error, FPIX_xpzp_Yrot_Error, FPIX_xmzp_Yrot_Error};
  float *  ZposDet[6] = {FPIX_xpzm_Zpos, FPIX_xmzm_Zpos, BPIX_xp_Zpos, BPIX_xm_Zpos, FPIX_xpzp_Zpos, FPIX_xmzp_Zpos};
  float *  ZposErrDet[6] = {FPIX_xpzm_Zpos_Error, FPIX_xmzm_Zpos_Error, BPIX_xp_Zpos_Error, BPIX_xm_Zpos_Error, FPIX_xpzp_Zpos_Error, FPIX_xmzp_Zpos_Error};
  float *  ZrotDet[6] = {FPIX_xpzm_Zrot, FPIX_xmzm_Zrot, BPIX_xp_Zrot, BPIX_xm_Zrot, FPIX_xpzp_Zrot, FPIX_xmzp_Zrot};
  float *  ZrotErrDet[6] = {FPIX_xpzm_Zrot_Error, FPIX_xmzm_Zrot_Error, BPIX_xp_Zrot_Error, BPIX_xm_Zrot_Error, FPIX_xpzp_Zrot_Error, FPIX_xmzp_Zrot_Error};


  //--Set up trend plots
  dummyGraph_xPos = new TGraphErrors(runRange,usedRuns,fitErrorZero,runError,fitErrorZero);
  dummyGraph_yPos = new TGraphErrors(runRange,usedRuns,fitErrorZero,runError,fitErrorZero);
  dummyGraph_zPos = new TGraphErrors(runRange,usedRuns,fitErrorZero,runError,fitErrorZero);
  dummyGraph_xRot = new TGraphErrors(runRange,usedRuns,fitErrorZero,runError,fitErrorZero);
  dummyGraph_yRot = new TGraphErrors(runRange,usedRuns,fitErrorZero,runError,fitErrorZero);
  dummyGraph_zRot = new TGraphErrors(runRange,usedRuns,fitErrorZero,runError,fitErrorZero);

  dummyGraph_xPos->SetMarkerColorAlpha(0,0.);
  dummyGraph_xPos->GetXaxis()->SetTitle("Run");
  dummyGraph_xPos->GetYaxis()->SetTitle("#Deltax [#mum]");
  dummyGraph_xPos->GetYaxis()->SetRangeUser(-xMax,xMax);
  dummyGraph_xPos->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+100);
  dummyGraph_xPos->GetXaxis()->SetNdivisions(4);
  dummyGraph_xPos->GetXaxis()->SetLabelSize(0.06);

  dummyGraph_yPos->SetMarkerColorAlpha(0,0.);
  dummyGraph_yPos->GetXaxis()->SetTitle("Run");
  dummyGraph_yPos->GetYaxis()->SetTitle("#Deltay [#mum]");
  dummyGraph_yPos->GetYaxis()->SetRangeUser(-yMax,yMax);
  dummyGraph_yPos->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+100);
  dummyGraph_yPos->GetXaxis()->SetNdivisions(4);
  dummyGraph_yPos->GetXaxis()->SetLabelSize(0.06);

  dummyGraph_zPos->SetMarkerColorAlpha(0,0.);
  dummyGraph_zPos->GetXaxis()->SetTitle("Run");
  dummyGraph_zPos->GetYaxis()->SetTitle("#Deltaz [#mum]");
  dummyGraph_zPos->GetYaxis()->SetRangeUser(-zMax,zMax);
  dummyGraph_zPos->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+100);
  dummyGraph_zPos->GetXaxis()->SetNdivisions(4);
  dummyGraph_zPos->GetXaxis()->SetLabelSize(0.06);

  dummyGraph_xRot->SetMarkerColorAlpha(0,0.);
  dummyGraph_xRot->GetXaxis()->SetTitle("Run");
  dummyGraph_xRot->GetYaxis()->SetTitle("#Delta#theta_{x} [#murad]");
  dummyGraph_xRot->GetYaxis()->SetRangeUser(-xRotMax,xRotMax);
  dummyGraph_xRot->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+100);
  dummyGraph_xRot->GetXaxis()->SetNdivisions(4);
  dummyGraph_xRot->GetXaxis()->SetLabelSize(0.06);

  dummyGraph_yRot->SetMarkerColorAlpha(0,0.);
  dummyGraph_yRot->GetXaxis()->SetTitle("Run");
  dummyGraph_yRot->GetYaxis()->SetTitle("#Delta#theta_{y} [#murad]");
  dummyGraph_yRot->GetYaxis()->SetRangeUser(-yRotMax,yRotMax);
  dummyGraph_yRot->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+100);
  dummyGraph_yRot->GetXaxis()->SetNdivisions(4);
  dummyGraph_yRot->GetXaxis()->SetLabelSize(0.06);

  dummyGraph_zRot->SetMarkerColorAlpha(0,0.);
  dummyGraph_zRot->GetXaxis()->SetTitle("Run");
  dummyGraph_zRot->GetYaxis()->SetTitle("#Delta#theta_{z} [#murad]");
  dummyGraph_zRot->GetYaxis()->SetRangeUser(-zRotMax,zRotMax);
  dummyGraph_zRot->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+100);
  dummyGraph_zRot->GetXaxis()->SetNdivisions(4);
  dummyGraph_zRot->GetXaxis()->SetLabelSize(0.06);

  for (int iDet = 0; iDet < 6; iDet++){
    if( !zeroFitError){
      gXpos[iDet] = new TGraphErrors(runRange,usedRuns,XposDet[iDet],runError,XposErrDet[iDet]);
      gXrot[iDet] = new TGraphErrors(runRange,usedRuns,XrotDet[iDet],runError,XrotErrDet[iDet]);
      gYpos[iDet] = new TGraphErrors(runRange,usedRuns,YposDet[iDet],runError,YposErrDet[iDet]);
      gYrot[iDet] = new TGraphErrors(runRange,usedRuns,YrotDet[iDet],runError,YrotErrDet[iDet]);
      gZpos[iDet] = new TGraphErrors(runRange,usedRuns,ZposDet[iDet],runError,ZposErrDet[iDet]);
      gZrot[iDet] = new TGraphErrors(runRange,usedRuns,ZrotDet[iDet],runError,ZrotErrDet[iDet]);
    }else{
      gXpos[iDet] = new TGraphErrors(runRange,usedRuns,XposDet[iDet],runError,fitErrorZero);
      gXrot[iDet] = new TGraphErrors(runRange,usedRuns,XrotDet[iDet],runError,fitErrorZero);
      gYpos[iDet] = new TGraphErrors(runRange,usedRuns,YposDet[iDet],runError,fitErrorZero);
      gYrot[iDet] = new TGraphErrors(runRange,usedRuns,YrotDet[iDet],runError,fitErrorZero);
      gZpos[iDet] = new TGraphErrors(runRange,usedRuns,ZposDet[iDet],runError,fitErrorZero);
      gZrot[iDet] = new TGraphErrors(runRange,usedRuns,ZrotDet[iDet],runError,fitErrorZero);
    }

    gXpos[iDet]->SetTitle(Form("Xpos_%s_%s_%s",det0[iDet],det1[iDet],det2[iDet]));
    gXpos[iDet]->GetXaxis()->SetTitle("Run");
    gXpos[iDet]->GetYaxis()->SetTitle("#Deltax [#mum]");
    gXpos[iDet]->GetYaxis()->SetRangeUser(-15,15);
    gXpos[iDet]->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+1);
    gXpos[iDet]->GetXaxis()->SetNdivisions(4);
    gXpos[iDet]->GetXaxis()->SetLabelSize(0.06);
    gXpos[iDet]->SetLineColor(colors[iDet]);
    gXpos[iDet]->SetMarkerColor(colors[iDet]);
    gXpos[iDet]->SetMarkerStyle(markers[iDet]);

    gYpos[iDet]->SetTitle(Form("Ypos_%s_%s_%s",det0[iDet],det1[iDet],det2[iDet]));
    gYpos[iDet]->GetXaxis()->SetTitle("Run");
    gYpos[iDet]->GetYaxis()->SetTitle("#mum");
    gYpos[iDet]->GetYaxis()->SetRangeUser(-20,20);
    gYpos[iDet]->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+1);
    gYpos[iDet]->GetXaxis()->SetNdivisions(4);
    gYpos[iDet]->GetXaxis()->SetLabelSize(0.06);
    gYpos[iDet]->SetLineColor(colors[iDet]);
    gYpos[iDet]->SetMarkerColor(colors[iDet]);
    gYpos[iDet]->SetMarkerStyle(markers[iDet]);

    gZpos[iDet]->SetTitle(Form("Zpos_%s_%s_%s",det0[iDet],det1[iDet],det2[iDet]));
    gZpos[iDet]->GetXaxis()->SetTitle("Run");
    gZpos[iDet]->GetYaxis()->SetTitle("#mum");
    gZpos[iDet]->GetYaxis()->SetRangeUser(-25,25);
    gZpos[iDet]->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+1);
    gZpos[iDet]->GetXaxis()->SetNdivisions(4);
    gXpos[iDet]->GetXaxis()->SetLabelSize(0.06);
    gZpos[iDet]->SetLineColor(colors[iDet]);
    gZpos[iDet]->SetMarkerColor(colors[iDet]);
    gZpos[iDet]->SetMarkerStyle(markers[iDet]);

    gXrot[iDet]->SetTitle(Form("Xrot_%s_%s_%s",det0[iDet],det1[iDet],det2[iDet]));
    gXrot[iDet]->GetXaxis()->SetTitle("Run");
    gXrot[iDet]->GetYaxis()->SetTitle("#murad");
    gXrot[iDet]->GetYaxis()->SetRangeUser(-40,40);
    gXrot[iDet]->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+1);
    gXrot[iDet]->GetXaxis()->SetNdivisions(4);
    gXrot[iDet]->SetLineColor(colors[iDet]);
    gXrot[iDet]->SetMarkerColor(colors[iDet]);
    gXrot[iDet]->SetMarkerStyle(markers[iDet]);

    gYrot[iDet]->SetTitle(Form("Yrot_%s_%s_%s",det0[iDet],det1[iDet],det2[iDet]));
    gYrot[iDet]->GetXaxis()->SetTitle("Run");
    gYrot[iDet]->GetYaxis()->SetTitle("#murad");
    gYrot[iDet]->GetYaxis()->SetRangeUser(-40,40);
    gYrot[iDet]->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+1);
    gYrot[iDet]->GetXaxis()->SetNdivisions(4);
    gYrot[iDet]->SetLineColor(colors[iDet]);
    gYrot[iDet]->SetMarkerColor(colors[iDet]);
    gYrot[iDet]->SetMarkerStyle(markers[iDet]);

    gZrot[iDet]->SetTitle(Form("Zrot_%s_%s_%s",det0[iDet],det1[iDet],det2[iDet]));
    gZrot[iDet]->GetXaxis()->SetTitle("Run");
    gZrot[iDet]->GetYaxis()->SetTitle("#murad");
    gZrot[iDet]->GetYaxis()->SetRangeUser(-40,40);
    gZrot[iDet]->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+1);
    gZrot[iDet]->GetXaxis()->SetNdivisions(4);
    gZrot[iDet]->SetLineColor(colors[iDet]);
    gZrot[iDet]->SetMarkerColor(colors[iDet]);
    gZrot[iDet]->SetMarkerStyle(markers[iDet]);

  }
  /*
  TLegend * leg = new TLegend(0.05,0.39,0.95,0.59);
  leg->SetNColumns(6);
  leg->SetTextFont(82);
  //leg->SetTextSize(100);
  leg->AddEntry(gZrot[0],"FPIX(x+,z-)","lp");
  leg->AddEntry(gZrot[1],"FPIX(x-,z-)","lp");
  leg->AddEntry(gZrot[2],"BPIX(x+)","lp");
  leg->AddEntry(gZrot[3],"BPIX(x-)","lp");
  leg->AddEntry(gZrot[4],"FPIX(x+,z+)","lp");
  leg->AddEntry(gZrot[5],"FPIX(x-,z+)","lp");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  */  
  TLegend * leg = new TLegend(0.2961,0.1578,0.5762,0.3690);
  leg->SetNColumns(2);
  leg->SetTextFont(82);
  //leg->SetTextSize(100);
  leg->AddEntry(gZrot[0],"FPIX(x+,z-)","lp");
  leg->AddEntry(gZrot[1],"FPIX(x-,z-)","lp");
  leg->AddEntry(gZrot[2],"BPIX(x+)","lp");
  leg->AddEntry(gZrot[3],"BPIX(x-)","lp");
  leg->AddEntry(gZrot[4],"FPIX(x+,z+)","lp");
  leg->AddEntry(gZrot[5],"FPIX(x-,z+)","lp");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);

  //-- Vertical lines to indicate alignment updates in the GT
  TLine * xPosUpdate257826  = new TLine(257826, -xMax, 257826, xMax);
  xPosUpdate257826->SetLineColor(1);
  xPosUpdate257826->SetLineStyle(2);
  xPosUpdate257826->SetLineWidth(2);  
  TLine * yPosUpdate257826  = new TLine(257826, -yMax, 257826, yMax);
  yPosUpdate257826->SetLineColor(1);
  yPosUpdate257826->SetLineStyle(2);
  yPosUpdate257826->SetLineWidth(2);
  TLine * zPosUpdate257826  = new TLine(257826, -zMax, 257826, zMax);
  zPosUpdate257826->SetLineColor(1);
  zPosUpdate257826->SetLineStyle(2);
  zPosUpdate257826->SetLineWidth(2);
  TLine * xRotUpdate257826  = new TLine(257826, -xRotMax, 257826, xRotMax);
  xRotUpdate257826->SetLineColor(1);
  xRotUpdate257826->SetLineStyle(2);
  xRotUpdate257826->SetLineWidth(2);
  TLine * yRotUpdate257826  = new TLine(257826, -yRotMax, 257826, yRotMax);
  yRotUpdate257826->SetLineColor(1);
  yRotUpdate257826->SetLineStyle(2);
  yRotUpdate257826->SetLineWidth(2);
  TLine * zRotUpdate257826  = new TLine(257826, -zRotMax, 257826, zRotMax);
  zRotUpdate257826->SetLineColor(1);
  zRotUpdate257826->SetLineStyle(2);
  zRotUpdate257826->SetLineWidth(2);

  TLine * xPosUpdate256746  = new TLine(256746, -xMax, 256746, xMax);
  xPosUpdate256746->SetLineColor(1);
  xPosUpdate256746->SetLineStyle(2);
  xPosUpdate256746->SetLineWidth(2);
  TLine * yPosUpdate256746  = new TLine(256746, -yMax, 256746, yMax);
  yPosUpdate256746->SetLineColor(1);
  yPosUpdate256746->SetLineStyle(2);
  yPosUpdate256746->SetLineWidth(2);
  TLine * zPosUpdate256746  = new TLine(256746, -zMax, 256746, zMax);
  zPosUpdate256746->SetLineColor(1);
  zPosUpdate256746->SetLineStyle(2);
  zPosUpdate256746->SetLineWidth(2);
  TLine * xRotUpdate256746  = new TLine(256746, -xRotMax, 256746, xRotMax);
  xRotUpdate256746->SetLineColor(1);
  xRotUpdate256746->SetLineStyle(2);
  xRotUpdate256746->SetLineWidth(2);
  TLine * yRotUpdate256746  = new TLine(256746, -yRotMax, 256746, yRotMax);
  yRotUpdate256746->SetLineColor(1);
  yRotUpdate256746->SetLineStyle(2);
  yRotUpdate256746->SetLineWidth(2);
  TLine * zRotUpdate256746  = new TLine(256746, -zRotMax, 256746, zRotMax);
  zRotUpdate256746->SetLineColor(1);
  zRotUpdate256746->SetLineStyle(2);
  zRotUpdate256746->SetLineWidth(2);

  TLine * xPosUpdate256715  = new TLine(256715, -xMax, 256715, xMax);
  xPosUpdate256715->SetLineColor(1);
  xPosUpdate256715->SetLineStyle(2);
  xPosUpdate256715->SetLineWidth(2);
  TLine * yPosUpdate256715  = new TLine(256715, -yMax, 256715, yMax);
  yPosUpdate256715->SetLineColor(1);
  yPosUpdate256715->SetLineStyle(2);
  yPosUpdate256715->SetLineWidth(2);
  TLine * zPosUpdate256715  = new TLine(256715, -zMax, 256715, zMax);
  zPosUpdate256715->SetLineColor(1);
  zPosUpdate256715->SetLineStyle(2);
  zPosUpdate256715->SetLineWidth(2);
  TLine * xRotUpdate256715  = new TLine(256715, -xRotMax, 256715, xRotMax);
  xRotUpdate256715->SetLineColor(1);
  xRotUpdate256715->SetLineStyle(2);
  xRotUpdate256715->SetLineWidth(2);
  TLine * yRotUpdate256715  = new TLine(256715, -yRotMax, 256715, yRotMax);
  yRotUpdate256715->SetLineColor(1);
  yRotUpdate256715->SetLineStyle(2);
  yRotUpdate256715->SetLineWidth(2);
  TLine * zRotUpdate256715  = new TLine(256715, -zRotMax, 256715, zRotMax);
  zRotUpdate256715->SetLineColor(1);
  zRotUpdate256715->SetLineStyle(2);
  zRotUpdate256715->SetLineWidth(2); 

  TLine * xPosUpdate262340  = new TLine(262340, -xMax, 262340, xMax);
  xPosUpdate262340->SetLineColor(1);
  xPosUpdate262340->SetLineStyle(2);
  xPosUpdate262340->SetLineWidth(2);
  TLine * yPosUpdate262340  = new TLine(262340, -yMax, 262340, yMax);
  yPosUpdate262340->SetLineColor(1);
  yPosUpdate262340->SetLineStyle(2);
  yPosUpdate262340->SetLineWidth(2);
  TLine * zPosUpdate262340  = new TLine(262340, -zMax, 262340, zMax);
  zPosUpdate262340->SetLineColor(1);
  zPosUpdate262340->SetLineStyle(2);
  zPosUpdate262340->SetLineWidth(2);
  TLine * xRotUpdate262340  = new TLine(262340, -xRotMax, 262340, xRotMax);
  xRotUpdate262340->SetLineColor(1);
  xRotUpdate262340->SetLineStyle(2);
  xRotUpdate262340->SetLineWidth(2);
  TLine * yRotUpdate262340  = new TLine(262340, -yRotMax, 262340, yRotMax);
  yRotUpdate262340->SetLineColor(1);
  yRotUpdate262340->SetLineStyle(2);
  yRotUpdate262340->SetLineWidth(2);
  TLine * zRotUpdate262340  = new TLine(262340, -zRotMax, 262340, zRotMax);
  zRotUpdate262340->SetLineColor(1);
  zRotUpdate262340->SetLineStyle(2);
  zRotUpdate262340->SetLineWidth(2);

  TLine * xPosUpdate262922  = new TLine(262922, -xMax, 262922, xMax);
  xPosUpdate262922->SetLineColor(1);
  xPosUpdate262922->SetLineStyle(2);
  xPosUpdate262922->SetLineWidth(2);
  TLine * yPosUpdate262922  = new TLine(262922, -yMax, 262922, yMax);
  yPosUpdate262922->SetLineColor(1);
  yPosUpdate262922->SetLineStyle(2);
  yPosUpdate262922->SetLineWidth(2);
  TLine * zPosUpdate262922  = new TLine(262922, -zMax, 262922, zMax);
  zPosUpdate262922->SetLineColor(1);
  zPosUpdate262922->SetLineStyle(2);
  zPosUpdate262922->SetLineWidth(2);
  TLine * xRotUpdate262922  = new TLine(262922, -xRotMax, 262922, xRotMax);
  xRotUpdate262922->SetLineColor(1);
  xRotUpdate262922->SetLineStyle(2);
  xRotUpdate262922->SetLineWidth(2);
  TLine * yRotUpdate262922  = new TLine(262922, -yRotMax, 262922, yRotMax);
  yRotUpdate262922->SetLineColor(1);
  yRotUpdate262922->SetLineStyle(2);
  yRotUpdate262922->SetLineWidth(2);
  TLine * zRotUpdate262922  = new TLine(262922, -zRotMax, 262922, zRotMax);
  zRotUpdate262922->SetLineColor(1);
  zRotUpdate262922->SetLineStyle(2);
  zRotUpdate262922->SetLineWidth(2);

  //--Era Change lines
  TLine * endpp13_x = new TLine(260630, -xMax, 260630, xMax);
  endpp13_x->SetLineColor(2);
  endpp13_x->SetLineStyle(1);
  endpp13_x->SetLineWidth(3);
  TLine * endpp13_y = new TLine(260630, -yMax, 260630, yMax);
  endpp13_y->SetLineColor(2);
  endpp13_y->SetLineStyle(1);
  endpp13_y->SetLineWidth(3);
  TLine * endpp13_z = new TLine(260630, -zMax, 260630, zMax);
  endpp13_z->SetLineColor(2);
  endpp13_z->SetLineStyle(1);
  endpp13_z->SetLineWidth(3);
  TLine * endpp13_xRot = new TLine(260630, -xRotMax, 260630, xRotMax);
  endpp13_xRot->SetLineColor(2);
  endpp13_xRot->SetLineStyle(1);
  endpp13_xRot->SetLineWidth(3);
  TLine * endpp13_yRot = new TLine(260630, -yRotMax, 260630, yRotMax);
  endpp13_yRot->SetLineColor(2);
  endpp13_yRot->SetLineStyle(1);
  endpp13_yRot->SetLineWidth(3);
  TLine * endpp13_zRot = new TLine(260630, -zRotMax, 260630, zRotMax);
  endpp13_zRot->SetLineColor(2);
  endpp13_zRot->SetLineStyle(1);
  endpp13_zRot->SetLineWidth(3);

  TLine * endpp502_x = new TLine(262340, -xMax, 262340, xMax);
  endpp502_x->SetLineColor(2);
  endpp502_x->SetLineStyle(1);
  endpp502_x->SetLineWidth(3);
  TLine * endpp502_y = new TLine(262340, -yMax, 262340, yMax);
  endpp502_y->SetLineColor(2);
  endpp502_y->SetLineStyle(1);
  endpp502_y->SetLineWidth(3);
  TLine * endpp502_z = new TLine(262340, -zMax, 262340, zMax);
  endpp502_z->SetLineColor(2);
  endpp502_z->SetLineStyle(1);
  endpp502_z->SetLineWidth(3);
  TLine * endpp502_xRot = new TLine(262340, -xRotMax, 262340, xRotMax);
  endpp502_xRot->SetLineColor(2);
  endpp502_xRot->SetLineStyle(1);
  endpp502_xRot->SetLineWidth(3);
  TLine * endpp502_yRot = new TLine(262340, -yRotMax, 262340, yRotMax);
  endpp502_yRot->SetLineColor(2);
  endpp502_yRot->SetLineStyle(1);
  endpp502_yRot->SetLineWidth(3);
  TLine * endpp502_zRot = new TLine(262340, -zRotMax, 262340, zRotMax);
  endpp502_zRot->SetLineColor(2);
  endpp502_zRot->SetLineStyle(1);
  endpp502_zRot->SetLineWidth(3);  

  //--Alignment Update bands
  TBox * xPosBox = new TBox(usedRuns[0]-1, -5, usedRuns[runRange-1]+1, 5);
  xPosBox->SetFillColorAlpha(5,0.5);
  TBox * yPosBox = new TBox(usedRuns[0]-1, -10, usedRuns[runRange-1]+1, 10);
  yPosBox->SetFillColorAlpha(5,0.5);
  TBox * zPosBox = new TBox(usedRuns[0]-1, -15, usedRuns[runRange-1]+1, 15);
  zPosBox->SetFillColorAlpha(5,0.5);
  TBox * xyzRotBox = new TBox(usedRuns[0]-1, -30, usedRuns[runRange-1]+1, 30);
  xyzRotBox->SetFillColorAlpha(5,0.5);

  //-- 0T boxes
  TBox * magnetCyle256355_x = new TBox(256355,-xMax,256489,xMax);
  magnetCyle256355_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle256355_y = new TBox(256355,-yMax,256489,yMax);
  magnetCyle256355_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle256355_z = new TBox(256355,-zMax,256489,zMax);
  magnetCyle256355_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle256355_xRot = new TBox(256355,-xRotMax,256489,xRotMax);
  magnetCyle256355_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle256355_yRot = new TBox(256355,-yRotMax,256489,yRotMax);
  magnetCyle256355_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle256355_zRot = new TBox(256355,-zRotMax,256489,zRotMax);
  magnetCyle256355_zRot->SetFillColorAlpha(13,0.5);

  TBox * magnetCyle257021_x = new TBox(257021,-xMax,257375,xMax);
  magnetCyle257021_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle257021_y = new TBox(257021,-yMax,257375,yMax);
  magnetCyle257021_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle257021_z = new TBox(257021,-zMax,257375,zMax);
  magnetCyle257021_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle257021_xRot = new TBox(257021,-xRotMax,257375,xRotMax);
  magnetCyle257021_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle257021_yRot = new TBox(257021,-yRotMax,257375,yRotMax);
  magnetCyle257021_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle257021_zRot = new TBox(257021,-zRotMax,257375,zRotMax);
  magnetCyle257021_zRot->SetFillColorAlpha(13,0.5);

  TBox * magnetCyle259896_x = new TBox(259896,-xMax,260324,xMax);
  magnetCyle259896_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle259896_y = new TBox(259896,-yMax,260324,yMax);
  magnetCyle259896_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle259896_z = new TBox(259896,-zMax,260324,zMax);
  magnetCyle259896_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle259896_xRot = new TBox(259896,-xRotMax,260324,xRotMax);
  magnetCyle259896_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle259896_yRot = new TBox(259896,-yRotMax,260324,yRotMax);
  magnetCyle259896_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle259896_zRot = new TBox(259896,-zRotMax,260324,zRotMax);
  magnetCyle259896_zRot->SetFillColorAlpha(13,0.5);

  TBox * magnetCyle260432_x = new TBox(260432,-xMax,260527,xMax);
  magnetCyle260432_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle260432_y = new TBox(260432,-yMax,260527,yMax);
  magnetCyle260432_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle260432_z = new TBox(260432,-zMax,260527,zMax);
  magnetCyle260432_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle260432_xRot = new TBox(260432,-xRotMax,260527,xRotMax);
  magnetCyle260432_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle260432_yRot = new TBox(260432,-yRotMax,260527,yRotMax);
  magnetCyle260432_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle260432_zRot = new TBox(260432,-zRotMax,260527,zRotMax);
  magnetCyle260432_zRot->SetFillColorAlpha(13,0.5);

  TBox * magnetCyle260744_x = new TBox(260744,-xMax,261084,xMax);
  magnetCyle260744_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle260744_y = new TBox(260744,-yMax,261084,yMax);
  magnetCyle260744_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle260744_z = new TBox(260744,-zMax,261084,zMax);
  magnetCyle260744_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle260744_xRot = new TBox(260744,-xRotMax,261084,xRotMax);
  magnetCyle260744_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle260744_yRot = new TBox(260744,-yRotMax,261084,yRotMax);
  magnetCyle260744_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle260744_zRot = new TBox(260744,-zRotMax,261084,zRotMax);
  magnetCyle260744_zRot->SetFillColorAlpha(13,0.5);

  TBox * magnetCyle261122_x = new TBox(261122,-xMax,261914,xMax);
  magnetCyle261122_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle261122_y = new TBox(261122,-yMax,261914,yMax);
  magnetCyle261122_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle261122_z = new TBox(261122,-zMax,261914,zMax);
  magnetCyle261122_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle261122_xRot = new TBox(261122,-xRotMax,261914,xRotMax);
  magnetCyle261122_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle261122_yRot = new TBox(261122,-yRotMax,261914,yRotMax);
  magnetCyle261122_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle261122_zRot = new TBox(261122,-zRotMax,261914,zRotMax);
  magnetCyle261122_zRot->SetFillColorAlpha(13,0.5);

  TBox * magnetCyle262348_x = new TBox(262348,-xMax,262442,xMax);
  magnetCyle262348_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle262348_y = new TBox(262348,-yMax,262442,yMax);
  magnetCyle262348_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle262348_z = new TBox(262348,-zMax,262442,zMax);
  magnetCyle262348_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle262348_xRot = new TBox(262348,-xRotMax,262442,xRotMax);
  magnetCyle262348_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle262348_yRot = new TBox(262348,-yRotMax,262442,yRotMax);
  magnetCyle262348_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle262348_zRot = new TBox(262348,-zRotMax,262442,zRotMax);
  magnetCyle262348_zRot->SetFillColorAlpha(13,0.5);

  TBox * magnetCyle263096_x = new TBox(263096,-xMax,263230,xMax);
  magnetCyle263096_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle263096_y = new TBox(263096,-yMax,263230,yMax);
  magnetCyle263096_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle263096_z = new TBox(263096,-zMax,263230,zMax);
  magnetCyle263096_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle263096_xRot = new TBox(263096,-xRotMax,263230,xRotMax);
  magnetCyle263096_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle263096_yRot = new TBox(263096,-yRotMax,263230,yRotMax);
  magnetCyle263096_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCyle263096_zRot = new TBox(263096,-zRotMax,263230,zRotMax);
  magnetCyle263096_zRot->SetFillColorAlpha(13,0.5);

  //--Line and box legend
  TLine * magnetCycleRef = new TLine(263096,-zRotMax,263230,zRotMax);
  magnetCycleRef->SetLineColor(13);
  magnetCycleRef->SetLineStyle(1);
  magnetCycleRef->SetLineWidth(7);
  TLegend * leg2 = new TLegend(0.2961,0.7078,0.5441,0.8093);
  leg2->SetTextFont(82);
  leg2->AddEntry(endpp13_x,"Data Era Switch","l");
  leg2->AddEntry(xPosUpdate262340,"Reference Geometry Update","l");
  leg2->AddEntry(magnetCycleRef,"Magnet Cycle","l");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);

  //TCanvas * cTrend = new TCanvas("cTrend","cTrend",3000,1800);
  //cTrend->Divide(3,2);
  
  TCanvas * cXPos = new TCanvas("cXPos","cXPos",1800,800);
  cXPos->cd();
  //cTrend->cd(1);
  dummyGraph_xPos->Draw("ap");
  //xPosBox->Draw("same");
  //magnetCyle256355_x->Draw("same");
  magnetCyle257021_x->Draw("same");
  magnetCyle259896_x->Draw("same");
  magnetCyle260432_x->Draw("same");
  magnetCyle260744_x->Draw("same");
  magnetCyle261122_x->Draw("same");
  magnetCyle262348_x->Draw("same");
  magnetCyle263096_x->Draw("same");
  endpp13_x->Draw("same");
  endpp502_x->Draw("same");
  if( (257826 > (usedRuns[0]-1)) && (257826 < (usedRuns[runRange-1]+1)) ) xPosUpdate257826->Draw("same");
  if( (256746 > (usedRuns[0]-1)) && (256746 < (usedRuns[runRange-1]+1)) ) xPosUpdate256746->Draw("same");
  if( (256715 > (usedRuns[0]-1)) && (256715 < (usedRuns[runRange-1]+1)) ) xPosUpdate256715->Draw("same");
  xPosUpdate262340->Draw("same");
  xPosUpdate262922->Draw("same");
  gXpos[0]->Draw("lpsame");
  gXpos[1]->Draw("lpsame");
  gXpos[2]->Draw("lpsame");
  gXpos[3]->Draw("lpsame");
  gXpos[4]->Draw("lpsame");
  gXpos[5]->Draw("lpsame");
  leg->Draw("same");
  leg2->Draw("same");
  latex->DrawLatex(0.16,0.91,"CMS");
  latex3->DrawLatex(0.208,0.91,"Preliminary");
  latex4->DrawLatex(0.52,0.91,"3.16 fb^{-1} (13 TeV pp) + 25.5 pb^{-1} (5.02 TeV pp) + ?.?? pb^{-1} (5.02 TeV PbPb)");
  latex2->DrawLatex(0.2968,0.85,"Tracker Alignment in 2015 Data");
  latex2->DrawLatex(0.2968,0.82,"Taking Used as Reference");
  cXPos->SaveAs("trendPlots/xPos.pdf");

  TCanvas * cYPos = new TCanvas("cYPos","cYPos",1800,800);
  cYPos->cd();
  //cTrend->cd(2);
  dummyGraph_yPos->Draw("ap");
  //yPosBox->Draw("same");
  //magnetCyle256355_y->Draw("same");
  magnetCyle257021_y->Draw("same");
  magnetCyle259896_y->Draw("same");
  magnetCyle260432_y->Draw("same");
  magnetCyle260744_y->Draw("same");
  magnetCyle261122_y->Draw("same");
  magnetCyle262348_y->Draw("same");
  magnetCyle263096_y->Draw("same");
  endpp13_y->Draw("same");
  endpp502_y->Draw("same");
  if( (257826 > (usedRuns[0]-1)) && (257826 < (usedRuns[runRange-1]+1)) ) yPosUpdate257826->Draw("same");
  if( (256746 > (usedRuns[0]-1)) && (256746 < (usedRuns[runRange-1]+1)) ) yPosUpdate256746->Draw("same");
  if( (256715 > (usedRuns[0]-1)) && (256715 < (usedRuns[runRange-1]+1)) ) yPosUpdate256715->Draw("same");
  yPosUpdate262340->Draw("same");
  yPosUpdate262922->Draw("same");
  gYpos[0]->Draw("lpsame");
  gYpos[1]->Draw("lpsame");
  gYpos[2]->Draw("lpsame");
  gYpos[3]->Draw("lpsame");
  gYpos[4]->Draw("lpsame");
  gYpos[5]->Draw("lpsame");
  leg->Draw("same");
  leg2->Draw("same");
  latex->DrawLatex(0.16,0.91,"CMS");
  latex3->DrawLatex(0.208,0.91,"Preliminary");
  latex4->DrawLatex(0.52,0.91,"3.16 fb^{-1} (13 TeV pp) + 25.5 pb^{-1} (5.02 TeV pp) + ?.?? pb^{-1} (5.02 TeV PbPb)");
  latex2->DrawLatex(0.2968,0.85,"Tracker Alignment in 2015 Data");
  latex2->DrawLatex(0.2968,0.82,"Taking Used as Reference");
  cYPos->SaveAs("trendPlots/yPos.pdf");

  TCanvas * cZPos = new TCanvas("cZPos","cZPos",1800,800);
  cZPos->cd();
  //cTrend->cd(3);
  dummyGraph_zPos->Draw("ap");
  //zPosBox->Draw("same");
  //magnetCyle256355_z->Draw("same");
  magnetCyle257021_z->Draw("same");
  magnetCyle259896_z->Draw("same");
  magnetCyle260432_z->Draw("same");
  magnetCyle260744_z->Draw("same");
  magnetCyle261122_z->Draw("same");
  magnetCyle262348_z->Draw("same");
  magnetCyle263096_z->Draw("same");
  endpp13_z->Draw("same");
  endpp502_z->Draw("same");
  if( (257826 > (usedRuns[0]-1)) && (257826 < (usedRuns[runRange-1]+1)) ) zPosUpdate257826->Draw("same");
  if( (256746 > (usedRuns[0]-1)) && (256746 < (usedRuns[runRange-1]+1)) ) zPosUpdate256746->Draw("same");
  if( (256715 > (usedRuns[0]-1)) && (256715 < (usedRuns[runRange-1]+1)) ) zPosUpdate256715->Draw("same");
  zPosUpdate262340->Draw("same");
  zPosUpdate262922->Draw("same");
  gZpos[0]->Draw("lpsame");
  gZpos[1]->Draw("lpsame");
  gZpos[2]->Draw("lpsame");
  gZpos[3]->Draw("lpsame");
  gZpos[4]->Draw("lpsame");
  gZpos[5]->Draw("lpsame");
  leg->Draw("same");
  leg2->Draw("same");
  latex->DrawLatex(0.16,0.91,"CMS");
  latex3->DrawLatex(0.208,0.91,"Preliminary");
  latex4->DrawLatex(0.52,0.91,"3.16 fb^{-1} (13 TeV pp) + 25.5 pb^{-1} (5.02 TeV pp) + ?.?? pb^{-1} (5.02 TeV PbPb)");
  latex2->DrawLatex(0.2968,0.85,"Tracker Alignment in 2015 Data");
  latex2->DrawLatex(0.2968,0.82,"Taking Used as Reference");
  cZPos->SaveAs("trendPlots/zPos.pdf");

  TCanvas * cXRot = new TCanvas("cXRot","cXRot",1800,800);
  cXRot->cd();
  //cTrend->cd(4);
  dummyGraph_xRot->Draw("ap");
  //xyzRotBox->Draw("same");
  //magnetCyle256355_xRot->Draw("same");
  magnetCyle257021_xRot->Draw("same");
  magnetCyle259896_xRot->Draw("same");
  magnetCyle260432_xRot->Draw("same");
  magnetCyle260744_xRot->Draw("same");
  magnetCyle261122_xRot->Draw("same");
  magnetCyle262348_xRot->Draw("same");
  magnetCyle263096_xRot->Draw("same");
  endpp13_xRot->Draw("same");
  endpp502_xRot->Draw("same");
  if( (257826 > (usedRuns[0]-1)) && (257826 < (usedRuns[runRange-1]+1)) ) xRotUpdate257826->Draw("same");
  if( (256746 > (usedRuns[0]-1)) && (256746 < (usedRuns[runRange-1]+1)) ) xRotUpdate256746->Draw("same");
  if( (256715 > (usedRuns[0]-1)) && (256715 < (usedRuns[runRange-1]+1)) ) xRotUpdate256715->Draw("same");
  xRotUpdate262340->Draw("same");
  xRotUpdate262922->Draw("same");
  gXrot[0]->Draw("lpsame");
  gXrot[1]->Draw("lpsame");
  gXrot[2]->Draw("lpsame");
  gXrot[3]->Draw("lpsame");
  gXrot[4]->Draw("lpsame");
  gXrot[5]->Draw("lpsame");
  leg->Draw("same");
  leg2->Draw("same");
  latex->DrawLatex(0.16,0.91,"CMS");
  latex3->DrawLatex(0.208,0.91,"Preliminary");
  latex4->DrawLatex(0.52,0.91,"3.16 fb^{-1} (13 TeV pp) + 25.5 pb^{-1} (5.02 TeV pp) + ?.?? pb^{-1} (5.02 TeV PbPb)");
  latex2->DrawLatex(0.2968,0.85,"Tracker Alignment in 2015 Data");
  latex2->DrawLatex(0.2968,0.82,"Taking Used as Reference");
  cXRot->SaveAs("trendPlots/xRot.pdf");

  TCanvas * cYRot = new TCanvas("cYRot","cYRot",1800,800);
  cYRot->cd();
  //cTrend->cd(5);
  dummyGraph_yRot->Draw("ap");
  //xyzRotBox->Draw("same");
  //magnetCyle256355_yRot->Draw("same");
  magnetCyle257021_yRot->Draw("same");
  magnetCyle259896_yRot->Draw("same");
  magnetCyle260432_yRot->Draw("same");
  magnetCyle260744_yRot->Draw("same");
  magnetCyle261122_yRot->Draw("same");
  magnetCyle262348_yRot->Draw("same");
  magnetCyle263096_yRot->Draw("same");
  endpp13_yRot->Draw("same");
  endpp502_yRot->Draw("same");
  if( (257826 > (usedRuns[0]-1)) && (257826 < (usedRuns[runRange-1]+1)) ) yRotUpdate257826->Draw("same");
  if( (256746 > (usedRuns[0]-1)) && (256746 < (usedRuns[runRange-1]+1)) ) yRotUpdate256746->Draw("same");
  if( (256715 > (usedRuns[0]-1)) && (256715 < (usedRuns[runRange-1]+1)) ) yRotUpdate256715->Draw("same");
  yRotUpdate262340->Draw("same");
  yRotUpdate262922->Draw("same");
  gYrot[0]->Draw("lpsame");
  gYrot[1]->Draw("lpsame");
  gYrot[2]->Draw("lpsame");
  gYrot[3]->Draw("lpsame");
  gYrot[4]->Draw("lpsame");
  gYrot[5]->Draw("lpsame");
  leg->Draw("same");
  leg2->Draw("same");
  latex->DrawLatex(0.16,0.91,"CMS");
  latex3->DrawLatex(0.208,0.91,"Preliminary");
  latex4->DrawLatex(0.52,0.91,"3.16 fb^{-1} (13 TeV pp) + 25.5 pb^{-1} (5.02 TeV pp) + ?.?? pb^{-1} (5.02 TeV PbPb)");
  latex2->DrawLatex(0.2968,0.85,"Tracker Alignment in 2015 Data");
  latex2->DrawLatex(0.2968,0.82,"Taking Used as Reference");
  cYRot->SaveAs("trendPlots/yRot.pdf");
  
  //cTrend->cd(6);
  TCanvas * cZRot = new TCanvas("cZRot","cZRot",1800,800);
  cZRot->cd();
  dummyGraph_zRot->Draw("ap");
  //xyzRotBox->Draw("same");
  //magnetCyle256355_zRot->Draw("same");
  magnetCyle257021_zRot->Draw("same");
  magnetCyle259896_zRot->Draw("same");
  magnetCyle260432_zRot->Draw("same");
  magnetCyle260744_zRot->Draw("same");
  magnetCyle261122_zRot->Draw("same");
  magnetCyle262348_zRot->Draw("same");
  magnetCyle263096_zRot->Draw("same");
  endpp13_zRot->Draw("same");
  endpp502_zRot->Draw("same");
  if( (257826 > (usedRuns[0]-1)) && (257826 < (usedRuns[runRange-1]+1)) ) zRotUpdate257826->Draw("same");
  if( (256746 > (usedRuns[0]-1)) && (256746 < (usedRuns[runRange-1]+1)) ) zRotUpdate256746->Draw("same");
  if( (256715 > (usedRuns[0]-1)) && (256715 < (usedRuns[runRange-1]+1)) ) zRotUpdate256715->Draw("same");
  zRotUpdate262340->Draw("same");
  zRotUpdate262922->Draw("same");
  gZrot[0]->Draw("lpsame");
  gZrot[1]->Draw("lpsame");
  gZrot[2]->Draw("lpsame");
  gZrot[3]->Draw("lpsame");
  gZrot[4]->Draw("lpsame");
  gZrot[5]->Draw("lpsame");
  leg->Draw("same");
  leg2->Draw("same");
  //latex->DrawLatex(0.18,0.84,"CMS");
  //latex3->DrawLatex(0.18,0.8,"Preliminary");
  latex->DrawLatex(0.16,0.91,"CMS");
  latex3->DrawLatex(0.208,0.91,"Preliminary");
  latex4->DrawLatex(0.52,0.91,"3.16 fb^{-1} (13 TeV pp) + 25.5 pb^{-1} (5.02 TeV pp) + ?.?? pb^{-1} (5.02 TeV PbPb)");
  latex2->DrawLatex(0.2968,0.85,"Tracker Alignment in 2015 Data");
  latex2->DrawLatex(0.2968,0.82,"Taking Used as Reference");
  cZRot->SaveAs("trendPlots/zRot.pdf");

  //cTrend->cd(0);
  //leg->Draw("same");
  //latex->DrawLatex(0.005,0.965,"CMS Preliminary");
  //cTrend->SaveAs("TrendPlot.pdf");
  //cTrend->Close();
}
