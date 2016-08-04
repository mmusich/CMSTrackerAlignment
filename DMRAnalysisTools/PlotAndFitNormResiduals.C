#include <Riostream.h>
#include <stdio.h>
#include <iomanip>
#include <TFile.h>
#include <TF1.h>
#include <TText.h>
#include <TH1D.h>
#include <TH2D.h>
#include <THStack.h>
#include <TPaveStats.h>
#include <TPaveText.h>
#include <TString.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TList.h"
#include "TObject.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TObjArray.h"
#include "TObjString.h"

Double_t getMaximum(TObjArray *array);
void setTDRStyle();
void DoubleGausFitResiduals(TH1 *hist);
void TripleGausFitResiduals(TH1 *hist);
void fitResiduals(TH1 *hist);
Double_t normGaus(Double_t *x, Double_t *par);
TCanvas* DrawCanvasWithRatio(TCanvas* canvas,Int_t nOfFiles);

//void PlotAndFitNormResiduals(TString namesandlabels="MC/OfflineValidationParallel_result.root=former MC scenario,MC/OfflineValidationParallel_result.root=new MC scenario,DATA/OfflineValidationParallel_result.root=2011 Data Legacy",Int_t nOfFiles=3,int a=0){

void PlotAndFitNormResiduals(TString namesandlabels="AlignmentValidation_validation_MC_isoMuons_summer12_DR53X_native.root=MC 53X native,AlignmentValidation_validation_MC_isoMuons_csa14_25ns_scenario_ape.root=MC 53X - csa 14 (25ns),AlignmentValidation_validation_2012ABC_isoMuons_reprocessing_FT_R_53_V18.root=Data 2012ABC,AlignmentValidation_validation_2012D_isoMuons_reprocessing_FT_R_53_V21.root=Data 2012D",Int_t nOfFiles=4,int a=0){

  //void PlotAndFitNormResiduals(TString namesandlabels="AlignmentValidation_validation_MC_isoMuons_summer12_DR53X_native.root=MC 53X native",Int_t nOfFiles=1,int a=0){

  //void PlotAndFitNormResiduals(TString namesandlabels="MC/OfflineValidationParallel_result.root=former MC scenario,MC/OfflineValidationParallel_result.root=new MC scenario",Int_t nOfFiles=2,int a=0){

  //setTDRStyle();    

  //gStyle->SetCanvasDefH(500); //Height of canvas
  //gStyle->SetCanvasDefW(500); //Width of canvas

  // Margins:
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetPadRightMargin(0.03); 
  //gStyle->SetOptStat("emr"); 
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gStyle->SetOptTitle(0);
  gStyle->SetNdivisions(505,"XYZ"); 
  gStyle->SetOptStat(0); 
  gStyle->SetNdivisions(505,"XYZ"); 
  

  //TFile *data = new TFile("mergeTestAPEonMP.root");
  //TFile *data = new TFile(filename);

  TList *FileList = new TList();
  TList *LabelList = new TList();
  
  TObjArray *nameandlabelpairs = namesandlabels.Tokenize(",");
  for (Int_t i = 0; i < nameandlabelpairs->GetEntries(); ++i) {
    TObjArray *aFileLegPair = TString(nameandlabelpairs->At(i)->GetName()).Tokenize("=");
    
    if(aFileLegPair->GetEntries() == 2) {
      FileList->Add( TFile::Open(aFileLegPair->At(0)->GetName())  );  // 2
      LabelList->Add( aFileLegPair->At(1) );
    }
    else {
      std::cout << "Please give file name and legend entry in the following form:\n" 
		<< " filename1=legendentry1,filename2=legendentry2\n";   
    }    
  }
  
  const Int_t NOfFiles = FileList->GetSize();
  if(NOfFiles!=nOfFiles){
    cout<<"&MSG-e: NOfFiles = "<<nOfFiles<<endl;
    return;
  }  

  TString LegLabels[10];  
  
  for(Int_t j=0; j < NOfFiles; j++) {   
    TObjString* legend = (TObjString*)LabelList->At(j);
    LegLabels[j] = legend->String();
    cout<<"LegLabels["<<j<<"]"<<LegLabels[j]<<endl;
  }

  Int_t nplot = 8; 
  TString plotnames[8] = {"h_NormXprime_TPBBarrel_1","h_NormYprime_TPBBarrel_1","h_NormXprime_TPEEndcap_2","h_NormYprime_TPEEndcap_2","h_NormXprime_TIBBarrel_1","h_NormXprime_TOBBarrel_4","h_NormXprime_TIDEndcap_2","h_NormXprime_TECEndcap_5"};
  TString names[8]= {"TrackerOfflineValidationStandalone/Pixel/h_NormXprime_TPBBarrel_1","TrackerOfflineValidationStandalone/Pixel/h_NormYprime_TPBBarrel_1","TrackerOfflineValidationStandalone/Pixel/h_NormXprime_TPEEndcap_2","TrackerOfflineValidationStandalone/Pixel/h_NormYprime_TPEEndcap_2","TrackerOfflineValidationStandalone/Strip/h_NormXprime_TIBBarrel_1","TrackerOfflineValidationStandalone/Strip/h_NormXprime_TOBBarrel_4","TrackerOfflineValidationStandalone/Strip/h_NormXprime_TIDEndcap_2","TrackerOfflineValidationStandalone/Strip/h_NormXprime_TECEndcap_5"}; 
  //  TString titles[8]= {"Normalized Residuals TPB (x_{local} coord)","Normalized Residuals TPB (y_{local} coord)","Normalized Residuals TPE (x_{local} coord)","Normalized Residuals TPE (y_{local} coord)","Normalized Residuals TIB","Normalized Residuals TOB","Normalized Residuals TID","Normalized Residuals TEC"};
  //TString titles[8]= {"TPB (x)","TPB (y)","TPE (x)","TPE (y)","TIB","TOB","TID","TEC"};
  TString titles[8]= {"Pixel Barrel (x)","Pixel Barrel (y)","Pixel Forward (x)","Pixel Forward (y)","Tracker Inner Barrel","Tracker Outer Barrel","Tracker Inner Disks","Tracker EndCaps"};

  //TString titles[8]= {"TPB","TPB","TPE","TPE","TIB","TOB","TID","TEC"};
  //TString titleX[8]={"(u¥_{pred} - u¥_{rec})/#sigma ","(v¥_{pred} - v¥_{rec})/#sigma ","(u¥_{pred} - u¥_{rec})/#sigma ","(v¥_{pred} - v¥_{rec})/#sigma ","(u¥_{pred} - u¥_{rec})/#sigma ","(u¥_{pred} - u¥_{rec})/ #sigma ","(u¥_{pred} - u¥_{rec})/#sigma","(u¥_{pred} - u¥_{rec})/#sigma"};
  TString titleX[8]={"#hat{r_{n}} = (x'_{pred}-x'_{rec})/#sigma","#hat{r_{n}} = (y'_{pred}-y'_{rec})/#sigma","#hat{r_{n}} = (x'_{pred}-x'_{rec})/#sigma","#hat{r_{n}} = (y'_{pred}-y'_{rec})/#sigma","#hat{r_{n}} = (x'_{pred}-x'_{rec})/#sigma","#hat{r_{n}} = (x'_{pred}-x'_{rec})/ #sigma","#hat{r_{n}} = (x'_{pred}-x'_{rec})/#sigma","#hat{r_{n}} = (x'_{pred}-x'_{rec})/#sigma"};
  //TString titleY[8]={"hits","hits","hits","hits","hits","hits","hits","hits"};
  TString titleY[8]={"hits fraction (%)","hits fraction (%)","hits fraction (%)","hits fraction (%)","hits fraction (%)","hits fraction (%)","hits fraction (%)","hits fraction (%)"};
  TString canvasnames[8]= {"cPXBx","cPXBy","cPXFx","cPXFy","cTIB","cTOB","cTID","cTEC"};
  
  cout<<"wonderPlotAndFit::OverlayTH1() -> function called"<<endl;
  
  TFile *file[NOfFiles];
  //TCanvas* canvas[NOfFiles][nplot];
  //TCanvas* canvas2[NOfFiles][nplot];
  TH1* histo[NOfFiles][nplot];
  TH1* histo2[NOfFiles][nplot];
  TPaveText *leg[nplot]; 
  const char* prepleg[NOfFiles][nplot];
  TString LEGO[10][8];
  Double_t theMaximum[NOfFiles][nplot];
  
  for(Int_t c=0; c<nplot; c++) {
    
    TCanvas *c1 = new TCanvas(canvasnames[c],canvasnames[c],800,700);
    leg[c] = new TPaveText(0.13,0.71,0.43,0.90,"NDC"); 
    leg[c]->SetTextAlign(11);
       
    //#########CANVAS SETTINGS##############  
    
    if(a==0){
      c1->SetLogy(0);
    } else {
      c1->SetLogy(1);
    }
    
    // c1->SetGridx();
    //c1->SetGridy();

    //########HISTOS BOOKING###############
    
    Int_t colors[8] = {kBlue,kRed,kMagenta,kMagenta-2,6,8,40,46};
    //Int_t styles[8] = {20,20,21,21,22,23,26,28};
    Int_t styles[8] = {20,21,24,25};
    Int_t linestyles[8]={1,1,1,1,1,1,1,1};

    //## N.B. since the MC input file contains both mp1382 and the former MC scenario we need to add a _2 to get it.
    // so the order is "MC/OfflineValidationParallel_result.root=Former MC scenario,MC/OfflineValidationParallel_result.root=New MC scenario,DATA/OfflineValidationParallel_result.root=DATA"
    TString suffix[8] = {"","","","","","","",""};

    for(Int_t j=0; j < NOfFiles; j++) { 

      std::cout<<"inside ["<<c<<"]["<<j<<"]"<< "names: "<<names[c]<<std::endl;

      file[j] = (TFile*)FileList->At(j);
      //canvas[j][c] = (TCanvas*)file[j]->Get(names[c]); 
      //histo[j][c] = (TH1F*)canvas[j][c]->GetPrimitive(plotnames[c]+suffix[j]);
      histo[j][c] = (TH1F*)file[j]->Get(names[c]);
      

      std::cout<<"inside ["<<c<<"]["<<j<<"]"<< "names: "<<names[c]<<std::endl;
      
      TString newString = TString(histo[j][c]->GetName())+Form("_file_%i",j);
      const char *newname = newString.Data();
      std::cout<<newname<<std::endl;
      histo[j][c]->SetName(newname);
      
      std::cout<<"inside ["<<c<<"]["<<j<<"]"<< "names: "<<names[c]<<std::endl;

      //Special cases for endcaps
      
      if(titles[c].Contains("TPE (x)")){
	//canvas2[j][c] = (TCanvas*)file[j]->Get("TrackerOfflineValidationStandalone/Pixel/h_NormXprime_TPEEndcap_3"); 
        //histo2[j][c] = (TH1F*)canvas2[j][c]->GetPrimitive("h_NormXprime_TPEEndcap_3"+suffix[j]);  
	histo2[j][c] = (TH1F*)file[j]->Get("TrackerOfflineValidationStandalone/Pixel/h_NormXprime_TPEEndcap_3"); 
      	histo[j][c]->Add(histo2[j][c],1);
      }
      else if(titles[c].Contains("TPE (y)")){
	//canvas2[j][c] = (TCanvas*)file[j]->Get("TrackerOfflineValidationStandalone/Pixel/h_NormYprime_TPEEndcap_3"); 
      	//histo2[j][c] = (TH1F*)canvas2[j][c]->GetPrimitive("h_NormYprime_TPEEndcap_3"+suffix[j]);  
	histo2[j][c] = (TH1F*)file[j]->Get("TrackerOfflineValidationStandalone/Pixel/h_NormYprime_TPEEndcap_3"); 
      	histo[j][c]->Add(histo2[j][c],1);
      }
      else if(titles[c].Contains("TID")){
	//canvas2[j][c] = (TCanvas*)file[j]->Get("TrackerOfflineValidationStandalone/Strip/h_NormXprime_TIDEndcap_3"); 
        //histo2[j][c] = (TH1F*)canvas2[j][c]->GetPrimitive("h_NormXprime_TIDEndcap_3"+suffix[j]);
	histo2[j][c] = (TH1F*)file[j]->Get("TrackerOfflineValidationStandalone/Strip/h_NormXprime_TIDEndcap_3"); 
      	histo[j][c]->Add(histo2[j][c],1);
      }
      else if(titles[c].Contains("TEC")){
	//canvas2[j][c] = (TCanvas*)file[j]->Get("TrackerOfflineValidationStandalone/Strip/h_NormXprime_TECEndcap_6"); 
        //histo2[j][c] = (TH1F*)canvas2[j][c]->GetPrimitive("h_NormXprime_TECEndcap_6"+suffix[j]);  
	histo2[j][c] = (TH1F*)file[j]->Get("TrackerOfflineValidationStandalone/Strip/h_NormXprime_TECEndcap_6"); 
      	histo[j][c]->Add(histo2[j][c],1);
      }
      
      //cout<<" histo  =  (TH1F*) "<<file[j]<<" ->Get("<<names[c]<<");"<<endl;
      //histo->SetStats(kTRUE);
      histo[j][c]->SetLineColor(colors[j]);
      histo[j][c]->Rebin(2);
      histo[j][c]->SetLineWidth(3);
      // histo[j][c]->SetFillColor(colors[j]);
      histo[j][c]->SetLineStyle(linestyles[j]);
      //if(j!=0) 
      histo[j][c]->SetMarkerStyle(styles[j]);
      histo[j][c]->SetMarkerSize(1.3);
      histo[j][c]->SetMarkerColor(colors[j]);
      histo[j][c]->SetTitle(titles[c]);
      histo[j][c]->GetXaxis()->CenterTitle(true);
      histo[j][c]->GetYaxis()->CenterTitle(true);
      histo[j][c]->GetXaxis()->SetTitleOffset(1.2);
      histo[j][c]->GetXaxis()->SetLabelSize(0.06);
      histo[j][c]->GetXaxis()->SetLabelFont(42); 
      histo[j][c]->GetXaxis()->SetRangeUser(-3.,3.);

      //normalize the histogram
      histo[j][c]->Sumw2();
      histo[j][c]->Scale(100./histo[j][c]->GetSumOfWeights());
      //histo[j][c]->Scale(1/1000.);

      //put the maxima
      if(j==0){
	theMaximum[j][c]=histo[0][c]->GetMaximum();
      } else {
	if(histo[j][c]->GetMaximum() > histo[0][c]->GetMaximum()){
	  theMaximum[j][c]=histo[j][c]->GetMaximum();
	} else {
	  theMaximum[j][c]=histo[0][c]->GetMaximum();
	}
      }

      //cout<<"theMaximum["<<j<<"]["<<c<<"] "<<theMaximum[j][c]<<endl;
      histo[0][c]->GetYaxis()->SetRangeUser(0.,theMaximum[j][c]*1.10);
      histo[j][c]->GetYaxis()->SetRangeUser(0.,theMaximum[j][c]*1.10);
      histo[j][c]->GetXaxis()->SetTitle(titleX[c]);
      histo[j][c]->GetXaxis()->SetTitleSize(0.06); 
      histo[j][c]->GetXaxis()->SetTitleFont(42);
      histo[j][c]->GetYaxis()->SetTitle(titleY[c]);
      histo[j][c]->GetYaxis()->SetLabelSize(0.06);
      histo[j][c]->GetYaxis()->SetLabelFont(42); 
      histo[j][c]->GetYaxis()->SetTitleFont(42);
      histo[j][c]->GetYaxis()->SetTitleSize(0.06);
      histo[j][c]->GetYaxis()->SetTitleOffset(0.9);
      
      //cout<<"wonderPlotAndFit::OverlayTH1() -> histogram taken"<<endl;
      c1->cd();
          
      TF1 *fit = (TF1*)histo[j][c]->GetListOfFunctions()->FindObject("tmp");   
      if(fit)  {
       	delete fit;
      }
      
      fitResiduals(histo[j][c]);
      //DoubleGausFitResiduals(histo[j][c]);
      TF1 *tmp1 = (TF1*)histo[j][c]->GetListOfFunctions()->FindObject("myfit");
      
      TString newfit = TString(tmp1->GetName())+Form("_file_%i",j);
      const char *newfitname = newfit.Data();
      tmp1->SetName(newfitname);

      if(tmp1){
      	tmp1->SetLineColor(colors[j]);
	tmp1->SetLineWidth(2); 
      }

      cout<<"wonderPlotAndFit::OverlayTH1() -> fit done"<<endl;

      c1->cd();
      if(j==0){ 
	histo[j][c]->Draw("E1");

      } else{ 
	if (j==2){
	  histo[j][c]->Draw("E1Psames");
	} else { 
	  histo[j][c]->Draw("E1Psames");
	}
      }

      tmp1->Draw("same");
  
      c1->Draw(); 
  
      // double n1= tmp1->GetParameter(0);
      // double m1= tmp1->GetParameter(1);
      double s1= tmp1->GetParameter(2);
      // double n2= tmp1->GetParameter(3);
      // double m2= tmp1->GetParameter(4);
      // double s2= tmp1->GetParameter(5);
      //double theMean = (n1*m1 + n1*m2)/(n1+n2);
      //double theRMS = TMath::Sqrt(((n1*(m1*m1 +s1*s1) + n2*(m2*m2 + s2*s2))/(n1+n2)) - theMean*theMean);

      double theMean = histo[j][c]->GetMean();
      double theRMS = histo[j][c]->GetRMS();
      double theSigma = s1;

      //TString tmp =  "#splitline{"+LegLabels[j]+"}{#LT#hat{r_{n}}#GT = %.1f rms = %.2f}";
      TString tmp =  "#splitline{"+LegLabels[j]+"}{#sigma_{fit} = %.2f rms = %.2f}";

      prepleg[j][c] = tmp;
      //  prepleg[j][c] = firstprepleg[j][c]+"}{#mu = %.2f #sigma = %.2f}";
      
      LEGO[j][c].Form(prepleg[j][c],theSigma,theRMS);
      cout<<"prepleg["<<j<<"]["<< c <<"] = " << prepleg[j][c] << endl;
      cout<<"theMean: "<<theMean<<" theRMS: "<<theRMS<<endl;
      TText *le1 = leg[c]->AddText(LEGO[j][c]); 
      le1->SetTextFont(42);
      le1->SetTextSize(0.045);
      le1->SetTextColor(colors[j]);
      
      leg[c]->SetFillColor(10);
      //leg2->SetFillColor(10);
      leg[c]->SetLineColor(10);
      leg[c]->SetShadowColor(0);
      if(j==nOfFiles-1){
	leg[c]->Draw();  
      }
      // }
      // else
      // 	leg[c]->Draw("same");
      
      
      // if(j==0){
      // 	TPaveText *pt = new TPaveText(0.65,0.84,0.92,0.96,"NDC");
      // 	pt->SetFillColor(10);
      // 	pt->SetTextColor(1);
      // 	pt->SetTextSize(0.035);
      // 	pt->SetTextFont(52);
      // 	pt->SetTextAlign(12);
      // 	TText *text1 = pt->AddText("CMS Preliminary");
      // 	text1->SetTextSize(0.035); 
      // 	TText *text2 = pt->AddText("Tracker Alignment 2011");
      // 	text2->SetTextSize(0.035);
      // 	TText *text3 = pt->AddText(titles[c]);
      // 	text3->SetTextSize(0.05); 
      // 	text3->SetTextColor(kBlue);
      // 	pt->Draw("sames"); 
      // }

      if(j==0){
	TPaveText *pt = new TPaveText(0.50,0.83,0.94,0.91,"NDC");
      	pt->SetFillColor(10);
      	pt->SetTextColor(1);
      	pt->SetTextSize(0.06);
      	pt->SetTextFont(72);
      	//pt->SetTextAlign(12);
      	TText *text1 = pt->AddText(titles[c]);
      	text1->SetTextSize(0.065); 
      	text1->SetTextColor(kBlue);
      	pt->Draw("sames"); 

	TPaveText *pt2 = new TPaveText(0.15,0.937,0.744,0.997,"NDC");
      	pt2->SetFillColor(10);
      	pt2->SetTextColor(1);
      	pt2->SetTextSize(0.07);
      	pt2->SetTextFont(52);
      	pt2->SetTextAlign(12);
	TText *text2 = pt2->AddText("CMS Preliminary Tracker Alignment 2014");
      	text2->SetTextSize(0.055);
	pt2->Draw("sames"); 
      }

      c1->cd();
      c1->Draw("sames");
      if(j== NOfFiles-1){
	c1->SaveAs(canvasnames[c]+".png");
	c1->SaveAs(canvasnames[c]+".pdf");
	c1->SaveAs(canvasnames[c]+".eps");
      }    
    } //ends loop on files

    DrawCanvasWithRatio(c1,nOfFiles);

  } //ends loop on plots
}
 
