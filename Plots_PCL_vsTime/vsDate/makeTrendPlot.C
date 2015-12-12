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

static const int NRuns = 168;
int runs[NRuns] = {256801, 256843, 256867, 256868, 256869, 256936, 256941, 257394, 257396, 257397, 257399, 257400, 257461, 257487, 257490, 257531, 257599, 257613, 257645, 257682, 257734, 257751, 257805, 257816, 257823, 257968, 257969, 258129, 258157, 258158, 258159, 258175, 258177, 258211, 258213, 258214, 258287, 258313, 258403, 258425, 258427, 258428, 258434, 258440, 258443, 258444, 258445, 258446, 258448, 258656, 258694, 258702, 258703, 258705, 258706, 258712, 258714, 258741, 258742, 258745, 258749, 258750, 259208, 259431, 259626, 259636, 259637, 259685, 259686, 259721, 259809, 259810, 259811, 259818, 259820, 259821, 259822, 259861, 259862, 259884, 259890, 259891, 260039, 260041, 260043, 260066, 260101, 260105, 260108, 260132, 260136, 260230, 260232, 260233, 260234, 260373, 260427, 260490, 260493, 260532, 260536, 260538, 260576, 260627, 262163, 262167, 262204, 262205, 262235, 262250, 262252, 262254, 262270, 262271, 262273, 262274, 262277, 262328, 262620, 262640, 262656, 262694, 262695, 262703, 262726, 262733, 262735, 262768, 262777, 262784, 262811, 262816, 262818, 262819, 262834, 262836, 262837, 262893, 262921, 262987, 262988, 263005, 263007, 263022, 263031, 263033, 263035, 263233, 263261, 263284, 263286, 263293, 263322, 263333, 263349, 263355, 263362, 263379, 263400, 263410, 263412, 263491, 263502, 263511, 263584, 263604, 263614, 263685 };

string collisionSystem[NRuns] = { "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp13", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "pp502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502", "PbPb502" };

double runBField[NRuns] = {3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.8, 3.8, 0, 0, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8, 3.8 };

long packedDate[NRuns] = {20150918171940, 20150919155728, 20150919225036, 20150920020529, 20150920022407, 20150921070202, 20150921092806, 20150924022726, 20150924040423, 20150924045955, 20150924070148, 20150924162149, 20150925061345, 20150925185035, 20150925230456, 20150926103718, 20150926222020, 20150927124934, 20150928062418, 20150928135604, 20150928215349, 20150929080024, 20150929152628, 20150929180647, 20150930063356, 20151001012310, 20151001054153, 20151002103556, 20151002143006, 20151003020722, 20151003052922, 20151003201216, 20151004101112, 20151004172800, 20151004183612, 20151004200456, 20151005165917, 20151005221220, 20151006154800, 20151006195749, 20151006204833, 20151006230125, 20151007020817, 20151007070029, 20151007085732, 20151007095052, 20151007114945, 20151007125055, 20151007173920, 20151009135129, 20151009211416, 20151010094728, 20151010125845, 20151010134244, 20151010182929, 20151010215938, 20151010233842, 20151011153510, 20151011200610, 20151011215435, 20151012020653, 20151012034342, 20151015143359, 20151018092133, 20151020074751, 20151020115131, 20151020132443, 20151021073839, 20151021095649, 20151022000333, 20151023022655, 20151023031330, 20151023035023, 20151023052148, 20151023063239, 20151023075925, 20151023111840, 20151023230445, 20151024023634, 20151024170519, 20151024180544, 20151024185341, 20151027053541, 20151027065304, 20151027134257, 20151027174530, 20151028021957, 20151028065211, 20151028092411, 20151028131231, 20151028140506, 20151029032856, 20151029043426, 20151029045909, 20151029053526, 20151030124427, 20151031061608, 20151031211600, 20151031215302, 20151101091528, 20151101132738, 20151101152118, 20151102005021, 20151103063147, 20151119191232, 20151120002948, 20151120125153, 20151120144313, 20151120220658, 20151121022632, 20151121040256, 20151121121702, 20151121202539, 20151121224135, 20151122004825, 20151122072440, 20151122100515, 20151123063422, 20151126013820, 20151126080245, 20151126100241, 20151126173506, 20151126190304, 20151126210254, 20151127112733, 20151127121009, 20151127134318, 20151127235452, 20151128005730, 20151128034436, 20151128140157, 20151128171927, 20151128192543, 20151128201847, 20151129005142, 20151129014201, 20151129064910, 20151130003928, 20151130152405, 20151130215845, 20151201023441, 20151201113351, 20151201122546, 20151201134639, 20151201143405, 20151201150212, 20151201193333, 20151203133441, 20151204063917, 20151204135224, 20151204174952, 20151204202306, 20151205070503, 20151205112520, 20151205194301, 20151205202927, 20151206004439, 20151206123542, 20151206220949, 20151207092031, 20151207110432, 20151208080332, 20151208140212, 20151208154241, 20151209142936, 20151209233553, 20151210091551, 20151211064647 };

static const int runRange = 168;

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

