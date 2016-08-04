#include "TH1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TKey.h"
#include "TStyle.h"
#include "TLegend.h"
#include <iostream>

void makeNiceCanv(TCanvas *c);
void makeNicePlotStyleAndColor(TH1F *hist,int color);
void superImpose(){

  gStyle->SetOptTitle(1);
  gStyle->SetTitleFont(72);
  gStyle->SetTitleColor(4);
  gStyle->SetTitleTextColor(1);
  gStyle->SetTitleFillColor(10);

  TFile *f1 = TFile::Open("cALLRMSVsEta_baseline.root");
  TFile *f2 = TFile::Open("cALLRMSVsEta_new_CPE.root");
 
  TString legs[2] = {"baseline","new CPE"};

  TCanvas *cBPixXRMSVsEta = new TCanvas("cBPixXRMSVsEta","RMS of DMR vs #eta (BPix-x)",700,700);
  TCanvas *cFPixXRMSVsEta = new TCanvas("cFPixXRMSVsEta","RMS of DMR vs #eta (FPix-x)",700,700);

  TCanvas *cBPixYRMSVsEta = new TCanvas("cBPixYRMSVsEta","RMS of DMR vs #eta (BPix-y)",700,700);
  TCanvas *cFPixYRMSVsEta = new TCanvas("cFPixYRMSVsEta","RMS of DMR vs #eta (FPix-y)",700,700);

  TCanvas *cTIBRMSVsEta  = new TCanvas("cTIBRMSVsEta" ,"RMS of DMR vs #eta (TIB)",700,700);
  TCanvas *cTIDRMSVsEta  = new TCanvas("cTIDRMSVsEta" ,"RMS of DMR vs #eta (TID)",700,700);
  TCanvas *cTOBRMSVsEta  = new TCanvas("cTOBRMSVsEta" ,"RMS of DMR vs #eta (TOB)",700,700);
  TCanvas *cTECRMSVsEta  = new TCanvas("cTECRMSVsEta" ,"RMS of DMR vs #eta (TEC)",700,700);

  makeNiceCanv(cBPixXRMSVsEta);
  makeNiceCanv(cFPixXRMSVsEta);
  makeNiceCanv(cBPixYRMSVsEta);
  makeNiceCanv(cFPixYRMSVsEta);

  makeNiceCanv(cTIBRMSVsEta);
  makeNiceCanv(cTIDRMSVsEta);
  makeNiceCanv(cTOBRMSVsEta);
  makeNiceCanv(cTECRMSVsEta);

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
  
    TH1F* h1xBPix[2];
    TH1F* h1yBPix[2];
    TH1F* h1xFPix[2];
    TH1F* h1yFPix[2];
    TH1F* h1TIB[2];
    TH1F* h1TID[2];
    TH1F* h1TOB[2];
    TH1F* h1TEC[2];   
  
    // first file
    TObject *oo1;
    TIter next1(c1->GetListOfPrimitives());
    while ((oo1=next1())) {
      if(oo1->InheritsFrom("TH1")){
	std::cout<<"h1 name:"<<oo1->GetName()<<std::endl;
	TString oo1Name = oo1->GetName();
	if(oo1Name.Contains("XBpix")){
	  h1xBPix[0]=(TH1F*)oo1;
	} else if(oo1Name.Contains("YBpix")){
	  h1yBPix[0]=(TH1F*)oo1;
	} else if(oo1Name.Contains("XFpix")){
	  h1xFPix[0]=(TH1F*)oo1;
	} else if(oo1Name.Contains("YFpix")){
	  h1yFPix[0]=(TH1F*)oo1;
	} else if(oo1Name.Contains("TIB")){
	  h1TIB[0]=(TH1F*)oo1;
	} else if(oo1Name.Contains("TID")){
	  h1TID[0]=(TH1F*)oo1;
	} else if(oo1Name.Contains("TOB")){
	  h1TOB[0]=(TH1F*)oo1;
	} else if(oo1Name.Contains("TEC")){
	  h1TEC[0]=(TH1F*)oo1;
	}
      }
    }
    
    // second file
    TObject *oo2;
    TIter next2(c2->GetListOfPrimitives());
    while ((oo2=next2())) {
      if(oo2->InheritsFrom("TH1")){
	std::cout<<"h2 name:"<<oo2->GetName()<<std::endl;
	TString oo2Name = oo2->GetName();
	if(oo2Name.Contains("XBpix")){
	  h1xBPix[1]=(TH1F*)oo2;
	} else if(oo2Name.Contains("YBpix")){
	  h1yBPix[1]=(TH1F*)oo2;
	} else if(oo2Name.Contains("XFpix")){
	  h1xFPix[1]=(TH1F*)oo2;
	} else if(oo2Name.Contains("YFpix")){
	  h1yFPix[1]=(TH1F*)oo2;
	} else if(oo2Name.Contains("TIB")){
	  h1TIB[1]=(TH1F*)oo2;
	} else if(oo2Name.Contains("TID")){
	  h1TID[1]=(TH1F*)oo2;
	} else if(oo2Name.Contains("TOB")){
	  h1TOB[1]=(TH1F*)oo2;
	} else if(oo2Name.Contains("TEC")){
	  h1TEC[1]=(TH1F*)oo2;
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
    cBPixXRMSVsEta->cd(); 
    for(Int_t i =0;i<2;i++){
      //  std::cout<<"i:"<<i<<std::endl;
      makeNicePlotStyleAndColor(h1xBPix[i],i);
      //std::cout<<"i:"<<i<<std::endl;
      if(i==0) h1xBPix[i]->Draw();
      else h1xBPix[i]->Draw("same");
      leg->AddEntry(h1xBPix[i],legs[i]);
    }
    leg->Draw("same");
    cBPixXRMSVsEta->SaveAs("cBPixXRMSVsEta.pdf");
    
    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cFPixXRMSVsEta->cd();
    for(Int_t i =0;i<2;i++){
      makeNicePlotStyleAndColor(h1xFPix[i],i);
      if(i==0) h1xFPix[i]->Draw();
      else h1xFPix[i]->Draw("same");
    }
    leg->Draw("same");
    cFPixXRMSVsEta->SaveAs("cFPixXRMSVsEta.pdf");

    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cBPixYRMSVsEta->cd(); 
    for(Int_t i =0;i<2;i++){
      makeNicePlotStyleAndColor(h1yBPix[i],i);
      if(i==0) h1yBPix[i]->Draw();
      else h1yBPix[i]->Draw("same");
    }
    leg->Draw("same");
    cBPixYRMSVsEta->SaveAs("cBPixYRMSVsEta.pdf");

    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cFPixYRMSVsEta->cd();
    for(Int_t i =0;i<2;i++){
      makeNicePlotStyleAndColor(h1yFPix[i],i);
      if(i==0) h1yFPix[i]->Draw();
      else h1yFPix[i]->Draw("same");
    }
    leg->Draw("same");
    cFPixYRMSVsEta->SaveAs("cFPixYRMSVsEta.pdf");

    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cTIBRMSVsEta->cd(); 
    for(Int_t i =0;i<2;i++){
      makeNicePlotStyleAndColor(h1TIB[i],i);
      if(i==0) h1TIB[i]->Draw();
      else h1TIB[i]->Draw("same");
    }
    leg->Draw("same");
    cTIBRMSVsEta->SaveAs("cTIBRMSVsEta.pdf");
    
    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cTIDRMSVsEta->cd(); 
    for(Int_t i =0;i<2;i++){
      makeNicePlotStyleAndColor(h1TID[i],i);
      if(i==0) h1TID[i]->Draw();
      else h1TID[i]->Draw("same");
    }
    leg->Draw("same");
    cTIDRMSVsEta->SaveAs("cTIDRMSVsEta.pdf");

    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cTOBRMSVsEta->cd();  
    for(Int_t i =0;i<2;i++){
      makeNicePlotStyleAndColor(h1TOB[i],i);
      if(i==0) h1TOB[i]->Draw();
      else h1TOB[i]->Draw("same");
    }
    leg->Draw("same");
    cTOBRMSVsEta->SaveAs("cTOBRMSVsEta.pdf");

    //%%%%%%%%%%%%%%%%%%%%%%%%%%
    cTECRMSVsEta->cd(); 
    for(Int_t i =0;i<2;i++){
      makeNicePlotStyleAndColor(h1TEC[i],i);
      if(i==0) h1TEC[i]->Draw();
      else h1TEC[i]->Draw("same");
    }
    leg->Draw("same");
    cTECRMSVsEta->SaveAs("cTECRMSVsEta.pdf");
  }
}

void makeNicePlotStyleAndColor(TH1F *hist,int color){

  //Int_t styles[4] = {kFullCircle,kFullSquare,kFullTriangleUp,kFullTriangleDown};
  Int_t styles[4] = {kFullCircle,kFullSquare,kFullCircle,kFullSquare};
  Int_t colors[4] = {kRed,kBlue,kMagenta,kMagenta-2};

  hist->SetStats(false);
  hist->GetYaxis()->SetRangeUser(0.1,2.5);
  hist->GetXaxis()->SetNdivisions(505);
  hist->SetLineWidth(2);
  hist->SetLineColor(colors[color]);
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