////////////////////////////////////////////////////////////////////
TCanvas* DrawCanvasWithRatio(TCanvas* canvas,Int_t nOfFiles)
////////////////////////////////////////////////////////////////////
{
					       
  TIter next(canvas->GetListOfPrimitives());
  //TH1F* denominator = NULL;
  TObjArray *numerators = new TObjArray();
  numerators->Expand(nOfFiles);
  TObject* obj = NULL;

  while ((obj = next())) {
    //if(obj->InheritsFrom("TH1") && TString(obj->GetName()).Contains("file_0")) {
    //  denominator=(TH1F*)obj;
    // } else if (obj->InheritsFrom("TH1")) {
    if(obj->InheritsFrom("TH1")){
      std::cout<<"Object name: "<<TString(obj->GetName())<<std::endl;
      numerators->Add(obj);
    }
  }

  TF1* NormFunc = new TF1(Form("%s_normFunc",canvas->GetName()),"gausn",-3.,3.); 
  NormFunc->SetParameters(10.,0.,1.);
  NormFunc->SetLineColor(kBlack);
  NormFunc->SetFillColor(kGray);
  NormFunc->SetFillStyle(3003);
  NormFunc->SetLineWidth(4);
  NormFunc->SetLineStyle(9);

  TCanvas* c = new TCanvas(Form("%s_withRatio",canvas->GetName()),Form("%s with ratio",canvas->GetTitle()),800,800);
  TPad *canvas_1 = new TPad("canvas_1", canvas->GetTitle(),0,0.25,1.0,1.0);
  canvas_1->SetFillColor(10); 
  canvas_1->Draw();
  TPad *canvas_2 = new TPad("canvas_2", Form("%s ratio",canvas->GetTitle()),0,0.,1.0,0.32);
  canvas_2->SetFillColor(10); 
  canvas_2->Draw();
  // in pad 1, put a copy of the input
  canvas_1->cd();
  canvas->DrawClonePad();
  NormFunc->Draw("same");
  for(Int_t i=0; i<numerators->GetEntries();i++){
    TH1F* h = (TH1F*)(numerators->At(i));
    h->Draw("same");
  }

  // in pad 2, put the ratio plot and the relative uncertainty from MC
  canvas_2->cd();
  gPad->SetBottomMargin(0.45);
  gPad->SetTopMargin(0.12);
  gPad->SetGridy();
  gPad->SetGridx();
  
  std::cout<<"there are: "<<numerators->GetEntries()<<" histograms in the array"<<std::endl;

  for(Int_t i=0; i<numerators->GetEntries();i++){
    
    std::cout<<"before taking histo, i:"<<i<<std::endl;

    TH1F* histo_ratio = (TH1F*)(numerators->At(i)->Clone());
    TF1 *tmp1;  
    
    TIter nextone(histo_ratio->GetListOfFunctions());
    TObject *oo;

    while ( (oo=nextone()) ) {
      if(oo->InheritsFrom("TF1")){   
	const char* fitName = oo->GetName();
	tmp1 = (TF1*)histo_ratio->GetListOfFunctions()->FindObject(fitName);   
	if(tmp1) histo_ratio->GetListOfFunctions()->Remove(tmp1);
      }
    }

    std::cout<<"after removing the fits, i:"<<i<<std::endl;
	
    // create the ratio histogram
    //ratio->SetTitle("");
    //histo_ratio->Sumw2();
    histo_ratio->Divide(NormFunc,1.);
    
    std::cout<<"after histo i:"<<i<<std::endl;

    histo_ratio->GetYaxis()->SetTitle("Ratio to Ideal");
    histo_ratio->GetYaxis()->SetTitleFont(42);
    histo_ratio->GetYaxis()->SetTitleOffset(0.41);
    histo_ratio->GetYaxis()->SetTitleSize(0.12);
    histo_ratio->GetYaxis()->SetLabelFont(42);
    histo_ratio->GetYaxis()->SetLabelSize(0.13);
    histo_ratio->GetYaxis()->SetNdivisions( 505 );
    //histo_ratio->GetXaxis()->SetTitle(denominator->GetXaxis()->GetTitle());
    histo_ratio->GetXaxis()->SetTitleFont(42);
    histo_ratio->GetXaxis()->SetTitleSize( 0.17 );
    histo_ratio->GetXaxis()->SetLabelSize(0.16);
    histo_ratio->GetXaxis()->SetLabelFont(42);
    //histo_ratio->GetXaxis()->SetRange(denominator->GetXaxis()->GetFirst(), denominator->GetXaxis()->GetLast());
    histo_ratio->SetMinimum(0.45);
    histo_ratio->SetMaximum(1.55);
    //histo_ratio->SetMarkerStyle(20);
    histo_ratio->SetMarkerSize(1.);
    if(i==0){
      histo_ratio->Draw("E1");
    } else {
      histo_ratio->Draw("E1same");
    } 
  }

  c->SaveAs(TString(canvas->GetName())+"_withRatio.png");
  c->SaveAs(TString(canvas->GetName())+"_withRatio.pdf");
  c->SaveAs(TString(canvas->GetName())+"_withRatio.eps");

  return c;

}

