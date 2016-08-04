#include "TH1.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TKey.h"
#include "TStyle.h"
#include "TLegend.h"
#include <iostream>

void makeNiceCanv(TCanvas *c);
void makeNicePlotStyleAndColor(TProfile *hist,int color);
void superImpose2(){

  gStyle->SetOptTitle(1);
  gStyle->SetTitleFont(72);
  gStyle->SetTitleColor(4);
  gStyle->SetTitleTextColor(1);
  gStyle->SetTitleFillColor(10);

  TFile *f1 = TFile::Open("cALLRMSNormVsEta_baseline.root");
  TFile *f2 = TFile::Open("cALLRMSNormVsEta_new_CPE.root");
 
  TString legs[2] = {"baseline","new CPE"};

  TCanvas *cBPixXRMSNormVsEta = new TCanvas("cBPixXRMSNormVsEta","RMS of normalized residuals vs #eta (BPix-x)",700,700);
  TCanvas *cFPixXRMSNormVsEta = new TCanvas("cFPixXRMSNormVsEta","RMS of normalized residuals vs #eta (FPix-x)",700,700);

  TCanvas *cBPixYRMSNormVsEta = new TCanvas("cBPixYRMSNormVsEta","RMS of normalized residuals vs #eta (BPix-y)",700,700);
  TCanvas *cFPixYRMSNormVsEta = new TCanvas("cFPixYRMSNormVsEta","RMS of normalized residuals vs #eta (FPix-y)",700,700);

  TCanvas *cTIBRMSNormVsEta = new TCanvas("cTIBRMSNormVsEta" ,"RMS of normalized residuals vs #eta (TIB)",700,700);
  TCanvas *cTIDRMSNormVsEta  = new TCanvas("cTIDRMSNormVsEta" ,"RMS of normalized residuals vs #eta (TID)",700,700);
  TCanvas *cTOBRMSNormVsEta  = new TCanvas("cTOBRMSNormVsEta" ,"RMS of normalized residuals vs #eta (TOB)",700,700);
  TCanvas *cTECRMSNormVsEta  = new TCanvas("cTECRMSNormVsEta" ,"RMS of normalized residuals vs #eta (TEC)",700,700);

  makeNiceCanv(cBPixXRMSNormVsEta);
  makeNiceCanv(cFPixXRMSNormVsEta);
  makeNiceCanv(cBPixYRMSNormVsEta);
  makeNiceCanv(cFPixYRMSNormVsEta);

  makeNiceCanv(cTIBRMSNormVsEta);
  makeNiceCanv(cTIDRMSNormVsEta);
  makeNiceCanv(cTOBRMSNormVsEta);
  makeNiceCanv(cTECRMSNormVsEta);

  f1->cd();

  TDirectory *currentDir = gDirectory;
  TKey *key;
  TIter nextkey(currentDir->GetListOfKeys());
  
  TObject *obj;

  while ((key = (TKey*)nextkey())) {
    obj = key->ReadObj();
    std::cout<<"object name is:"<<TString((obj->GetName()))<<std::endl;
    TString objName = TString((obj->GetName()));
    
    TCanvas *c1 =(TCanvas*)f1->Get(objName);
    TCanvas *c2 =(TCanvas*)f2->Get(objName);

    TProfile* h1xBPix[2];
    TProfile* h1yBPix[2];
    TProfile* h1xFPix[2];
    TProfile* h1yFPix[2];
    TProfile* h1TIB[2];
    TProfile* h1TID[2];
    TProfile* h1TOB[2];
    TProfile* h1TEC[2];   
  
    // first file
    TObject *oo1;
    TIter next1(c1->GetListOfPrimitives());
    while ((oo1=next1())) {
      if(oo1->InheritsFrom("TProfile")){
	std::cout<<"h1 name:"<<oo1->GetName()<<std::endl;
	TString oo1Name = oo1->GetName();
	if(oo1Name.Contains("XNormResBPix")){
	  h1xBPix[0]=(TProfile*)oo1;
	} else if(oo1Name.Contains("YNormResBPix")){
	  h1yBPix[0]=(TProfile*)oo1;
	} else if(oo1Name.Contains("XNormResFPix")){
	  h1xFPix[0]=(TProfile*)oo1;
	} else if(oo1Name.Contains("YNormResFPix")){
	  h1yFPix[0]=(TProfile*)oo1;
	} else if(oo1Name.Contains("TIB")){
	  h1TIB[0]=(TProfile*)oo1;
	} else if(oo1Name.Contains("TID")){
	  h1TID[0]=(TProfile*)oo1;
	} else if(oo1Name.Contains("TOB")){
	  h1TOB[0]=(TProfile*)oo1;
	} else if(oo1Name.Contains("TEC")){
	  h1TEC[0]=(TProfile*)oo1;
	}
      }
    }
    
    // second file
    TObject *oo2;
    TIter next2(c2->GetListOfPrimitives());
    while ((oo2=next2())) {
      if(oo2->InheritsFrom("TProfile")){
	std::cout<<"h2 name:"<<oo2->GetName()<<std::endl;
	TString oo2Name = oo2->GetName();
	if(oo2Name.Contains("XNormResBPix")){
	  h1xBPix[1]=(TProfile*)oo2;
	} else if(oo2Name.Contains("YNormResBPix")){
	  h1yBPix[1]=(TProfile*)oo2;
	} else if(oo2Name.Contains("XNormResFPix")){
	  h1xFPix[1]=(TProfile*)oo2;
	} else if(oo2Name.Contains("YNormResFPix")){
	  h1yFPix[1]=(TProfile*)oo2;
	} else if(oo2Name.Contains("TIB")){
	  h1TIB[1]=(TProfile*)oo2;
	} else if(oo2Name.Contains("TID")){
	  h1TID[1]=(TProfile*)oo2;
	} else if(oo2Name.Contains("TOB")){
	  h1TOB[1]=(TProfile*)oo2;
	} else if(oo2Name.Contains("TEC")){
	  h1TEC[1]=(TProfile*)oo2;
	}
      }
    }

    TLegend *leg = new TLegend(0.14,0.7,0.54,0.9);
    //leg->SetNColumns(2);
    leg->SetLineColor(10);
    leg->SetFillColor(10);
    leg->SetTextFont(42);
    leg->SetTextSize(0.04);
    
    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cBPixXRMSNormVsEta->cd(); 
    for(Int_t i =0;i<2;i++){
      std::cout<<"i:"<<i<<std::endl;
      makeNicePlotStyleAndColor(h1xBPix[i],i);
      std::cout<<"i:"<<i<<std::endl;
      if(i==0) h1xBPix[i]->Draw("C");
      else h1xBPix[i]->Draw("Csame");
      h1xBPix[i]->Draw("E2same");
      leg->AddEntry(h1xBPix[i],legs[i],"LP");
    }
    leg->Draw("same");
    cBPixXRMSNormVsEta->SaveAs("cBPixXRMSNormVsEta.pdf");
    
    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cFPixXRMSNormVsEta->cd();
    for(Int_t i =0;i<2;i++){
      makeNicePlotStyleAndColor(h1xFPix[i],i);
      if(i==0) h1xFPix[i]->Draw("C");
      else h1xFPix[i]->Draw("Csame");
      h1xFPix[i]->Draw("E2same");
    }
    leg->Draw("same");
    cFPixXRMSNormVsEta->SaveAs("cFPixXRMSNormVsEta.pdf");

    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cBPixYRMSNormVsEta->cd(); 
    for(Int_t i =0;i<2;i++){
      makeNicePlotStyleAndColor(h1yBPix[i],i);
      if(i==0) h1yBPix[i]->Draw("C");
      else h1yBPix[i]->Draw("Csame");
      h1yBPix[i]->Draw("E2same");
    }
    leg->Draw("same");
    cBPixYRMSNormVsEta->SaveAs("cBPixYRMSNormVsEta.pdf");

    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cFPixYRMSNormVsEta->cd();
    for(Int_t i =0;i<2;i++){
      makeNicePlotStyleAndColor(h1yFPix[i],i);
      if(i==0) h1yFPix[i]->Draw("C");
      else h1yFPix[i]->Draw("Csame");
      h1yFPix[i]->Draw("E2same");
    }
    leg->Draw("same");
    cFPixYRMSNormVsEta->SaveAs("cFPixYRMSNormVsEta.pdf");

    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cTIBRMSNormVsEta->cd(); 
    for(Int_t i =0;i<2;i++){
      makeNicePlotStyleAndColor(h1TIB[i],i);
      if(i==0) h1TIB[i]->Draw("C");
      else h1TIB[i]->Draw("Csame");
      h1TIB[i]->Draw("E2same");
    }
    leg->Draw("same");
    cTIBRMSNormVsEta->SaveAs("cTIBRMSNormVsEta.pdf");
    
    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cTIDRMSNormVsEta->cd(); 
    for(Int_t i =0;i<2;i++){
      makeNicePlotStyleAndColor(h1TID[i],i);
      if(i==0) h1TID[i]->Draw("C");
      else h1TID[i]->Draw("Csame");
      h1TID[i]->Draw("E2same");
    }
    leg->Draw("same");
    cTIDRMSNormVsEta->SaveAs("cTIDRMSNormVsEta.pdf");

    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cTOBRMSNormVsEta->cd();  
    for(Int_t i =0;i<2;i++){
      makeNicePlotStyleAndColor(h1TOB[i],i);
      if(i==0) h1TOB[i]->Draw("C");
      else h1TOB[i]->Draw("Csame");
      h1TOB[i]->Draw("E2same");
    }
    leg->Draw("same");
    cTOBRMSNormVsEta->SaveAs("cTOBRMSNormVsEta.pdf");

    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cTECRMSNormVsEta->cd(); 
    for(Int_t i =0;i<2;i++){
      makeNicePlotStyleAndColor(h1TEC[i],i);
      if(i==0) h1TEC[i]->Draw("C");
      else h1TEC[i]->Draw("Csame");
      h1TEC[i]->Draw("E2same");
    }
    leg->Draw("same");
    cTECRMSNormVsEta->SaveAs("cTECRMSNormVsEta.pdf");
  }
}