TDatime TIME;

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

    TIME.Set(2003,01,01,00,00,00);
    int offset = TIME.Convert();

    long pack = packedDate[iRun];
    int theYear = pack / 10000000000;
    pack = pack % 10000000000;
    int theMonth = pack / 100000000;
    pack = pack % 100000000;
    int theDay = pack / 1000000;
    pack = pack % 1000000;
    int theHour = pack / 10000;
    pack = pack % 10000;
    int theMinute = pack / 100;
    int theSecond = pack % 100;

    TIME.Set(theYear, theMonth, theDay, theHour, theMinute, theSecond); 
    usedRuns[iRun] = TIME.Convert() - offset;

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
    //usedRuns[i] = runs[iRun];
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
  dummyGraph_xPos->GetXaxis()->SetTimeDisplay(1);
  dummyGraph_xPos->GetXaxis()->SetTimeFormat("%d/%m");
  dummyGraph_xPos->GetXaxis()->SetTitle("Date");
  dummyGraph_xPos->GetYaxis()->SetTitle("#Deltax [#mum]");
  dummyGraph_xPos->GetYaxis()->SetRangeUser(-xMax,xMax);
  dummyGraph_xPos->GetXaxis()->SetLimits(usedRuns[0],usedRuns[runRange-1]);
  dummyGraph_xPos->GetXaxis()->SetNdivisions(6);
  dummyGraph_xPos->GetXaxis()->SetLabelSize(0.06);

  dummyGraph_yPos->SetMarkerColorAlpha(0,0.);
  dummyGraph_yPos->GetXaxis()->SetTimeDisplay(1);
  dummyGraph_yPos->GetXaxis()->SetTimeFormat("%d/%m");
  dummyGraph_yPos->GetXaxis()->SetTitle("Date");
  dummyGraph_yPos->GetYaxis()->SetTitle("#Deltay [#mum]");
  dummyGraph_yPos->GetYaxis()->SetRangeUser(-yMax,yMax);
  dummyGraph_yPos->GetXaxis()->SetLimits(usedRuns[0],usedRuns[runRange-1]);
  dummyGraph_yPos->GetXaxis()->SetNdivisions(6);
  dummyGraph_yPos->GetXaxis()->SetLabelSize(0.06);

  dummyGraph_zPos->SetMarkerColorAlpha(0,0.);
  dummyGraph_zPos->GetXaxis()->SetTimeDisplay(1);
  dummyGraph_zPos->GetXaxis()->SetTimeFormat("%d/%m");
  dummyGraph_zPos->GetXaxis()->SetTitle("Date");
  dummyGraph_zPos->GetYaxis()->SetTitle("#Deltaz [#mum]");
  dummyGraph_zPos->GetYaxis()->SetRangeUser(-zMax,zMax);
  dummyGraph_zPos->GetXaxis()->SetLimits(usedRuns[0],usedRuns[runRange-1]);
  dummyGraph_zPos->GetXaxis()->SetNdivisions(6);
  dummyGraph_zPos->GetXaxis()->SetLabelSize(0.06);

  dummyGraph_xRot->SetMarkerColorAlpha(0,0.);
  dummyGraph_xRot->GetXaxis()->SetTimeDisplay(1);
  dummyGraph_xRot->GetXaxis()->SetTimeFormat("%d/%m");
  dummyGraph_xRot->GetXaxis()->SetTitle("Date");
  dummyGraph_xRot->GetYaxis()->SetTitle("#Delta#theta_{x} [#murad]");
  dummyGraph_xRot->GetYaxis()->SetRangeUser(-xRotMax,xRotMax);
  dummyGraph_xRot->GetXaxis()->SetLimits(usedRuns[0],usedRuns[runRange-1]);
  dummyGraph_xRot->GetXaxis()->SetNdivisions(6);
  dummyGraph_xRot->GetXaxis()->SetLabelSize(0.06);

  dummyGraph_yRot->SetMarkerColorAlpha(0,0.);
  dummyGraph_yRot->GetXaxis()->SetTimeDisplay(1);
  dummyGraph_yRot->GetXaxis()->SetTimeFormat("%d/%m");
  dummyGraph_yRot->GetXaxis()->SetTitle("Date");
  dummyGraph_yRot->GetYaxis()->SetTitle("#Delta#theta_{y} [#murad]");
  dummyGraph_yRot->GetYaxis()->SetRangeUser(-yRotMax,yRotMax);
  dummyGraph_yRot->GetXaxis()->SetLimits(usedRuns[0],usedRuns[runRange-1]);
  dummyGraph_yRot->GetXaxis()->SetNdivisions(6);
  dummyGraph_yRot->GetXaxis()->SetLabelSize(0.06);

  dummyGraph_zRot->SetMarkerColorAlpha(0,0.);
  dummyGraph_zRot->GetXaxis()->SetTimeDisplay(1);
  dummyGraph_zRot->GetXaxis()->SetTimeFormat("%d/%m");
  dummyGraph_zRot->GetXaxis()->SetTitle("Date");
  dummyGraph_zRot->GetYaxis()->SetTitle("#Delta#theta_{z} [#murad]");
  dummyGraph_zRot->GetYaxis()->SetRangeUser(-zRotMax,zRotMax);
  dummyGraph_zRot->GetXaxis()->SetLimits(usedRuns[0],usedRuns[runRange-1]);
  dummyGraph_zRot->GetXaxis()->SetNdivisions(6);
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
    gXpos[iDet]->GetXaxis()->SetTimeDisplay(1);
    gXpos[iDet]->GetXaxis()->SetTimeFormat("%d/%m");
    gXpos[iDet]->GetXaxis()->SetTitle("Date");
    gXpos[iDet]->GetYaxis()->SetTitle("#Deltax [#mum]");
    gXpos[iDet]->GetYaxis()->SetRangeUser(-15,15);
    gXpos[iDet]->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+1);
    gXpos[iDet]->GetXaxis()->SetNdivisions(6);
    gXpos[iDet]->GetXaxis()->SetLabelSize(0.06);
    gXpos[iDet]->SetLineColor(colors[iDet]);
    gXpos[iDet]->SetMarkerColor(colors[iDet]);
    gXpos[iDet]->SetMarkerStyle(markers[iDet]);

    gYpos[iDet]->SetTitle(Form("Ypos_%s_%s_%s",det0[iDet],det1[iDet],det2[iDet]));
    gYpos[iDet]->GetXaxis()->SetTimeDisplay(1);
    gYpos[iDet]->GetXaxis()->SetTimeFormat("%d/%m");
    gYpos[iDet]->GetXaxis()->SetTitle("Date");
    gYpos[iDet]->GetYaxis()->SetTitle("#mum");
    gYpos[iDet]->GetYaxis()->SetRangeUser(-20,20);
    gYpos[iDet]->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+1);
    gYpos[iDet]->GetXaxis()->SetNdivisions(6);
    gYpos[iDet]->GetXaxis()->SetLabelSize(0.06);
    gYpos[iDet]->SetLineColor(colors[iDet]);
    gYpos[iDet]->SetMarkerColor(colors[iDet]);
    gYpos[iDet]->SetMarkerStyle(markers[iDet]);

    gZpos[iDet]->SetTitle(Form("Zpos_%s_%s_%s",det0[iDet],det1[iDet],det2[iDet]));
    gZpos[iDet]->GetXaxis()->SetTimeDisplay(1);
    gZpos[iDet]->GetXaxis()->SetTimeFormat("%d/%m");
    gZpos[iDet]->GetXaxis()->SetTitle("Date");
    gZpos[iDet]->GetYaxis()->SetTitle("#mum");
    gZpos[iDet]->GetYaxis()->SetRangeUser(-25,25);
    gZpos[iDet]->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+1);
    gZpos[iDet]->GetXaxis()->SetNdivisions(6);
    gXpos[iDet]->GetXaxis()->SetLabelSize(0.06);
    gZpos[iDet]->SetLineColor(colors[iDet]);
    gZpos[iDet]->SetMarkerColor(colors[iDet]);
    gZpos[iDet]->SetMarkerStyle(markers[iDet]);

    gXrot[iDet]->SetTitle(Form("Xrot_%s_%s_%s",det0[iDet],det1[iDet],det2[iDet]));
    gXrot[iDet]->GetXaxis()->SetTimeDisplay(1);
    gXrot[iDet]->GetXaxis()->SetTimeFormat("%d/%m");
    gXrot[iDet]->GetXaxis()->SetTitle("Date");
    gXrot[iDet]->GetYaxis()->SetTitle("#murad");
    gXrot[iDet]->GetYaxis()->SetRangeUser(-40,40);
    gXrot[iDet]->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+1);
    gXrot[iDet]->GetXaxis()->SetNdivisions(6);
    gXrot[iDet]->SetLineColor(colors[iDet]);
    gXrot[iDet]->SetMarkerColor(colors[iDet]);
    gXrot[iDet]->SetMarkerStyle(markers[iDet]);

    gYrot[iDet]->SetTitle(Form("Yrot_%s_%s_%s",det0[iDet],det1[iDet],det2[iDet]));
    gYrot[iDet]->GetXaxis()->SetTimeDisplay(1);
    gYrot[iDet]->GetXaxis()->SetTimeFormat("%d/%m");
    gYrot[iDet]->GetXaxis()->SetTitle("Date");
    gYrot[iDet]->GetYaxis()->SetTitle("#murad");
    gYrot[iDet]->GetYaxis()->SetRangeUser(-40,40);
    gYrot[iDet]->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+1);
    gYrot[iDet]->GetXaxis()->SetNdivisions(6);
    gYrot[iDet]->SetLineColor(colors[iDet]);
    gYrot[iDet]->SetMarkerColor(colors[iDet]);
    gYrot[iDet]->SetMarkerStyle(markers[iDet]);

    gZrot[iDet]->SetTitle(Form("Zrot_%s_%s_%s",det0[iDet],det1[iDet],det2[iDet]));
    gZrot[iDet]->GetXaxis()->SetTimeDisplay(1);
    gZrot[iDet]->GetXaxis()->SetTimeFormat("%d/%m");
    gZrot[iDet]->GetXaxis()->SetTitle("Date");
    gZrot[iDet]->GetYaxis()->SetTitle("#murad");
    gZrot[iDet]->GetYaxis()->SetRangeUser(-40,40);
    gZrot[iDet]->GetXaxis()->SetLimits(usedRuns[0]-1,usedRuns[runRange-1]+1);
    gZrot[iDet]->GetXaxis()->SetNdivisions(6);
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
  TLegend * leg = new TLegend(0.2789,0.1578,0.5265,0.3690);
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
  TDatime time257826;
  time257826.Set(2003,01,01,00,00,00);
  int oset = time257826.Convert();
  time257826.Set(2015,9,30,07,45,28);
  float t257826 = time257826.Convert() - oset;
  TLine * xPosUpdate257826  = new TLine(t257826, -xMax, t257826, xMax);
  xPosUpdate257826->SetLineColor(1);
  xPosUpdate257826->SetLineStyle(2);
  xPosUpdate257826->SetLineWidth(2);  
  TLine * yPosUpdate257826  = new TLine(t257826, -yMax, t257826, yMax);
  yPosUpdate257826->SetLineColor(1);
  yPosUpdate257826->SetLineStyle(2);
  yPosUpdate257826->SetLineWidth(2);
  TLine * zPosUpdate257826  = new TLine(t257826, -zMax, t257826, zMax);
  zPosUpdate257826->SetLineColor(1);
  zPosUpdate257826->SetLineStyle(2);
  zPosUpdate257826->SetLineWidth(2);
  TLine * xRotUpdate257826  = new TLine(t257826, -xRotMax, t257826, xRotMax);
  xRotUpdate257826->SetLineColor(1);
  xRotUpdate257826->SetLineStyle(2);
  xRotUpdate257826->SetLineWidth(2);
  TLine * yRotUpdate257826  = new TLine(t257826, -yRotMax, t257826, yRotMax);
  yRotUpdate257826->SetLineColor(1);
  yRotUpdate257826->SetLineStyle(2);
  yRotUpdate257826->SetLineWidth(2);
  TLine * zRotUpdate257826  = new TLine(t257826, -zRotMax, t257826, zRotMax);
  zRotUpdate257826->SetLineColor(1);
  zRotUpdate257826->SetLineStyle(2);
  zRotUpdate257826->SetLineWidth(2);

  TDatime time262340;
  time262340.Set(2015,11,23,8,02,32);
  float t262340 = time262340.Convert() - oset;
  TLine * xPosUpdate262340  = new TLine(t262340, -xMax, t262340, xMax);
  xPosUpdate262340->SetLineColor(1);
  xPosUpdate262340->SetLineStyle(2);
  xPosUpdate262340->SetLineWidth(2);
  TLine * yPosUpdate262340  = new TLine(t262340, -yMax, t262340, yMax);
  yPosUpdate262340->SetLineColor(1);
  yPosUpdate262340->SetLineStyle(2);
  yPosUpdate262340->SetLineWidth(2);
  TLine * zPosUpdate262340  = new TLine(t262340, -zMax, t262340, zMax);
  zPosUpdate262340->SetLineColor(1);
  zPosUpdate262340->SetLineStyle(2);
  zPosUpdate262340->SetLineWidth(2);
  TLine * xRotUpdate262340  = new TLine(t262340, -xRotMax, t262340, xRotMax);
  xRotUpdate262340->SetLineColor(1);
  xRotUpdate262340->SetLineStyle(2);
  xRotUpdate262340->SetLineWidth(2);
  TLine * yRotUpdate262340  = new TLine(t262340, -yRotMax, t262340, yRotMax);
  yRotUpdate262340->SetLineColor(1);
  yRotUpdate262340->SetLineStyle(2);
  yRotUpdate262340->SetLineWidth(2);
  TLine * zRotUpdate262340  = new TLine(t262340, -zRotMax, t262340, zRotMax);
  zRotUpdate262340->SetLineColor(1);
  zRotUpdate262340->SetLineStyle(2);
  zRotUpdate262340->SetLineWidth(2);

  TDatime time262922;
  time262922.Set(2015,11,30,16,20,20);
  float t262922 = time262922.Convert() - oset;
  TLine * xPosUpdate262922  = new TLine(t262922, -xMax, t262922, xMax);
  xPosUpdate262922->SetLineColor(1);
  xPosUpdate262922->SetLineStyle(2);
  xPosUpdate262922->SetLineWidth(2);
  TLine * yPosUpdate262922  = new TLine(t262922, -yMax, t262922, yMax);
  yPosUpdate262922->SetLineColor(1);
  yPosUpdate262922->SetLineStyle(2);
  yPosUpdate262922->SetLineWidth(2);
  TLine * zPosUpdate262922  = new TLine(t262922, -zMax, t262922, zMax);
  zPosUpdate262922->SetLineColor(1);
  zPosUpdate262922->SetLineStyle(2);
  zPosUpdate262922->SetLineWidth(2);
  TLine * xRotUpdate262922  = new TLine(t262922, -xRotMax, t262922, xRotMax);
  xRotUpdate262922->SetLineColor(1);
  xRotUpdate262922->SetLineStyle(2);
  xRotUpdate262922->SetLineWidth(2);
  TLine * yRotUpdate262922  = new TLine(t262922, -yRotMax, t262922, yRotMax);
  yRotUpdate262922->SetLineColor(1);
  yRotUpdate262922->SetLineStyle(2);
  yRotUpdate262922->SetLineWidth(2);
  TLine * zRotUpdate262922  = new TLine(t262922, -zRotMax, t262922, zRotMax);
  zRotUpdate262922->SetLineColor(1);
  zRotUpdate262922->SetLineStyle(2);
  zRotUpdate262922->SetLineWidth(2);

  //--Era Change lines
  TDatime time260630;
  time260630.Set(2015,11,03,07,16,10);
  float t260630 = time260630.Convert() - oset;
  TLine * endpp13_x = new TLine(t260630, -xMax, t260630, xMax);
  endpp13_x->SetLineColor(2);
  endpp13_x->SetLineStyle(1);
  endpp13_x->SetLineWidth(3);
  TLine * endpp13_y = new TLine(t260630, -yMax, t260630, yMax);
  endpp13_y->SetLineColor(2);
  endpp13_y->SetLineStyle(1);
  endpp13_y->SetLineWidth(3);
  TLine * endpp13_z = new TLine(t260630, -zMax, t260630, zMax);
  endpp13_z->SetLineColor(2);
  endpp13_z->SetLineStyle(1);
  endpp13_z->SetLineWidth(3);
  TLine * endpp13_xRot = new TLine(t260630, -xRotMax, t260630, xRotMax);
  endpp13_xRot->SetLineColor(2);
  endpp13_xRot->SetLineStyle(1);
  endpp13_xRot->SetLineWidth(3);
  TLine * endpp13_yRot = new TLine(t260630, -yRotMax, t260630, yRotMax);
  endpp13_yRot->SetLineColor(2);
  endpp13_yRot->SetLineStyle(1);
  endpp13_yRot->SetLineWidth(3);
  TLine * endpp13_zRot = new TLine(t260630, -zRotMax, t260630, zRotMax);
  endpp13_zRot->SetLineColor(2);
  endpp13_zRot->SetLineStyle(1);
  endpp13_zRot->SetLineWidth(3);

  TLine * endpp502_x = new TLine(t262340, -xMax, t262340, xMax);
  endpp502_x->SetLineColor(2);
  endpp502_x->SetLineStyle(1);
  endpp502_x->SetLineWidth(3);
  TLine * endpp502_y = new TLine(t262340, -yMax, t262340, yMax);
  endpp502_y->SetLineColor(2);
  endpp502_y->SetLineStyle(1);
  endpp502_y->SetLineWidth(3);
  TLine * endpp502_z = new TLine(t262340, -zMax, t262340, zMax);
  endpp502_z->SetLineColor(2);
  endpp502_z->SetLineStyle(1);
  endpp502_z->SetLineWidth(3);
  TLine * endpp502_xRot = new TLine(t262340, -xRotMax, t262340, xRotMax);
  endpp502_xRot->SetLineColor(2);
  endpp502_xRot->SetLineStyle(1);
  endpp502_xRot->SetLineWidth(3);
  TLine * endpp502_yRot = new TLine(t262340, -yRotMax, t262340, yRotMax);
  endpp502_yRot->SetLineColor(2);
  endpp502_yRot->SetLineStyle(1);
  endpp502_yRot->SetLineWidth(3);
  TLine * endpp502_zRot = new TLine(t262340, -zRotMax, t262340, zRotMax);
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
  TDatime time256355;
  time256355.Set(2015,9,12,06,13,02);
  float t256355 = time256355.Convert() - oset;
  TDatime time256489;
  time256489.Set(2015,9,15,8,20,43);
  float t256489 = time256489.Convert() - oset;
  TBox * magnetCycle256355_x = new TBox(t256355,-xMax,t256489,xMax);
  magnetCycle256355_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle256355_y = new TBox(t256355,-yMax,t256489,yMax);
  magnetCycle256355_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle256355_z = new TBox(t256355,-zMax,t256489,zMax);
  magnetCycle256355_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle256355_xRot = new TBox(t256355,-xRotMax,t256489,xRotMax);
  magnetCycle256355_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle256355_yRot = new TBox(t256355,-yRotMax,t256489,yRotMax);
  magnetCycle256355_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle256355_zRot = new TBox(t256355,-zRotMax,t256489,zRotMax);
  magnetCycle256355_zRot->SetFillColorAlpha(13,0.5);

  TDatime time257021;
  time257021.Set(2015,9,21,18,15,28);
  float t257021 = time257021.Convert() - oset;
  TDatime time257375;
  time257375.Set(2015,9,23,22,24,16);
  float t257375 = time257375.Convert() - oset;
  TBox * magnetCycle257021_x = new TBox(t257021,-xMax,t257375,xMax);
  magnetCycle257021_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle257021_y = new TBox(t257021,-yMax,t257375,yMax);
  magnetCycle257021_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle257021_z = new TBox(t257021,-zMax,t257375,zMax);
  magnetCycle257021_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle257021_xRot = new TBox(t257021,-xRotMax,t257375,xRotMax);
  magnetCycle257021_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle257021_yRot = new TBox(t257021,-yRotMax,t257375,yRotMax);
  magnetCycle257021_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle257021_zRot = new TBox(t257021,-zRotMax,t257375,zRotMax);
  magnetCycle257021_zRot->SetFillColorAlpha(13,0.5);

  TDatime time259896;
  time259896.Set(2015,10,25,03,23,14);
  float t259896 = time259896.Convert() - oset;
  TDatime time260324;
  time260324.Set(2015,10,29,16,59,24);
  float t260324 = time260324.Convert() - oset;
  TBox * magnetCycle259896_x = new TBox(t259896,-xMax,t260324,xMax);
  magnetCycle259896_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle259896_y = new TBox(t259896,-yMax,t260324,yMax);
  magnetCycle259896_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle259896_z = new TBox(t259896,-zMax,t260324,zMax);
  magnetCycle259896_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle259896_xRot = new TBox(t259896,-xRotMax,t260324,xRotMax);
  magnetCycle259896_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle259896_yRot = new TBox(t259896,-yRotMax,t260324,yRotMax);
  magnetCycle259896_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle259896_zRot = new TBox(t259896,-zRotMax,t260324,zRotMax);
  magnetCycle259896_zRot->SetFillColorAlpha(13,0.5);

  TDatime time260432;
  time260432.Set(2015,10,31,10,32,10);
  float t260432 = time260432.Convert() - oset;
  TDatime time260527;
  time260527.Set(2015,11,01,03,27,17);
  float t260527 = time260527.Convert() - oset;
  TBox * magnetCycle260432_x = new TBox(t260432,-xMax,t260527,xMax);
  magnetCycle260432_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle260432_y = new TBox(t260432,-yMax,t260527,yMax);
  magnetCycle260432_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle260432_z = new TBox(t260432,-zMax,t260527,zMax);
  magnetCycle260432_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle260432_xRot = new TBox(t260432,-xRotMax,t260527,xRotMax);
  magnetCycle260432_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle260432_yRot = new TBox(t260432,-yRotMax,t260527,yRotMax);
  magnetCycle260432_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle260432_zRot = new TBox(t260432,-zRotMax,t260527,zRotMax);
  magnetCycle260432_zRot->SetFillColorAlpha(13,0.5);

  TDatime time260744;
  time260744.Set(2015,11,04,13,56,34);
  float t260744 = time260744.Convert() - oset;
  TDatime time261084;
  time261084.Set(2015,11,11,14,15,00);
  float t261084 = time261084.Convert() - oset;
  TBox * magnetCycle260744_x = new TBox(t260744,-xMax,t261084,xMax);
  magnetCycle260744_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle260744_y = new TBox(t260744,-yMax,t261084,yMax);
  magnetCycle260744_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle260744_z = new TBox(t260744,-zMax,t261084,zMax);
  magnetCycle260744_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle260744_xRot = new TBox(t260744,-xRotMax,t261084,xRotMax);
  magnetCycle260744_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle260744_yRot = new TBox(t260744,-yRotMax,t261084,yRotMax);
  magnetCycle260744_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle260744_zRot = new TBox(t260744,-zRotMax,t261084,zRotMax);
  magnetCycle260744_zRot->SetFillColorAlpha(13,0.5);

  TDatime time261122;
  time261122.Set(2015,11,12,07,25,22);
  float t261122 = time261122.Convert() - oset;
  TDatime time261914;
  time261914.Set(2015,11,18,12,9,9);
  float t261914 = time261914.Convert() - oset;
  TBox * magnetCycle261122_x = new TBox(t261122,-xMax,t261914,xMax);
  magnetCycle261122_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle261122_y = new TBox(t261122,-yMax,t261914,yMax);
  magnetCycle261122_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle261122_z = new TBox(t261122,-zMax,t261914,zMax);
  magnetCycle261122_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle261122_xRot = new TBox(t261122,-xRotMax,t261914,xRotMax);
  magnetCycle261122_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle261122_yRot = new TBox(t261122,-yRotMax,t261914,yRotMax);
  magnetCycle261122_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle261122_zRot = new TBox(t261122,-zRotMax,t261914,zRotMax);
  magnetCycle261122_zRot->SetFillColorAlpha(13,0.5);

  TDatime time262348;
  time262348.Set(2015,11,23,10,56,11);
  float t262348 = time262348.Convert() - oset;
  TDatime time262442;
  time262442.Set(2015,11,24,9,37,13);
  float t262442 = time262442.Convert() - oset;
  TBox * magnetCycle262348_x = new TBox(t262348,-xMax,t262442,xMax);
  magnetCycle262348_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle262348_y = new TBox(t262348,-yMax,t262442,yMax);
  magnetCycle262348_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle262348_z = new TBox(t262348,-zMax,t262442,zMax);
  magnetCycle262348_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle262348_xRot = new TBox(t262348,-xRotMax,t262442,xRotMax);
  magnetCycle262348_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle262348_yRot = new TBox(t262348,-yRotMax,t262442,yRotMax);
  magnetCycle262348_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle262348_zRot = new TBox(t262348,-zRotMax,t262442,zRotMax);
  magnetCycle262348_zRot->SetFillColorAlpha(13,0.5);

  TDatime time263096;
  time263096.Set(2015,12,02,04,47,55);
  float t263096 = time263096.Convert() - oset;
  TDatime time263230;
  time263230.Set(2015,12,03,8,11,38);
  float t263230 = time263230.Convert() - oset;
  TBox * magnetCycle263096_x = new TBox(t263096,-xMax,t263230,xMax);
  magnetCycle263096_x->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle263096_y = new TBox(t263096,-yMax,t263230,yMax);
  magnetCycle263096_y->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle263096_z = new TBox(t263096,-zMax,t263230,zMax);
  magnetCycle263096_z->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle263096_xRot = new TBox(t263096,-xRotMax,t263230,xRotMax);
  magnetCycle263096_xRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle263096_yRot = new TBox(t263096,-yRotMax,t263230,yRotMax);
  magnetCycle263096_yRot->SetFillColorAlpha(13,0.5);
  TBox * magnetCycle263096_zRot = new TBox(t263096,-zRotMax,t263230,zRotMax);
  magnetCycle263096_zRot->SetFillColorAlpha(13,0.5);

  //--Line and box legend
  TLine * magnetCycleRef = new TLine(t263096,-zRotMax,t263230,zRotMax);
  magnetCycleRef->SetLineColor(13);
  magnetCycleRef->SetLineStyle(1);
  magnetCycleRef->SetLineWidth(7);
  TLegend * leg2 = new TLegend(0.2789,0.7078,0.5265,0.8093);
  leg2->SetTextFont(82);
  leg2->AddEntry(endpp13_x,"Data Era Switch","l");
  leg2->AddEntry(xPosUpdate262340,"Reference Geometry Update","l");
  leg2->AddEntry(magnetCycleRef,"Magnet Cycle","l");
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);

  //TCanvas * cTrend = new TCanvas("cTrend","cTrend",3000,1800);
  //cTrend->Divide(3,2);
  
  TCanvas * cXPos = new TCanvas("cXPos","cXPos",1800,800);
  cXPos->cd();
  //cTrend->cd(1);
  dummyGraph_xPos->Draw("ap");
  //xPosBox->Draw("same");
  //magnetCycle256355_x->Draw("same");
  magnetCycle257021_x->Draw("same");
  magnetCycle259896_x->Draw("same");
  magnetCycle260432_x->Draw("same");
  magnetCycle260744_x->Draw("same");
  magnetCycle261122_x->Draw("same");
  magnetCycle262348_x->Draw("same");
  magnetCycle263096_x->Draw("same");
  endpp13_x->Draw("same");
  endpp502_x->Draw("same");
  xPosUpdate257826->Draw("same");
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
  //latex->DrawLatex(0.16,0.91,"CMS");
  //latex3->DrawLatex(0.208,0.91,"Preliminary");
  latex4->DrawLatex(0.515,0.91,"3.16 fb^{-1} (13 TeV pp) + 25.5 pb^{-1} (5.02 TeV pp) + 303.5 #mub^{-1} (5.02 TeV PbPb)");
  latex2->DrawLatex(0.29,0.85,"Tracker Alignment in 2015 Data");
  latex2->DrawLatex(0.29,0.82,"Taking Used as Reference");
  cXPos->SaveAs("trendPlots/xPos.pdf");

  TCanvas * cYPos = new TCanvas("cYPos","cYPos",1800,800);
  cYPos->cd();
  //cTrend->cd(2);
  dummyGraph_yPos->Draw("ap");
  //yPosBox->Draw("same");
  //magnetCycle256355_y->Draw("same");
  magnetCycle257021_y->Draw("same");
  magnetCycle259896_y->Draw("same");
  magnetCycle260432_y->Draw("same");
  magnetCycle260744_y->Draw("same");
  magnetCycle261122_y->Draw("same");
  magnetCycle262348_y->Draw("same");
  magnetCycle263096_y->Draw("same");
  endpp13_y->Draw("same");
  endpp502_y->Draw("same");
  yPosUpdate257826->Draw("same");
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
  //latex->DrawLatex(0.16,0.91,"CMS");
  //latex3->DrawLatex(0.208,0.91,"Preliminary");
  latex4->DrawLatex(0.515,0.91,"3.16 fb^{-1} (13 TeV pp) + 25.5 pb^{-1} (5.02 TeV pp) + 303.5 #mub^{-1} (5.02 TeV PbPb)");
  latex2->DrawLatex(0.29,0.85,"Tracker Alignment in 2015 Data");
  latex2->DrawLatex(0.29,0.82,"Taking Used as Reference");
  cYPos->SaveAs("trendPlots/yPos.pdf");

  TCanvas * cZPos = new TCanvas("cZPos","cZPos",1800,800);
  cZPos->cd();
  //cTrend->cd(3);
  dummyGraph_zPos->Draw("ap");
  //zPosBox->Draw("same");
  //magnetCycle256355_z->Draw("same");
  magnetCycle257021_z->Draw("same");
  magnetCycle259896_z->Draw("same");
  magnetCycle260432_z->Draw("same");
  magnetCycle260744_z->Draw("same");
  magnetCycle261122_z->Draw("same");
  magnetCycle262348_z->Draw("same");
  magnetCycle263096_z->Draw("same");
  endpp13_z->Draw("same");
  endpp502_z->Draw("same");
  zPosUpdate257826->Draw("same");
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
  //latex->DrawLatex(0.16,0.91,"CMS");
  //latex3->DrawLatex(0.208,0.91,"Preliminary");
  latex4->DrawLatex(0.515,0.91,"3.16 fb^{-1} (13 TeV pp) + 25.5 pb^{-1} (5.02 TeV pp) + 303.5 #mub^{-1} (5.02 TeV PbPb)");
  latex2->DrawLatex(0.29,0.85,"Tracker Alignment in 2015 Data");
  latex2->DrawLatex(0.29,0.82,"Taking Used as Reference");
  cZPos->SaveAs("trendPlots/zPos.pdf");

  TCanvas * cXRot = new TCanvas("cXRot","cXRot",1800,800);
  cXRot->cd();
  //cTrend->cd(4);
  dummyGraph_xRot->Draw("ap");
  //xyzRotBox->Draw("same");
  //magnetCycle256355_xRot->Draw("same");
  magnetCycle257021_xRot->Draw("same");
  magnetCycle259896_xRot->Draw("same");
  magnetCycle260432_xRot->Draw("same");
  magnetCycle260744_xRot->Draw("same");
  magnetCycle261122_xRot->Draw("same");
  magnetCycle262348_xRot->Draw("same");
  magnetCycle263096_xRot->Draw("same");
  endpp13_xRot->Draw("same");
  endpp502_xRot->Draw("same");
  xRotUpdate257826->Draw("same");
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
  //latex->DrawLatex(0.16,0.91,"CMS");
  //latex3->DrawLatex(0.208,0.91,"Preliminary");
  latex4->DrawLatex(0.515,0.91,"3.16 fb^{-1} (13 TeV pp) + 25.5 pb^{-1} (5.02 TeV pp) + 303.5 #mub^{-1} (5.02 TeV PbPb)");
  latex2->DrawLatex(0.29,0.85,"Tracker Alignment in 2015 Data");
  latex2->DrawLatex(0.29,0.82,"Taking Used as Reference");
  cXRot->SaveAs("trendPlots/xRot.pdf");

  TCanvas * cYRot = new TCanvas("cYRot","cYRot",1800,800);
  cYRot->cd();
  //cTrend->cd(5);
  dummyGraph_yRot->Draw("ap");
  //xyzRotBox->Draw("same");
  //magnetCycle256355_yRot->Draw("same");
  magnetCycle257021_yRot->Draw("same");
  magnetCycle259896_yRot->Draw("same");
  magnetCycle260432_yRot->Draw("same");
  magnetCycle260744_yRot->Draw("same");
  magnetCycle261122_yRot->Draw("same");
  magnetCycle262348_yRot->Draw("same");
  magnetCycle263096_yRot->Draw("same");
  endpp13_yRot->Draw("same");
  endpp502_yRot->Draw("same");
  yRotUpdate257826->Draw("same");
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
  //latex->DrawLatex(0.16,0.91,"CMS");
  //latex3->DrawLatex(0.208,0.91,"Preliminary");
  latex4->DrawLatex(0.515,0.91,"3.16 fb^{-1} (13 TeV pp) + 25.5 pb^{-1} (5.02 TeV pp) + 303.5 #mub^{-1} (5.02 TeV PbPb)");
  latex2->DrawLatex(0.29,0.85,"Tracker Alignment in 2015 Data");
  latex2->DrawLatex(0.29,0.82,"Taking Used as Reference");
  cYRot->SaveAs("trendPlots/yRot.pdf");
  
  //cTrend->cd(6);
  TCanvas * cZRot = new TCanvas("cZRot","cZRot",1800,800);
  cZRot->cd();
  dummyGraph_zRot->Draw("ap");
  //xyzRotBox->Draw("same");
  //magnetCycle256355_zRot->Draw("same");
  magnetCycle257021_zRot->Draw("same");
  magnetCycle259896_zRot->Draw("same");
  magnetCycle260432_zRot->Draw("same");
  magnetCycle260744_zRot->Draw("same");
  magnetCycle261122_zRot->Draw("same");
  magnetCycle262348_zRot->Draw("same");
  magnetCycle263096_zRot->Draw("same");
  endpp13_zRot->Draw("same");
  endpp502_zRot->Draw("same");
  zRotUpdate257826->Draw("same");
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
  //latex->DrawLatex(0.16,0.91,"CMS");
  //latex3->DrawLatex(0.208,0.91,"Preliminary");
  latex4->DrawLatex(0.515,0.91,"3.16 fb^{-1} (13 TeV pp) + 25.5 pb^{-1} (5.02 TeV pp) + 303.5 #mub^{-1} (5.02 TeV PbPb)");
  latex2->DrawLatex(0.29,0.85,"Tracker Alignment in 2015 Data");
  latex2->DrawLatex(0.29,0.82,"Taking Used as Reference");
  cZRot->SaveAs("trendPlots/zRot.pdf");

  //cTrend->cd(0);
  //leg->Draw("same");
  //latex->DrawLatex(0.005,0.965,"CMS Preliminary");
  //cTrend->SaveAs("TrendPlot.pdf");
  //cTrend->Close();
}