// Float_t fitResiduals(TH1 *hist) const
// {
//   float fitResult(9999);
//   if (!hist || hist->GetEntries() < 20) return fitResult;
  
//   float mean  = hist->GetMean();
//   float sigma = hist->GetRMS();
  
//   try { // for < CMSSW_2_2_0 since ROOT warnings from fit are converted to exceptions
//     // Remove the try/catch for more recent CMSSW!
//     // first fit: two RMS around mean
//     TF1 func("tmp", "gaus", mean - 1.5*sigma, mean + 1.5*sigma); 
//     if (0 == hist->Fit(&func,"QNR")) { // N: do not blow up file by storing fit!
//       mean  = func.GetParameter(1);
//       sigma = func.GetParameter(2);
//       // second fit: three sigma of first fit around mean of first fit
//       func.SetRange(mean - 2.*sigma, mean + 2.*sigma);
//       // I: integral gives more correct results if binning is too wide
//       // L: Likelihood can treat empty bins correctly (if hist not weighted...)
//       if (0 == hist->Fit(&func, "Q0LR")) {
// 	if (hist->GetFunction(func.GetName())) { // Take care that it is later on drawn:
// 	  //  hist->GetFunction(func.GetName())->ResetBit(TF1::kNotDraw);
// 	}
// 	fitResult.first = func.GetParameter(1);
// 	fitResult.second = func.GetParameter(2);
//       }
//     }
//   } catch (cms::Exception const & e) {
//     edm::LogWarning("Alignment") << "@SUB=TrackerOfflineValidation::fitResiduals"
// 				 << "Caught this exception during ROOT fit: "
// 				 << e.what();
//   }
  