void makeNicePlotStyleAndColor(TProfile *hist,int color){

  //Int_t styles[4] = {kFullCircle,kFullSquare,kFullTriangleUp,kFullTriangleDown};
  Int_t styles[4] = {kFullCircle,kFullSquare,kFullCircle,kFullSquare};
  Int_t colors[4] = {kRed,kBlue,kMagenta,kMagenta-2};

  hist->SetStats(false);
  hist->GetYaxis()->SetRangeUser(0.,1.7);
  hist->GetXaxis()->SetNdivisions(505);
  hist->SetLineWidth(2);
  hist->SetLineColor(colors[color]);
  hist->SetFillStyle(3001);
  hist->SetFillColor(colors[color]-4);
  hist->SetMarkerColor(colors[color]);
  hist->SetMarkerStyle(styles[color]);
  hist->GetXaxis()->CenterTitle(true);
  hist->GetYaxis()->CenterTitle(true);
  hist->GetXaxis()->SetTitleFont(42); 
  hist->GetYaxis()->SetTitleFont(42);  
  hist->GetXaxis()->SetTitleSize(0.045);
  hist->GetYaxis()->SetTitleSize(0.045);
  hist->GetXaxis()->SetTitleOffset(1.);
  hist->GetYaxis()->SetTitleOffset(1.1);
  hist->GetXaxis()->SetLabelFont(42);
  hist->GetYaxis()->SetLabelFont(42);
  hist->GetYaxis()->SetLabelSize(.045);
  hist->GetXaxis()->SetLabelSize(.045);
  hist->SetMarkerSize(1.8);
}

void makeNiceCanv(TCanvas *c){
  
  //c->SetGridx();
  c->SetGridy();
  c->cd()->SetBottomMargin(0.11);
  c->cd()->SetLeftMargin(0.11);
  c->cd()->SetRightMargin(0.07);
  c->cd()->SetTopMargin(0.08);  

}