//   return fitResult;
// }

//##########################################
// Fitting Function
//##########################################
void TripleGausFitResiduals(TH1 *hist){
  
  float mean  = hist->GetMean();
  float sigma = hist->GetRMS();

  Double_t par[9];
  TF1 func1("gaus1", "gaus", mean - 0.5*sigma, mean + 0.5*sigma); 
  TF1 func2("gaus2", "gaus", mean - 1*sigma, mean + 1*sigma); 
  TF1 func3("gaus3", "gaus", mean - 2*sigma, mean + 2*sigma); 
  TF1 func("tmp", "gaus(0)+gaus(3)+gaus(6)", mean - 2*sigma, mean + 2*sigma); 
  hist->Fit(&func1,"QNR");
  hist->Fit(&func2,"QNR+");
  hist->Fit(&func3,"QNR+");

  func1.GetParameters(&par[0]);
  func2.GetParameters(&par[3]);
  func3.GetParameters(&par[6]);
  //  cout<<"partials fit done!"<<endl;
  
  if(hist->GetEntries()>20) {
    
    //cout<<"histo entries: "<<hist->GetEntries()<<endl; 

    func.SetParameters(par);
    if (0 == hist->Fit(&func,"QNR")) { // N: do not blow up file by storing fit!
      
      // cout<<"before extracting parameters"<<endl;
      
      mean  = func.GetParameter(1);
      sigma = func.GetParameter(2);
      
      //cout<<"first total fit done!"<<endl;
      
      // second fit: three sigma of first fit around mean of first fit
      func.SetRange(mean - 2*sigma, mean + 2*sigma);
      // I: integral gives more correct results if binning is too wide
      // L: Likelihood can treat empty bins correctly (if hist not weighted...)
      if (0 == hist->Fit(&func, "Q0LR")) {
	if (hist->GetFunction(func.GetName())) { // Take care that it is later on drawn:
	  hist->GetFunction(func.GetName())->ResetBit(TF1::kNotDraw);
	}
 
	//cout<<"fit done!"<<endl;
	
      }
    }
    
  } else {
    cout<<"Unable to perform double gaussian fit "<<endl;
    // func.SetParameters(0);
    hist->Fit(&func, "Q0LR");
  }
  
  return;


}

//*************************************************************
void fitResiduals(TH1 *hist)
//*************************************************************
{
  //float fitResult(9999);
  //if (hist->GetEntries() < 20) return ;
  
  float mean  = hist->GetMean();
  float sigma = hist->GetRMS();
  
  if(TMath::IsNaN(mean) || TMath::IsNaN(sigma)){  
    mean=0;
    sigma= - hist->GetXaxis()->GetBinLowEdge(1) + hist->GetXaxis()->GetBinLowEdge(hist->GetNbinsX()+1) ;
  }

  TF1 func("myfit", "gaus", mean - 1.*sigma, mean + 1.*sigma); 
  if (0 == hist->Fit(&func,"QNR")) { // N: do not blow up file by storing fit!
    mean  = func.GetParameter(1);
    sigma = func.GetParameter(2);
    // second fit: three sigma of first fit around mean of first fit
    func.SetRange(mean - 2.5*sigma, mean + 2.5*sigma);
      // I: integral gives more correct results if binning is too wide
      // L: Likelihood can treat empty bins correctly (if hist not weighted...)
    if (0 == hist->Fit(&func, "Q0LR")) {
      if (hist->GetFunction(func.GetName())) { // Take care that it is later on drawn:
	hist->GetFunction(func.GetName())->ResetBit(TF1::kNotDraw);
      }
    }
  }
}

void DoubleGausFitResiduals(TH1 *hist)
{
  //float fitResult(9999);
  // if (!hist || hist->GetEntries() < 20) return;
  
  float mean  = hist->GetMean();
  float sigma = hist->GetRMS();

  Double_t par[6];
  TF1 func1("gaus1", "gaus", mean - 0.25*sigma, mean + 0.25*sigma); 
  TF1 func2("gaus2", "gaus", mean - 3*sigma, mean + 3*sigma); 
  TF1 func("myfit", "gaus(0)+gaus(3)", mean - 2*sigma, mean + 2*sigma); 
  
  hist->Fit(&func1,"QNR");
  hist->Fit(&func2,"QNR+");
  func1.GetParameters(&par[0]);
  func2.GetParameters(&par[3]);
  //  cout<<"partials fit done!"<<endl;
  
  if(hist->GetEntries()>20) {
    
    //cout<<"histo entries: "<<hist->GetEntries()<<endl; 

    func.SetParameters(par);
    if (0 == hist->Fit(&func,"QNR")) { // N: do not blow up file by storing fit!
      
      // cout<<"before extracting parameters"<<endl;
      
      mean  = func.GetParameter(1);
      sigma = func.GetParameter(2);
      
      //cout<<"first total fit done!"<<endl;
      
      // second fit: three sigma of first fit around mean of first fit
      func.SetRange(mean - 3*sigma, mean + 3*sigma);
      // I: integral gives more correct results if binning is too wide
      // L: Likelihood can treat empty bins correctly (if hist not weighted...)
      if (0 == hist->Fit(&func, "Q0LR")) {
	if (hist->GetFunction(func.GetName())) { // Take care that it is later on drawn:
	  hist->GetFunction(func.GetName())->ResetBit(TF1::kNotDraw);
	}
 
	//cout<<"fit done!"<<endl;
	
      }
    }
    
  } else {
    cout<<"Unable to perform double gaussian fit "<<endl;
    // func.SetParameters(0);
    hist->Fit(&func, "Q0LR");
  }
  
  return;
}

void setTDRStyle() {
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  //tdrStyle->SetCanvasDefH(600); //Height of canvas
  //tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);     //Position on screen
  tdrStyle->SetCanvasDefY(0);

  // For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

  // For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

  // For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);
  
  tdrStyle->SetEndErrorSize(2);
  //  tdrStyle->SetErrorMarker(20);
  tdrStyle->SetErrorX(0.);
  // tdrStyle->SetMarkerStyle(20);

  //For the fit/function:
  //tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

  //For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

  // For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat("emr"); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Float_t x = 0);
  // tdrStyle->SetStatY(Float_t y = 0);
  
  // Margins:

  //tdrStyle->SetPadTopMargin(0.05);
  //tdrStyle->SetPadBottomMargin(0.10);
  //tdrStyle->SetPadLeftMargin(0.12);
  //tdrStyle->SetPadRightMargin(0.05);

  // For the Global title:
  
  tdrStyle->SetOptTitle(1);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);
  
  // For the axis titles:
  
  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(1.45);
  tdrStyle->SetTitleYOffset(1.25);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

  // For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

  // For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  // tdrStyle->SetNdivisions(505, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

  // Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

  // Postscript options:
  tdrStyle->SetPaperSize(20.,20.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->cd();

}

Double_t getMaximum(TObjArray *array){

  Double_t theMaximum = (static_cast<TH1*>(array->At(0)))->GetMaximum();
  for(Int_t i = 0; i< array->GetSize(); i++){
    if( (static_cast<TH1*>(array->At(i)))->GetMaximum() > theMaximum){
      theMaximum = (static_cast<TH1*>(array->At(i)))->GetMaximum();
      //cout<<"i= "<<i<<" theMaximum="<<theMaximum<<endl;
    }
  }
  return theMaximum;
}


//////////////////////////////////////////////////////////////////////////////////////
Double_t normGaus(Double_t *x, Double_t *par){

  double xx= x[0];
  
  double norm = par[0];
  double mean = par[1];
  double sigm = par[2];
  
  const double _invSq2Pi = 1.0 / sqrt( 2.0 * TMath::Pi());
  
  double res = norm * _invSq2Pi /sigm * TMath::Exp( -0.5 * (xx - mean) * (xx -mean) /sigm /sigm );
  
  return res;
}
